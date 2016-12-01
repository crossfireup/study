#include<stdio.h>

int print_int(int num)
{
    printf("int is %d\n", num);
    return num;
}

int add(int a, int b)
{
    int c = a + b;
    return c;
}

int main(void)
{
    int i = 3, j = 4;
    int k = add(print_int(i), print_int(j));
    printf("k is %d\n", k); 
    return 0;
}

