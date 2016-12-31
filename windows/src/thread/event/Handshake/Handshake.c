#include <windows.h>
#include <windowsx.h>
#include <process.h>
#include <tchar.h>
#include <strsafe.h>

#include "Resource.h"

HANDLE g_hevtRequestSubmitted;

HANDLE g_hevtResultReturned;

TCHAR g_szSharedRequestAndResultBuffer[1024];

TCHAR g_szServerShutdown[] = _T("Server Shutdown");

HWND g_hMainDlg;

DWORD WINAPI ServerThread(PVOID pvParam)
{
    BOOL fShutdown = FALSE;

    while(!fShutdown){
        WaitForSingleObject(g_hevtRequestSubmitted, INFINITE);

        fShutdown = (g_hMainDlg == NULL) && (_tcscmp(g_szSharedRequestAndResultBuffer, g_szServerShutdown) == 0);

        if(!fShutdown){
            _tcsrev(g_szSharedRequestAndResultBuffer);
        }

        SetEvent(g_hevtResultReturned);
    }

    return(0);
}

BOOL Dlg_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM LPARAM)
{
    Static_SetIcon(hWnd, IDI_HANDSHAKE);

    Edit_SetText(GetDlgItem(hWnd, IDC_REQUEST), _T("Some test data"));

    g_hMainDlg = hWnd;

    return(TRUE);
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT notifyCode)
{
    switch(id){
        case IDCANCEL:
            EndDialog(hWnd, id);
            break;
        case IDC_SUBMIT:
            Edit_GetText(GetDlgItem(hWnd, IDC_REQUEST), g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer));

            SetEvent(g_hevtRequestSubmitted);
            WaitForSingleObject(g_hevtResultReturned, INFINITE);

            Edit_SetText(GetDlgItem(hWnd, IDC_RESULT), g_szSharedRequestAndResultBuffer);
            break;
    }

}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg){
        HANDLE_MSG(hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Dlg_OnCommand);
    }
    return(FALSE);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTSTR pszCmdLine, int nShowCmd)
{
    g_hevtRequestSubmitted = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hevtResultReturned = CreateEvent(NULL, FALSE, FALSE, NULL);

    DWORD dwThreadId;
    HANDLE hThread = (HANDLE) _beginthreadex(NULL, 0, ServerThread, NULL, 0, &dwThreadId);

    DialogBox(hInstance, MAKEINTRESOURCE(IDD_HANDSHAKE), NULL, Dlg_Proc);
	g_hMainDlg = NULL;

    _tcscpy_s(g_szSharedRequestAndResultBuffer, _countof(g_szSharedRequestAndResultBuffer), g_szServerShutdown);

    SetEvent(g_hevtRequestSubmitted);

    HANDLE h[2];
    h[0] = g_hevtResultReturned;
    h[1] = hThread;
    WaitForMultipleObjects(2, h, TRUE, INFINITE);

    CloseHandle(hThread);
    CloseHandle(g_hevtRequestSubmitted);
    CloseHandle(g_hevtResultReturned);

    return(0);
}

