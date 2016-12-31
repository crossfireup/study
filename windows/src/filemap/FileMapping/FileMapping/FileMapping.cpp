#include <Windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <strsafe.h>

#include "FileMapping.h"
#include "resource.h"

BOOL Dlg_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	Static_SetIcon(hWnd, IDI_FILEMAPPING);
	Edit_SetText(GetDlgItem(hWnd, IDC_DATA), _T("Some test data"));
	Button_Enable(GetDlgItem(hWnd, IDC_CLOSE), FALSE);
	return TRUE;
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	static HANDLE s_hFileMap = NULL;
	switch (id) {
	case IDCANCEL:
		EndDialog(hWnd, id);
		break;
	case IDC_CREATE:
		if (codeNotify != BN_CLICKED)
			break;
#if 0
		HANDLE hFile = CreateFile(_T("test.dat"),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
#endif // 0

		s_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			4 * 1024,
			_T("FileMappingShareData"));
		if (s_hFileMap != NULL) {
			if (GetLastError() == ERROR_ALIAS_EXISTS) {
				MessageBox(hWnd, _T("Mapping Already exists\r\n"), NULL, MB_OK);
			}
			else {
				PVOID pView = MapViewOfFile(s_hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

				if (pView != NULL) {
					Edit_GetText(GetDlgItem(hWnd, IDC_DATA), (PTSTR)pView, 4 * 1024);

					UnmapViewOfFile(pView);

					Button_Enable(hWndCtl, FALSE);
					Button_Enable(GetDlgItem(hWnd, IDC_CLOSE), TRUE);
				}
			}
		}
		else {
			MessageBox(hWnd, _T("Can't create file mapping\r\n"), NULL, MB_OK);
		}
		break;
	case IDC_CLOSE:
		if (codeNotify != BN_CLICKED)
			break;

		if (CloseHandle(s_hFileMap)) {
			Button_Enable(GetDlgItem(hWnd, IDC_CREATE), TRUE);
			Button_Enable(hWndCtl, FALSE);
		}
		break;
	case IDC_OPEN:
		if (codeNotify != BN_CLICKED)
			break;

		HANDLE hFileMapT = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, 0, _T("FileMappingShareData"));

		if (hFileMapT != NULL) {
			PVOID pView = MapViewOfFile(hFileMapT, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

			if (pView != NULL) {
				Edit_SetText(GetDlgItem(hWnd, IDC_DATA), (PTSTR)pView);
				UnmapViewOfFile(pView);
			}
			else {
				MessageBox(hWnd, _T("Can't map view\r\r"), NULL, MB_OK);
			}
		}
		else {
			MessageBox(hWnd, _T("Can't open map\r\r"), NULL, MB_OK);
		}
		CloseHandle(hFileMapT);
		break;
	}
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		Dlg_OnInitDialog(hWnd, (HWND)(wParam), lParam);
		break;
	case WM_COMMAND:
		// HANDLE_WM_COMMAND(hWnd, wParam, lParam, Dlg_OnCommand);
		Dlg_OnCommand(hWnd, (int)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
		break;
	}
	return(FALSE);
}

typedef BOOL (WINAPI *MY_FN)(HWND hWndNewOwner);
#pragma comment(linker, "/export:OpenClipboard=_OpenClipboard@4")

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstancePre, PTSTR lpCmdLine, int nShowCmd)
{
	// DialogBox(hInstance, MAKEINTRESOURCE(IDD_FILEMAPPING), NULL, Dlg_Proc);
	HMODULE hModule = LoadLibrary("USER32.dll");
	if (hModule == NULL) {
		MessageBox(NULL, _T("LoadLibrary error\r\n"), NULL, MB_OK);
		return(1);
	}
	MY_FN fn = (MY_FN)GetProcAddress(hModule, _T("OpenClipboard"));
	if (fn == NULL) {
		TCHAR szMsg[1024];
		StringCchPrintf(szMsg, 1024, _T("GetProcAddress error:%ld\r\r"), GetLastError());
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return(2);
	}
	if (!fn(NULL)) {
		MessageBox(NULL, _T("OpenClipboard error\r\r"), NULL, MB_OK);
		return(3);
	}
	EmptyClipboard();
	GLOBALHANDLE gMem = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 1024);
	PTCHAR p = (PTCHAR) GlobalLock(gMem);
	memcpy(p, _T("helloc world\r\n"), 1024);
	GlobalUnlock(gMem);
	SetClipboardData(CF_TEXT, gMem);
	CloseClipboard();
	GlobalFree(gMem);
	FreeLibrary(hModule);
	return(0);
}