#include<stdio.h>

int print(int a, int b)
{
    int c = 1;
    int d = 2;
    int e = c + d;
    int f = e + 1;
    return c + d + e + f;
}

int __cdecl main(void)
{
    char a=1;
    char c[]="1234567890";
    char *p="1234567890";
    a = p[1];
    a = c[1];
    printf("a=%d, c=%s, p=%s\n", a, c, p);
    return 0;
}

