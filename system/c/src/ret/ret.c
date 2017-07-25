#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int ret = -2;

    int a0 = !ret;
    int a1 = !!ret;

    printf("a0 = %d\n", a0);
    printf("a1 = %d\n", a1);

    return EXIT_SUCCESS;
}
