#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "user32.lib")    

int main(void)  
{     
    BOOL fResult;
    MOUSEKEYS mouseKeys;    // mouse keys
    
    mouseKeys.cbSize = sizeof(MOUSEKEYS);

    // Get the current mouse select.         
    fResult = SystemParametersInfo(SPI_GETMOUSEKEYS,   // Get mouse information
                                   sizeof(MOUSEKEYS),          
                                   &mouseKeys,    // Holds mouse information
                                   0);             // Not used           
                                   
    // Double it.         
    if( fResult )     
    {
        mouseKeys.dwFlags = (mouseKeys.dwFlags & ~MKF_RIGHTBUTTONSEL) | MKF_LEFTBUTTONSEL;
        
        // Change the mouse select to the new value.
       fResult = SystemParametersInfo(SPI_SETMOUSEKEYS,      // Set mouse information
                             sizeof(MOUSEKEYS),               
                             &mouseKeys,        // Mouse information
                             SPIF_SENDCHANGE);  // Update Win.ini
       if(!fResult){
           fprintf(stderr, "call SystemParametersInfo failed: %d\n", GetLastError());
           exit(EXIT_FAILURE);
       }
    } else {
        fprintf(stderr, "call SystemParametersInfo failed: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


