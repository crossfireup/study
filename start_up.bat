@rem start programs
@rem schtasks /create /SC ONLOGON /TN start_enjoy /TR "D:\study\start_up.bat" /F
@rem schtasks /delete /TN start_enjoy /F

@rem start /B sublime_text.exe

@start /B code

@rem start /B vmrun -T ws start "D:\vms\VMware\CentOS_6.6_x64_basic\CentOS_6.6_x64_basic.vmx" nogui

@rem start /B vmrun -T ws start "D:\vms\VMware\Ubuntu_15.1_x64\Ubuntu 64 bit.vmx" nogui

@rem start /B vmrun -T ws start "D:\vms\VMware\kali_2.0_x64_2016_02\kali_2.0_x64_2016_02.vmx" nogui

@start /B vmrun -T ws start "D:\vms\VMware\Windows_7_x86_ult\Windows_7_x86_ult.vmx" nogui

@start /B wireshark

@start /B firefox

@start /B explorer D:\study

@start /B devenv

@exit 0