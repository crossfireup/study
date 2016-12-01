# start
  [Guide to x86 assembly Language](http://www.cs.virginia.edu/~evans/cs216/guides/x86.html)

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