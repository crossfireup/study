# reference
    Windows NT File System Internals : OSR Classic Reprints
    Troubleshooting with the Windows Sysinternals Tools          
    https://msdn.microsoft.com/en-us/windows/hardware/drivers/gettingstarted/index
    https://msdn.microsoft.com/en-us/windows/hardware/drivers/network/roadmap-for-developing-ndis-protocol-drivers

# windows tools:
    - package
      - sysinternals
      - windows resource tool
      - SUA
      - cygwin
      - mingwin
      - support tools
      - sdk
      - ddk
    
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

      schtask /create -ru 
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

      wmic process get commandline | grep java

      WMIC /OUTPUT:C:\Process.txt path win32_process get Caption,Processid,Commandline

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

      net user administrator /active:yes
      net user administrator <passwd>
      net user administrator /active:no
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

      net use \\192.168.2.128\admin$ /user:dolphin-xp-sp3\dolphin
      ```

    * doskey
      ```
      doskey /histroy 
      where ls
      C:\Windows\SUA\common\ls.exe
      doskey /overstrike ll=C:\Windows\SUA\common\ls -l
      ll 
    
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

      file share     fsmgmt.msc
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

    * [Event Tracing for Windows (ETW)](https://msdn.microsoft.com/en-us/magazine/ee412263.aspx)
      xperf.exe
      C:\etl> xperf -help start
      C:\etl> xperf -help stop

      - logman

      - tracerpt(trace report)

    * systrace
      - logger.exe
      - wt(trace and watch data) in windbg

    * assoc and ftype
      ```
      C:\>assoc .pcap
      .pcap=wireshark-capture-file

      C:\>ftype wireshark-capture-file
      wireshark-capture-file="C:\Program Files\Wireshark\Wireshark.exe" "%1"

      C:\>assoc .dump
      File association not found for extension .dump

      C:\>assoc .dump=wireshark-capture-file
      .dump=wireshark-capture-file

      Type:
        ASSOC .pl=PerlScript FTYPE PerlScript=perl.exe %1 %* 

      To invoke the Perl script, type:
        script.pl 1 2 3 

      To eliminate the need to type the extensions, type:
       set PATHEXT=.pl;%PATHEXT% 
      ```

    - packege
      ```
      pkgmgr
      msiexec
      ```
    - cmd 
      ```
      setx - Set environment variables permanently, SETX can be used to set Environment Variables for the machine (HKLM) or currently logged on user (HKCU).
      setx /M PATH "%PATH%;<your-new-path>"
      subst - Substitute a drive letter for a network or local path.

      pathman
      ```

    - cacls
      ```
      cacls c:\windows /G guest:RW
      icacls


# sysinternals
    * get open files 
      - handle -u Administrator
      - handle -p cmd

    * procexp
      ```
      # run as administrator
      "C:\Program Files\SysInternals\procexp.exe" /e /t


      # registry
      Windows Registry Editor Version 5.00

      [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe]
      "Debugger"="\"C:\\PROGRAM FILES\\SYSINTERNALS\\PROCEXP.EXE\" /e"
      ```

    - regjump
      ```
      regjump HKLM\SOFTWARE\MICROSOFT\WINDOWS NT\CURRENTVERSION\DIGITALPRODUCTID
      reg query "HKLM\SOFTWARE\MICROSOFT\WINDOWS NT\CURRENTVERSION" /v DIGITALPRODUCTID
      ```

    - sysmon
      - config.xml
        ```
        <?xml version="1.0"?>
        <Sysmon schemaversion="3.20">
        <EventFiltering>
            <!-- <HashAlgorithms>*</HashAlgorithms> -->
        <NetworkConnect onmatch="include">
            <Image condition="contains">chrome.exe</Image>
            <Image condition="contains">iexplore.exe</Image>
            <Image condition="contains">firefox.exe</Image>
            <Image condition="contains">MicrosoftEdgeCP.exe</Image>
            <Image condition="contains">MicrosoftEdge.exe</Image>
            <Image condition="contains">explorer.exe</Image>
            <DestinationPort condition="is">80</DestinationPort>
            <DestinationPort condition="is">443</DestinationPort>
            <DestinationPort condition="is">8080</DestinationPort>
        </NetworkConnect>

        <ProcessCreate onmatch="include">
            <Image condition="contains">procexp.exe</Image>
        </ProcessCreate>
        <ProcessTerminate onmatch="exclude">
        </ProcessTerminate>

        </EventFiltering>
        </Sysmon>
        ```

      - Management 
        ``` 
        # install
        sysmon -i -accepteula config.xml
        # update
        sysmon -c config.xml
        # uninstall
        sysmon -u 
        ```

      - query event log
        ```
        wevtutil qe Microsoft-Windows-Sysmon/Operational /f:text
        eventvwr.msc
        ```

# common useful gui 
  - godmod
    ```
    mkdir .{ED7BA470-8E54-465E-825C-99712043E01C}
    rmdir ".{ED7BA470-8E54-465E-825C-99712043E01C}"
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
        ```
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
        ```
        .srcpath
        .srcpath+ xy
        .syspath+ c:\symblos\
        ```

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
    
    * common usage
      - remote debugging through tcp
        - server:
          ```
          .server tcp:port=5555

          dbgsvc -t tcp:port=5555
          ```
        
        - client:
          ```
          windbg -remote tcp:port=5555,server=192.168.1.1
          ```

    * breakpoints 
      - Viewing Set Breakpoints
        ```
        To view each of the breakpoints that have been set, you can use the bl (Breakpoint List) command.

        0:000> bl
        0 e 00523689 e 1 0001 (0001)  0:**** notepad!WinMainCRTStartup

        Here we have one breakpoint defined, the entry is broken into a few columns:

            0 - Breakpoint ID
            e - Breakpoint Status - Can be enabled or disabled.
            00523689 - Memory Address
            e 1 - Memory address access flags (execute) and size - For hardware breakpoints only
            0001 (0001) - Number of times the breakpoint is hit until it becomes active with the total passes in parentheses (this is for a special use case)
            0:**** - Thread and process information, this defines it is not a thread-specific breakpoint
            notepad!WinMainCRTStartup - The corresponding module and function offset associated with the memory address
        ```

      - break on access
        – bl – List existing breakpoints. Each breakpoint listed has a number in the list.
        – bc * : Clear all breakpoints.
        – bc number : Clear breakpoint identified by number.
        – be number : Enable breakpoint identified by number.
        – bd number : Disable breakpoint identified by number.
        – bp `module!source.c:20` : Set breakpoint at source.c line 20 in module.
        – bm module!pattern* : Set a breakpoint on symbols starting with pattern in module.
        – bu module!function : Set a breakpoint on function as soon as module is loaded.
        – ba r4 variable : Set a breakpoint for read access on 4 bytes of variable.
        – ba w4 address : Set a breakpoint for write access on 4 bytes at address.
        – bp @@(class::method) : Break on method defined in class. Useful if the same method is overloaded and thus present on several addresses.
        – bp module!function /1 : Trigger only once a breakpoint at function in module.
        – bp module!function k : Hit breakpoint at function in module after k-1 passes.
        – ba w4 address “k;g” : Display call stack every write access on 4 bytes at address.
        – bu module!function “.dump C:\Dump.dmp; g” : Create a dump in C:\Dump.dmp every time breakpoint at function in module is hit.
        – bp /t thread : Set a kernel mode breakpoint that only triggers when hit in the context of the associated thread.
        – bp /p process : Set a kernel mode breakpoint that only triggers when hit in the context of the associated process.
        -.logopen FilePath; .bpcmds; .logclose : Save breakpoints to FilePath.
        – $<FilePath : Reload breakpoints from FilePath.
        ```
        ba e 1 0x7c234ef

        be 
        bd
        bc
        ```

    * excpetions: sx
      - excepion or event occurs

      - breaking on module load
        ```
        sxe ld IMM32.dll
        ```
      - ignore exceptions enabled
        ```
        sxi ld IMM32.dll
        ```

      - Display Exception Record
	      ```
        .exr -1
        ```

    *  trace and stepping
      - go
        – g : Start executing the given process or thread.
        – g `:number`; ? poi(variable); g : Executes the current program to source line number, print the value of variable then resume execution.
        – gc : Resume execution from a conditional breakpoint.
        – gu : Execute until the current function is complete.
        – gh : Go with Exception Handled.
        – gn : Go with Exception Not Handled.

      - step into
        ```
        tc
        tt
        tr
        ```
      - step over
        – pr : Toggle displaying of registers.
        – p count “kb” : Step through count source lines then execute “kb”.
        – pc : Step to next CALL instruction.
        – pt – Steps through until the next return instruction.
        – pa address : Step until address is reached.

      - step out
        ```
        gu # go util functions return
        ```

    * Call stack
      – k : Display call stack.
      – kn : Display call stack with frame numbers.
      – kb : Display call stack with first three parameters passed to each function.
      – kb FrameCount : Display first FrameCount frames only.
      – kp : Display all of the parameters for each function that is called in the stack trace.
      – kn : Display frame numbers.

      – !findstack symbol 2 : Display all stacks that contain symbol.

      – .frame : Show current frame.
      – .frame FrameNumber : Set frame FrameNumber for the local context.
      – .frame /r FrameNumber : Display registers in frame FrameNumber.

      – !running -ti : Dump the stacks of each thread that is running on all processors.
      – !stacks : Give a brief summary of the state of every thread.

    * Heap
      – dt ntdll!_HEAP : Dump _HEAP structure.
      – !heap : List all heaps with index and Heap address.
      – !heap -h : List all of the current process heap with start and end addresses.
      – !heap -h HeapIndex : Display detailed heap information for heap with index HeapIndex.
      – !heap -s 0 : Display summary for all heaps including reserved and committed memory …
      – !heap -flt s 0x50 : Display all of the allocations of size 0x50.
      – !heap -stat -h address : Display heap usage statistics for HeapHandle is equal to address.
      – !heap -b alloc tag HeapIndex : Breakpoint in heap with index HeapIndex on HeapAlloc calls with TAG equal to tag.
      – !heap -p -all : Display details of all allocations in all heaps in the process.
      – !heap -l : Make the debugger detect leaked heap blocks.

    * registers
      – rm ? : Show possible Mask bits.
      – rm 1 : Enable integer registers only.
      – r : Display the integer registers.
      – r eax, edx : Display only eax and edx.
      – r eax=5, edx=6 : Assign new values to eax and edx.
      – r eax:1ub : Display only the first byte from eax.
      – rF : Display the floating-point register.

    * variables 
      – dv /t /i /V : Dump local variables with type information, addresses and EBP offsets and classify them into categories.
      – dt module!pattern* -v -s Length : List with verbose output all variables that begin with pattern in module that have Length bytes size.

      – dt ntdll!_PEB : Dump _PEB structure.
      – dt module!struct : Show fields of the structure struct defined in module with their offsets and types.
      – dt module!struct -rCount : Dump fields of the structure struct defined in module recursively for Count levels.

      – dt module!struct var. : Dump var defined in strcut in module and expand its subfields.
      – dt module!struct var.. : Expand subfields of var defined in strcut in module for 2 levels.

    * memory
      – dd address : Display double-words at address.
      – dd address LLength: Display Length double-words at address.
      – du address : Display unicode chars at address.
      – du address LLength : Display Length unicode chars at address.
      – !mapped_file address : Display name of file that contains address.
      – !address : Show all memory regions of our process.
      – !address address : Retreive inforamation about a region of memory at address.

      – eb address value : Set byte at address to value.
      – ew address value : Set word at address to value.
      – ed address value : Set double-word at address to value.

      – ds /c width address : Display width chars at address.
      – dS /c width address : Display width unicode chars at address.

      – c address1 LLength address2 : Compare Length bytes at address1 with address2.
      – m address1 LLength address2 : Move Length bytes at address1 to address2.
      – f address LLength ‘A’ ‘B’ ‘C’ – Fill memory location from address to address + Length – 1 with the pattern “ABC”, repeated as many times as necessary.

      – s -a address LLength “pattern” : Search memory location from address to address + Length – 1 for pattern.
      – s -wa address LLength “pattern” : Search only writable memory from address to address + Length – 1 for pattern.

      – !poolused : Display memory use summaries, based on the tag used for each pool allocation.
      – !vm : Display summary information about virtual memory use statistics on the target system.

      – u address : Unassemble code at address.

    * Memory dump
      – .dump FileName : Dump small memory image into FileName.
      – .dump /ma FileName : Dump complete memory image into FileName.

    * Locks
      – !locks : Display all kernel mode locks held on resources by threads.
      – !qlocks : Display the state of all queued spin locks.

    * Extension DLLs
      – .load ExtensionDLL : Load the extension DLL ExtensionDLL into the debugger.
      – .unload ExtensionDLL : Unload the extension DLL ExtensionDLL.
      
      – .chain : List all extensions that the debugger has loaded.
      – .unloadall : Unload all extension DLLs from the debugger.
      – .setdll ExtensionDLL : Change the default extension DLL to ExtensionDLL for the debugger

    * Application Verifier
      – !avrf : Display a variety of output produced by Application Verifier. If a Stop has occurred, reveal the its nature and what caused it.
      – !verifier 0xf : Display the status of Driver Verifier and its actions.
      – !verifier 0x80 address : Display log associated with the specified address within the kernel pool Allocate and Free operations.
      – !verifier 0x100 address : Display log associated with the IRP at address.

    * calculator
      ```
      ?bc28 + cdf234e * 2
      ```

    * analyze
      – !analyse -v : Display verbose information about the current exception or bug check.
      – !analyze -show BugCheckCode : Display information about BugCheckCode bug check code.
      - !analyze -v -hang

    * debug info
      ```
      # a unofficial undocumented command
      .dumpdebug 

      !ready
      ```

    * peb(Prototype Debugger Extension)
      ```
      # grep filter
      !grep exe !peb
    
    * set remote debug using vmware
        1. [Installation](http://www.microsoft.com/whdc/devtools/debugging/installx86.mspx)

        2. Setting the symbol file path
            ```
            _NT_SYMBOL_PATH=srv*C:\Windows\Symbols*https://msdl.microsoft.com/download/symbols

            # If you want to observe the process of symbol matching, you can enable verbose symbol matching by executing the command
            !sym noisy 

            # Afterwards, you can force windbg to reload the symbols by typing
            .reload /f
            ```
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
    
    * enable local kernel debug 
      - add a new boot entry
        ```
        bcdedit /v
          Windows Boot Loader
          -------------------
          identifier              {b8b48bdb-0c8d-11e6-9f5f-b012a345769a}
          device                  partition=C:
          path                    \Windows\system32\winload.exe
          description             Windows 7 Enterprise
          locale                  en-US
          inherit                 {6efb52bf-1766-41db-a6b3-0ee5eff72bd7}
          recoverysequence        {2acc94f3-0d0c-11e6-a124-936c4ff2683c}
          recoveryenabled         Yes
          osdevice                partition=C:
          systemroot              \Windows
          resumeobject            {b8b48bda-0c8d-11e6-9f5f-b012a345769a}
          nx                      OptIn
          bootlog                 Yes
          sos                     Yes

        bcdedit /copy {b8b48bdb-0c8d-11e6-9f5f-b012a345769a} -d "Windows 7 Enterprise With Debug On"
          The entry was successfully copied to {9ee65318-1029-11e6-bdc5-d24cbb4066ca}.

        bcdedit /v
          Windows Boot Loader
          -------------------
          identifier              {9ee65318-1029-11e6-bdc5-d24cbb4066ca}
          device                  partition=C:
          path                    \Windows\system32\winload.exe
          description             Windows 7 Enterprise With Debug On
          locale                  en-US
          inherit                 {6efb52bf-1766-41db-a6b3-0ee5eff72bd7}
          recoverysequence        {2acc94f3-0d0c-11e6-a124-936c4ff2683c}
          recoveryenabled         Yes
          osdevice                partition=C:
          systemroot              \Windows
          resumeobject            {b8b48bda-0c8d-11e6-9f5f-b012a345769a}
          nx                      OptIn
          bootlog                 Yes
          sos                     Yes
        ```

      - set debug on new boot entry and make it as default boot entry
        ```
        bcdedit /debug  {9ee65318-1029-11e6-bdc5-d24cbb4066ca} on
        # windows 10
        bcdedit /set {9ee65318-1029-11e6-bdc5-d24cbb4066ca} local 
        
        bcdedit /default {9ee65318-1029-11e6-bdc5-d24cbb4066ca}
        bcdedit /timeout 16

        bcdedit /v
        ```

      - restart computer
        ```
        shutdown /g
        ```
      
      - start local debuggin
        ```
        windgb -kl
        kd -kl      
        ```

      - referrence
        http://www.microsoft.com/whdc/system/platform/firmware/bcd.mspx
        Local Kernel-Mode Debugging - windbg help documentation
  
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

        * lm v m calc*
        
        * x calc!gpsz*
          01014db0 calc!gpszNum = <no type information>
        * dd calc!gpszNum l1
          01014db0  00098f38
        * du 98f38 # unicode characters
          00098f38  "58746921."
        * r eip=40103a
        * tr # step in
        * pr # step over
        * pc, pt, pct # step to next call or return
        * q, qd # quit, detach
    
    - BSOD debugging using windbg
      - set windows to enable full memory dump on crash
        ```
        sysdm.cpl
        advanced -> startup and recovery ->  settings 
          automate restart 
          kernel memory dump
          dump file :%SystemRoot%\MEMORY.DMP
        ```

      - set _NT_SYMBOLS_PATH
        ```
        setx /m _NT_SYMBOL_PATH "srv*C:\Windows\Symbols*https://msdl.microsoft.com/download/symbols"
        ```
      
      - open dump file in windbg

      - analyze
        ```
        2: kd> !analyze -v
         *******************************************************************************
         *                                                                             *
         *                        Bugcheck Analysis                                    *
         *                                                                             *
         *******************************************************************************
         
         SYSTEM_THREAD_EXCEPTION_NOT_HANDLED (7e)
         This is a very common bugcheck.  Usually the exception address pinpoints
         the driver/function that caused the problem.  Always note this address
         as well as the link date of the driver/image that contains this address.
         Arguments:
         Arg1: ffffffffc0000005, The exception code that was not handled
         Arg2: fffff880034422bf, The address that the exception occurred at
         Arg3: fffff8801ad237c8, Exception Record Address
         Arg4: fffff8801ad23020, Context Record Address
         
         Debugging Details:
         ------------------
         DUMP_CLASS: 1
         DUMP_QUALIFIER: 401
         BUILD_VERSION_STRING:  7601.23572.amd64fre.win7sp1_ldr.161011-0600
         DUMP_TYPE:  1
         BUGCHECK_P1: ffffffffc0000005
         BUGCHECK_P2: fffff880034422bf
         BUGCHECK_P3: fffff8801ad237c8
         BUGCHECK_P4: fffff8801ad23020
         EXCEPTION_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.
         FAULTING_IP: 
         nm3!NetmonOidRequestComplete+53
         fffff880`034422bf 894734          mov     dword ptr [rdi+34h],eax
         
         EXCEPTION_RECORD:  fffff8801ad237c8 -- (.exr 0xfffff8801ad237c8)
         ExceptionAddress: fffff880034422bf (nm3!NetmonOidRequestComplete+0x0000000000000053)
            ExceptionCode: c0000005 (Access violation)
           ExceptionFlags: 00000000
         NumberParameters: 2
            Parameter[0]: 0000000000000000
            Parameter[1]: ffffffffffffffff
         Attempt to read from address ffffffffffffffff
         
         CONTEXT:  fffff8801ad23020 -- (.cxr 0xfffff8801ad23020)
         rax=0000000000000000 rbx=fffffa801d577fb0 rcx=0000000073656c74
         rdx=fffffa801d577fb0 rsi=00000000c000000d rdi=7665442820352066
         rip=fffff880034422bf rsp=fffff8801ad23a00 rbp=fffffa8014a1aa10
          r8=00000000c000000d  r9=0000000000000000 r10=fffff88002257fa0
         r11=0000000000000000 r12=fffffa80162411c0 r13=00000000c0000001
         r14=0000000000000000 r15=fffff88001ac9110
         iopl=0         nv up ei pl nz na po nc
         cs=0010  ss=0018  ds=002b  es=002b  fs=0053  gs=002b             efl=00010206
         nm3!NetmonOidRequestComplete+0x53:
         fffff880`034422bf 894734          mov     dword ptr [rdi+34h],eax ds:002b:76654428`2035209a=????????
         Resetting default scope
         
         CPU_COUNT: 4
         CPU_MHZ: 9be
         CPU_VENDOR:  GenuineIntel
         CPU_FAMILY: 6
         CPU_MODEL: 3a
         CPU_STEPPING: 9
         CPU_MICROCODE: 6,3a,9,0 (F,M,S,R)  SIG: 12'00000000 (cache) 12'00000000 (init)
         DEFAULT_BUCKET_ID:  WIN7_DRIVER_FAULT
         PROCESS_NAME:  System
         CURRENT_IRQL:  0
         ERROR_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.

         EXCEPTION_CODE_STR:  c0000005
         EXCEPTION_PARAMETER1:  0000000000000000
         EXCEPTION_PARAMETER2:  ffffffffffffffff

         FOLLOWUP_IP: 
         nm3!NetmonOidRequestComplete+53
         fffff880`034422bf 894734          mov     dword ptr [rdi+34h],eax
         READ_ADDRESS:  ffffffffffffffff 
         
         STACK_TEXT:  
         fffff880`1ad23a00 fffff880`0344224c : 00000000`00000103 00000000`105469a0 fffffa80`14a1aa10 fffff880`1ad23a60 : nm3!NetmonOidRequestComplete+0x53
         fffff880`1ad23a30 fffff880`01aee582 : fffffa80`1d577fb0 fffffa80`14a71c80 00000000`0001010e fffffa80`14b4f870 : nm3!NetmonOidRequest+0x124
         fffff880`1ad23a60 fffff880`01a6d44c : fffffa80`00000000 fffff880`01ac9110 fffffa80`14b4f870 fffffa80`14a71c80 : ndis!ndisFDoOidRequest+0x222
         fffff880`1ad23b30 fffff800`01ece355 : fffff880`01a6d400 fffff800`0206e280 fffffa80`11985460 fffffa80`00000002 : ndis!ndisDoOidRequests+0x4c
         fffff880`1ad23b70 fffff800`02160236 : 00000000`00000000 fffffa80`11985460 00000000`00000080 fffffa80`0cdceb10 : nt!ExpWorkerThread+0x111
         fffff880`1ad23c00 fffff800`01eb6706 : fffff880`02257180 fffffa80`11985460 fffffa80`11cecb50 fffff880`1c91e380 : nt!PspSystemThreadStartup+0x5a
         fffff880`1ad23c40 00000000`00000000 : fffff880`1ad24000 fffff880`1ad1e000 fffff880`1ad238a0 00000000`00000000 : nt!KxStartSystemThread+0x16
         
         
         SYMBOL_STACK_INDEX:  0
         
         SYMBOL_NAME:  nm3!NetmonOidRequestComplete+53
         
         FOLLOWUP_NAME:  MachineOwner
         
         MODULE_NAME: nm3
         
         IMAGE_NAME:  nm3.sys
         
         DEBUG_FLR_IMAGE_TIMESTAMP:  4c102c5f
         
         STACK_COMMAND:  .cxr 0xfffff8801ad23020 ; kb
         
         FAILURE_BUCKET_ID:  X64_0x7E_nm3!NetmonOidRequestComplete+53
         
         BUCKET_ID:  X64_0x7E_nm3!NetmonOidRequestComplete+53
         
         PRIMARY_PROBLEM_CLASS:  X64_0x7E_nm3!NetmonOidRequestComplete+53
      ```
    
    # get thread info
      ```
      2: kd> !thread
        THREAD fffffa8011985460  Cid 0004.1828  Teb: 0000000000000000 Win32Thread: 0000000000000000 RUNNING on processor 2
        Not impersonating
        DeviceMap                 fffff8a000008540
        Owning Process            fffffa800cdceb10       Image:         System
        Attached Process          N/A            Image:         N/A
        Wait Start TickCount      176719         Ticks: 0
        Context Switch Count      440176         IdealProcessor: 1             
        UserTime                  00:00:00.000
        KernelTime                00:00:05.397
        Win32 Start Address nt!ExpWorkerThread (0xfffff80001ece244)
        Stack Init fffff8801ad23c70 Current fffff8801ad238a0
        Base fffff8801ad24000 Limit fffff8801ad1e000 Call 0000000000000000
        Priority 13 BasePriority 13 PriorityDecrement 0 IoPriority 2 PagePriority 5
        Child-SP          RetAddr           : Args to Child                                                           : Call Site
        fffff880`1ad227f8 fffff800`0223bf24 : 00000000`0000007e ffffffff`c0000005 fffff880`034422bf fffff880`1ad237c8 : nt!KeBugCheckEx
        fffff880`1ad22800 fffff800`021f9745 : fffff800`0206e298 fffff800`01ebae42 000067ef`269255d6 fffffa80`11985460 : nt!PspUnhandledExceptionInSystemThread+0x24
        fffff880`1ad22840 fffff800`01ef0cb4 : 00000000`00000000 00000000`00000000 fffffa80`14dea000 fffff800`02058580 : nt! ?? ::NNGAKEGL::`string'+0x21dc
        fffff880`1ad22870 fffff800`01ef072d : fffff800`0202b3d0 fffff880`1ad23c00 00000000`00000000 fffff800`01e55000 : nt!_C_specific_handler+0x8c
        fffff880`1ad228e0 fffff800`01eef505 : fffff800`0202b3d0 fffff880`1ad22958 fffff880`1ad237c8 fffff800`01e55000 : nt!RtlpExecuteHandlerForException+0xd
        fffff880`1ad22910 fffff800`01f00a05 : fffff880`1ad237c8 fffff880`1ad23020 fffff880`00000000 76654428`00000007 : nt!RtlDispatchException+0x415
        fffff880`1ad22ff0 fffff800`01ec4a82 : fffff880`1ad237c8 fffffa80`1d577fb0 fffff880`1ad23870 00000000`c000000d : nt!KiDispatchException+0x135
        fffff880`1ad23690 fffff800`01ec338a : 00000000`00000005 fffff880`01aee7c1 fffffa80`14b4e820 00000000`00000005 : nt!KiExceptionDispatch+0xc2
        fffff880`1ad23870 fffff880`034422bf : ffff0000`1b7ea80e 00000000`00000001 00000000`00000000 fffffa80`14a1aa10 : nt!KiGeneralProtectionFault+0x10a (TrapFrame @ fffff880`1ad23870)
        fffff880`1ad23a00 fffff880`0344224c : 00000000`00000103 00000000`105469a0 fffffa80`14a1aa10 fffff880`1ad23a60 : nm3!NetmonOidRequestComplete+0x53
        fffff880`1ad23a30 fffff880`01aee582 : fffffa80`1d577fb0 fffffa80`14a71c80 00000000`0001010e fffffa80`14b4f870 : nm3!NetmonOidRequest+0x124
        fffff880`1ad23a60 fffff880`01a6d44c : fffffa80`00000000 fffff880`01ac9110 fffffa80`14b4f870 fffffa80`14a71c80 : ndis!ndisFDoOidRequest+0x222
        fffff880`1ad23b30 fffff800`01ece355 : fffff880`01a6d400 fffff800`0206e280 fffffa80`11985460 fffffa80`00000002 : ndis!ndisDoOidRequests+0x4c
        fffff880`1ad23b70 fffff800`02160236 : 00000000`00000000 fffffa80`11985460 00000000`00000080 fffffa80`0cdceb10 : nt!ExpWorkerThread+0x111
        fffff880`1ad23c00 fffff800`01eb6706 : fffff880`02257180 fffffa80`11985460 fffffa80`11cecb50 fffff880`1c91e380 : nt!PspSystemThreadStartup+0x5a
        fffff880`1ad23c40 00000000`00000000 : fffff880`1ad24000 fffff880`1ad1e000 fffff880`1ad238a0 00000000`00000000 : nt!KxStartSystemThread+0x16
      
      #display words and symbos
      - dds displays double-word (4 byte) values like the dd command. 
      - dqs displays quad-word (8 byte) values like the dq command. 
      - dps displays pointer-sized values (4 byte or 8 byte, depending on the target computer's architecture) like the dp command.

      # Base fffff8801ad24000 Limit fffff8801ad1e000 Call 0000000000000000
      dps fffff8801ad1e000 fffff8801ad24000
      ```

    - 


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

(3b34.294c): Access violation - code c0000005 (!!! second chance !!!)


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

  * [add ida association](https://msdn.microsoft.com/en-us/library/windows/desktop/cc144171(v=vs.85).aspx)
    ```
    Windows Registry Editor Version 5.00

    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x86]
    @="Open with IDA pro(x&86)"

    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x86\Icon]
    @="\"C:\\Program Files (x86)\\IDA 6.8\\idaq.exe\",0"

    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x86\command]
    @="\"C:\\Program Files (x86)\\IDA 6.8\\idaq.exe\" \"%1\" "


    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x64]
    @="Open with IDA pro(x&64)"

    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x64\Icon]
    @="\"C:\\Program Files (x86)\\IDA 6.8\\idaq64.exe\",0"

    [HKEY_CLASSES_ROOT\exefile\shell\IDA_pro_x64\command]
    @="\"C:\\Program Files (x86)\\IDA 6.8\\idaq64.exe\" \"%1\" "
    ```
  

# [network tracing in windows](https://msdn.microsoft.com/en-us/library/windows/desktop/dd569136(v=vs.85).aspx)
  - network tracing architecture
    - ![architecture](img/network_tracing_architecture.png)

  - start trace
    ```
    # trace
    netsh trace show scenarios 
    netsh trace show providers (show all including ones not relevant to network)
    netsh trace show scenarios internetclient
    netsh trace start scenarios=FileSharing scenarios=DirectAccess
    netsh trace start scenarios=wlan provider=Microsoft-Windows-Dhcp-client
    ```
    # two files are generated by default: 
      - an Event Trace Log (ETL) file (default nettrace.etl)

        - Trace events are collected in the ETL file, which can be viewed using tools such as Network Monitor
        
        - tracefile=filename.etl # set filename

      - a .cab file.(default nettrace.cab): report.etl, report.html

        - rich information about the software and hardware on the system such as the adapter information, 
          build, operating system, and wireless settings. 

        - Report.etl is another copy of the same information included in nettrace.etl. 

        - report.html file includes additional information about the trace events and the other information collected.

        - recieve most info avalaible , set 
          report=yes
    
    # using filter
      ```
      netsh trace start InternetClient provider=Microsoft-Windows-TCPIP level=5 keywords=ut:ReceivePath,ut:SendPath.
      ```
      Level	|    Setting	     |  Description
      ----- |    -------       |  ----------
      1	    |    Critical	     |  Only critical events will be shown.
      2	    |    Errors	       |  Critical events and errors will be shown.
      3	    |    Warnings	     |  Critical events, errors, and warnings will be shown.
      4	    |    Informational |	Critical events, errors, warnings, and informational events will be shown.
      5	    |    Verbose	     |  All events will be shown.

      - show provider filter
        ```
        # specific provider can be found by typing netsh trace show provider 
        netsh trace show provider Microsoft-Windows-TCPIP
        ```

      - packet filtering capability
        ```
        netsh trace start capture = yes ipv4.address 
        netsh trace show capturefilterHelp
        ```

    # stop trace
      ```
      netsh trace stop
      ```
  # tools
    - Service Trace Viewer Tool (SvcTraceViewer.exe)
    - Windows and SQL Server Network Monitor Parsers 

# [software tracing](https://msdn.microsoft.com/en-us/windows/hardware/drivers/devtest/survey-of-software-tracing-tools)
  1. tracing related concept
    - trace provider: a user-mode application or kernel-mode driver that uses Event Tracing for Windows (ETW) technology to 
      generate trace messages or trace events

    - trace log: event trace log(.etl) stores the trace message generated during one or more trace sessions

  2. tools in Windows driver kits or windows software kits
    - controlling trace sessions(trace controller)
      - traceview.exe is GUI-base __trace-controller__ and __trace-consumer__ especially for real-time display of trace messages,
        It enables, configures, starts, updates, and stops trace session. This tool also formats, filters, and displays trace messages 
        from real-time trace sessions and trace logs.

      - tracelog.exe is command-line __trace controller__ that enables, configures, starts, updates, and stops real-time and log sessions and supports :
        - user-mode sessions
        - kernel-mode trace sessions
        - NT Kernel Logger trace sessions 
        - the Global Logger (boot) trace session. 
        - tracing to measure time spent in deferred procedure calls (DPCs) and interrupt service routines (ISRs).
      
      - Logman (Logman.exe) is a fully functional, command-based trace controller that is designed especially to control the logging of 
        performance counters and event traces.

    - creating tmf files
      - Tracepdb (Tracepdb.exe) is a command-line support tool that creates trace message format (TMF) files from the trace message 
        formatting instructions in PDB symbol files.

      - Tracefmt can create TMF files from PDB symbol files.

    - formating and display trace messages(trace consummers)
      - Tracefmt:
        - command-line trace consumer
        - formats real-time __trace sessions__ or __trace logs__
        - writes them to files or displays them in the Command Prompt window.
      
      - Tracerpt (Tracerpt.exe) 
        - command-line trace consumer 
        - formats __trace events (TraceEvent)__ and __performance counters__
        - writes them to CSV or XML files. 
        - analyzes the events and generates summary reports.

      - traceview 
        - GUI-based tool, both trace controller and trace consumer
        - formats and displays  real-time trace sessions or trace logs
        - displays in a tabular form, easier to filter and browse.

    - Viewing trace events in a debugger
      - !wmitrace: debugger extension displays the trace message in trace session buffer before write to log files or delivery for display
      
      - tracelog -kd to redirect trace message to KD

      - traceview -kd redirect trace message to Windbg

    - Analyzing DPC and ISR execution times
      - windows xp sp2 or later 
        - tracelog to log DPC or ISR in the NT kernel log session;
        - tracerpt to create summery from logs;



# Troubleshooting technics
  - perfmon 
    cpu not accurate

  - resmon
    cannot save file

  - WPA(windows performance analyzer)
    - windows performance recorder:
      wprui: UI
      wpr.exe: command-line-based


  - windbg
    - crash dmp file
    - sysmbols path set 

  - poolmon
    ```
    P - Sorts tag list by Paged, Non-Paged, or mixed. Note that P cycles through each one.
    B - Sorts tags by max byte usage.
    M - Sorts tags by max byte allocation.
    T - Sort tags alphabetically by tag name.
    E - Display Paged, Non-paged total across bottom. Cycles through.
    A - Sorts tags by allocation size.
    F - Sorts tags by "frees".
    S - Sorts tags by the differences of allocs and frees.
    E - Display Paged, Non-paged total across bottom. Cycles through.
    Q - Quit.
    ```

  - verifier.exe (driver verifier)
    - remember to turn off when not needed

    crash and hangs --> memory, driver

  - kernel or application
    kernel  -> blue screen -> get crash
    hangs -> force crash -> blue screen

  - 

# 1. windows kernel research
  1. fork code
  2. download book
  3. windows via c/c++
    # [kernel object](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724515(v=vs.85).aspx)
      * The system provides three categories of objects: user, graphics device interface (GDI), and kernel
        - user objects support window management:
          - Accelerator: table	Keyboard Accelerators
          - Caret
          - Cursor
          - DDE conversation: Dynamic Data Exchange Management Library
          - Hook
          - Icon
          - Menu
          - windows
            - Window
            - Window position
        - gdi objects support graphics
          - bitmap
          - brush
          - pen and extend pen
          - colors
          - font
          - device contexts
            - DC (device context)
            - Memory DC
          - region
          - metafiles
            - Enhanced metafile
            - Enhanced metafile DC
            - metafile

        - kernel objects support memory management, process execution, and interprocess communications (IPC)        
          - Access: token	Access Control
          - Change: notification	Directory Change Notifications
          - Communications device
          - Applications
            - Console input	Character-Mode 
            - Console screen buffer	Character-Mode 
          - Desktop	
          - Event	Synchronization
          - Event log	Event Logging
          - File	Files and Clusters
          - File mapping	File Mapping
          - Heap	Memory Management
          - Job	
          - Mailslot	Mailslots
          - Module	Dynamic-Link Libraries
          - Mutex	Synchronization
          - Pipe	Pipes
          - Process	Processes and Threads
          - Semaphore	Synchronization
            - Semaphore	Synchronization
            - Timer	Synchronization
            - Timer queue	Synchronization
            - Timer-queue timer	Synchronization
          - Socket	Windows Sockets 2
          - Thread	Processes and Threads
          - Update resource	Resources
          - Window station	Window Stations             
        
      * kernel object has SECURITY_ATTRIBUTES in parameters when created;

      * kernel object is managed by handle table created by os;

        index | pointer to kernel object | access mask | sign
        [handle table entry](http://www.alex-ionescu.com/?p=196)
        # get handle using procexp
          Ctrl+h #show object handles
          ```
          explore.exe  pid: 1952
          0xD50	Mutant	\Sessions\1\BaseNamedObjects\DBWinMutex	0x00160001	0xFFFFFA8012063FC0		READ_CONTROL | SYNCHRONIZE | WRITE_DAC | QUERY_STATE

        # livekd:
          - show object info
            ```
            0: kd> !object \Sessions\1\BaseNamedObjects\DBWinMutex
            Object: fffffa8012063fc0  Type: (fffffa800cde53c0) Mutant
                ObjectHeader: fffffa8012063f90 (new version)
                HandleCount: 17 PointerCount: 18
                Directory Object: fffff8a0012b2230  Name: DBWinMutex
            ```

          - show handle info
            ```
            # !handle [Handle [KMFlags [Process [TypeName]]]]
            # Bit 0 (0x1) :Displays handle type information.
            # Bit 1 (0x2): Displays basic handle information.
            # Bit 2 (0x4): Displays handle name information.
            # Bit 3 (0x8): Displays object-specific handle information, when available.
            # handle_index: 0xd50 kmflags: 0x2 pid: 1952 
            # 0x prefix (hexadecimal), the 0n prefix (decimal), the 0t prefix (octal), or the 0y prefix (binary).
            0: kd> !handle 0xd50 2 0n1952 
            PROCESS fffffa8010f0b2f0
                SessionId: 1  Cid: 07a0    Peb: 7fffffde000  ParentCid: 0630
                DirBase: 3e053b000  ObjectTable: fffff8a0030984e0  HandleCount: 1439.
                Image: explorer.exe

            Handle table at fffff8a0030984e0 with 1439 entries in use

            0d50: Object: fffffa8012063fc0  GrantedAccess: 00160001 Entry: fffff8a004cd2540
            Object: fffffa8012063fc0  Type: (fffffa800cde53c0) Mutant
                ObjectHeader: fffffa8012063f90 (new version)
                    HandleCount: 17 PointerCount: 18
                    Directory Object: fffff8a0012b2230  Name: DBWinMutex
            ```

          - show handle table
            ```
            dt nt!_HANDLE_TABLE fffff8a0030984e0
            +0x000 TableCode        : 0xfffff8a0`039cd001
            +0x008 QuotaProcess     : 0xfffffa80`10f0b2f0 _EPROCESS
            +0x010 UniqueProcessId  : 0x00000000`000007a0 Void
            +0x018 HandleLock       : _EX_PUSH_LOCK
            +0x020 HandleTableList  : _LIST_ENTRY [ 0xfffff8a0`030ea540 - 0xfffff8a0`0301d7d0 ]
            +0x030 HandleContentionEvent : _EX_PUSH_LOCK
            +0x038 DebugInfo        : (null)
            +0x040 ExtraInfoPages   : 0n0
            +0x044 Flags            : 0
            +0x044 StrictFIFO       : 0y0
            +0x048 FirstFreeHandle  : 0x104c
            +0x050 LastFreeHandleEntry : 0xfffff8a0`05500ff0 _HANDLE_TABLE_ENTRY
            +0x058 HandleCount      : 0x59f
            +0x05c NextHandleNeedingPool : 0x1c00
            +0x060 HandleCountHighWatermark : 0x689
            ```

          - show table entry
            ```
            0: kd> dt nt!_HANDLE_TABLE_ENTRY  fffff8a004cd2540
            +0x000 Object           : 0xfffffa80`12063f91 Void
            +0x000 ObAttributes     : 0x12063f91
            +0x000 InfoTable        : 0xfffffa80`12063f91 _HANDLE_TABLE_ENTRY_INFO
            +0x000 Value            : 0xfffffa80`12063f91
            +0x008 GrantedAccess    : 0x160001
            +0x008 GrantedAccessIndex : 1
            +0x00a CreatorBackTraceIndex : 0x16
            +0x008 NextFreeTableEntry : 0x160001
            ```

            dt nt!_KMUTANT <addr> will show you the layout of the mutex itself. 
            There's also an nt!_OBJECT_HEADER that precedes it
          (!object displays the address of the header).

      * thread, file, metux, filemapping
        CreateXXX
        return:
           NULL(0) error, but CreateFile needs to check for INVALID_HANDLE_VALUE(-1)
      
      * terminal service namespace
        * session 0(inactive terminal service)
        * Global
        * Local
        * Private

      - process
        * Environments
          ```
          HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment

          HKEY_CURRENT_USER\Environment

          SendMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)_T("Environment"));
          ```

      - FileMapping
        ```
        * HANDLE hFile = CreateFile();
        * HANDLE hFileMapping = CreateFileMapping(hFile, ...);
          CloseHandle(hFile);
        * PVOID pvFile = MapViewOfFile(hFileMapping, ...); 
          // increase ref count of file object and filemapping object
          CloseHandle(hFileMapping);
        * UnmapViewOfFile(pvFile, ...);
          // CloseHandle(hFileMapping);
          // CloseHandle(hFile);

      - 


# windows internal
  1. subsystem
    * csrss - client/server runtime subsystem


# MS15-050
  - 

# visual studio
  - create project from sources
    // Disable warning messages 4507 and 4034.  
    #pragma warning( disable : 4507 34 )  
      
    // Issue warning 4385 only once.  
    #pragma warning( once : 4385 )  
      
    // Report warning 4164 as an error.  
    #pragma warning( error : 164 )  

  - error scheme definition
    https://social.msdn.microsoft.com/Forums/en-US/31f52b76-b0de-406d-9c25-2f329dd7cf1c/microsoftcommontargetserrors-and-over-a-hundred-warnings?forum=Vsexpressvb
    close all opened text editor in vs

  - error open hlpviewer
    - open procmon
      ```
      include PrcessName hlpviewer.exe
      
      monitor registry and file
      ```
    - result
      ```
      8:51:57.0637073	9296	HlpViewer.exe	9324	CreateFile	C:\Users\Dobly\AppData\Local\Microsoft\HelpViewer2.1\VisualStudio12_en-US\catalogType.xml	__NAME NOT FOUND__	Desired Access: Read Attributes, Disposition: Open, Options: Open Reparse Point, Attributes: n/a, ShareMode: Read, Write, Delete, AllocationSize: n/a
      ```
      catalogType.xml 

    - install catalog
      ```
      C:\ProgramData\Microsoft\HelpLibrary2\Catalogs\VisualStudio12\

      hlpctntMgr /operation install /catalogName VisualStudio12 /locale en-US /sourceUri C:\Users\Dobly\AppData\Local\Microsoft\HelpViewer2.1\VisualStudio12_en-US\helpcontentsetup.msha
      ```

    - [driver sign](https://technet.microsoft.com/en-us/library/dd919238(v=ws.10).aspx)
      - create a digital certificate for signing
        ```
        C:\WinDDK\7600.16385.1\bin\x86\makecert -$ individual -r -pe -n "CN=Dobly - for test use only" -ss "self-signing store" -sr LocalMachine "DDK.cer"
        ```

      - Add the certificate to the Trusted Root Certification Authorities store
        This step is required for locally created certificates, such as those created by using MakeCert, which are not directly traceable to a Trusted Root Certification Authority certificate.
        ```
        C:\WinDDK\7600.16385.1\bin\x86\CertMgr.Exe /add "DDK.cer" /s /r localMachine root
        ```

      - Add the certificate to the per machine Trusted Publishers store
        To use your new certificate to confirm the valid signing of device drivers, it must also be installed in the per computer Trusted Publishers store.
        ```
        C:\WinDDK\7600.16385.1\bin\x86\CertMgr /add "DDK.cer" /s /r localMachine trustedpublisher
        ```
      
      - Enable the Kernel-Mode Test-Signing Boot Configuration Option
        ```
        bcdedit /set testsigning on
        ```

      - Sign the device driver package with the certificate
        ```
        C:\WinDDK\7600.16385.1\bin\x86\signtool.exe sign /a /v /s "self-signing store" /n "Dobly" /t http://timestamp.verisign.com/scripts/timestamp.dll "protector.sys"

        C:\WinDDK\7600.16385.1\bin\x86\signtool.exe verify /pa /v "protector.sys"
        ```

      - [Viewing Code Integrity Events](https://msdn.microsoft.com/en-us/windows/hardware/drivers/install/enabling-the-system-event-audit-log)
        - Enable Security Audit Policy
          ```
          Auditpol /set /Category:System /failure:enable
          ```
        - Enable Verbose Logging of Code Integrity Diagnostic Events
          ```
          eventvwr.msc  
            Applications and Services Logs -> Microsoft -> Windows ->  CodeIntegrity
          ```
    - create kernel driver service and start it
      ```
      sc create genport type= kernel binpath= "c:\driver\genport.sys" start= auto
      sc start protectorservice 
      ```

  - driver
    - driver support routines
      - Object Manager Routines

    - trace log 
      ```
      trace message header (TMH) 
      trace level
      trace flags
      ```

  
  - kernel api
    prefix  | description
    ------  | ------------
    Aux     | Auxiliary Library
    Clfs    | Common Log File System
    Cc      | Cache Manager
    Cm      | Configuration Manager
    Ex      | Executive (Memory Allocation wrappers, etc)
    Flt     | Filter Manager
    Hal     | Hardware Abstraction Layer
    Io      | I/O Manager
    Ke      | Kernel Core
    Mm      | Memory Manager
    Nt      | Native Services (User Mode)
    Ob      | Object Manager
    Po      | PnP/Power Manager
    Ps      | Processes and Threads
    Rtl     | Run Time Library
    Se      | Security Reference Monitor
    Wmi     | Windows Management Instrumentation
    Zw      | Kernel Mode Wrappers for Nt*

    wrappers:
    Csq     | Cancel-Safe IRP Queue
  
- [64-bit application](https://msdn.microsoft.com/en-us/library/hb5z4sxd.aspx)
  ```
  Inline ASM is not supported for x64. Use MASM or compiler intrinsics (x64 Intrinsics).
  intrin.h __lidt
  ```
  