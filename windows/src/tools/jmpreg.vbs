'Launches Registry Editor with the chosen branch open automatically
'Author  : Ramesh Srinivasan
'Website: http://windowsxp.mvps.org

Set WshShell = CreateObject("WScript.Shell")

Dim MyKey

MyKey = Inputbox("Type the Registry path")

'MyKey = "My Computer\" & MyKey    ' for xp
Mykey = "Computer\" & MyKey       'windows 7


WshShell.RegWrite "HKCU\Software\Microsoft\Windows\CurrentVersion\Applets\Regedit\Lastkey",MyKey,"REG_SZ"

'WshShell.Run "regedit", 1,True

Set WshShell = Nothing