#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void combine (const char *str, const size_t slen, char *res, \
        size_t rlen, size_t pos)
{
    unsigned int i;
    unsigned int j;

    for(i = pos; i < slen; i++){
        res[rlen++] = str[i];

        for(j = 0; j < rlen; j++){
            putchar(res[j]);
        }
        putchar('\n');

        pos++;
        combine(str, slen, res, rlen, pos);
        rlen--;
    }

    return;
}

int main(int argc, char *argv[])
{
    int i;
    int nlen;
    char *str;
    char *res;

    if(argc < 2){
        fprintf(stderr, "Usage: %s <chars>\n", argv[0] );
        exit(EXIT_FAILURE);
    }

    nlen = strlen(argv[1]);

    if(nlen < 1){
        fprintf(stderr, "Usage: %s <chars>\n", argv[0] );
        exit(EXIT_FAILURE);
    }

    if((str = (char *) malloc(nlen * sizeof(char))) == NULL){
        perror("malloc fialed");
        exit(EXIT_FAILURE);
    }

    if((res = (char *) malloc(nlen * sizeof(char))) == NULL){
        perror("malloc fialed");
        free(str);
        exit(EXIT_FAILURE);
    }

    srand((int)time(NULL));
    for(i = 0; i < nlen; i++){
        str[i] = argv[1][i];
        res[i] = '\0';
        putchar(str[i]);
    }
    putchar('\n');

    combine(str, nlen, res, 0, 0);

    free(str);
    free(res);

    exit(EXIT_SUCCESS);
}
