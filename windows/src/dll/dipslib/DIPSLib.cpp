#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#include "../displib/../../comm/CmnHdr.h"
#include "Resource.h"
#define DIPSLIBAPI _declspec(dllexport)
#include "DIPSLib.h"


#ifdef _DEBUG
void ForceDebugBreak()
{
	__try{
		DebugBreak();
	}__except(UnhandledExceptionFilter(GetExceptionInformation())) {

	}
}
#else
#define void ForceDebugBreak	
#endif


LRESULT WINAPI GetMsgProc(int ncode, WPARAM wParam, LPARAM lParam);

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#pragma data_seg("Shared")
	HHOOK g_hHook = NULL;
	DWORD g_dwThreadIdDIPS = 0;
#pragma data_seg()

#pragma comment(linker, "/section:Shared,rws")

	
HINSTANCE g_hInstDll = NULL;

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, PVOID fImpLoad)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		g_hInstDll = hInstDll;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

BOOL WINAPI SetDIPSHook(DWORD dwThreadId)
{
	BOOL bOk = FALSE;

	if (dwThreadId != 0) {
		chASSERT(dwThreadId);

		g_dwThreadIdDIPS = GetCurrentThreadId();

		g_hHook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hInstDll, dwThreadId);

		bOk = (g_hHook != NULL);
		if (bOk) {
			bOk = PostThreadMessage(dwThreadId, WM_NULL, 0, 0);
		}
		else {
			chASSERT(g_hHook != NULL);
			bOk = UnhookWindowsHookEx(g_hHook);
		}
	}
	return(bOk);
}

LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	static BOOL bFirstTime = TRUE;

	if (bFirstTime) {
		bFirstTime = FALSE;

		ForceDebugBreak();
		CreateDialog(g_hInstDll, MAKEINTRESOURCE(IDD_DIPS), NULL, Dlg_Proc);
		
		PostThreadMessage(g_dwThreadIdDIPS, WM_NULL, 0, 0);
	}
	return(CallNextHookEx(g_hHook, nCode, wParam, lParam));
}

void Dlg_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
}

static const TCHAR g_szRegSubKey[] = _T("Software\\Wintellect\\Desktop Item Position Saver");

void SaveListViewItemPositions(HWND hWndLV)
{
	int nMaxItems = ListView_GetItemCount(hWndLV);

	LONG l = RegDeleteKey(HKEY_CURRENT_USER, g_szRegSubKey);

	HKEY hKey;
	l = RegCreateKeyEx(HKEY_CURRENT_USER, g_szRegSubKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL);

	for (int nItem = 0; nItem < nMaxItems; nItem++) {
		TCHAR szName[MAX_PATH];
		LPWSTR b;
		WCHAR a;
		ListView_GetItemText(hWndLV, nItem, 0, szName, MAX_PATH);
		POINT pt;
		ListView_GetItemPosition(hWndLV, nItem, &pt);
		l = RegSetKeyValue(hKey, szName, 0, REG_BINARY, &pt, sizeof(pt));
		chASSERT(l == ERROR_SUCCESS);
	}
	RegCloseKey(hKey);
}

void RestoreListViewItemPositions(HWND hWndLV)
{
	HKEY hKey;

	LONG l = RegOpenKeyEx(HKEY_CURRENT_USER, g_szRegSubKey, 0, KEY_QUERY_VALUE, &hKey);

	if (l == ERROR_SUCCESS) {
		DWORD dwStyle = GetWindowStyle(hWndLV);

		if (dwStyle & LVS_AUTOARRANGE)
			SetWindowLong(hWndLV, GWL_STYLE, dwStyle & LVS_AUTOARRANGE);

		l = NO_ERROR;
		for (int nIndex = 0; l != ERROR_NO_MORE_ITEMS; l++) {
			TCHAR szName[MAX_PATH];
			DWORD cbValueName = _countof(szName);

			POINT pt;
			DWORD cbData = sizeof(pt), nItem;

			DWORD dwType;
			l = RegEnumValue(hKey, nIndex, szName, &cbValueName, NULL, &dwType, (PBYTE)&pt, &cbData);
			if (l == ERROR_NO_MORE_ITEMS)
				continue;
			if ((dwType == REG_BINARY) && (cbData == sizeof(pt))) {
				LV_FINDINFO lvfi;
				lvfi.flags = LVFI_STRING;
				lvfi.psz = szName;
				nItem = ListView_FindItem(hWndLV, 0, &lvfi);
				if (nItem != -1) {
					ListView_SetItemPosition(hWndLV, nIndex, pt.x, pt.y);
				}
			}
		}
		SetWindowLong(hWndLV, GWL_STYLE, dwStyle);
		RegCloseKey(hKey);
	}	
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		chHANDLE_DLGMSG(hWnd, WM_CLOSE, Dlg_OnClose);
	case WM_APP:
		if (lParam)
			SaveListViewItemPositions((HWND)wParam);
		else
			RestoreListViewItemPositions((HWND)wParam);
	}
	return(FALSE);
}