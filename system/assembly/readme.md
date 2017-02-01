# start
  [Guide to x86 assembly Language](http://www.cs.virginia.edu/~evans/cs216/guides/x86.html)
  http://asm.sourceforge.net/resources.html
  http://mikeos.sourceforge.net/
  http://www.ctyme.com/intr/cat.htm
  http://beefchunk.com/documentation/sys-programming/bootstraps/PC_Bootstrap_Loader_Programming_Tutorial.html

# linux
  nasm -f elf hello.asm
  ld -m efl_i386 -s hello.o -o hello

# basics
  * push 
    1. decrements ESP by 4
    2. places its operand into the contents of the 32-bit location at address [ESP]

  * call, ret — Subroutine call and return 

  * Calling Convention

    a protocol about how to call and return from routines

    * The C calling convention: based on the push, pop, call, and ret instructions
        * Subroutine parameters are passed on the stack
        * registers saved on stack, local variables are placed in memory on the stack
    
    * two sets of rules
      * the caller of the subroutine
      * the callee 

# asm 
  
  gcc.pdf 
  ibm https://www.ibm.com/developerworks/library/l-ia/
    ```
    asm [volatile] ( AssemblerTemplate
                    : OutputOperands
                    [ : InputOperands
                    [ : Clobbers ] ])

    asm [volatile] goto ( AssemblerTemplate
                        :
                        : InputOperands
                        : Clobbers
                        : GotoLabels)
    extended asm statements must be inside a function, Only basic asm may be outside functions
    The asm keyword is a GNU extension. When writing code that can be compiled with ‘-ansi’ and the various ‘-std’ options, use __asm__ instead of asm

    Simple Constraints:
    * ‘g’ Any register, memory or immediate integer operand is allowed, except for registers that are not general registers.
    * ‘r’ A register operand is allowed provided that it is in a general register.
        a	%eax
        b 	%ebx
        c 	%ecx
        d 	%edx
        S	%esi
        D	%edi
    * ‘m’ A memory operand is allowed, with any kind of address that the machine supports in general.
    * ‘o’ A memory operand is allowed, but only if the address is offsettable. 
    * ‘p’ An operand that is a valid memory address is allowed

    Constraint Modifier Characters:
        When the compiler fixes up the operands to satisfy the constraints, it needs to
        know which operands are read by the instruction and which are written by it.
        1.‘=’ identifies an operand which is only written; 
        2. ‘+’ identifies an operand that is both read and written; 
        3. all other operands are assumed to only be read.
    * '=' Means that this operand is written to by this instruction: the previous value is discarded and replaced by new data.
    * '+' Means that this operand is both read and written by the instruction.
    * '&' Means (in a particular alternative) that this operand is an earlyclobber operand, which is written before the instruction 
        is finished using the input operands.Therefore, this operand may not lie in a register that is read by the instruction or 
        as part of any memory address.
    * '%' Declares the instruction to be commutative for this operand and the following operand. This means that the compiler
        may interchange the two operands if that is the cheapest way to make all operands fit the constraints. ‘%’ applies to
        all alternatives and must appear as the first character in the constraint. Only read-only operands can use ‘%’.

* exceptions and interrupts 
  The difference between interrupts and exceptions is that interrupts are used to
  handle asynchronous events external to the processor, but exceptions handle
  conditions detected by the processor itself in the course of executing
  instructions.
  1. interrupts
    * Maskable interrupts, which are signalled via the INTR pin.
    * Nonmaskable interrupts, which are signalled via the NMI (Non-Maskable Interrupt) pin.
  2. exceptions
    * Processor detected. These are further classified as 
      1. faults: Faults are either detected before the instruction begins to execute, or during execution of the instruction.
                  If detected during the instruction, the fault is reported with the machine restored to a state that permits the
                  instruction to be restarted.
      2. traps: A trap is an exception that is reported at the instruction boundary immediately after the instruction 
                in which the exception was detected. 
      3. aborts: An abort is an exception that permits neither precise location of the instruction causing the exception nor restart of the program
                  that caused the exception. Aborts are used to report severe errors, such as hardware errors and inconsistent or 
                  illegal values in system tables.
    * Programmed. The instructions INTO, INT 3, INT n, and BOUND can trigger exceptions.
      These instructions are often called "software interrupts", but the processor handles them as exceptions.
      
  * compile intel architecture  using gcc
    [gas vs nasm] (https://web.archive.org/web/20090303224539/http://ibm.com/developerworks/linux/library/l-gas-nasm.html)
    [at&t intel](http://www.lxhp.in-berlin.de/lhpas86.html)
    [GAS](http://asm.sourceforge.net/howto/gas.html)
    * as now supports assembly
      * using Intel assembler syntax __.intel_syntax__ selects Intel mode, __.att_syntax__ switches back to the usual AT&T mode 
        for compatibility with the output of gcc. 
      * prefix, or noprefix specifying whether registers require a % prefix.

   * [AT&T Intel](http://www.sourceware.org/binutils/docs-2.12/as.info/i386-Syntax.html)
      * immediate: AT&T immediate operands are preceded by $; Intel immediate operands are undelimited
      * register:  AT&T register operands are preceded by %; Intel register operands are undelimited. 
      * jump/call: AT&T absolute (as opposed to PC relative) jump/call operands are prefixed by *; they are undelimited in Intel syntax. 
      * operands:  AT&T and Intel syntax use the opposite order for source and destination operands. Intel add eax, 4 is addl $4, %eax. 
                   The source, dest convention is maintained for compatibility with previous Unix assemblers.
      * memory size: 
        In AT&T syntax the size of memory operands is determined from the last character of the instruction mnemonic. 
        Mnemonic suffixes of b, w, l and q specify byte (8-bit), word (16-bit), long (32-bit) and quadruple word (64-bit) memory references. 

        Intel syntax accomplishes this by prefixing memory operands (not the instruction mnemonics) with byte ptr, word ptr, dword ptr and qword ptr. 
         Intel: mov al, byte ptr foo
         AT&T:  movb foo, %al
      * immediate long jump:
        AT&T: lcall/ljmp $CS:$DX   lret $stack-adjust
        INTEL: call/jmp far cs:dx  ret far stack-adjust
      * sections:The AT&T assembler does not provide support for multiple section programs. Unix style systems expect all programs to be single sections. 
        

    1. add .intel_syntax noprefix
    ```c
    /* intel_syntax.c
    #include <stdio.h>
    #include <stdlib.h>

    int get_random(void)
    {
        __asm__(".intel_syntax noprefix \n\tmov eax, 42");
    }

    int main(void)
    {
        printf("number is %d\n", get_random());
        exit(0);
    }
    ```
    2. compile use inter
      ```
      gcc -nasm=intel intel_syntax.c

* nasm
  * macro
    * normal define
       %define are case sensitive
       %idefine instead of %define (the ‘i’ stands for ‘insensitive’) 
       you can define all the case variants of a macro at once
      %define THIS_VERY_LONG_MACRO_NAME_IS_DEFINED_TO \
          THIS_VALUE
    * Resolving %define: %xdefine
      ```asm
      %xdefine isTrue 1
      %xdefine isFalse isTrue
      %xdefine isTrue 0
      val1: db isFalse          # 1
      %xdefine isTrue 1
      val2: db isFalse          # 1
      ```
    
    * Macro Indirection: %[...]
      ```asm
      [bits 16]
      mov ax,Foo%[__BITS__] ; # mov ax, Foo16

      %xdefine Bar Quux     ; Expands due to %xdefine
      %define Bar %[Quux]   ; Expands due to %[...]
      ```

    * Concatenating Single Line Macro Tokens: %+
      ```asm
      %define BDASTART 400h ; Start of BIOS data area
      struc tBIOSDA ; its structure
      .COM1addr RESW 1
      .COM2addr RESW 1
      ; ..and so on
      endstruc

      %define BDA(x) BDASTART + tBIOSDA. %+ x

      mov ax,BDA(COM1addr)    ; mov ax,BDASTART + tBIOSDA.COM1addr
      mov bx,BDA(COM2addr)    ; mov bx,BDASTART + tBIOSDA.COM2addr
      ```
    * The Macro Name Itself: %? and %??
      * %? refers to the macro name as invoked.
      * %?? refers to the macro name as declared.
      ```asm
      %idefine Foo mov %?,%??
      foo      ; mov foo,Foo
      FOO      ; mov FOO,Foo
      

      %idefine keyword $%?
      can be used to make a keyword "disappear", for example in case a new instruction has been used as a label in
      older code. For example:
         %idefine pause $%?
      ```
    * Undefining Single−Line Macros: %undef

    * Preprocessor Variables: %assign
      %assign i i+1

    * Defining Strings: %defstr
      ```
      %defstr test TEST
      %define test ’TEST’
      ```
    * Defining Tokens: %deftok
      ```
      %deftok test ’TEST’
      %define test TEST
      ```
      
