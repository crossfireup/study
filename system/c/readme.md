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


* [restrict](https://en.wikipedia.org/wiki/Restrict https://en.wikipedia.org/wiki/Pointer_aliasing)
  
  It says that for the lifetime of the pointer, only the pointer itself or a value directly derived from it (such as pointer + 1) will
  be used to access the object to which it points. This limits the effects of pointer aliasing, aiding optimizations.

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
    3. setsid() 
       * be a session leader 
       * leader in a new process group
       * no control tty

         [why fork twice](http://stackoverflow.com/questions/881388/what-is-the-reason-for-performing-a-double-fork-when-creating-a-daemon)
         
          Strictly speaking, the double-fork has nothing to do with re-parenting the daemon as a child of init. All that is necessary to re-parent the child is that the parent must exit.
          This can be done with only a single fork. Also, doing a double-fork by itself doesn't re-parent the daemon process  to init; the daemon's parent must exit. 
          In other words, the parent always exits when forking a proper daemon so that the daemon process is re-parented to init.
 
          So why the double fork? POSIX.1-2008 Sec. 11.2.3, "The Controlling Terminal", has the answer (emphasis added):
          ```
          The controlling terminal for a session is allocated by the session leader in an implementation-defined manner. If a session leader has no controlling terminal, and opens a terminal device file that is not already associated with a session without using the O_NOCTTY option (see open()),  it is implementation-defined whether the terminal becomes the controlling terminal of the session leader. If a process which is not a session leader opens a terminal file, or the O_NOCTTY option is used on open(), then that terminal shall not become the controlling terminal of the  calling process.
          ```
          This tells us that if a daemon process does something like this ...

          ```c
          int fd = open("/dev/console", O_RDWR);
          ```
         ... then the daemon process might acquire /dev/console as its controlling terminal, depending on whether the daemon process is a session leader, and depending on the system implementation. The program can guarantee that the above call will not acquire a controlling terminal if the program  first ensures that it is not a session leader.
 
         Normally, when launching a daemon, setsid is called (from the child process after calling fork) to dissociate the daemon from its controlling terminal. However, calling setsid also means that the calling process will be the session leader of the new session, which leaves open the  possibility that the daemon could reacquire a controlling terminal. The double-fork technique ensures that the daemon process is not the session leader, which then guarantees that a call to open, as in the example above, will not result in the daemon process reacquiring a controlling  terminal.
 
         The double-fork technique is a bit paranoid. It may not be necessary if you know that the daemon will never open a terminal device file.
          Also, on some systems it may not be necessary even if the daemon does open a terminal device file, since that behavior is implementation-defined. 
          However,  one thing that is not implementation-defined is that only a session leader can allocate the controlling terminal. 
          If a process isn't a session leader, it can't allocate a controlling terminal. Therefore, if you want to be paranoid and be certain that the daemon process cannot inadvertently  acquire a controlling terminal, regardless of any implementation-defined specifics, then the double-fork technique is essential.
        


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
      gcc -E hello.c -o hello.i
    * compile
      gcc -S hello.i -o hello.s

      /usr/libexec/gcc/x86_64-redhat-linux/4.4.7/cc1 open.c

    * assembly
      as hello.s -o hello.o
      gcc -c hello.s -o hello.o

      nm -Ca  # list all function in lib so

    * ld 
      make sure libmylib.so exist, if not, make a link to mylib.so.xx.xx.xx
      ld find error ways:
      1. LD_DEBUG=all make 
      2. ld -lmylib --verbose or -Wl,--verbose or -Xlinker --verbose to gcc for passing parameters to ld
    
    * [create tiny size](http://www.muppetlabs.com/~breadbox/software/tiny/teensy.html)
      [libc free](https://blogs.oracle.com/ksplice/entry/hello_from_a_libc_free)

      gcc -Wall -s -nostdlib tiny.o

      gcc -fno-builtin/-fno-builtin-function

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

# macros
  * # and ##
    * The number-sign or "stringizing" operator (#) converts macro parameters to string literals without expanding the parameter definition. 
    * The double-number-sign or "token-pasting" operator (##), which is sometimes called the "merging" operator, is used in both object-like and function-like macros. 
      It permits separate tokens to be joined into a single token and therefore cannot be the first or last token in the macro definition.

      #define paster( n ) printf_s( "token" #n " = %d", token##n )  
      int token9 = 9;  
      paster( 9 );   --> printf_s( "token" "9" " = %d", token9 );   --> printf_s( "token9 = %d", token9 );  



      