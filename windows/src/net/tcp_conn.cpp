#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <stdio.h>

// Need to link with Iphlpapi.lib and Ws2_32.lib
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
/* Note: could also use malloc() and free() */

int main()
{

    // Declare and initialize variables
    PMIB_TCPTABLE2 pTcpTable;
    ULONG ulSize = 0;
    DWORD dwRetVal = 0;

    char szLocalAddr[128];
    char szRemoteAddr[128];

    struct in_addr IpAddr;

    int i;

    pTcpTable = (MIB_TCPTABLE2 *) MALLOC(sizeof (MIB_TCPTABLE2));
    if (pTcpTable == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    ulSize = sizeof (MIB_TCPTABLE);
// Make an initial call to GetTcpTable2 to
// get the necessary size into the ulSize variable
    if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable);
        pTcpTable = (MIB_TCPTABLE2 *) MALLOC(ulSize);
        if (pTcpTable == NULL) {
            printf("Error allocating memory\n");
            return 1;
        }
    }
// Make a second call to GetTcpTable2 to get
// the actual data we require
    if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) == NO_ERROR) {
        printf("Number of entries: %d\n", (int) pTcpTable->dwNumEntries);
        printf("%-18s  %-15s  %-5s  %-15s  %-5s  %-8s  %-10s\n",
                "TCP State", "Local Addr", "Local Port", "Remote Addr", "Remote Port", "Pid", "Name");
        for (i = 0; i < (int) pTcpTable->dwNumEntries; i++) {
            printf("%03d - ", i,
                   pTcpTable->table[i].dwState);
            switch (pTcpTable->table[i].dwState) {
            case MIB_TCP_STATE_CLOSED:
                printf("%-12s  ", "CLOSED");
                break;
            case MIB_TCP_STATE_LISTEN:
                printf("%-12s  ", "LISTEN");
                break;
            case MIB_TCP_STATE_SYN_SENT:
                printf("%-12s  ", "SYN-SENT");
                break;
            case MIB_TCP_STATE_SYN_RCVD:
                printf("%-12s  ", "SYN-RECEIVED");
                break;
            case MIB_TCP_STATE_ESTAB:
                printf("%-12s  ", "ESTABLISHED");
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
                printf("%-12s  ", "FIN-WAIT-1");
                break;
            case MIB_TCP_STATE_FIN_WAIT2:
                printf("%-12s  ", "FIN-WAIT-2 ");
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
                printf("%-12s  ", "CLOSE-WAIT");
                break;
            case MIB_TCP_STATE_CLOSING:
                printf("%-12s  ", "CLOSING");
                break;
            case MIB_TCP_STATE_LAST_ACK:
                printf("%-12s  ", "LAST-ACK");
                break;
            case MIB_TCP_STATE_TIME_WAIT:
                printf("%-12s  ", "TIME-WAIT");
                break;
            case MIB_TCP_STATE_DELETE_TCB:
                printf("%-12s  ", "DELETE-TCB");
                break;
            default:
                wprintf(L"UNKNOWN dwState value: %d", pTcpTable->table[i].dwState);
                break;
            }

            IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwLocalAddr;
            strcpy_s(szLocalAddr, sizeof (szLocalAddr), inet_ntoa(IpAddr));
            printf("%-20s", szLocalAddr);

            printf("%-10d", ntohs((u_short)pTcpTable->table[i].dwLocalPort));

            IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwRemoteAddr;
            strcpy_s(szRemoteAddr, sizeof (szRemoteAddr), inet_ntoa(IpAddr));
            printf("%-20s", szRemoteAddr);

            printf("%-10d",
                   ntohs((u_short)pTcpTable->table[i].dwRemotePort));
                   
            printf("%-9d", pTcpTable->table[i].dwOwningPid);

			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if(hSnapshot) {
				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if(Process32First(hSnapshot, &pe32)) {
					do {
						if (pe32.th32ProcessID == pTcpTable->table[i].dwOwningPid){
							printf("%s\n", pe32.szExeFile);
							break;
						}
					} while(Process32Next(hSnapshot, &pe32));
					if(pe32.th32ProcessID != pTcpTable->table[i].dwOwningPid)
						printf("\n");
				} else {
                    printf("\n");
                }
				CloseHandle(hSnapshot);
			}

#if 0
            printf("%ld - ",
                   pTcpTable->table[i].dwOffloadState);
            switch (pTcpTable->table[i].dwOffloadState) {
            case TcpConnectionOffloadStateInHost:
                printf("Owned by the network stack and not offloaded \n");
                break;
            case TcpConnectionOffloadStateOffloading:
                printf("In the process of being offloaded\n");
                break;
            case TcpConnectionOffloadStateOffloaded:
                printf("Offloaded to the network interface control\n");
                break;
            case TcpConnectionOffloadStateUploading:
                printf("In the process of being uploaded back to the network stack \n");
                break;
            default:
                printf("UNKNOWN Offload state value\n");
                break;
            }
#endif
        }
    } else {
        printf("\tGetTcpTable2 failed with %d\n", dwRetVal);
        FREE(pTcpTable);
        return 1;
    }

    if (pTcpTable != NULL) {
        FREE(pTcpTable);
        pTcpTable = NULL;
    }

    return 0;    
}

