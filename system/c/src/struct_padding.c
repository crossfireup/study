#include <stdio.h>
#include <stdlib.h>

#ifdef bool
#undef bool
#endif

typedef enum {
    false = 0,
    true = 1
}bool;

#define GET_OFF_PAD(name, type, n_type, offset, align, padding, before_pad) \
    get_off_pad((#name"\t"#type), sizeof(type), sizeof(n_type), (offset), (align), (padding), (before_pad) )

typedef struct _test {
    char data1;
    short data2;
    int data3;
    char data4;
}test;

#define offset_of(type, member) \
    (int)&(((type *) 0 )->member )

int get_off_pad(const char *name, const int len, const int n_len, \
        const int offset, const int align, int *padding, bool before_pad, const int left)
{
    int back_pad = 0;
    int new_offset = 0;
    int next_offset = 0;

    if(align == 0)
    {
        *padding = 0;
        return new_offset;
    }

    if(before_pad){
        back_pad = (align - (offset & (align-1))) & (align - 1);
        new_offset = (offset + back_pad) & ~(align - 1);
    } else {
        new_offset = offset;
    }

    *padding = (len + 1)& ~1;
    if((*padding + n_len)> align)
    {
        *padding = align - len;
    } else {
        *padding = *padding - len;
    }
    next_offset = new_offset + *padding + len;
    printf("%-8s\t%5d\t%5d\n", name, new_offset, *padding);

    return next_offset;
}

int main()
{
    test t;
    int offset = 0;
    int padding = 0;

    printf("%d\n", offset_of(test, data1));
    printf("%d\n", offset_of(test, data2));
    printf("%d\n", offset_of(test, data3));
    printf("%d\n", offset_of(test, data4));
    offset = GET_OFF_PAD(t.data1, char, short, offset, 4, &padding, true);
    offset = GET_OFF_PAD(t.data2, short, int, offset, 4, &padding, false);
    offset = GET_OFF_PAD(t.data3, int, char, offset, 4, &padding, false);
    offset = GET_OFF_PAD(t.data4, char, int, offset, 4, &padding, false);

    exit(EXIT_SUCCESS);
}
