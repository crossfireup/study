#include <Windows.h>
#include <Winuser.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "user32")
int _cdecl main (
    int argc, 
    TCHAR *argv[])
{           
    if (RegisterHotKey(
        NULL,
        1,
        MOD_ALT | MOD_NOREPEAT,
        0x42))  //0x42 is 'b'
    {
        printf("Hotkey 'ALT+b' registered, using MOD_NOREPEAT flag\n");
    }
 
    exit(0);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        if (msg.message == WM_HOTKEY)
        {
            printf("WM_HOTKEY received\n");            
        }
    } 
 
    return 0;
}
