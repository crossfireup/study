# android 
  1. termux in android 
  2. android x86
  3. busybox

# android x86 
  * [7.0_x86](http://www.osboxes.org/android-x86/#android-x86-7_0-vmware) 
    * Disable Mouse Integration for VirtualBox: 
       Run virtual machine go to menu Machine > Disable Mouse Integration or simply press Right CTRL + i to enable/disable mouse integration.
    * for VMware:
       After setting up, go to “Virtual Machine Settings” > under “Hardware” Tab > Select “Display” > Enable “Accelerate 3D graphics”

# remote debug
  * 5.1 
    1. enable debug mode 
      * touch build number for 7 times
      * enable usb debuging
    2. connect your device through usb
      * get your ip addr:
        ```
        adb shell netcfg
        ```
      * check teh connectivity
        ```
        ping 192.168.1.4
        ```
      * open debug port 
        ```
        adb tcpip 6666
        ```
    3. connect device through wifi
      ```
      adb kill-server
      adb start-server
      adb connect 192.168.1.4:6666

      adb -s emulator install test.apk
      ```
    4. test 
      ```
      adb shell
      netstat -anltp
      ```
    5. enable usb debugging
      ```
      adb disconnect 192.168.1.4
      adb kill-server
      adb usb
      adb devices -l
      ```

# package manager
  ```
  sysdump
  adb shell pm list packages
  adb shell pm path com.example.someapp

  adb pull /data/*.apk path

  export PATH=$PATH:/data/data/com.termux/files/usr/bin:/data/data/com.termux/files/usr/bin/applets
  export LD_LIBRARY_PATH=/data/data/com.termux/files/usr/lib
  ```

# tools
  - apktool
  - dex2jar
  - JD-ui
  - ClassyShark.jar