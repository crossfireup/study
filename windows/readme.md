# reference
    Windows NT File System Internals : OSR Classic Reprints
    Troubleshooting with the Windows Sysinternals Tools          
    https://msdn.microsoft.com/en-us/windows/hardware/drivers/gettingstarted/index
    https://msdn.microsoft.com/en-us/windows/hardware/drivers/network/roadmap-for-developing-ndis-protocol-drivers
# windows tools:
    * appwiz.cpl
    * inetcpl.cpl
    * resmon
    * perfmon
    * taskmgr
    * control.exe system
    * evenvwr.exe
    * msra.exe    remote assistant
    * rstrui.exe
    * winver.exe
    * msinfo32
    * UserAccoutControlSettings
    * wscui.exe       windows action center
    * control.exe /name Microsoft.Troubleshooting
    * compmgmt.msc services.msc diskmgmt.msc devmgmt.msc evenvwr.exe
        gpedit.msc
    * schdtasks.exe
      ```
      schtasks /run /tn “TASKNAMEINQUOTES”
      C:\WINDOWS\SchedLgU.txt

      schtasks.exe /query /tn "start-up"
      schtasks.exe /change /TN "start-up" /enable
      ```
    * optionalfeatures.exe

    * secedit /analyze 

    *  network tools
        ```
        ncpa.cpl
        arp
        hostname
        ipconfig
        nbtstat
        netsh
        netstat
        nslookup
        ping
        route
        tracert
        pathping

        arp -d *

        ipconfig /flushdns
        ipconfig /registerdns
        nbtstat -R 
        nbtstat -RR

        ipconfig /all
        netsh interface ip show config
        netsh -r remoteip interface ip show config 
        netsh interface ip show dns
        ipconfig /displaydns

        dhcp:
            ipconfig /release
            ipconfig /renew 
            ipconfig /showclassid
            ipconfig /setclassid
        ```
    
    * winmgmt.exe

    * wmic:
      ```
      SERVICE WHERE CAPTION='TELNET' CALL STARTSERVICE

      ENVIRONMENT CREATE NAME="TEMP"; VARIABLEVALUE="NEW"

      PROCESS WHERE NAME="CALC.EXE" DELETE

      process get name,processid, executablepath
     
      product   --list all installed software

      wmicwmic:root\cli>context
      NAMESPACE             : root\cimv2
      ROLE                  : root\cli
      NODE(S)               : DOBLY-PC
      IMPLEVEL              : IMPERSONATE
      [AUTHORITY            : N/A]
      AUTHLEVEL             : PKTPRIVACY
      LOCALE                : ms_409
      PRIVILEGES            : ENABLE
      TRACE                 : OFF
      RECORD                : N/A
      INTERACTIVE           : ON
      FAILFAST              : OFF
      OUTPUT                : STDOUT
      APPEND                : STDOUT
      USER                  : N/A
      AGGREGATE             : ON
      ```

    * slmgr : software licensing service
        /dli
        /dlv
        /xpr

    * check exe is 32-bits or 64-bits
      * check executable file header: 0x14C for x86 or 0x8664 for x64
        ```
        dumpbin /HEaders stdcall_x64.exe | grep machine
             14C machine (x86)
                   32 bit word machine
        ```
    
    * wf.msc # windows firewall
      firewall.cpl
    
    * main.cpl
      desk.cpl
      sysdm.cpl

    * net
      ```
      net share admin$ /users:3
      net share
      net use
      ```

    * netsh
      ```
      netsh firewall set opmode disable
      ```

    * sc
      ```
      https://forum.sysinternals.com/topic15919.html
      http://stackoverflow.com/questions/828432/psexec-access-denied-errors/14103682#14103682
      windows xp sp3
      sc query type= all state= inactive | findstr /I "remote"
      sc config remoteaccess start= auto
      [SC] ChangeServiceConfig SUCCESS

      sc start remoteaccess
      SERVICE_NAME: remoteaccess
        TYPE               : 20  WIN32_SHARE_PROCESS
        STATE              : 2  START_PENDING
                                (NOT_STOPPABLE,NOT_PAUSABLE,IGNORES_SHUTDOWN)
        WIN32_EXIT_CODE    : 0  (0x0)
        SERVICE_EXIT_CODE  : 0  (0x0)
        CHECKPOINT         : 0x0
        WAIT_HINT          : 0x7d0
        PID                : 1420
        FLAGS              :

      sc query lanmanworkstation
      SERVICE_NAME: lanmanworkstation
        TYPE               : 20  WIN32_SHARE_PROCESS
        STATE              : 4  RUNNING
                                (STOPPABLE,PAUSABLE,ACCEPTS_SHUTDOWN)
        WIN32_EXIT_CODE    : 0  (0x0)
        SERVICE_EXIT_CODE  : 0  (0x0)
        CHECKPOINT         : 0x0
        WAIT_HINT          : 0x0

      sc query lanmanserver
      SERVICE_NAME: lanmanserver
        TYPE               : 20  WIN32_SHARE_PROCESS
        STATE              : 4  RUNNING
                                (STOPPABLE,PAUSABLE,ACCEPTS_SHUTDOWN)
        WIN32_EXIT_CODE    : 0  (0x0)
        SERVICE_EXIT_CODE  : 0  (0x0)
        CHECKPOINT         : 0x0
        WAIT_HINT          : 0x0

      sc query sharedaccess

      cmdkey /add:192.168.2.128 /user:dolphin /pass:
      Enter the password for 'dolphin' to connect to '192.168.2.128':

      cmdky /list

      secpol.msc security-setting -> local policies -> security options -> "network access: sharing and security mode for local account"
        set it to "classical local user loggin as themselves"

      net user \\192.168.2.128\admin$ /user:dolphin-xp-sp3\dolphin
      ```
    
    * vs code
      ```
      Ctrl+D

      Ctrl+Shift+L  mutil to one line 

      Ctrl+Shift+P show command
      ```
    
    * control panel tools
      ```
        Control panel tool             Command
      -----------------------------------------------------------------
      Accessibility Options          control access.cpl
      Add New Hardware               control sysdm.cpl add new hardware
      Add/Remove Programs            control appwiz.cpl
      Date/Time Properties           control timedate.cpl
      Display Properties             control desk.cpl
      FindFast                       control findfast.cpl
      Fonts Folder                   control fonts
      Internet Properties            control inetcpl.cpl
      Joystick Properties            control joy.cpl
      Keyboard Properties            control main.cpl keyboard
      Microsoft Exchange             control mlcfg32.cpl
          (or Windows Messaging)
      Microsoft Mail Post Office     control wgpocpl.cpl
      Modem Properties               control modem.cpl
      Mouse Properties               control main.cpl
      Multimedia Properties          control mmsys.cpl
      Network Properties             control netcpl.cpl      
                                      NOTE: In Windows NT 4.0, Network
                                      properties is Ncpa.cpl # network control panel applet
      Password Properties            control password.cpl
      PC Card                        control main.cpl pc card (PCMCIA)
      Power Management (Windows 95)  control main.cpl power
      Power Management (Windows 98)  control powercfg.cpl
      Printers Folder                control printers
      Regional Settings              control intl.cpl
      Scanners and Cameras           control sticpl.cpl
      Sound Properties               control mmsys.cpl sounds
      System Properties              control sysdm.cpl
      ```

    * download using command
      - Powershell:
        1. Invoke-WebRequest:iwr, wget, curl
          ```
          wget -Uri http://www.winhelponline.com/blog/wp-content/uploads/reg/copypath.reg -OutFile copypath.reg
          ```
        2. Start-BitsTransfer:
          ```
          Start-BitsTransfer -Source http://www.winhelponline.com/blog/wp-content/uploads/reg/copypath.reg
          ```

      - cmd:
        1. bitsadmin.exe
        ```
        bitsadmin.exe /transfer regdownload /download /priority high ^
          http://www.winhelponline.com/blog/wp-content/uploads/reg/copypath.reg C:\Users\Dobly\Downloads\cmd_download\bits_copypath.reg
        ```

* [hook](https://en.wikipedia.org/wiki/Hooking)
     hooking covers a range of techniques used to alter or augment the behavior of an operating system, 
     of applications, or of other software components by intercepting function calls or messages or events passed between
      software components. Code that handles such intercepted function calls, events or messages is called a "hook".

      ILT: import lookup table
      IAT: import address table

* assembly
    1. windbg
      * [set windbg as postmortem debugger](https://msdn.microsoft.com/en-us/library/windows/hardware/ff542967(v=vs.85).aspx)
        ```
        C:\Program Files (x86)\Windows Kits\8.1\Debuggers\x64\windbg.exe –I
        C:\Program Files (x86)\Windows Kits\8.1\Debuggers\x86\windbg.exe –I

        HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AeDebug
        Debugger = "C:\Program Files (x86)\Windows Kits\8.1\Debuggers\x64\windbg.exe" -p %ld -e %ld -c ".dump /j %p /u d:\debug\AeDebug.dmp; qd" 
        Auto = 1

        HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows NT\CurrentVersion\AeDebug
        Debugger = "C:\Program Files (x86)\Windows Kits\8.1\Debuggers\x86\windbg.exe" -p %ld -e %ld –g -c ".jdinfo 0x%p"

        Debugger = "C:\Windows\system32\vsjitdebugger.exe" -p %ld -e %ld
        ```

      * dependency walker
        1. executables are just sequences of bytes
        2. symbols help debugger to:
            * map raw address to source code
            * analyze internal layout and size of app
        3. pdb -> program database
            * newest debug info format coff and codeview are deprecated
            * pdbs are stored separately from executables
            * pdb format undocumented
            * special apis work with it: dbghelp.dll MsDiaxy.dll
        
      * [fpo](https://msdn.microsoft.com/en-us/library/2kxx5t2c.aspx)

        cl /Oy(-) enable/disable frame pointer ommition, can free one register called EBP
         The /Ox (Full Optimization) and /O1, /O2 (Minimize Size, Maximize Speed) options imply /Oy. 
         Specifying /Oy– after the /Ox, /O1, or /O2 option disables /Oy, whether it is explicit or implied.
        
      * debug info
        1. linker:/pdbstripped:
           * Public functions and variables
           * FPO information
        2. Private functions and variables
        3. Source file and line information
        4. Type information
        
      * options for debug 
        * Compiler options: /Z7, /Zi, /ZI
        * Linker options: /debug, /pdb, /pdbstripped
    
      * match debug info
        * signature in executables and pdb files during building:
          1. timestamp (pdb v2.0)
          2. guid (pdb v7.0) 
        * debugger match the signature and they must be same
        * algorithm to search pdb files:
            1. try module path
            2. try name and path specified in PE header 
                ( NB10 or rsds debug header)
            3. set _NT_SYMBOLS_PATH or _NT_ALT_SYMBOLS_PATH environment variables
    
    * attach mode
      1. invasive
      2. noninvasive is usefull if:
        * app is debugging by vs, can still use windbg for debugging
        * the target application is completely frozen and 
            can't lauch the break-in thread neccessary for a true attach
    
    * dbg command
      * regular cmd used to __debug process__
        
        k lm g

      * mata or dot-commands __control the behavior of debugger__
        
        .sympath  .cls  .lastevent  .detach  .if
    
      * extention cmd 
        - implemented as export functions in extension dlls
        - large part of what makes windbg such a powerfull debugger
        - lots of preinstalled dlls: exts.dll, ntsdexts.dll, uext.dll,wow64exts.dll, kdexts.dll, ..
        - can write our own extension dll
        - !analyze !address !handle, !ped 
    
      * _NT_SOURCE_PATH environment variable
        
        .srcpath
        .srcpath+ xy
    
      * processed and thread on nt
        * each process is represented by executive process block(EPROCESS) in kernel-mode in system address space
        * each process has one or more thread represented by executables thread block(ETHREAD) in kernel-mode in system address space
        * EPROCESS points to related structs such as ETHREAD
        * EPROCESS points to PEB(process environment block) in process address space
        * ETHREAD points to TEB(thread environment block) in process address space

        * PEB = Process Environment Block
          - basic image information (base address, version numbers, module list)
          - process heap information
          - environment variables
          - command-line parameter
          - DLL search path
          - Display it: !peb, dt nt!_PEB
        * TEB = Thread Environment block
          - stack information (stack-base and stack-limit)
          - TLS (Thread Local Storage) array
          - Display it: !teb, dt nt!_TEB

    
    * set remote debug using vmware
        1. Installation
            http://www.microsoft.com/whdc/devtools/debugging/installx86.mspx
        2. Setting the symbol file path
            _NT_SYMBOL_PATH=srv*C:\Windows\Symbols*https://msdl.microsoft.com/download/symbols

            If you want to observe the process of symbol matching, you can enable verbose symbol matching by executing the command

            !sym noisy 

            Afterwards, you can force windbg to reload the symbols by typing

            .reload /f
        3. configure environment in vmware
            * windows xp:
            ```
            c:\boot.ini               

            [boot loader]
            timeout=30
            default=multi(0)disk(0)rdisk(0)partition(1)\WINDOWS
            [operating systems]
            multi(0)disk(0)rdisk(0)partition(1)\WINDOWS=”Microsoft Windows XP Professional” /fastdetect
            multi(0)disk(0)rdisk(0)partition(1)\WINDOWS=”Microsoft Windows XP Professional Debug Mode” /fastdetect /debug /debugport=COM2 /baudrate=115200 
            ```
            
            * vista and above:
            ```
            Administrator (using runas) and execute bcdedit. The format of the command is:

            bcdedit /dbgsettings DebugType [debugport:Port] [baudrate:Baud]

            1. serial debugging (using COM1 at 115200bps) it is:

                bcdedit /dbgsettings serial debugport:1 baudrate:115200

            2. 1394 (using channel 32) it is:

                bcdedit /dbgsettings 1394 CHANNEL:32

            3. USB (using “debugging” as the target name) it is:

                bcdedit /dbgsettings USB targetname:debugging

            After that, you need to enable debugging by typing:

                bcdedit /debug on

            In order to disable it later, you can type:

                bcdedit /debug off
            ```

            * create a serial port on vmware workstation:
                
                * The name of the named pipe is \\.\pipe\com_port (you can use whatever you want after \\.\pipe\)
                * The COM port number is 2 (see in the picture where it is mentioned "Serial Port 2" on the left pane)
                * The two dropboxes with this end is the server and the other end is an application.
                * According to the documentation, about "Yield CPU on Poll":
                ```
                This configuration option forces the affected virtual machine to yield processor time if the only task it
                 is trying to do is poll the virtual serial port.
                ```

        4. use debugging tools:
            windbg -k com:pipe,port=\\.\pipe\com_port,resets=0,reconnect
            kd -k com:pipe,port=\\.\pipe\com_port,resets=0,reconnect

            * reference:
                http://stackoverflow.com/questions/33820520/kernel-debug-with-a-vmware-machine
                https://blogs.msdn.microsoft.com/iliast/2006/12/11/windbg-tutorials/
    * use windbg debug a process in kernel debug [https://blogs.msdn.microsoft.com/iliast/2008/02/01/debugging-user-mode-processes-using-a-kernel-mode-debugger/]
        * !process 0 0
            ```
            PROCESS 81ddd220  SessionId: 3  Cid: 0724    Peb: 7ffdf000  ParentCid: 0200
                DirBase: 0e013000  ObjectTable: e1272418  HandleCount: 148.
                Image: winlogon.exe

            PROCESS 81ab43a8  SessionId: 0  Cid: 065c    Peb: 7ffdf000  ParentCid: 0258
                DirBase: 0f65a000  ObjectTable: e1ac6750  HandleCount:  88.
                Image: rdpclip.exe

            PROCESS 81b0c370  SessionId: 3  Cid: 06dc    Peb: 7ffdf000  ParentCid: 0724
                DirBase: 1019b000  ObjectTable: e1288098  HandleCount: 136.
                Image: logonui.exe

            PROCESS 81ea9da8  SessionId: 0  Cid: 02c8    Peb: 7ffdf000  ParentCid: 0710
                DirBase: 10cd4000  ObjectTable: e1639768  HandleCount:  21.
                Image: calc.exe
            ```

        * .process /i 81ea9da8  # After you press “g”, you have to wait for the windows scheduler to do the context switch.
           .process /r /p 85709738 #  the debugger does the context switch immediately (as opposed to the windows scheduler) and there is no waiting time.  

        * lm 
        
        * x calc!gpsz*
          01014db0 calc!gpszNum = <no type information>
        * dd calc!gpszNum l1
          01014db0  00098f38
        * du 98f38 # unicode characters
          00098f38  "58746921."
        * r eip=40103a
        * tr # step in
        * pr # step over

* software debugging
    * catagory
        1. target environment 
            windows, linux, macOS, etc
            for language run in vm such as java and .net
        2. taget code 
            * native debugging
            * inter-op debugging (混合)
            * script debugging
        3. target excute mode
            * user mode debugging
            * kernel mode debugging
        4. debugger and target location
            * local debugging
            * remote debugging
        5. target activity
            * live target debugging
            * dump file debbugging
        6. debugging tools
    * break point:
        1. set space 
            * code bk
            * data bk
            * I/O bk
        2. set method
            * software break: IA32 INT 3 , only for code breakpoint
            * hardware break: debugging registers: DR0-DR7
        3. others
            * tracepoint
            * condition breakpoint 
    * step by step:
        1. a assembly instruction:
            * IA32: set trap flag to genarate INT 1
        2. a phrase in src code: 
        3. a branch:
            set dbgctl msr btf(branch trap flag), set tf 
        4. a task:
            set TSS(task status segment) T to 1
    * method    
        * print
        * log
        * event trace
        * dump
        * stack backtrace
        * disassemble
        * watch and modify data
        * control the process and thread debugging on

    * basic procedure
       1. replay fault
       2. locate the root cause
       3. explore and implement a solution
       4. verify the solution
    * tools
       bugzilla
    * cost 
       period          | cost
       ------          | ----
       requirement     | 2
       design          | 5
       coding          | 10
       developing test | 20
       acceptance test | 50
       run             | 150
    * debug and test 
       * test: find defect
       * debug: find root cause
    * cpu debug support 
        1. INT 3
        2. EFLAGS TF
        3. DR0-DR7
        4. breakpoint exception(#BP): INT 3
        6. debugpoint exception(#DP): deubgging events cause by others except int 3
        7. tss T flag: task trap flag 
        8. branck record: record address of branch, interrupts or exceptions before
        9. performance monitor: monitor and optimize cup and software
        10. JTAG:  Joint Test Action Group 
    * IA32
        1. 4GB
        2. flat memory model
        3. paging
        4. debugging registers
        5. virtual 8086
        6. SMM: system management mode include power management, hardware control and other firmware
        7. MMX: multimedia extention, SIMD
        8. APIC: local and io
        9. msr: model specific registers, rdmsr  wrmsr
        10. mtrr: memory type and range register: UC(unreachable), WC(write-combine), WT(write-throght), WP(write-protect)
        11. SSE: Stream SIMD extentio
    
    * int 3: software breakpoint
      - breakpoint on code, not suitable for data or I/O.
      - can't add breakpoint to ROM, use hard interrupt
      - can't work when IDT or IVT being destroyed, use hard level debugging tools
    
    * hardware breakpoint
      - IA32 debug registers dr0-dr7
        - dr4, dr5 are reserved, when debug extension enables(cr4 DE=1), access dr4 or dr5 cause 
          undefined instruction(#UD), when disabled, dr4 and dr5 are alias of dr6 and dr7 seperately
        
        - 4 32-bit address regester dr0-dr3: 
          - 64bit on 64-bit system
          - Specifies the addresses of up to 4 breakpoints
          - 
        - 1 32-bit status  register dr6: high 32 reserved on 64-bit system
        - 1 32-bit control register dr7: high 32 reserved on 64-bit system


# registry
  * structures
    1. https://blogs.technet.microsoft.com/ganand/2008/01/05/internal-structures-of-the-windows-registry/
    2. https://technet.microsoft.com/library/cc750583.aspx
    3. https://support.microsoft.com/en-us/help/256986/windows-registry-information-for-advanced-users
  
  * location
    * %SystemRoot%\System32\Config folder on Windows NT 4.0, Windows 2000, Windows XP, Windows Server 2003, and Windows Vista.
    * HKEY_CURRENT_USER are in the %SystemRoot%\Profiles\Username folder
      ```
      Registry hive	Supporting files
      HKEY_LOCAL_MACHINE\SAM	Sam, Sam.log, Sam.sav
      HKEY_LOCAL_MACHINE\Security	Security, Security.log, Security.sav
      HKEY_LOCAL_MACHINE\Software	Software, Software.log, Software.sav
      HKEY_LOCAL_MACHINE\System	System, System.alt, System.log, System.sav
      HKEY_CURRENT_CONFIG	System, System.alt, System.log, System.sav, Ntuser.dat, Ntuser.dat.log
      HKEY_USERS\DEFAULT	Default, Default.log, Default.sav
      ```

# windows internal
  1. subsystem
    * csrss - client/server runtime subsystem
