#include <stdio.h>
#include <windows.h>
#include <tchar.h>

BOOL CALLBACK EnumResourceNameCallback(HMODULE hModule, LPCTSTR lpType,
    LPWSTR lpName, LONG_PTR lParam)
{
    HRSRC hResInfo = FindResource(hModule, lpName, lpType);
    DWORD cbResource = SizeofResource(hModule, hResInfo);

    HGLOBAL hResData = LoadResource(hModule, hResInfo);
    const BYTE *pResource = (const BYTE *)LockResource(hResData);

    TCHAR filename[MAX_PATH];
    if (IS_INTRESOURCE(lpName))
        _stprintf_s(filename, _T("#%d.manifest"), lpName);
    else
        _stprintf_s(filename, _T("%s.manifest"), lpName);

    FILE *f = _tfopen(filename, _T("wb"));
    fwrite(pResource, cbResource, 1, f);
    fclose(f);

    UnlockResource(hResData);
    FreeResource(hResData);

    return TRUE;   // Keep going
}

int _tmain(int argc, _TCHAR* argv[])
{
    const TCHAR *pszFileName = argv[1];

    HMODULE hModule = LoadLibraryEx(pszFileName, NULL, LOAD_LIBRARY_AS_DATAFILE);
    EnumResourceNames(hModule, RT_MANIFEST, EnumResourceNameCallback, NULL);
    FreeLibrary(hModule);

    return 0;
}
