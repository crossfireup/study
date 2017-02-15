## Troubleshooting Guide for Java.[http://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/index.html] #

# JPDA(java platform debugger architecture)
    ```
                   Components                          Debugger Interfaces
    
                    /    |--------------|
                   /     |     VM       |
     debuggee ----(      |--------------|  <------- JVM TI - Java VM Tool Interface
                   \     |   back-end   |
                    \    |--------------|
                    /           |
     comm channel -(            |  <--------------- JDWP - Java Debug Wire Protocol
                    \           |
                         |--------------|
                         | front-end    |
                         |--------------|  <------- JDI - Java Debug Interface
                         |      UI      |
                         |--------------|
    ```
  * debug
    ```
    C:\Program Files (x86)\Java\jdk1.7.0_55\bin>jdb -listconnectors

    Connector: com.sun.jdi.CommandLineLaunch  Transport: dt_shmem
      description: Launches target using Sun Java VM command line and attaches to it

      Argument: home Default value: C:\Program Files (x86)\Java\jdk1.7.0_55\jre
      description: Home directory of the SDK or runtime environment used to launch the application

      Argument: options (no default)
      description: Launched VM options

      Required Argument: main (no default)
      description: Main class and arguments, or if -jar is an option, the main jar file and arguments

      Argument: suspend Default value: true
      description: All threads will be suspended before execution of main

      Required Argument: quote Default value: "
      description: Character used to combine space-delimited text into a single command line argument

      Required Argument: vmexec Default value: java
      description: Name of the Java VM launcher

    Connector: com.sun.jdi.ProcessAttach  Transport: local
      description: Attaches to debuggee by process-id (pid)

      Required Argument: pid (no default)
      description: pid

      Argument: timeout (no default)
      description: Timeout while waiting to attach

    Connector: sun.jvm.hotspot.jdi.SACoreAttachingConnector  Transport: filesystem
      description: This connector allows you to attach to a core file using the Serviceability Agent

      Required Argument: javaExecutable (no default)
      description: Pathname of Java Executable

      Argument: core Default value: core
      description: Pathname of a corefile from a Java Process

    Connector: sun.jvm.hotspot.jdi.SADebugServerAttachingConnector  Transport: RMI
      description: This connector allows you to attach to a Java Process via a debug server with the Serviceability Agent

      Required Argument: debugServerName (no default)
      description: Name of a remote SA Debug Server

    Connector: sun.jvm.hotspot.jdi.SAPIDAttachingConnector  Transport: local process
      description: This connector allows you to attach to a Java process using the Serviceability Agent

      Required Argument: pid (no default)
      description: PID of a Java process


    jdb -connect sun.jvm.hotspot.jdi.SAPIDAttachingConnector:pid=2736 
    ```

* disassembly
    * 
      javac LCG.class
      javap -c -verbose LCG.class