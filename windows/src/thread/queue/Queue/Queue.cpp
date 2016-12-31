#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>
#include <process.h>

#include "Resource.h"

class CQueue {
public:
	struct Element {
		int m_nThreadNum, m_nRequestNum;
	};

	typedef Element *PELEMENT;

private:
	PELEMENT m_pElements;
	int m_nMaxElements;
	HANDLE m_h[2];
	HANDLE &m_hmtxQ;
	HANDLE &m_hsemNumElements;

public:
	CQueue(int nMaxElements);
	~CQueue();

	BOOL Append(PELEMENT pElement, DWORD dwMilliseconds);
	BOOL Remove(PELEMENT pElement, DWORD dwMilliseconds);
};

CQueue::CQueue(int nMaxElements)
	: m_hmtxQ(m_h[0]), m_hsemNumElements(m_h[1])
{
	m_pElements = (PELEMENT)HeapAlloc(GetProcessHeap(), 0, nMaxElements * sizeof(Element));
	m_nMaxElements = nMaxElements;
	m_hmtxQ = CreateMutex(NULL, FALSE, NULL);
	m_hsemNumElements = CreateSemaphore(NULL, 0, nMaxElements, NULL);
}

CQueue::~CQueue()
{
	CloseHandle(m_hsemNumElements);
	CloseHandle(m_hmtxQ);
	HeapFree(GetProcessHeap(), 0, m_pElements);
}

BOOL CQueue::Append(PELEMENT pElement, DWORD dwMilliseconds)
{
	BOOL fOk = FALSE;
	DWORD dw = WaitForSingleObject(m_hmtxQ, dwMilliseconds);
	if (dw == WAIT_OBJECT_0) {
		long lPreCount;
		fOk = ReleaseSemaphore(m_hsemNumElements, 1, &lPreCount);
		if (fOk) {
			m_pElements[lPreCount] = *pElement;
		}
		else {
			SetLastError(dw);
		}
		ReleaseMutex(m_hmtxQ);
	}
	else {
		SetLastError(ERROR_TIMEOUT);
	}
	return(fOk);
}

BOOL CQueue::Remove(PELEMENT pElement, DWORD dwMilliseconds)
{
	BOOL fOk =  (WaitForMultipleObjects(_countof(m_h), m_h, TRUE, dwMilliseconds) == WAIT_OBJECT_0);
	if (fOk) {
		*pElement = m_pElements[0];
		MoveMemory(m_pElements, &m_pElements[1], sizeof(Element) * m_nMaxElements - 1);

		ReleaseMutex(m_hmtxQ);
	}
	else {
		SetLastError(ERROR_TIMEOUT);
	}
	return fOk;
}

CQueue g_q(10);
volatile LONG g_fShutdown = FALSE;
HWND g_hwnd;

HANDLE g_hThreads[MAXIMUM_WAIT_OBJECTS];
int g_nNumThreads = 0;

DWORD WINAPI ClientThread(PVOID pvParam)
{
	int nThreadNum = PtrToLong(pvParam);
	HWND hWndLB = GetDlgItem(g_hwnd, IDC_CLIENTS);
	
	int nRequestNum = 0;
	while ((PVOID)1 != InterlockedCompareExchangePointer((PVOID *)&g_fShutdown, (PVOID)0, (PVOID)0)) {
		nRequestNum++;
		TCHAR sz[1024];
		CQueue::Element e = { nThreadNum, nRequestNum };
		if (g_q.Append(&e, 200)) {
			StringCchPrintf(sz, _countof(sz), _T("Sending %d:%d"), nThreadNum, nRequestNum);
		}
		else {
			StringCchPrintf(sz, _countof(sz), _T("Sending %d:%d (%s)"),
				nThreadNum, nRequestNum, (GetLastError() == ERROR_TIMEOUT) ? _T("timeout") : _T("full"));
		}
		ListBox_SetCurSel(hWndLB, ListBox_AddString(hWndLB, sz));
		Sleep(2500);
	}
	return(0);
}

DWORD WINAPI ServerThread(PVOID pvParam)
{
	int nThreadNum = PtrToLong(pvParam);
	HWND hwndLB = GetDlgItem(g_hwnd, IDC_SERVERS);

	while ((PVOID)1 != InterlockedCompareExchangePointer((PVOID *)&g_fShutdown, (PVOID)0, (PVOID)0)) {
		TCHAR sz[1024];
		CQueue::Element e;
		if (g_q.Remove(&e, 5000)) {
			StringCchPrintf(sz, _countof(sz), _T("%d: Processing %d:%d"), nThreadNum, e.m_nThreadNum, e.m_nRequestNum);
			Sleep(2000 * e.m_nThreadNum);
		}
		else {
			StringCchPrintf(sz, _countof(sz), _T("%d: (timeout)"), nThreadNum);
		}

		ListBox_SetCurSel(hwndLB, ListBox_AddString(hwndLB, sz));
	}
	return(0);
}

BOOL Dlg_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	Static_SetIcon(hWnd, IDI_QUEUE);

	g_hwnd = hWnd;

	DWORD hThreadId;

	for (int x = 0; x < 4; x++) 
		g_hThreads[g_nNumThreads++] = (HANDLE)_beginthreadex(NULL, 0, 
			(_beginthreadex_proc_type) ClientThread, 
			(PVOID)(INT_PTR)x, 0, (UINT *)&hThreadId);

	for(int x = 0; x < 2; x++)
		g_hThreads[g_nNumThreads++] = (HANDLE)_beginthreadex(NULL, 0,
		(_beginthreadex_proc_type)ServerThread,
			(PVOID)(INT_PTR)x, 0, (UINT *)&hThreadId);

	return(TRUE);
}

void Dlg_OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT codeNotify)
{
	switch (id) {
	case IDCANCEL:
		EndDialog(hWnd, id);
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

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PTSTR pszCmdLine, int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_QUEUE), NULL, Dlg_Proc);
	InterlockedExchange(&g_fShutdown, TRUE);

	WaitForMultipleObjects(g_nNumThreads, g_hThreads, TRUE, INFINITE);
	while (g_nNumThreads--)
		CloseHandle(g_hThreads[g_nNumThreads]);

	return(0);
}