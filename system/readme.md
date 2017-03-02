__os development__
# introduction
  This is a record for my own os develop, I put all the knowledge referring to os in it
  - good website
    http://web.archive.org/web/20021207220335/http://www.nondot.org/sabre/os/articles
    http://www.osdever.net/tutorials/
  
  - books
    intel docs
    assmebly

# plan
  This tutorial was created in an attempt to show you, the reader, how to set up the basics for a kernel. This involves:
  1) Setting up your development environment
  2) The basics: Setting the stage for GRUB
  3) Linking in other files and calling main()
  4) Printing to the screen
  5) Setting up a custom Global Descriptor Table (GDT)
  6) Setting up a custom Interrupt Descriptor Table (IDT)
  7) Setting up Interrupt Service Routines (ISRs) to handle your Interrupts and IRQs
  8) Remapping the Programmable Interrupt Controllers (PICs) to new IDT entries
  9) Installing and servicing IRQs
  10) Managing the Programmable Interval Timer / System Clock (PIT)
  11) Managing Keyboard IRQs and Keyboard Data
  12) ...and the rest is up to you!

# details
  * protect mode
      So immediately after instructing the CPU to switch mode, we can issue a far jump, which will force the
      CPU to flush the pipeline (i.e. complete all of instructions currently in different stages of the pipeline).
  
  * call c function

    compiled the C code into a raw machine code file
    ```
    -ffreestanding :implies -fno-builtin
    -fhosted   Assert that compilation targets a hosted environment.  This implies -fbuiltin
    gcc -ffreestanding -m32 c basic.c -o basic.o

    ld -o basic.bin -Ttext 0x0 --oformat binary basic.o 
    # disassemble to 32-bits assembly
    ndisasm -b 32 basic.bin > basic.dis
    ```
  
  * read disk
    https://en.wikipedia.org/wiki/INT_13H#INT_13h_AH.3D02h:_Read_Sectors_From_Driv
    * kernel entry
        gcc -ffreestanding -m32 -c kernel.c -o kernel.o
        nasm -f elf kernel_entry.s -o kernel_entry.o
        ld -Ttext 0x1000 --oformat binary kernel_entry.o kernel.o -o kernel.bin -m elf_i386

    * CHS 24-bit
      * 10 bits for the cylinder number, or a total of 1,024 cylinders.
      * 8 bits for the head number, or a total of 256 heads.
      * 6 bits for the sector number, or a total of 63 sectors

    * screen 
      framebuffer at address 0xB8000 is just an array of 16-bit words, each 16-bit value representing the display of one character.
      (80 * y + x) * 2

      15-12 11-8  7-0
      BG    FG   CHAR
      0:black,1:blue, 2:green, 3:cyan, 4:red, 5:magenta, 6:brown, 7:light grey, 8:dark grey,
      9:light blue, 10:light green, 11:light cyan, 12:light red, 13:light magneta, 14: light brown, 15: white. 

      The VGA controller also has some ports on the main I/O bus:
        * control register at 0x3D4
        * data    register at 0x3D5
        rdtsc : read timestamp conter

      * screen print [vga](http://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/home.htm)
    
      * vga
        In real mode offsets are limited to 64K, because of the 16-bit nature of the 8086. 
        In real mode, the segment address is shifted left four bits and added to the offset, allowing for a 20 bit address (20 bits = 1 MB); 
        in protected mode segments are offsets into a table in memory which tells where the segment is located. 
        ```
        lspci | grep -i vga
          00:0f.0 VGA compatible controller: VMware SVGA II Adaptertab
        lspci -v  -s 00:0f.0
          00:0f.0 VGA compatible controller: VMware SVGA II Adapter (prog-if 00 [VGA controller])
          Subsystem: VMware SVGA II Adapter
          Flags: bus master, medium devsel, latency 64, IRQ 16
          I/O ports at 1070 [size=16]
          Memory at e8000000 (32-bit, prefetchable) [size=128M]
          Memory at fe000000 (32-bit, non-prefetchable) [size=8M]
          [virtual] Expansion ROM at c0000000 [disabled] [size=32K]
          Capabilities: [40] Vendor Specific Information: Len=00 <?>
          Kernel driver in use: vmwgfx
        ```

      * print
          error forget save registers in print functions
          the real error code is 0x0c : unsupported track or invalid media
          always focus on the error code of a function call

      

      * idt
        The IDT may contain any of three kinds of gate descriptors:
        • Task-gate descriptor
        • Interrupt-gate descriptor
        • Trap-gate descriptor
        range: 0 - 255. 0 - 31 are reserved by the Intel 64 and IA-32 architectures for architecture-defined exceptions and interrupts.
        http://www.rcollins.org/articles/pmbasics/tspec_a1_doc.html#SB1
        detect whether or not we are in protected mode before the error code is removed:
          machine status word (MSW), or the system register CR0. 
        APIC (Advanced, Programmable, Interrupt Controller)

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
              These instructions are often called "software interrupts", but the processor handles them as exceptions

        * [interrupts](http://www.osdever.net/tutorials/view/interrupts-exceptions-and-idts-part-1-interrupts-isrs-irqs-the-pic)
          alter the normal program flow to handle external events or to report errors or exceptional conditions

        * ISR(Interrupt Service Routine) is the code executed when an interrupt occurs.
          CPU takes care of the most compilcated part by saving the SS, EIP, ESP, and CS registers to the stack. 
          ```asm
          isr:
          pusha ; Push AX, CX, DX, BX, original SP, BP, SI, and DI.
          push gs
          push fs
          push es
          push ds

          ; do what you want to here :)

          pop ds
          pop es
          pop fs
          pop gs
          popa
          iret
          ```
        * IDT format http://www.rcollins.org/articles/pmbasics/tspec_a1_doc.html#SB1
          31	                  15	               14	      12	          7         	4	      0
          Offset 31-16(word)	Present(1 bit)	DPL(2 bits)	01110(5 bits)	000(3 bits)	Not Used	4
          Selector31-16(word)	      Offset 15-0(word)	                                              0

          objcopy -O binary test.o test.bin # generate binary format
        
        * idt implements
          * code, data, and stack segments that make up the execution environment of a program or procedure
          * two system segments: the task-state segment (TSS) and the LDT. 
          * The GDT is not considered a segment because it is not accessed by means of a segment selector and segment descriptor.
          * TSSs and LDTs have segment descriptors defined for them.
          * a set of special descriptors called gates (call gates, interrupt gates, trap gates, and task gates)

          * In switching tasks, the processor performs the following actions:
            1. Stores the state of the current task in the current TSS.
            2. Loads the task register with the segment selector for the new task.
            3. Accesses the new TSS through a segment descriptor in the GDT.
            4. Loads the state of the new task from the new TSS into the general-purpose registers, the segment registers,
              the LDTR, control register CR3 (base address of the paging-structure hierarchy), the EFLAGS register, and the
              EIP register.
    
          * Interrupt and Exception Handling
            * IDT
              * External interrupts, software interrupts and exceptions are handled through the interrupt descriptor table (IDT).
              * The IDT stores a collection of gate descriptors that provide access to interrupt and exception handlers. 
                * gate descriptors contains:
                  1. interrupt gate : the associated handler procedure is accessed in a manner similar to calling a procedure through a call gate  
                  2. trap gate : the associated handler procedure is accessed in a manner similar to calling a procedure through a call gate   
                  3. task gate: the handler is accessed through a task switch.
              * IDT is not a segment, like GDT, base adress of idt is in IDTR
              *  interrupt vector provides an index into the IDT coming from:
                1. internal hardware
                2. an external interrupt controller
                3. software by means of an INT, INTO, INT 3, or BOUND instruction

          * define idt structures
            * define isr
            * lidt
            * remapping pics to new idt entries
              * pic(Programmable Interrupt Controller) handles hardware interrupts (IRQ0, IRQ1, etc.).
              * consist
                1. PIC1  -> IRQ0 - IRQ7
                2. PIC2  -> IRQ8 - IRQ15
              * [remap hardware interrupts](http://www.osdever.net/tutorials/view/programming-the-pic):
                * why
                  * in real mode, hardware interrupts are mapped to interrupt 8-15 (first PIC) and 70-77 (second PIC).
                  * int protect mode, interrupt 8-15 are reserved for exceptions
                * how : by sending some ICW (Initialization Commands Words) to the PICs controller.
                  1. send ICW1 to PIC1 (20h) and PIC2 (A0h)
                  2. send ICW2 to 21h for the first PIC and 0A1h for the second PIC
                  3. send ICW3 to 21h for the first PIC and 0A1h for the second PIC
                  4. send ICW4 to 21h for the first PIC and 0A1h for the second PIC
                * [ICWs](http://retired.beyondlogic.org/interrupts/interupt.htm)
                  * ICW1: Interrupt Trigger Type/ Address Interval/ Cascade ?/ With ICW4
                  * ICW2: Selects Base Vector Address. 00001000 (0x08) for PIC1 and 01110000 (0x70) for PIC2 
                  * ICW3: Master/ Slave Connection Information.
                  * ICW4: The only thing we must set is 8086/8080 Mode which is done using Bit 0
                * [IRQs](http://www.osdever.net/tutorials/view/irqs)

                  line  |  interrupt | function
                  ----- |  --------- | ---------
                  IRQ0  |   08       | system timer
                  IRQ1  |   09       | keyboard
                  IRQ2  |   0A       | PC/XT: EGA vertical retrace or maybe available
                        |            | PC/AT: see explanation below
                  IRQ3  |   0B       | COM2 or maybe available
                  IRQ4  |   0C       | COM1
                  IRQ5  |   0D       | PC/XT: hard disk drive
                        |            | PC/AT: LPT2 or maybe available
                  IRQ6  |   0E       | floppy disk drive
                  IRQ7  |   0F       | LPT1
                  IRQ8  |   70       | PC/AT: CMOS Real Time Clock
                  IRQ9  |   71       | PC/AT: see explanation below
                  IRQ10 |   72       | PC/AT: probably available
                  IRQ11 |   73       | PC/AT: probably available
                  IRQ12 |   74       | PC/AT: probably available
                        |            | PS/2: mouse
                  IRQ13 |   75       | PC/AT: numeric coprocessor
                  IRQ14 |   76       | PC/AT: hard disk drive
                  IRQ15 |   77       | PC/AT: probably available

                * [registers for pic](https://en.wikipedia.org/wiki/Programmable_Interrupt_Controller)
                  * Interrupt Request Register (IRR):
                    specifies which interrupts are pending acknowledgement,
                    and is typically a symbolic register which can not be directly accessed
                  * In-Service Register (ISR):
                    The ISR register specifies which interrupts have been acknowledged,
                    but are still waiting for an End Of Interrupt (EOI).
                  * Interrupt Mask Register (IMR):
                    specifies which interrupts are to be ignored and not acknowledged. 
                  
                  A simple register schema such as this allows up to two distinct interrupt requests to be outstanding 
                  at one time, one waiting for acknowledgement, and one waiting for EOI.

                  There are a number of common priority schemas in PICs including hard priorities, specific priorities, and 
                  rotating priorities.

                  Interrupts may be either edge triggered or level triggered.

                  There are a number of common ways of acknowledging an interrupt has completed when an EOI is issued. 
                  These include specifying which interrupt completed, using an implied interrupt which has 
                  completed (usually the highest priority pending in the ISR), and treating interrupt acknowledgement as the EOI.
                                          
                            not masked                Priority Resolver simply selects the IRQ of highest priority.
                  interrupt -----------> IMR --> IRR -------------------------------------------------------------> IS

      * memory management

        * physical addressing 
          a linear address is treated as a physical address.

        * paging (virtual memory)
          all code, data, stack, and system segments (including the GDT and IDT) can be paged with only 
          the most recently accessed pages(page frames) being held in physical memory.
          * locate in physical memory containing in page structures
          * base address of the paging-structure in CR3
          * page structure contains:
            1. the base of a page frame
            2. access rights
            3. memory management Information

        * logical and linear address 
          logical -> linear:
          * segment selector -> gdt -> segment descriptor
          * examine access rights and range of segments
          * base address + offset -> linear addres
        
        * paging (linear-address translation)
          linear -> physical


      * System Registers
        * The system flags and IOPL field in the EFLAGS register control task and mode switching, interrupt handling,
          instruction tracing, and access rights.
        * The control registers (CR0, CR2, CR3, and CR4) contain a variety of flags and data fields for controlling 
          systemlevel operations. Other flags in these registers are used to indicate support for specific processor 
          capabilities within the operating system or executive.
        * The debug registers  allow the setting of breakpoints for use in debugging programs and systems software. 
        * The GDTR, LDTR, and IDTR registers contain the linear addresses and sizes (limits) of their respective tables.
        * The task register contains the linear address and size of the TSS for the current task. 
        * Model-specific registers
          The model-specific registers (MSRs) are a group of registers available primarily to operating-system or executive
          procedures (that is, code running at privilege level 0). These registers control items such as the debug extensions,
          the performance-monitoring counters, the machine- check architecture, and the memory type ranges (MTRRs).
      
      * mode of operations
                    PE = 1 | 0                    VM = 1 | 0
        real mode  <-----------> protected mode <---------------> Virtual-8086 mode 
        
        virtual-8086: allows the processor execute 8086 software in a protected, multitasking environment
        
