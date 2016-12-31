#include <windows.h>
#include <winbase.h>
#include <tchar.h>

#include "../../../comm/CmnHdr.h"


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID fimpLoad)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		char szBuf[MAX_PATH * 100] = { 0 };
		PBYTE pb = NULL;

		MEMORY_BASIC_INFORMATION mbi;
		while (VirtualQuery(pb, &mbi, sizeof(mbi))) {
			int nLen;
			char szModName[MAX_PATH];

			if (mbi.State == MEM_FREE)
				mbi.AllocationBase = mbi.BaseAddress;

			if ((mbi.AllocationBase == hInstance) || (mbi.AllocationBase != mbi.BaseAddress) || (mbi.BaseAddress == NULL)) {
				nLen = 0;
			}
			else {
				nLen = GetModuleFileNameA((HINSTANCE)mbi.AllocationBase, szModName, _countof(szModName));
			}

			if (nLen > 0) {
				wsprintfA(strchr(szBuf, 0), "n%p-%s\n", mbi.AllocationBase, szModName);
			}
			pb += mbi.RegionSize;
		}

		chMB(&szBuf[1]);
	}
	return(TRUE);
}