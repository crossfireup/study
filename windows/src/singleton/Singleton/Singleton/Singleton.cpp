#include "Resource.h"

#include "..\..\..\comm\CmnHdr.h"
#include <windowsx.h>
#include <sddl.h>
#include <tchar.h>
#include <strsafe.h>

HWND g_hDlg;

HANDLE g_hSingleton = NULL;
HANDLE g_hBoundary = NULL;
HANDLE g_hNamespace = NULL;

BOOL g_bNamespaceOpend = FALSE;

PCTSTR g_szBoundary = _T("3-Boundary");
PCTSTR g_szNameSpace = _T("3-Namespace");

#define DETAILS_CTRL  GetDlgItem(g_hDlg, IDC_EDIT_DETAILS)

void AddText(PCTSTR pszFormat, ...)
{
	va_list argList;
	va_start(argList, pszFormat);

	TCHAR sz[20 * 1024];

	Edit_GetText(DETAILS_CTRL, sz, _countof(sz));
	_vstprintf_s(_tcschr(sz, _T('\0')), _countof(sz) - _tcslen(sz), pszFormat, argList);
	Edit_SetText(DETAILS_CTRL, sz);
	va_end(argList);
}

void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {
	case IDOK:
	case IDCANCEL:
		EndDialog(hwnd, id);
		break;
	}
}

void CheckInstance()
{
	g_hBoundary = CreateBoundaryDescriptor(g_szBoundary, 0);

	BYTE localAdminSID[SECURITY_MAX_SID_SIZE];
	PSID pLocalAdminSID = &localAdminSID;
	DWORD cbSID = sizeof(localAdminSID);
	if (!CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, pLocalAdminSID, &cbSID)) {
		AddText(_T("CreateWellKnownSid failed: %u\r\n"), GetLastError());
		return;
	}

	if (!AddSIDToBoundaryDescriptor(&g_hBoundary, localAdminSID)) {
		AddText(_T("AddSIDToBounderDescriptor failed: %u\r\n"), GetLastError());
		return;
	}

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(_T("D:(A;;GA;;;BA)"), SDDL_REVISION_1, &sa.lpSecurityDescriptor, NULL)) {
		AddText(_T("Security Descriptor creation failed: %u\r\n"), GetLastError());
		return;
	}

	g_hNamespace = CreatePrivateNamespace(&sa, g_hBoundary, g_szNameSpace);

	LocalFree(sa.lpSecurityDescriptor);

	DWORD dwLastError = GetLastError();
	if (g_hNamespace == NULL) {
		if (dwLastError == ERROR_ACCESS_DENIED) {
			AddText(_T("Access Denied when creating the namespace.\r\n"));
			AddText(_T("  You must be running as administrator.\r\n\r\n"));
			return;
		}
		else {
			if (dwLastError == ERROR_ALIAS_EXISTS) {
				AddText(_T("CreatePrivateNameSpace failed: %u\r\n"), GetLastError());
				g_hNamespace = OpenPrivateNamespace(g_hBoundary, g_szNameSpace);
				if (g_hNamespace == NULL) {
					AddText(_T(" and OpenPrivateNamespace failed: %u\r\n"), GetLastError());
					return;
				}
				else {
					g_bNamespaceOpend = TRUE;
					AddText(_T(" but OpenPrivateNamespace succeeded\r\n\r\n"));
					return;
				}
			}
			else {
				AddText(_T("Unexpected error occured: %u\r\n\r\n"), dwLastError);
				return;
			}
		}
	}
	TCHAR szMutexName[64];
	StringCchPrintf(szMutexName, _countof(szMutexName), _T("%s\\%s"), g_szNameSpace, _T("Singleton"));

	g_hSingleton = CreateMutex(NULL, FALSE, szMutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		AddText(_T("Another instance of Singleton is running:\r\n"));
		AddText(_T("--> Impossible to access application features.\r\n"));
	}
	else {
		AddText(_T("First instance of Singleton:\r\n"));
		AddText(_T("--> Access application features now.\r\n"));
	}
}

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	chSETDLGICONS(hwnd, IDI_SINGLETON);
	g_hDlg = hwnd;

	CheckInstance();
	return(TRUE);
}


INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
		chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
	}
	return(FALSE);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	INT_PTR ret;

	ret = DialogBox(hInstance, MAKEINTRESOURCE(IDD_SINGLETON), NULL, Dlg_Proc);

	if (ret < 0) {
		TCHAR errMsg[1024];
		StringCchPrintf(errMsg, _countof(errMsg), _T("DialogBox error: %d\r\n"), GetLastError());
		MessageBox(NULL, errMsg, _T("ERROR"), MB_OKCANCEL);
	}

	if (g_hSingleton != NULL) {
		CloseHandle(g_hSingleton);
	}

	if (g_hNamespace != NULL) {
		if (g_bNamespaceOpend) {
			ClosePrivateNamespace(g_hNamespace, 0);
		}
		else {
			ClosePrivateNamespace(g_hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
		}
	}

	if (g_hBoundary != NULL) {
		DeleteBoundaryDescriptor(g_hBoundary);
	}
	return(0);
}