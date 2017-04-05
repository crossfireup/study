/*
 * compile:
 *    cl /GS /FAsc /Zi gs_test.c /Fegs_test
 *
 */
#include <windows.h>

/* force gs check when bufsize <= 4, /GS diable by default */
#pragma strict_gs_check(on)  

void vulnearable(char *s)
{
    char b[4];

    strcpy(b, s);
}

int main(int argc, char *argv[])
{
    vulnearable(argv[1]);

    return 0;
}
