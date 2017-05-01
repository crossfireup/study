#include <stdio.h>
#include <wchar.h>
#include <tchar.h>
#include <windowsx.h>
#include <Windows.h>
#include <Winbase.h>
#include <ShlObj.h>
#include <strsafe.h>

extern "C" const IMAGE_DOS_HEADER __ImageBase;

void MessageBoxPrintf(HWND hWnd, UINT uType, PTSTR format, ...)
{
	va_list ap;
	TCHAR szBuff[1024];

	va_start(ap, format);
	vsprintf_s(szBuff, 1024, format, ap);
	MessageBox(hWnd, szBuff, NULL, uType);
	
	va_end(ap);
}

void DumpModule()
{
    HMODULE hModule = GetModuleHandle(NULL);
    _tprintf(_T("with GetModuleHandle(NULL) = 0x%x\r\n"), hModule);

    _tprintf(_T("with __ImageBase = 0x%x\r\n"), (HINSTANCE)&__ImageBase);

    hModule = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
    (PCTSTR)DumpModule,
    &hModule);
    _tprintf(_T("with GetModuleHandleEx = 0x%x\r\n"), hModule);
}

void DumpEnvStrings()
{
	PTSTR pEnvBlock = GetEnvironmentStrings();
	TCHAR szName[MAX_PATH];
	TCHAR szValue[MAX_PATH];;
	PTSTR pszCurrent = pEnvBlock;
	HRESULT hr = S_OK;
	PCTSTR pszPos = NULL;
	int current = 0;

	while (pszCurrent != NULL) {
		if (*pszCurrent != _T('=')) {
			pszPos = _tcschr(pszCurrent, _T('='));

			pszPos++;

			size_t cbNameLength = (size_t)pszPos - (size_t)pszCurrent - sizeof(TCHAR);
			hr = StringCbCopyN(szName, MAX_PATH, pszCurrent, cbNameLength);
			if (FAILED(hr)) {
				break;
			}

			hr = StringCchCopyN(szValue, MAX_PATH, pszPos, _tcslen(pszPos) + 1);
			if (SUCCEEDED(hr)) {
				_tprintf(_T("[%u] %s=%s\r\n"), current, szName, szValue);
			}
			else if (hr == STRSAFE_E_INSUFFICIENT_BUFFER) {
				_tprintf(_T("[%u] %s=%s...\r\n"), current, szName, szValue);
			}
			else {
				_tprintf(_T("[%u] %s=???\r\n"), current, szName);
				break;
			}

		}
		else {
			_tprintf(_T("[%u] %s\r\n"), current, pszCurrent);
		}
		current++;
		while (*pszCurrent != _T('\0'))
			pszCurrent++;
		pszCurrent++;
		if (*pszCurrent == _T('\0'))
			break;
	}

	FreeEnvironmentStrings(pEnvBlock);
}

void EnvExpand(void)
{
	DWORD chValue = ExpandEnvironmentStrings(_T("%PATH%"), NULL, 0);
	PTSTR pszBuffer = new TCHAR[chValue];
	ExpandEnvironmentStrings(_T("%PATH%"), pszBuffer, chValue);
	_tprintf(_T("%PATH%=%s\r\n"), pszBuffer);
	delete pszBuffer;
	return;
}


BOOL GetProcessElevation(DWORD dwProcessId, TOKEN_ELEVATION_TYPE *pElevationType, BOOL *pIsAdmin)
{
	HANDLE hToken = NULL;
	DWORD dwSize;
	HANDLE hProcess = NULL;

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
	if (hProcess == NULL) {
		MessageBoxPrintf(NULL, MB_OK, "open process error: %d\n", GetLastError());
		return FALSE;
	}

	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		return(FALSE);

	CloseHandle(hProcess);

	BOOL bResult = FALSE;

	if (GetTokenInformation(hToken, TokenElevationType, pElevationType,
		sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) {
		BYTE adminSID[SECURITY_MAX_SID_SIZE];
		dwSize = sizeof(adminSID);
		CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID, &dwSize);

		if (*pElevationType == TokenElevationTypeLimited) {
			HANDLE hUnfiltedToken = NULL;
			GetTokenInformation(hToken, TokenLinkedToken, (VOID *)&hUnfiltedToken,
				sizeof(HANDLE), &dwSize);

			if (CheckTokenMembership(hToken, adminSID, pIsAdmin)) {
				bResult = TRUE;
			}

			CloseHandle(hUnfiltedToken);
		}
		else {
			*pIsAdmin = IsUserAnAdmin();
			bResult = TRUE;
		}
	}
	CloseHandle(hToken);
	return(bResult);
}

void ProcessCreate(void)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL ret;
	TCHAR szCmdLine[] = _T("notepad"); //_T("c:\\windows\\system32\\notepad.exe")
	ret = CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (ret == 0) {
		_tprintf(_T("create process error: %d\r\n"), GetLastError());
		return;
	}
	_tprintf(_T("cmdline: %s\r\n"), szCmdLine);

	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = _T("runas");
	sei.lpFile = _T("cmd.exe");
	sei.nShow = SW_SHOWNORMAL;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	if (!ShellExecuteEx(&sei)) {
		int status = GetLastError();
		if (status == ERROR_CANCELLED) {
			MessageBox(NULL, "user canceled", "msg", MB_OK);
		}
		else if (status == ERROR_FILE_NOT_FOUND) {
			MessageBox(NULL, "file not found", "msg", MB_OK);
		}

	}; ;

	TOKEN_ELEVATION_TYPE tet;
	BOOL isAdmin = FALSE;

	if (!GetProcessElevation(GetCurrentProcessId(), &tet, &isAdmin)) {
		MessageBoxPrintf(NULL, MB_OK, _T("GetProcessElevation error: %d"), GetLastError());
	}
		
	if (isAdmin) {
		MessageBox(NULL, _T("Is admin"), NULL, MB_OK);
	}
	else {
		MessageBoxPrintf(NULL, MB_OK, _T("not a admin"));
	}
}

void ShowSysInfo()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	_tprintf("ProcessorArch: %ld\nPageSize: %ld\nMinAppAddr: %ld\nMaxAppAddr: %ld\nAllocationGranularity: %ld\n", 
		si.wProcessorArchitecture, si.dwPageSize, si.lpMinimumApplicationAddress, si.lpMaximumApplicationAddress, si.dwAllocationGranularity);
	return;
}

void ShowProcessors()
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pBuffer = NULL;
	DWORD dwSize = 0;
	DWORD procCoreCount = 0;
	BOOL bResult = GetLogicalProcessorInformation(pBuffer, &dwSize);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
		_tprintf(_T("Impossible to get processor information\r\n"));
		return;
	}

	pBuffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(dwSize);
	bResult = GetLogicalProcessorInformation(pBuffer, &dwSize);
	if (!bResult) {
		free(pBuffer);
		_tprintf(_T("Impossible to get processor information\r\n"));
		return;
	}
	procCoreCount = 0;
	DWORD lpiCount = dwSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	for (DWORD current = 0; current < lpiCount; current++) {
		if (pBuffer[current].Relationship == RelationProcessorCore) {
			_tprintf(_T(" + one CPU core (HYPERTHREADING)\r\n"));
		}
		else {
			_tprintf(_T(" + one CPU socket\r\n"));
		}
		procCoreCount++;
	}
	_tprintf(_T(" -> %d active CPU(s) \r\n"), procCoreCount);

	free(pBuffer);
}

DWORD WINAPI thr_fn(void *arg)
{
	TCHAR szName[] = "hello c world!\r\n";
	for (; ; ) {
		Sleep(10);
	}
}

int _tmain(int argc, TCHAR *argv[])
{
    /*DumpModule();
	DumpEnvStrings();
	EnvExpand();
	ProcessCreate();
	ShowSysInfo();

	ShowProcessors();*/

	HANDLE hThread = CreateThread(NULL, 0, thr_fn, NULL, 0, NULL);
	if (hThread == NULL) {
		MessageBoxPrintf(NULL, MB_OK, "create thread error: %d", GetLastError());
		return(1);
	}
	SuspendThread(hThread);

	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	ctx.ContextFlags = CONTEXT_CONTROL;
	ctx.Eip = 0x00010000;
	SetThreadContext(hThread, &ctx);
	ResumeThread(hThread);
	ResumeThread(hThread);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
    return(0);
}
