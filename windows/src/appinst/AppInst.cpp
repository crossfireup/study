#include "../comm/CmnHdr.h"
#include "Resource.h"
#include <windowsx.h>
#include <tchar.h>

UINT g_uMsgAppInstCountUpdate = WM_APP + 123;

#pragma data_seg("Shared")
volatile LONG g_lApplicationInstance = 0;
#pragma data_seg()

#pragma comment(linker, "/Section:Shared,RWS")

BOOL Dlg_OnInitDialog(HWND hWnd, HWND hFocus, LPARAM lParam)
{
	chSETDLGICONS(hWnd, IDI_APPINST);

	PostMessage(HWND_BROADCAST, g_uMsgAppInstCountUpdate, 0, 0);
	return(TRUE);
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {
	case IDCANCEL:
		InterlockedDecrement(&g_lApplicationInstance);
		PostMessage(HWND_BROADCAST, g_uMsgAppInstCountUpdate, 0, 0);
		EndDialog(hWnd, id);
		break;
	}
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == g_uMsgAppInstCountUpdate) {
		SetDlgItemInt(hWnd, IDC_COUNT, g_lApplicationInstance, FALSE);
	}

	switch (uMsg) {
		chHANDLE_DLGMSG(hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hWnd, WM_COMMAND, Dlg_OnCommand);
	}
	return(FALSE);
}

int WINAPI _tWinMain(HINSTANCE hInstanceEx, HINSTANCE, PTSTR, int)
{
	g_uMsgAppInstCountUpdate = RegisterWindowMessage(_T("MsgAppInstCountUpdate"));

	InterlockedExchangeAdd(&g_lApplicationInstance, 1);

	DialogBox(hInstanceEx, MAKEINTRESOURCE(IDD_APPINST), NULL, Dlg_Proc);

	PostMessage(HWND_BROADCAST, g_uMsgAppInstCountUpdate, 0, 0);

	return(0);
}