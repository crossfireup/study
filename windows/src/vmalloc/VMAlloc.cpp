#include "../comm/CmnHdr.h"
#include "Resource.h"
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>


#define MAX_MYDATA (50)

typedef struct {
	BOOL bInUse;
	BYTE bOtherData[2048 - sizeof(BOOL)];
}MYDATA, *PMYDATA;


UINT g_uPageSize = 0;

PMYDATA g_pMyData = NULL;

RECT g_rcMemMap;

BOOL Dlg_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	EnableWindow(GetDlgItem(hWnd, IDC_INDEXTEXT), FALSE);
	EnableWindow(GetDlgItem(hWnd, IDC_INDEX), FALSE);
	EnableWindow(GetDlgItem(hWnd, IDC_USE), FALSE);
	EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), FALSE);
	EnableWindow(GetDlgItem(hWnd, IDC_GARBAGECOLLECT), FALSE);

	GetWindowRect(GetDlgItem(hWnd, IDC_MEMMAP), &g_rcMemMap);
	MapWindowPoints(NULL, hWnd, (LPPOINT)&g_rcMemMap, 2);
	DestroyWindow(GetDlgItem(hWnd, IDC_MEMMAP));

	TCHAR szBuf[10];
	StringCchPrintf(szBuf, _countof(szBuf), _T("%d KB"), g_uPageSize / 1024);
	SetDlgItemText(hWnd, IDC_PAGESIZE, szBuf);

	SetDlgItemInt(hWnd, IDC_INDEX, 0, FALSE);

	return(TRUE);
}

void Dlg_OnDestroy(HWND hWnd)
{
	if (g_pMyData != NULL) {
		VirtualFree(g_pMyData, 0, MEM_RELEASE);
	}
}

VOID GarbageCollect(PVOID pvBase, DWORD dwNum, DWORD dwStructSize)
{
	UINT uMaxPages = dwNum * dwStructSize / g_uPageSize;
	for (UINT uPage = 0; uPage < uMaxPages; uPage++) {
		BOOL bAnyAllocInThisPage = FALSE;
		UINT uIndex = uPage * g_uPageSize / dwStructSize;
		UINT uIndexLast = uIndex + g_uPageSize / dwStructSize;
		for (; uIndex < uIndexLast; uIndex++) {
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQuery(&g_pMyData[uIndex], &mbi, sizeof(mbi));
			bAnyAllocInThisPage = ((mbi.State == MEM_COMMIT) &&
				* (PBOOL)((PBYTE)pvBase + dwStructSize * uIndex));

			if (bAnyAllocInThisPage)
				break;
		}

		if (!bAnyAllocInThisPage) {
			VirtualFree(&g_pMyData[uIndexLast - 1], dwStructSize, MEM_DECOMMIT);
		}
	}
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	UINT uIndex = 0;

	switch (id) {
	case IDCANCEL:
		EndDialog(hWnd, id);
		break;

	case IDC_RESERVE:
		g_pMyData = (PMYDATA)VirtualAlloc(NULL, MAX_MYDATA * sizeof(MYDATA), MEM_RESERVE, PAGE_READWRITE);

		EnableWindow(GetDlgItem(hWnd, IDC_RESERVE), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_INDEXTEXT), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_INDEX), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_USE), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_GARBAGECOLLECT), TRUE);

		SetFocus(GetDlgItem(hWnd, IDC_INDEX));

		InvalidateRect(hWnd, &g_rcMemMap, FALSE);
		break;

	case IDC_INDEX:
		if (codeNotify != EN_CHANGE)
			break;

		uIndex = GetDlgItemInt(hWnd, IDC_INDEX, NULL, FALSE);
		if ((g_pMyData != NULL) && chINRANGE(0, uIndex, MAX_MYDATA - 1)) {
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQuery(&g_pMyData[uIndex], &mbi, sizeof(mbi));
			BOOL bOk = (mbi.State == MEM_COMMIT);
			if (bOk)
				bOk = g_pMyData[uIndex].bInUse;

			EnableWindow(GetDlgItem(hWnd, IDC_USE), !bOk);
			EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), bOk);
		}
		else {
			EnableWindow(GetDlgItem(hWnd, IDC_USE), FALSE);
			EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), FALSE);
		}
		break;

	case IDC_USE:
		uIndex = GetDlgItemInt(hWnd, IDC_INDEX, NULL, FALSE);
		VirtualAlloc(&g_pMyData[uIndex], sizeof(MYDATA), MEM_COMMIT, PAGE_READWRITE);

		g_pMyData[uIndex].bInUse = TRUE;

		EnableWindow(GetDlgItem(hWnd, IDC_USE), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), TRUE);

		SetFocus(GetDlgItem(hWnd, IDC_CLEAR));

		InvalidateRect(hWnd, &g_rcMemMap, FALSE);
		break;

	case IDC_CLEAR:
		uIndex = GetDlgItemInt(hWnd, IDC_INDEX, NULL, FALSE);
		g_pMyData[uIndex].bInUse = FALSE;
		EnableWindow(GetDlgItem(hWnd, IDC_USE), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_CLEAR), FALSE);

		SetFocus(GetDlgItem(hWnd, IDC_USE));

		InvalidateRect(hWnd, &g_rcMemMap, FALSE);
		break;

	case IDC_GARBAGECOLLECT:
		GarbageCollect(g_pMyData, MAX_MYDATA, sizeof(MYDATA));

		InvalidateRect(hWnd, &g_rcMemMap, FALSE);
		break;
	}
}

void Dlg_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);

	UINT uMaxPages = MAX_MYDATA * sizeof(MYDATA) / g_uPageSize;
	UINT uMemMapWidth = g_rcMemMap.right - g_rcMemMap.left;

	if (g_pMyData == NULL) {
		Rectangle(ps.hdc, g_rcMemMap.left, g_rcMemMap.top, g_rcMemMap.right, g_rcMemMap.bottom);
	}
	else {
		for (UINT uPage = 0; uPage < uMaxPages; uPage++) {
			UINT uIndex = uPage * g_uPageSize / sizeof(MYDATA);
			UINT uIndexLast = uIndex + g_uPageSize / sizeof(MYDATA);
			for (; uIndex < uIndexLast; uIndex++) {
				MEMORY_BASIC_INFORMATION mbi;
				VirtualQuery(&g_pMyData[uIndex], &mbi, sizeof(mbi));

				int nBrush = 0;
				switch (mbi.State) {
				case MEM_FREE:
					nBrush = WHITE_BRUSH;
					break;
				case MEM_RESERVE:
					nBrush = GRAY_BRUSH;
					break;
				case MEM_COMMIT:
					nBrush = BLACK_BRUSH;
					break;
				}

				SelectObject(ps.hdc, GetStockObject(nBrush));
				Rectangle(ps.hdc, g_rcMemMap.left + uMemMapWidth / uMaxPages * uPage,
					g_rcMemMap.top,
					g_rcMemMap.left + uMemMapWidth / uMaxPages * (uPage + 1),
					g_rcMemMap.bottom);
			}
		}
	}
	EndPaint(hWnd, &ps);
}

INT_PTR WINAPI Dlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		chHANDLE_DLGMSG(hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hWnd, WM_COMMAND, Dlg_OnCommand);
		chHANDLE_DLGMSG(hWnd, WM_PAINT, Dlg_OnPaint);
		chHANDLE_DLGMSG(hWnd, WM_DESTROY, Dlg_OnDestroy);
	}
	return(FALSE);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPre, PTSTR, int) {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	g_uPageSize = si.dwPageSize;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_VMALLOC), NULL, Dlg_Proc);
	return(0);
}