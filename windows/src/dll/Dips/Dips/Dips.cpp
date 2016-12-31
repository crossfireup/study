// Disp.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#include "../../../comm/CmnHdr.h"
#include "Resource.h"
#include "../../dipslib/DIPSLib.h"

BOOL Dlg_OnInitialize(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	chSETDLGICONS(hWnd, IDI_DIPS);
	return(TRUE);
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {
	case IDC_SAVE:
	case IDC_RESTORE:
	case IDCANCEL:
		EndDialog(hWnd, id);
		break;
	}
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		chHANDLE_DLGMSG(hWnd, WM_INITDIALOG, Dlg_OnInitialize);
		chHANDLE_DLGMSG(hWnd, WM_COMMAND, Dlg_OnCommand);
	}
	return(FALSE);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstPre, PTSTR pszCmdLine, int nShow)
{
	CharUpperBuff(pszCmdLine, 1);
	TCHAR cWhatToDo = pszCmdLine[0];

	if ((cWhatToDo != _T('S')) && (cWhatToDo != _T('R'))) {
		cWhatToDo = 0;
	}

	if (cWhatToDo == 0) {
		switch (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIPS), NULL, Dlg_Proc)) {
		case IDC_SAVE:
			cWhatToDo = _T('S');
			break;
		case IDC_RESTORE:
			cWhatToDo = _T('R');
			break;
		}
	}

	if (cWhatToDo == 0) {
		return(0);
	}

	HWND hWndLV = GetFirstChild(GetFirstChild(FindWindow(_T("Progman"), NULL)));
	chVERIFY(IsWindow(hWndLV));

	chVERIFY(SetDIPSHook(GetWindowThreadProcessId(hWndLV, NULL)));

	MSG msg;
	GetMessage(&msg, NULL, 0, 0);

	HWND hWndDIPS = FindWindow(NULL, TEXT("Wintellect DIPS"));
	chASSERT(IsWindow(hWndDIPS));

	BOOL bSave = (cWhatToDo == TEXT('S'));

	SendMessage(hWndDIPS, WM_APP, (WPARAM)hWndLV, bSave);

	SendMessage(hWndDIPS, WM_CLOSE, 0, 0);

	chASSERT(!IsWindow(hWndDIPS));

	SetDIPSHook(0);
    return 0;
}

