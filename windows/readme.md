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

    * optionalfeatures.exe

    * secedit /analyze 

    *   arp
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
    
    * winmgmt.exe

    * wmic:
         SERVICE WHERE CAPTION='TELNET' CALL STARTSERVICE

         ENVIRONMENT CREATE NAME="TEMP"; VARIABLEVALUE="NEW"

         PROCESS WHERE NAME="CALC.EXE" DELETE

         wmic product   --list all installed software

wmic:root\cli>context
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



[global switches] <command>

The following global switches are available:
/NAMESPACE           Path for the namespace the alias operate against.
/ROLE                Path for the role containing the alias definitions.
/NODE                Servers the alias will operate against.
/IMPLEVEL            Client impersonation level.
/AUTHLEVEL           Client authentication level.
/LOCALE              Language id the client should use.
/PRIVILEGES          Enable or disable all privileges.
/TRACE               Outputs debugging information to stderr.
/RECORD              Logs all input commands and output.
/INTERACTIVE         Sets or resets the interactive mode.
/FAILFAST            Sets or resets the FailFast mode.
/USER                User to be used during the session.
/PASSWORD            Password to be used for session login.
/OUTPUT              Specifies the mode for output redirection.
/APPEND              Specifies the mode for output redirection.
/AGGREGATE           Sets or resets aggregate mode.
/AUTHORITY           Specifies the <authority type> for the connection.
/?[:<BRIEF|FULL>]    Usage information.

For more information on a specific global switch, type: switch-name /?


The following alias/es are available in the current role:
ALIAS                    - Access to the aliases available on the local system
BASEBOARD                - Base board (also known as a motherboard or system board) management.
BIOS                     - Basic input/output services (BIOS) management.
BOOTCONFIG               - Boot configuration management.
CDROM                    - CD-ROM management.
COMPUTERSYSTEM           - Computer system management.
CPU                      - CPU management.
CSPRODUCT                - Computer system product information from SMBIOS.
DATAFILE                 - DataFile Management.
DCOMAPP                  - DCOM Application management.
DESKTOP                  - User's Desktop management.
DESKTOPMONITOR           - Desktop Monitor management.
DEVICEMEMORYADDRESS      - Device memory addresses management.
DISKDRIVE                - Physical disk drive management.
DISKQUOTA                - Disk space usage for NTFS volumes.
DMACHANNEL               - Direct memory access (DMA) channel management.
ENVIRONMENT              - System environment settings management.
FSDIR                    - Filesystem directory entry management.
GROUP                    - Group account management.
IDECONTROLLER            - IDE Controller management.  
IRQ                      - Interrupt request line (IRQ) management.
JOB                      - Provides  access to the jobs scheduled using the schedule service.
LOADORDER                - Management of system services that define execution dependencies.
LOGICALDISK              - Local storage device management.
LOGON                    - LOGON Sessions.
MEMCACHE                 - Cache memory management.
MEMORYCHIP               - Memory chip information.
MEMPHYSICAL              - Computer system's physical memory management.
NETCLIENT                - Network Client management.
NETLOGIN                 - Network login information (of a particular user) management.
NETPROTOCOL              - Protocols (and their network characteristics) management.
NETUSE                   - Active network connection management.
NIC                      - Network Interface Controller (NIC) management.
NICCONFIG                - Network adapter management.
NTDOMAIN                 - NT Domain management.
NTEVENT                  - Entries in the NT Event Log.
NTEVENTLOG               - NT eventlog file management.
ONBOARDDEVICE            - Management of common adapter devices built into the motherboard (system board).
OS                       - Installed Operating System/s management.
PAGEFILE                 - Virtual memory file swapping management.
PAGEFILESET              - Page file settings management.
PARTITION                - Management of partitioned areas of a physical disk.
PORT                     - I/O port management.
PORTCONNECTOR            - Physical connection ports management.
PRINTER                  - Printer device management.
PRINTERCONFIG            - Printer device configuration management.
PRINTJOB                 - Print job management.
PROCESS                  - Process management.
PRODUCT                  - Installation package task management.
QFE                      - Quick Fix Engineering.
QUOTASETTING             - Setting information for disk quotas on a volume.
RDACCOUNT                - Remote Desktop connection permission management.
RDNIC                    - Remote Desktop connection management on a specific network adapter.
RDPERMISSIONS            - Permissions to a specific Remote Desktop connection.
RDTOGGLE                 - Turning Remote Desktop listener on or off remotely.
RECOVEROS                - Information that will be gathered from memory when the operating system fails.
REGISTRY                 - Computer system registry management.
SCSICONTROLLER           - SCSI Controller management.
SERVER                   - Server information management.
SERVICE                  - Service application management.
SHADOWCOPY               - Shadow copy management.
SHADOWSTORAGE            - Shadow copy storage area management.
SHARE                    - Shared resource management.
SOFTWAREELEMENT          - Management of the  elements of a software product installed on a system.
SOFTWAREFEATURE          - Management of software product subsets of SoftwareElement.
SOUNDDEV                 - Sound Device management.
STARTUP                  - Management of commands that run automatically when users log onto the computer system.
SYSACCOUNT               - System account management.
SYSDRIVER                - Management of the system driver for a base service.
SYSTEMENCLOSURE          - Physical system enclosure management.
SYSTEMSLOT               - Management of physical connection points including ports,  slots and peripherals, and proprietary connections points.
TAPEDRIVE                - Tape drive management.
TEMPERATURE              - Data management of a temperature sensor (electronic thermometer).
TIMEZONE                 - Time zone data management.
UPS                      - Uninterruptible power supply (UPS) management.
USERACCOUNT              - User account management.
VOLTAGE                  - Voltage sensor (electronic voltmeter) data management.
VOLUME                   - Local storage volume management.
VOLUMEQUOTASETTING       - Associates the disk quota setting with a specific disk volume.
VOLUMEUSERQUOTA          - Per user storage volume quota management.
WMISET                   - WMI service operational parameters management.

For more information on a specific alias, type: alias /?

CLASS     - Escapes to full WMI schema.
PATH      - Escapes to full WMI object paths.
CONTEXT   - Displays the state of all the global switches.
QUIT/EXIT - Exits the program.

For more information on CLASS/PATH/CONTEXT, type: (CLASS | PATH | CONTEXT) /?



    * wusa.exe  
        windows update stand alone installler

        Link-Local Multicast Name Resolution (LLMNR) protocol 


    * tasklist 
        tasklist /svc /fi "imagename eq svchost.exe"

        sc config foo type= shared
        sc config foo type= own

        HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Svchost

        HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\wuauserv\Type

        svchost -k XLServicePlatform

        net stop XLServicePlatform
        sc config XLServicePlatform  type= own
        net start XLServicePlatform

        sc config wuauserv type= own
        
        %systemroot%\system32\svchost.exe -k WindowsUpdate

        
        ** Create a new REG_MULTI_SZ value named WindowsUpdates in the HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Svchost key. 
            REG_MULTI_SZ WindowsUpdate wuauserv
        ** Add the name of the service (in this case wuauserv) to the value. 
            You also need to remove the wuauserv from the list in the HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Svchost\Netsvcs value to prevent conflicts.
        ** Now navigate to the HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet \Services\wuauserv key and change the ImagePath value from %systemroot%\system32\svchost.exe -k netsvcs to: %systemroot%\system32\svchost.exe -k WindowsUpdates
        ** Restart the Automatic Updates service and you should now see a new instance of SVCHOST.EXE that only contains the Automatic Updates service.
        ** This method can be repeated to isolate multiple services into their own groups.
          To revert back to the original configurations, reverse the steps above and restart the machine.  Use the backup of the registry to ensure that you get the right services back into the proper groups.


$ assoc .rb=RubyScript
.rb=RubyScript
$ ftype RubyScript="c:\ruby\bin\ruby.exe" "%1" % *
RubyScript="c:\ruby\bin\ruby.exe" "%1" % *



"C:\Program Files (x86)\MyDrivers\DriverGenius2013\ksoft\khelper.exe" /WebIconUrl*https://www.duba.com/?f=qd_desktop*

tools:
    remote management tools:
        winrs
        winrm
    where wev*.exe

    wf.msc --windows firewall

    waitfor.exe
        waitfor setupready
        waitfor /s 127.0.0.1 /si setupready

    sc --service control


    Netplwiz.exe --config user remote access this computer


    "C:\Windows\system32\oobe\msoobe.exe /A."  --xp

    systempropertiesadvanced.exe

    SystemPropertiesPerformance.exe

    SC CREATE <servicename> Displayname= "<servicename>" binpath= "srvstart.exe <servicename> -c <path to srvstart config file>" start= <starttype>
    sc create Startup binPath= "start /b D:\study\start_up.cmd" type= kernel start= auto error= severe Displayname= "AutoStart"

    * Windows Defender is turned off or not working

        You may receive a message: Windows Defender has been turned off, and it isn’t monitoring your computer.

        If you have another antivirus software installed, it will turn off Windows Defender. But if you do not and yet , then you might want to carry out the following troubleshooting steps:

        1] Check if you have all the latest Windows Updates installed, including having the latest version of Windows Defender and its definitions.

        2] Did you uninstall any security software recently – especially Norton or McAfee? If so maybe its partial uninstallation is causing issues. Use McAfee Consumer Products Removal Tool or some antivirus removal tool to ensure that you have even removed its remnants.

        3] Have you checked your computer for malware? Or did you just recover from a malware attack? I suggest you download and run a stand-alone portable antivirus scanner and run an offline scan from your USB – or else use an online antivirus scanner service to scan your PC.

        4] Open Action Center and see if you are able to enable Windows Defender.

        5] Run services.msc to open Services Manager. Ensure that the Windows Defender service is started and set to Automatic.

        6] If Windows Defender Service (WinDefend) or Windows Defender Network Inspection Service (WdNisSvc)  of Windows Defender keeps stopping, turning off or could not start,

        Re-register the following dll files and see if it helps you. Run each command in an elevated command prompt one after the other and hit Enter:

            regsvr32 wuaueng.dll
            regsvr32 wucltui.dll
            regsvr32 softpub.dll
            regsvr32 wintrust.dll
            regsvr32 initpki.dll
            regsvr32 wups.dll
            regsvr32 wuweb.dll
            regsvr32 atl.dll
            regsvr32 mssip32.dll

        7] Run regedit and navigate to the following key:

            HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows Defender
            Here ensure that the value of these DWORDS is 1 : DisableAntiSpyware and DisableAntiVirus.

            If it is 0, then you will have to use our freeware RegOwnit to take ownership of these Registry keys and then change its value from 0 to 1. RegOwnit allows you to take ownership of a Windows Registry key using Administrator, Home Users or the current Logged On User account.

        8] It may also happen that Windows Security Center may prompt you to “Check Settings” for the Malware Protection, and when you click the “Turn on now” button, it may show an error that says “There are no new definitions available to download for Windows Defender“.

            It may be possible that the issue may have been caused due to an inconsistent WMI repository. Restarting the WMI repository should thus help resolve the issue.

            Open Command Prompt as an Administrator. Type the following command and hit Enter:

            winmgmt /verifyrepository

        If you get a message “WMI repository is not consistent“, run the following command:

            winmgmt /salvagerepository
    


    Ctrl+D

     Ctrl+Shift+L  mutil to one line 

     Ctrl+Shift+P show command

* [hook](https://en.wikipedia.org/wiki/Hooking)
     hooking covers a range of techniques used to alter or augment the behavior of an operating system, 
     of applications, or of other software components by intercepting function calls or messages or events passed between
      software components. Code that handles such intercepted function calls, events or messages is called a "hook".

      ILT: import lookup table
      IAT: import address table

      HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AeDebug
      "C:\WinDDK\7600.16385.1\Debuggers\windbg.exe" -p %ld -e %ld -g

* assembly
    1. windbg工具使用：
      
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