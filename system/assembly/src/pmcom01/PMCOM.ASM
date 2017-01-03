; pmcom.asm   .COM program to switch to raw 32-bit pmode
; Version 1.0 March 5, 1998
; Sample code
; by John S. Fine  johnfine@erols.com
; I do not place any restrictions on your use of this source code
; I do not provide any warranty of the correctness of this source code
;_____________________________________________________________________________
;
; This program should be assembled into a .COM file by NASM, without using any
; linker:
;
; NASM -o PMCOM.COM PMCOM.ASM
;
; I don't actually recommend that you build raw protected mode programs this
; way.  I recommend that you use NASM to generate .OBJ files and djgpp to
; generate COFF files and link them together with my linker JLOC.
;
; I built this example, which does not use JLOC, because of several questions
; that have been asked to me directly or through comp.lang.asm.x86 or through
; the pmode-l@fys.ruu.nl mailing list.  This example demonstrates the answers to
; those questions.
;
; It is a .COM file that should be started in real mode (no EMM386 or other
; memory manager).  It will switch to 32-bit pmode then use an IDT entry, then
; a TSS, then display a message and hang.
;
; Some of the questions whose answers it demonstrates are:
;______________________________________
;
; How do you work around the NASM problem that NASM thinks offsets require link
; time relocation even when there is no linking required?
;
; For code, data and bss, I define the symbols fixC, fixD and fixB, as the
; amounts by which those segments will be relocated by the "linker".  In fact
; there will be no linker nor relocation, so all three values will be zero;
; However, they are strangely computed zeroes that can be used to fix offsets
; that NASM must believe are not relocatable.
;______________________________________
;
; How do you may descriptors readable in the source code of the GDT, IDT and
; LDT and cut down on the large number of errors that occur when building each
; descriptor by hand?
;
; You use my GDTNASM.INC file to define symbols and a macro that make building
; descriptors easy.  (Actually you should use my GDT.INC file, which does the
; same thing better;  But GDT.INC cannot be used without JLOC).
;______________________________________
;
; How do you set up an IDT?
;
; See below.
;______________________________________
;
; How do you set up a TSS?  And what are the minimum contents required to use
; a TSS?
;
; See below.
;______________________________________
;
; How do you use .data and .bss in NASM without a linker to rearrange things?
;
; You just do.  NASM sorts it all out for you.
;_____________________________________________________________________________


; First I define a few basic parameters.  Be sure to change the DISP_MEM
; value if it doesn't match your system.
;_____________________________________________________________________________

STACK_SIZE  equ	4096
DISP_MEM    equ 0xB8000

; Now the first step of dealing with the relocated offsets problem.  We tell
; NASM that this .COM file starts at offset 0x100 and the code is relocated
; by the difference between where it starts and 0x100 (a strangely computed
; zero).
;_____________________________________________________________________________

segment .text
org 0x100
fixC equ $-0x100

; To really prove that NASM sorts out the .data and .bss segments, I am going to
; put some data here before the first instruction in the source code.  In the
; COM file, NASM will have moved this data after all the code.
;
; Using segments lets me put the data in the source file close to the code that
; uses it without coding JMP instructions to get around it.
;_____________________________________________________________________________

segment .data

; Now I define the GDT.  I use gdtnasm.inc to make it easy.  I use the,
; otherwise unused, first 8 bytes of the gdt to hold the descriptor-like thing
; used to load the GDT register.
;
; Some GDT entries need to be patched with the run-time location of the COM
; file.  Some don't.  To make that easy, I group all the ones that need to be
; patched before all the ones that don't.
;_____________________________________________________________________________

%include "gdtnasm.inc"

gdt	dw	gdt_limit
	dd	gdt
	dw	0

code32	desc	0, codeLEN-1, D_CODE + D_BIG
data32	desc	0, stack_top, D_DATA + D_BIG + D_WRITE
tss0	desc	tss0_begin-fixB, tss_size, D_TSS
tss1	desc	tss1_begin-fixD, tss_size, D_TSS

gdt_patches equ ($-gdt) / 8   ;All GDT entries before this line must be patched

flat32	desc	0, 0xFFFFF,   D_DATA + D_BIG + D_BIG_LIM + D_WRITE

gdt_limit equ $-gdt-1

segment .text
begin:
	cli

; Now I do the actual patching.  Pretty obvious, I hope.
;_____________________________________________________________________________

	xor	eax, eax
	mov	ax, cs
	shl	eax, 4
	mov	bx, gdt+2
	mov	cx, gdt_patches
.loop:	add	[bx], eax		;Patch a GDT entry
	add	bx, 8
	loop	.loop
	lgdt	[gdt]			;Now load gdt register

; Now I load the idt register.  That needs a little descriptor-like thing as an
; operand for lidt.  We don't get to bury it in the IDT itself the way we did
; with the GDT.  Like the GDT, it needs to be patched.  Since the code32 entry
; in the GDT was patched, none of the entries inside the IDT need to be patched.
; I hate having code32 at a different base than flat32, but if you don't, you
; either need to move everything after loading as a COM, or patch a lot more
; things.  Usually I don't load as a COM and I use JLOC, so these problems
; don't occur.
;_____________________________________________________________________________

segment .data
idt_ptr	dw idt_limit
	dd idt
segment .text
	add	[idt_ptr+2], eax	;Patch the pointer to the IDT
	lidt	[idt_ptr]		;Load the IDT register

; Now we switch to protected mode.
;_____________________________________________________________________________

	mov	eax, cr0
	inc	ax
	mov	cr0, eax

; Now we JMP to the 32-bit code.  Notice how much easier this is in NASM than in
; other assemblers.  We don't need to kludge the JMP instruction, we just do it.
; We also switch the assembler from 16 bit defaults to 32 bit defaults without
; the bother that other assemblers might require.
;_____________________________________________________________________________

	jmp	code32-gdt : start32
bits 32
start32:

; Once you are in protected mode, it is usually a good idea to put valid
; selectors in ds and es.  In this example I don't actually use them, but if you
; copy some of this code for real projects, you probably need this step.
;_____________________________________________________________________________

	mov	ax, flat32-gdt
	mov	ds, ax
	mov	es, ax

; The stack is inside the data32 segment.  We need a valid stack before we can
; use an interrupt.
;_____________________________________________________________________________

	mov	ax, data32-gdt
	mov	ss, ax
	mov	esp, stack_top

; Now I have the IDT and the interrupt instruction.  I threw in a halt which
; is never reached just to prove that the int did something.
; I show just one interrupt descriptor, after that they are all pretty much
; the same thing.
; Use D_INT to make sure interrupts are disabled on entry to the service
; routine.  Use D_TRAP to leave the interrupt flag unchanged on entry.  That is
; the only difference between them.  In this example it doesn't matter.
; The alignment is not really needed, but it makes interrupts work faster and it
; makes the IDT a lot easier to look at in a debugger or a hex dumper (not that
; I ever put bugs in).
;_____________________________________________________________________________

segment .data
	align 8
idt:
	desc	service_0-fixC, code32-gdt, D_INT
idt_limit equ $-idt-1
segment .text
	int	0
	halt
service_0:

; Now I show the use of a minimal TSS.  When JMPing to a TSS, the CPU must store
; the old context somewhere, so you must have a TSS before you JMP to the first
; one (or the CPU may store the old context somewhere you don't like).  This is
; the reason for the ltr instruction.  The initial TSS is written before it is
; read so we just allocate it in .bss (uninitialized).
;
; I wanted to see the minimum fields that really matter when JMPing to a TSS.
; It seems to be just the obvious ones:  cs:eip and ss:esp.  The rest of tss1
; is zero filled by istruc.  Note that ss:esp is used and NOT ss0:esp0, since we
; are not doing a ring transition.
;_____________________________________________________________________________

%include "tss.inc"
segment .bss
tss0_begin	resb	tss_size
segment .data
tss1_begin:
	istruc tss
	at tss.eip, dd task_entry
	at tss.esp, dd stack_top
	at tss.cs,  dw code32-gdt
	at tss.ss,  dw data32-gdt
	iend

segment	.text
	mov	ax, tss0-gdt
	ltr	ax
	jmp	tss1-gdt : 0

task_entry:

; Since I put minimal content in the TSS, I need to set up es before the stosw.
; Since data32 and flat32 are different, I am trying to reduce confusion by
; using ss for data32 and ds,es for flat32.  It is still confusing.  Don't do
; it this way in a real project:  Load, move or map to a fixed linear address
; and use JLOC to make it all work.
;_____________________________________________________________________________

	mov	ax, flat32-gdt
	mov	es, ax

; Now I just display something and hang to prove it all worked.
;_____________________________________________________________________________

segment .data
message db 'We got here! ',0
segment .text
	mov	esi, message
	mov	edi, DISP_MEM
	mov	ah, 7		;Attribute
	ss lodsb
.loop:	stosw
	ss lodsb
	test	al, al
	jnz	.loop

	jmp	$

; Now I compute the rest of those strange zeroes needed to deal with that NASM
; problem.
;
; This code must come last.  It include the stack allocation.  Everything else
; in each segment should preceed it.
;_____________________________________________________________________________

segment	.text
	align	16
codeLEN equ $-fixC	;Length of the .text segment

segment .data
	align	16
fixD equ $$-codeLEN
comLEN equ $-fixD	;Length of the com file

segment .bss
	resb	STACK_SIZE
	alignb	16
fixB equ $$-comLEN
stack_top equ $-fixB	;Length of entire run-time image
