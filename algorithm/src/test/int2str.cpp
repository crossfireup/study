#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *int2str(int n, char *s)
{
    const char *digit = "0123456789";
    char sign = '\0';

    if( n < 0){
        sign = '-';
        n *= -1;
    }

    int pos = 0;
    do {
        s[pos++] = digit[n % 10];
        n /= 10;
    } while(n);

    if(sign == '-')
        s[pos++] = sign;

    char tmp = '\0';
    for(int i = 0; i < pos / 2; i++){
        tmp = s[i];
        s[i] = s[pos - i - 1];
        s[pos - i - 1] = tmp;
    }

    s[pos] = '\0';

    return s;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage: %s number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i = atoi(argv[1]);
    char *s = NULL;

    s = (char *) malloc( (strlen(argv[1] ) + 1) * sizeof(char));
    s = int2str(i, s);

    printf("int2str: %s", s);

    exit(EXIT_SUCCESS);
}
