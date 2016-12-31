#include <windows.h>
#include <winbase.h>
#include <windowsx.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <malloc.h>
#include <TLHelp32.h>

#include "../../../comm/CmnHdr.h"
#include "Resource.h"

#ifdef UNICODE
#define InjectLib InjectLibW
#define EjectLib EjectLibW
#else
#define InjectLib InjectLibA
#define EjectLib EjectLibA
#endif

BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile)
{
	BOOL bOk = FALSE;
	HANDLE hProcess = NULL, hThread = NULL;
	PWSTR pszLibFileRemote = NULL;

	__try {
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_CREATE_THREAD |
			PROCESS_VM_OPERATION |
			PROCESS_VM_WRITE,
			FALSE,
			dwProcessId);
		if (hProcess == NULL) __leave;

		int cch = 1 + lstrlenW(pszLibFile);
		int cb = cch * sizeof(wchar_t);

		pszLibFileRemote = (PWSTR)VirtualAllocEx(hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
		if (pszLibFileRemote == NULL) __leave;

		if (!WriteProcessMemory(hProcess, pszLibFileRemote, (PVOID)pszLibFile, cb, NULL)) __leave;

		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("Kernel32")), "LoadLibraryW");

		if (pfnThreadRtn == NULL) __leave;

		hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, pszLibFileRemote, 0, NULL);
		if (hThread == NULL) __leave;

		WaitForSingleObject(hThread, INFINITE);

		bOk = TRUE;
	}
	__finally {
		if (pszLibFileRemote != NULL) {
			VirtualFreeEx(hProcess, pszLibFileRemote, 0, MEM_RELEASE);
		}

		if (hThread != NULL)
			CloseHandle(hThread);
		if (hProcess != NULL)
			CloseHandle(hProcess);
	}
	return(bOk);
}

BOOL WINAPI InjectLibA(DWORD dwProcessId, PCSTR pszLibFiile)
{
	SIZE_T cchSize = lstrlenA(pszLibFiile) + 1;
	PWSTR pszLibFileW = (PWSTR)_alloca(cchSize * sizeof(wchar_t));

	StringCchPrintfW(pszLibFileW, cchSize, L"%S", pszLibFiile);

	return(InjectLibW(dwProcessId, pszLibFileW));
}

BOOL WINAPI EjectLibW(DWORD dwProcessId, PCTSTR pszLibFile)
{
	BOOL bOk = FALSE;
	HANDLE hthSnapshot = NULL;
	HANDLE hProcess = NULL, hThread = NULL;

	__try {
		hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if (hthSnapshot == NULL) __leave;

		MODULEENTRY32W me = { sizeof(me) };
		BOOL bFound = FALSE;
		BOOL bMoreMods = Module32FirstW(hthSnapshot, &me);
		for (; bMoreMods; bMoreMods = Module32NextW(hthSnapshot, &me)) {
			bFound = (_wcsicmp(me.szExePath, pszLibFile) == 0);
			if (bFound)
				break;
		}
		if (!bFound) __leave;

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_CREATE_THREAD |
			PROCESS_VM_OPERATION,
			FALSE,
			dwProcessId);
		if (hProcess == NULL) __leave;

		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("Kernel32")), "FreeLibrary");
		if (pfnThreadRtn == NULL) __leave;

		hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, me.modBaseAddr, 0, NULL);
		if (hThread == NULL) __leave;

		WaitForSingleObject(hThread, INFINITE);

		bOk = TRUE;
	}
	__finally {
		if (hthSnapshot != NULL)
			CloseHandle(hthSnapshot);

		if (hThread != NULL)
			CloseHandle(hThread);
		
		if (hProcess != NULL)
			CloseHandle(hProcess);
	}
	return(bOk);
}

BOOL WINAPI EjectLibA(DWORD dwProcessId, PCSTR pszLibFile)
{
	SIZE_T cchSize = lstrlenA(pszLibFile) + 1;
	PWSTR pszLibFileW = (PWSTR)_alloca(cchSize * sizeof(wchar_t));
	StringCchPrintfW(pszLibFileW, cchSize, L"%S", pszLibFile);
	return(EjectLibW(dwProcessId, pszLibFileW));
}

BOOL Dlg_OnInitDialog(HWND hWnd, HANDLE hWndFocus, LPARAM lParam)
{
	Static_SetIcon(hWnd, IDI_INJLIB);
	return(TRUE);
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT uCodeNofity)
{
	switch (id) {
	case IDCANCEL:
		EndDialog(hWnd, id);
		break;
	case IDC_INJECT:
		DWORD dwProcessId = GetDlgItemInt(hWnd, IDC_PROCESSID, NULL, FALSE);
		if (dwProcessId == 0) {
			dwProcessId = GetCurrentProcessId();
		}

		TCHAR szLibFile[MAX_PATH];
		GetModuleFileName(NULL, szLibFile, MAX_PATH);
		PTSTR pFileName = _tcsrchr(szLibFile, _T('\\')) + 1;
		_tcscpy_s(pFileName, _countof(szLibFile) - (pFileName - szLibFile ), _T("ImageWalk.dll"));
		if (InjectLib(dwProcessId, szLibFile)) {
			chVERIFY(EjectLib(dwProcessId, szLibFile));
			chMB("DLL Injection/Ejection successful.");
		}
		else {
			chMB("DLL Injection/Ejection failed.");
		}
		break;
	}
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, Dlg_OnCommand);
	}
	return(FALSE);
}

int _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTSTR pszCmdLine, int nShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_INJLIB), NULL, Dlg_Proc);
	return(0);
}