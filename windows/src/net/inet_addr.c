#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>
#include <windows.h>


// need link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int __cdecl main(int argc, char **argv)
{

    //-----------------------------------------
    // Declare and initialize variables
    WSADATA wsaData;
    int iResult;

    unsigned long ulAddr = INADDR_NONE;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s <IPv4 address>\n", argv[0]);
        printf("  inetaddr converts a string containing an\n");
        printf("  IPv4 address in one of the supported formats\n");
        printf("  to a unsigned long representing an IN_ADDR\n");
        printf("      %s 192.168.16.34\n", argv[0]);
        return 1;
    }
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

//--------------------------------
// Call inet_addr(). If the call succeeds,
// the result variable will hold a IN_ADDR
    ulAddr = inet_addr(argv[1]);
    if ( ulAddr == INADDR_NONE ) {
        printf("inet_addr failed and returned INADDR_NONE\n");
        WSACleanup();
        return 1;
    }   
    
    if (ulAddr == INADDR_ANY) {
        printf("inet_addr failed and returned INADDR_ANY\n");
        WSACleanup();
        return 1;  
    }

    printf("inet_addr returned success\n");
    
    // Here we could implement code to retrieve each address and 
    // print out the hex bytes
    int i = 0;
    char *ptr = NULL;
     for(i=0, ptr= (char *) &ulAddr; i < 4; i++, ptr++) {
         printf("%x ", (unsigned char)*ptr);
     }

    WSACleanup();
    return 0;
}
