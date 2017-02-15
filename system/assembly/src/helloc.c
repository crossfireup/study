#include <stdio.h>

int print_int(int a, int b)
{
    printf("a=%d, b=%d\n", a, b);
    return a+b;
}

int main(void)
{
    print_int(1, 2);
    return 0;
}
