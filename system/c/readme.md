## Socket Header Files
https://www.gnu.org/software/libc/manual/

http://www.iso-9899.info/wiki/Books#Learning_C

http://planet.kernel.org/

http://www.makelinux.net/ldd3/

Rootkit Programming

## Socket header files contain data definitions, structures, constants, macros, and options used by socket subroutines. An application program must include the appropriate header file to make use of structures or other information a particular socket subroutine requires. Commonly used socket header files are:
    header                        | description
    ------                        | -----------
     /usr/include/netinet/in.h 	  | Defines Internet constants and structures.
     /usr/include/arpa/nameser.h  | Contains Internet name server information.
     /usr/include/netdb.h 	      | Contains data definitions for socket subroutines.
     /usr/include/resolv.h        | Contains resolver global definitions and variables.
     /usr/include/sys/socket.h    | Contains data definitions and socket structures.
     /usr/include/sys/socketvar.h | Defines the kernel structure per socket and contains buffer queues.
     /usr/include/sys/types.h     | Contains data type definitions.
     /usr/include/sys/un.h        | Defines structures for the UNIX interprocess communication domain.
     /usr/include/sys/ndd_var.h   | Defines structures for the AIX Network Device Driver (NDD) domain.
     /usr/include/sys/atmsock.h   | Contains constants and structures for the Asynchronous Transfer Mode (ATM) protocol in the AIX NDD domain.

  In addition to commonly used socket header files, Internet address translation subroutines require the inclusion of the inet.h file. The inet.h file is located in the /usr/include/arpa directory.
  Socket Address Data Structures 

  The socket data structure defines the socket. During a socket subroutine, the system dynamically creates the socket data structure. The socket address is specified by a data structure that is defined in a header file. See the sockaddr Structure figure for an illustration of this data structure.  
  
  The /usr/include/sys/socket.h file contains the sockaddr structure. The contents of the sa_data structure depend on the protocol in use.  
  
  The types of socket-address data structures are as follows:  
  * struct sockaddr_in 	Defines sockets used for machine-to-machine communication across a network and interprocess communication (IPC). The /usr/include/netinet/in.h file contains the sockaddr_in structure.
  * struct sockaddr_un 	Defines UNIX domain sockets used for local IPC only. These sockets require complete path name specification and do not traverse networks. The /usr/include/sys/un.h file contains the sockaddr_un structure.
  * struct sockaddr_ns 	Defines the Xerox Network Services (XNS) sockets to be used for reliable, full-duplex, connection-oriented services to an application. The /usr/include/netns/ns.h file contains the sockaddr_ns structure.
  * struct sockaddr_ndd Defines the AIX NDD sockets used for machine-to-machine communication across a physical network. The /usr/include/sys/ndd_var.h file contains the sockaddr_ndd structure. Depending upon socket types and protocol, other header files may need to be included. 


* [Type Qualifiers](http://www.oracle.com/technetwork/server-storage/solaris10/cc-restrict-139391.html)
  - const: No writes through this lvalue.

  - volatile: No cacheing through this lvalue

  - [restric](https://en.wikipedia.org/wiki/Restrict https://en.wikipedia.org/wiki/Pointer_aliasing)
  
    - for the lifetime of the pointer, only the pointer itself or a value directly derived from it (such as pointer + 1) will be used to access the object to which it points. 
    - limits the effects of pointer aliasing, aiding optimizations

* pthread 
  
  [reference](https://computing.llnl.gov/tutorials/pthreads/#Compiling)

  Compiler / Platform  | Compiler Command 	  | Description
  -------------------  | ----------------     | -----------
  INTEL Linux 	       | icc -pthread 	C     | icpc -pthread 	C++
  PGI Linux 	       | pgcc -lpthread C     | pgCC -lpthread 	C++
  GNU Linux, Blue Gene | gcc -pthread GNU C   | g++ -pthread 	GNU C++
  IBM Blue Gene 	   | bgxlc_r/bgcc_r C (ANSI /non-ANSI) | bgxlC_r, bgxlc++_r 	C++
  
  [stackoverflow](http://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux)
  * -pthread tells the compiler to link in the pthread library as well as configure the compilation for threads.
  
  * -lpthread option only causes the pthread library to be linked - the pre-defined macros don't get defined.

* daemon
  
  * rules
    1. pid file in /var/run/daemon.pid
    2. configurtion /etc/daemon.conf
    3. auto init 
      
       /etc/init.d
      
       /etc/inttab
    4. reload configurtion can set SIGHUP handler to handler reloading
      daemon has no tty or alphan no expectation for SIGHUP, so can use SIGHUP for reloading

  * create steps:
    1. umask(0)

    2. fork() exit father 
      - reparent to be a child of init

    3. setsid() 
      * dissociate the daemon fro its controlling terminal
      * be a session leader 
        - the process can still reacquire a controlling terminal
        - only session leader can allocate a control tty
      * leader in a new process group

    4. [2nd fork() exit father to ensure no controlling terminal](http://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon)
        
        - POSIX.1-2008 Sec. 11.2.3, "The Controlling Terminal", has the answer (emphasis added):
          ```
          The controlling terminal for a session is allocated by the session leader in an implementation-defined manner. If a session leader has no controlling terminal, and opens a terminal device file that is not already associated with a session without using the O_NOCTTY option (see open()),  it is implementation-defined whether the terminal becomes the controlling terminal of the session leader. If a process which is not a session leader opens a terminal file, or the O_NOCTTY option is used on open(), then that terminal shall not become the controlling terminal of the  calling process.
          ```
        - for example:
          ```c
          int fd = open("/dev/console", O_RDWR);
          ```
        - then the daemon process might acquire /dev/console as its controlling terminal, depending on whether the daemon process is a session leader, and depending on the system implementation. 

        - The program can guarantee the above call will not acquire a controlling terminal if first ensures that it is not a session leader.

        - The double-fork technique is a bit paranoid. It may not be necessary if you know that the daemon will never open a terminal device file.

        - on some systems it may not be necessary even if the daemon does open a terminal device file, since that behavior is implementation-defined. 

        - one thing that is not implementation-defined is that only a session leader can allocate the controlling terminal. 
        
    4. chdir("/") to root or where it works

    5. close unneccessary file description

    6. redirection stdin, stdout, stderr to /dev/null

  * ERROR CODE TABLE

    /usr/include/asm/errno.h
    
# gcc
-------------
  * create lib
    [Creating a shared and static library with the gnu compiler](http://www.adp-gmbh.ch/cpp/gcc/create_lib.html)

    https://www.gnu.org/software/gcc/bugs/segfault.html

    https://www.gnu.org/software/libc/manual/html_node/Server-Example.html

    http://www.tutorialspoint.com/unix_system_calls/_newselect.htm

    http://www.microhowto.info/howto/build_a_shared_library_using_gcc.html

    ```bash
    gcc -shared -fPIC -Wl,-soname,libqux.so.1 -o libqux.so foo.o bar.o baz.o -lc
    ````
    1. The -fPIC option is needed when linking as it was when compiling to ensure that any code added by the linker is compatible with code previously generated by the compiler.

    2. The -Wl option passes a comma-separated list of arguments to the linker. As its name suggests, -soname specifies the required soname. If these options are omitted then the library will not have an soname.

    3. The ldconfig manpage recommends explicitly linking against libc, which has been done above using the -l option (-lc).

    * preprocess
      ```
      gcc -E hello.c -o hello.i
      ```
    * compile
      ```
      gcc -S hello.i -o hello.s

      /usr/libexec/gcc/x86_64-redhat-linux/4.4.7/cc1 open.c
      ```
    * assembly
      ```
      as hello.s -o hello.o
      gcc -c hello.s -o hello.o

      nm -Ca  # list all function in lib so
      ```

    * use library
      ```
      gcc -I/usr/local/lib strnlen_test.c -l:libcmockery.a - strnlen_test

      # -l expand cmockery to libcmockery
      gcc /local/lib strnlen_test.c -lcmockery - strnlen_test

      gcc program.o -llib1 -Wl,-Bstatic -llib2 -Wl,-Bdynamic -llib3

      #define asmlinkage extern "c"
      
      sudo apt-get install gcc-multilib g++-multilib
      ./configure --build=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
      ```

    * ld : make sure libmylib.so exist, if not, make a link to mylib.so.xx.xx.xx
      - ld find error ways:
        1. LD_DEBUG=all make 
        2. ld -lmylib --verbose or -Wl,--verbose or -Xlinker --verbose to gcc for passing parameters to ld

      - error in file order:
        - object files and libraries in the order that they depend on each other - as a consequential rule of thumb
        - put the library AFTER the module you are compiling.

      - link against installed libraries in a given directory, LIBDIR,
        - use libtool, and specify the full pathname of the library

        - use the `-LLIBDIR' flag during linking and do at least one of the following:
          - add LIBDIR to the `LD_LIBRARY_PATH' environment variable
            during execution
          - add LIBDIR to the `LD_RUN_PATH' environment variable
            during linking
          - use the `-Wl,--rpath -Wl,LIBDIR' linker flag
          - have your system administrator add LIBDIR to `/etc/ld.so.conf'
          - ld(1) and ld.so(8) manual pages.

    * [create tiny size](http://www.muppetlabs.com/~breadbox/software/tiny/teensy.html)
      [libc free](https://blogs.oracle.com/ksplice/entry/hello_from_a_libc_free)
      ```
      gcc -Wall -s -nostdlib tiny.o

      gcc -fno-builtin/-fno-builtin-function
      ```
    * The compiler option -D can be used to define the macro MY_MACRO from command line.

    * inline
      * -finline-functions: direct GCC to try to integrate all “simple enough” functions into their callers
      * GCC implements three diﬀerent semantics of declaring a function inline:
        1. ‘-std=gnu89’ or ‘-fgnu89-inline’
        2.  gnu_inline attribute is present on all inline declarations
        3.  ‘-std=c99’, ‘-std=c11’, ‘-std=gnu99’ or ‘-std=gnu11’(without ‘-fgnu89-inline’)
      * writing a header fle to be included in ISO C90 programs, write __inline__ instead of inline
      * two important cases:
        1. inline keyword is used on a static function
          ```c
          static inline int
          inc (int *a)
          {
          return (*a)++;
          }
          ```
        2.  first declared without using the inline keyword and then is defned with inline
          ```c
          extern int inc (int *a);
          inline int
          inc (int *a)
          {
          return (*a)++;
          }
          ```
        * gcc generate no assembler code for function(options '-fkeep-inline-functions' not used) if:
          1. all calls to the function are integrated into the caller
          2. the function's address is never used
          3. functions own's assembler code never used
        * unsuitable for inline substitution(‘-Winline’ warns show failure detail):
          1. variadic functions:
            myprintf(fmt, ...)
          2. use of alloca
          3. use of computed goto
          4. use of nonlocal goto
          5. use of nested functions
          6. use of setjmp
          7. use of __builtin_longjmp, __builtin_return or __builtin_apply_args
        * no inline when no optimizing unless use 'always-inline':
          ```c
          /* Prototype. */
          inline void foo (const char) __attribute__((always_inline));   
          ```
        * a non-static inline function is always compiled on its own in the usual fashion for that:
          * the compiler must assume that there may be calls from other source fles
          * a global symbol can be defned only once in any program, the function must not be 
            defned in the other source files,so the calls therein cannot be integrated.
        * inline and extern in the function defnition,then the defnition is used only for inlining
          * function never compiled to its own, not even if you refer to its address explicitly.Such an address 
            becomes an external reference, as if you had only declared the function, and had not defned it.
          * This combination of inline and extern has almost the eﬀect of a macro. 
            * function definition in a header file with inline and extern keywords,
              causes most calls to the function to be inlined
            * put another copy of definition (lack inline and extern) in a library file, 
              any uses of the function refer to single copy in librar

  - get define
    ```
    echo | gcc -E -xc -include 'stddef.h' - | grep size_t
    typedef long unsigned int size_t;

    # compile without stdlib, frame protector and frame pointer 
    CFLAGS = -ffreestanding -O2 -m32 -g -Wall -Wextra -nostdinc -fno-builtin -fno-stack-protector -fomit-frame-pointer

    LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -nostdlib
    ```

  - compile to raw binary 
    ```
    -ffreestanding :implies -fno-builtin
    -fhosted   Assert that compilation targets a hosted environment.  This implies -fbuiltin
    gcc -ffreestanding -m32 c basic.c -o basic.o
    ```

  - [selectively enable or disable certain types of diagnostics](https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html)
    - format
      ```c
      #pragma GCC diagnostic kind option
      
      #pragma GCC diagnostic warning "-Wformat"
      #pragma GCC diagnostic error "-Wformat"
      #pragma GCC diagnostic ignored "-Wformat"
      ```

    - remember the state of the diagnostics as of each __push__, and restore to that point at each __pop__
      ```c
      #pragma GCC diagnostic error "-Wuninitialized"
        foo(a);                       /* error is given for this one */
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wuninitialized"
        foo(b);                       /* no diagnostic for this one */
      #pragma GCC diagnostic pop
        foo(c);                       /* error is given for this one */
      #pragma GCC diagnostic pop
        foo(d);                       /* depends on command-line options */
      ```

    - printing messages during compilation. 
      ```c
      #pragma message "Compiling " __FILE__ "..."

      #define DO_PRAGMA(x) _Pragma (#x)
      #define TODO(x) DO_PRAGMA(message ("TODO - " #x))

      TODO(Remember to fix this)
      ```

    - usage
      ```c
      #define DIAG_STR(s) #s
      #define DIAG_JOINSTR(x,y) DIAG_STR(x ## y)

      #ifdef _MSC_VER
      #define DIAG_DO_PRAGMA(x) __pragma (#x)
      #define DIAG_PRAGMA(compiler,x) DIAG_DO_PRAGMA(warning(x))
      #else /* _MSC_VER */ 
      #define DIAG_DO_PRAGMA(x) _Pragma (#x)
      #define DIAG_PRAGMA(compiler,x) DIAG_DO_PRAGMA(compiler diagnostic x)
      #endif
      #if defined(__clang__)
      # define DISABLE_WARNING(gcc_unused,clang_option,msvc_unused) DIAG_PRAGMA(clang,push) DIAG_PRAGMA(clang,ignored DIAG_JOINSTR(-W,clang_option))
      # define ENABLE_WARNING(gcc_unused,clang_option,msvc_unused) DIAG_PRAGMA(clang,pop)
      #elif defined(_MSC_VER)
      # define DISABLE_WARNING(gcc_unused,clang_unused,msvc_errorcode) DIAG_PRAGMA(msvc,push) DIAG_DO_PRAGMA(warning(disable:##msvc_errorcode))
      # define ENABLE_WARNING(gcc_unused,clang_unused,msvc_errorcode) DIAG_PRAGMA(msvc,pop)
      #elif defined(__GNUC__)
      #if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
      # define DISABLE_WARNING(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,push) DIAG_PRAGMA(GCC,ignored DIAG_JOINSTR(-W,gcc_option))
      # define ENABLE_WARNING(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,pop)
      #else
      # define DISABLE_WARNING(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,ignored DIAG_JOINSTR(-W,gcc_option))
      # define ENABLE_WARNING(gcc_option,clang_option,msvc_unused) DIAG_PRAGMA(GCC,warning DIAG_JOINSTR(-W,gcc_option))
      #endif
      #endif
      ```

    - pragma
      - gcc: _Pragma
      - msvc: __pragma 

    - [attribute](https://gcc.gnu.org/onlinedocs/gcc-4.7.2/gcc/Function-Attributes.html)
      - __attribute__ ((unused))

  - compile c++
    ```
    gcc leton.cpp -lstdc++
    g++ letion.cpp
    ```

# io
-----
  * file
    
    RESTRICTED DELETION FLAG OR STICKY BIT: 

    The  restricted deletion flag or sticky bit is a single bit, whose interpretation depends on the file type.  
    
    * For directories, it prevents unprivileged users from removing or renaming a file in the directory  unless  they  own
    the  file or the directory; this is called the restricted deletion flag for the directory, and is commonly found
    on world-writable directories like /tmp. 
    * For regular files on some older systems, the bit saves  the  program’s
    text image on the swap device so it will load more quickly when run; this is called the sticky bit.
    
    buffer:
      stderr not full buffered
      stdout, stdin is full buffered when not directed to interactive device
      setvbuf(stdout, NULL, _IONBF, 0)
      ioctl

  * open 
    1. file access flags: O_RDWR, O_RDONLY, O_WRONLY
    2. file create flags: O_CREAT, o_TRUNC, O_DIRECTORY,O_DIRECT
    3. file status flags: O_ASYNC, O_NONBLOCK, OAPPEND

# buffer overflow
    * Make sure that the memory auditing is done properly in the program using utilities like valgrind memcheck
    * Use fgets() instead of gets().
    * Use strncmp() instead of strcmp(), strncpy() instead of strcpy() and so on.

# socket
  * ruptime
    1. add service config
      vi /etc/services
      ruptime    180/tcp   # ruptime

      vi /etc/hosts
      <ip> hostname

    2. start server to listen
       ruptimed 
    3. start client
       ruptime hostname

# [sequence point](https://en.wikipedia.org/wiki/Sequence_point)

  defines any point in a computer program's execution at which it is guaranteed that all side effect of previous evaluations
  will have been performed, and no side effects from subsequent evaluations have yet been performed;

  * In C[5] and C++,[6] sequence points occur in the following places. (In C++, overloaded operators act like functions, and thus operators that have been overloaded introduce sequence points in the same way as function calls.)

    1. Between evaluation of the left and right operands of the && (logical AND), || (logical OR) (as part of short-circuit evaluation), 
    and comma operators. For example, in the expression *p++ != 0 && *q++ != 0, all side effects of the sub-expression *p++ != 0 are completed before any attempt to access q.
    2. Between the evaluation of the first operand of the ternary "question-mark" operator and the second or third operand. 
      For example, in the expression a = (*p++) ? (*p++) : 0 there is a sequence point after the first *p++, 
      meaning it has already been incremented by the time the second instance is executed.
    3. At the end of a full expression. This category includes expression statements (such as the assignment a=b;), return statements, the controlling expressions of if, switch, while, or do-while statements, and all three expressions in a for statement.
    4. Before a function is entered in a function call. The order in which the arguments are evaluated is not specified, but this sequence point means that all of their side effects are complete before the function is entered. In the expression f(i++) + g(j++) + h(k++), f is called with a parameter of the original value of i, but i is incremented before entering the body of f. Similarly, j and k are updated before entering g and h respectively. However, it is not specified in which order f(), g(), h() are executed, nor in which order i, j, k are incremented. If the body of f accesses the variables j and k, it might find them not-incremented, incremented, or even not-incremented and then incremented(?). (The function call f(a,b,c) is not a use of the comma operator; the order of evaluation for a, b, and c is unspecified.)
    5. At a function return, after the return value is copied into the calling context. (This sequence point is only specified in the C++ standard; it is present only implicitly in C.[7])
    6. At the end of an initializer; for example, after the evaluation of 5 in the declaration int a = 5;.
    7. Between each declarator in each declarator sequence; for example, between the two evaluations of a++ in int x = a++, y = a++.[8] (This is not an example of the comma operator.)
    8. After each conversion associated with an input/output format specifier. For example, in the expression printf("foo %n %d", &a, 42), there is a sequence point after the %n is evaluated and before printing 42.

# io multiplexing
  * level-trigger

  * edge-trigger
    1. signal-driven io
      * Establish the signal handler before enabling signal-driven I/O

        On some UNIX implementations,  SIGIO is ignored by default.
      * Setting the file descriptor owner
        ```c
        fcntl(fd, F_SETOWN, pid);
        ```
        On older UNIX implementations, an ioctl() operation—either  FIOSETOWN or
        SIOCSPGRP —was used to achieve the same effect as  F_SETOWN . For compatibility,
        these ioctl() operations are also provided on Linux.

        The fcntl()  F_GETOWN operation returns the ID of the process or process group
        that is to receive signals when I/O is possible on a specified file descriptor:
        ```c
        id = fcntl(fd, F_GETOWN);
        if (id == -1)
          errExit("fcntl");
        ```
        A process group ID is returned as a negative number by this call.
        The ioctl() operation that corresponds to  F_GETOWN on older UNIX implementa-
        tions was  FIOGETOWN or  SIOCGPGRP . Both of these ioctl() operations are also provided
        on Linux.
      
      * 

# process
  * memory
    If a processtries to access an address for which there is no corresponding page-table entry, it
    receives a  SIGSEGV signal.

    allocates and deallocates pages:
    * stack grow downward beyond limits previously reached;
    * allocated or deallocated on the heap: 
      brk(), sbrk(), malloc() family functions;

       Traditionally, the UNIX system has provided two system calls for manipulating the program break,
       and these are both available on Linux: brk() and sbrk();
       The precise upper limit on where the program break can be set depends on a range of factors, including: 
       1. the process resource limit for the size of the data segment ( RLIMIT_DATA , described in Section 36.3);
       2. the location of memory mappings, shared memory segments, and shared libraries.

       In general, free() doesn’t lower the program break, but instead adds the block of
        memory to a list of free blocks that are recycled by future calls to malloc().
    * share memory:
      * shmat()
      * mmap(), munmap()
    
  * preprocess
    * [variadic macro](https://en.wikipedia.org/wiki/Variadic_macro)
      ```
      #define PRINT_ERR(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
      # define dbgprintf(...) realdbgprintf (__FILE__, __LINE__, __VA_ARGS__)
      for gcc:
      #define PRINT_ERR(fmt, ...) fprintf(fmt, ##__VA_ARGS__)
      which removes the trailing comma when __VA_ARGS__ is empty.

        PRINT_ERR("hello c %s\n", "world");
        PRINT_ERR("hello c \n");

        fprintf(stderr, "hello c %s\n", "world");
        fprintf(stderr, "hello c \n");
      ```

    - #define macro
      ```c
      /* ensures that the code acts like a statement (function call) http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing*/
      #define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

      ```

# macros
  * # and ##
    * The number-sign or "stringizing" operator (#) converts macro parameters to string literals without expanding the parameter definition. 
    * The double-number-sign or "token-pasting" operator (##), which is sometimes called the "merging" operator, is used in both object-like and function-like macros. 
      It permits separate tokens to be joined into a single token and therefore cannot be the first or last token in the macro definition.

      #define paster( n ) printf_s( "token" #n " = %d", token##n )  
      int token9 = 9;  
      paster( 9 );   --> printf_s( "token" "9" " = %d", token9 );   --> printf_s( "token9 = %d", token9 );  

# structure
  - padding
    ```
    # pseudo-code, see actual code below
    padding = (align - (offset mod align)) mod align
    new offset = offset + padding = offset + (align - (offset mod align)) mod align      

    # c code
    padding = (align - (offset & (align - 1))) & (align - 1) = (-offset) & (align - 1)
    new_offset = (offset + alian - 1) & ~(align -1)

    struct MixedData  /* After compilation in 32-bit x86 machine */
    {
        char Data1; /* 1 byte */
        char Padding1[1]; /* 1 byte for the following 'short' to be aligned on a 2 byte boundary
    assuming that the address where structure begins is an even number */
        short Data2; /* 2 bytes */
        int Data3;  /* 4 bytes - largest structure member */
        char Data4; /* 1 byte */
        char Padding2[3]; /* 3 bytes to make total size of the structure 12 bytes */
    };
    ```

# grammar
  - switch case
    ```c
    switch (val)  
    {  
    case VAL:             /* <- C error is here */
      int newVal = 42;  
      break;
    case ANOTHER_VAL:     /* <- C++ error is here */
      ...
      break;
    }
    /* Adding an extra {} block fixes both C++ and C problems */
    {
      int newVal = 42;  
      break;
    }
    ```
    - Jumps that bypass initialization are illegal in C++. 
      - case ANOTHER_VAL: label jumps into the scope of variable newVal bypassing its initialization. 
      - labeled-declaration is allowed but labeled -initialization is not allowed.
      ```c
      /* remove the initializer from variable declaration  */
      switch (val)  
      {  
      case VAL: 
        int newVal;
        newVal = 42;  
        break;
      case ANOTHER_VAL:     /* Now it works in C++! */
        ...
        break;
      }
      ```
    - In C language declarations are not statements. They cannot be labeled. 
      ```c
      /*
      *  In C, according to the specification,
      *  §6.8.1 Labeled Statements:
      *  labeled-statement:
      *      identifier : statement
      *      case constant-expression : statement
      *    default : statement
      */ 
      /* Just add an empty statement after the case VAL: label and the code will become valid */
      switch (val)  
      {  
      case VAL:;            /* Now it works in C! */
        int newVal = 42;  
        break;
      case ANOTHER_VAL:  
        ...
        break;
      }
      ```