#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int delete_ascii_chars(char *str, size_t n_str, char *del, size_t n_del)
{
    int i, j;
    unsigned char signs[128];
    
    if(n_str < 1 || n_del < 1)
        return 0;

    for(i = 0; i < 128; i++){
        signs[i] = 0; 
    }

    for(i = 0; i < n_del; i++){
        signs[del[i]] = 1;
    }

    for(i = 0, j = 0; i < n_str; i++){
        if(!signs[str[i]]){
            str[j++] = str[i];
        }
    }
    str[j+1] = '\0';
    return i - j;
}

#define STR_SIZE 256
#define DEL_SIZE 8

int main(void)
{
    const char *base64_char="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefgh" \
                             "ijklmnopqrstuvwxyz0123456789+/=";
    char str[STR_SIZE+1];
    char del[DEL_SIZE+1];
    int i;

    srand((int)time(NULL));
    for(i = 0; i < STR_SIZE; i++){
        str[i] = base64_char[rand() % 64];
    }
    str[STR_SIZE] = '\0';

    for(i = 0; i < DEL_SIZE; i++){
        del[i] = base64_char[rand() % 64];
    }
    del[DEL_SIZE] = '\0';

    printf("string:%s\ndelete chars:%s\n",str, del);

    i = delete_ascii_chars(str, STR_SIZE, del, DEL_SIZE);

    printf("delete %d char(s), result:%s\n", i, str);
}
