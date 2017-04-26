#include <stdio.h>

#pragma pack(1)
typedef struct _big_struct {
    char data[128];
} big_struct;

big_struct get_big_struct()
{
    big_struct tmp;

    tmp.data[0] = 0;

    return tmp;
}

int main(void)
{
    big_struct bs = get_big_struct();

    return 0;
}
