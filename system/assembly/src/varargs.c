#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int my_print(int code, char *fmt, ...)
{
    char *p = NULL;
    int size = 0;
    va_list ap;
    va_start(ap, fmt);

    size = vsnprintf(p, size, fmt, ap);
    if (size > 0)
        p = (char *)malloc(size);
    else
        return -1;
    vsnprintf(p, size, fmt, ap);
    fprintf(stdout, p);
    free(p);
    va_end(ap);
    return(code);
}

int main(void)
{
    my_print(1, "this a test:%d %s\n", 8888, "Helloc");
    return(0);
}
