## Socket Header Files
https://www.gnu.org/software/libc/manual/

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


    
    ERROR CODE TABLE
Error number 	Error Code 	Error Description
1 	EPERM 	Operation not permitted
2 	ENOENT 	No such file or directory
3 	ESRCH 	No such process
4 	EINTR 	Interrupted system call
5 	EIO 	I/O error
6 	ENXIO 	No such device or address
7 	E2BIG 	Argument list too long
8 	ENOEXEC 	Exec format error
9 	EBADF 	Bad file number
10 	ECHILD 	No child processes
11 	EAGAIN 	Try again
12 	ENOMEM 	Out of memory
13 	EACCES 	Permission denied
14 	EFAULT 	Bad address
15 	ENOTBLK 	Block device required
16 	EBUSY 	Device or resource busy
17 	EEXIST 	File exists
18 	EXDEV 	Cross-device link
19 	ENODEV 	No such device
20 	ENOTDIR 	Not a directory
21 	EISDIR 	Is a directory
22 	EINVAL 	Invalid argument
23 	ENFILE 	File table overflow
24 	EMFILE 	Too many open files
25 	ENOTTY 	Not a typewriter
26 	ETXTBSY 	Text file busy
27 	EFBIG 	File too large
28 	ENOSPC 	No space left on device
29 	ESPIPE 	Illegal seek
30 	EROFS 	Read-only file system
31 	EMLINK 	Too many links
32 	EPIPE 	Broken pipe
33 	EDOM 	Math argument out of domain of func
34 	ERANGE 	Math result not representable
35 	EDEADLK 	Resource deadlock would occur
36 	ENAMETOOLONG 	File name too long
37 	ENOLCK 	No record locks available
38 	ENOSYS 	Function not implemented
39 	ENOTEMPTY 	Directory not empty
40 	ELOOP 	Too many symbolic links encountered
42 	ENOMSG 	No message of desired type
43 	EIDRM 	Identifier removed
44 	ECHRNG 	Channel number out of range
45 	EL2NSYNC 	Level 2 not synchronized
46 	EL3HLT 	Level 3 halted
47 	EL3RST 	Level 3 reset
48 	ELNRNG 	Link number out of range
49 	EUNATCH 	Protocol driver not attached
50 	ENOCSI 	No CSI structure available
51 	EL2HLT 	Level 2 halted
52 	EBADE 	Invalid exchange
53 	EBADR 	Invalid request descriptor
54 	EXFULL 	Exchange full
55 	ENOANO 	No anode
56 	EBADRQC 	Invalid request code
57 	EBADSLT 	Invalid slot
59 	EBFONT 	Bad font file format
60 	ENOSTR 	Device not a stream
61 	ENODATA 	No data available
62 	ETIME 	Timer expired
63 	ENOSR 	Out of streams resources
64 	ENONET 	Machine is not on the network
65 	ENOPKG 	Package not installed
66 	EREMOTE 	Object is remote
67 	ENOLINK 	Link has been severed
68 	EADV 	Advertise error
69 	ESRMNT 	Srmount error
70 	ECOMM 	Communication error on send
71 	EPROTO 	Protocol error
72 	EMULTIHOP 	Multihop attempted
73 	EDOTDOT 	RFS specific error
74 	EBADMSG 	Not a data message
75 	EOVERFLOW 	Value too large for defined data type
76 	ENOTUNIQ 	Name not unique on network
77 	EBADFD 	File descriptor in bad state
78 	EREMCHG 	Remote address changed
79 	ELIBACC 	Can not access a needed shared library
80 	ELIBBAD 	Accessing a corrupted shared library
81 	ELIBSCN 	.lib section in a.out corrupted
82 	ELIBMAX 	Attempting to link in too many shared libraries
83 	ELIBEXEC 	Cannot exec a shared library directly
84 	EILSEQ 	Illegal byte sequence
85 	ERESTART 	Interrupted system call should be restarted
86 	ESTRPIPE 	Streams pipe error
87 	EUSERS 	Too many users
88 	ENOTSOCK 	Socket operation on non-socket
89 	EDESTADDRREQ 	Destination address required
90 	EMSGSIZE 	Message too long
91 	EPROTOTYPE 	Protocol wrong type for socket
92 	ENOPROTOOPT 	Protocol not available
93 	EPROTONOSUPPORT 	Protocol not supported
94 	ESOCKTNOSUPPORT 	Socket type not supported
95 	EOPNOTSUPP 	Operation not supported on transport endpoint
96 	EPFNOSUPPORT 	Protocol family not supported
97 	EAFNOSUPPORT 	Address family not supported by protocol
98 	EADDRINUSE 	Address already in use
99 	EADDRNOTAVAIL 	Cannot assign requested address
100 	ENETDOWN 	Network is down
101 	ENETUNREACH 	Network is unreachable
102 	ENETRESET 	Network dropped connection because of reset
103 	ECONNABORTED 	Software caused connection abort
104 	ECONNRESET 	Connection reset by peer
105 	ENOBUFS 	No buffer space available
106 	EISCONN 	Transport endpoint is already connected
107 	ENOTCONN 	Transport endpoint is not connected
108 	ESHUTDOWN 	Cannot send after transport endpoint shutdown
109 	ETOOMANYREFS 	Too many references: cannot splice
110 	ETIMEDOUT 	Connection timed out
111 	ECONNREFUSED 	Connection refused
112 	EHOSTDOWN 	Host is down
113 	EHOSTUNREACH 	No route to host
114 	EALREADY 	Operation already in progress
115 	EINPROGRESS 	Operation now in progress
116 	ESTALE 	Stale NFS file handle
117 	EUCLEAN 	Structure needs cleaning
118 	ENOTNAM 	Not a XENIX named type file
119 	ENAVAIL 	No XENIX semaphores available
120 	EISNAM 	Is a named type file
121 	EREMOTEIO 	Remote I/O error
122 	EDQUOT 	Quota exceeded
123 	ENOMEDIUM 	No medium found
124 	EMEDIUMTYPE 	Wrong medium type
125 	ECANCELED 	Operation Canceled
126 	ENOKEY 	Required key not available
127 	EKEYEXPIRED 	Key has expired
128 	EKEYREVOKED 	Key has been revoked
129 	EKEYREJECTED 	Key was rejected by service
130 	EOWNERDEAD 	Owner died
131 	ENOTRECOVERABLE 	State not recoverable


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
      make sure mylib.so exist, if not, make a link to mylib.so.xx.xx.xx
      ld find error ways:
      1. LD_DEBUG=all make 
      2. ld -lmylib --verbose or -Wl,--verbose or -Xlinker --verbose to gcc for passing parameters to ld

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
