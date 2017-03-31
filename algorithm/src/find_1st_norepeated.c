#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_1st_once(const unsigned char *str, size_t len)
{
    unsigned int i;
    static unsigned int stats[128];

    if(str == NULL || len < 1)
        return -1;
    
    for(i = 0; i < 128; i++){
        stats[i] = 0;
    }

    for(i = 0; i < len; i++){
        stats[str[i]]++;
    }

    for(i = 0; i < len; i++){
        if(stats[str[i]] == 1){
            return i;
        }
    }

    return -1;
}

#define STR_SIZE 200

int main(void)
{
    const char *base64_char="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi" \
        "jklmnopqrstuvwxyz0123456789+/=";
    unsigned char str[STR_SIZE];
    int i;

    srand((int)time(NULL));

    for(i = 0; i < STR_SIZE; i++){
        str[i] = base64_char[rand() % 64];
        putchar(str[i]);
    }

    putchar('\n');

    i = find_1st_once(str, STR_SIZE - 1);

    if(i < 0) {
        printf("no ascii char find\n");
        exit(EXIT_FAILURE);
    } else {
        printf("1st char in %d is %c\n", i, str[i]);
        exit(EXIT_SUCCESS);
    }
}

