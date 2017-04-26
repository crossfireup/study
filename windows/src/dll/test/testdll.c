#include <windows.h>

BOOL WINAPI DllMain(
          _Out_ HINSTANCE hInstance,
            _In_  ULONG     ulReason,
                    LPVOID    Reserved
        )
{
    switch(ulReason) {
        case DLL_PROCESS_ATTACH :
            MessageBox(NULL, "Helloc", "Information", MB_OK);
            break;
        case DLL_PROCESS_DETACH:
            MessageBox(NULL, "Goodbye", "Information", MB_OK);
            break;

    }

    return TRUE;
}


