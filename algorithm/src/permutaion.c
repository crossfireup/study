#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void permutation(const char *str,const size_t slen, char *res, \
         size_t rlen, unsigned char *selected)
{
    unsigned int i;

    /* arrive at the end of str */
    if(rlen == slen ){
        for(i = 0; i < slen; i++){
            putchar(res[i]);
        } 
        putchar('\n');

        return;
    }

    for(i = 0; i < slen; i++){
        if(selected[i])
            continue;
        /* select a elemant */
        selected[i] = 1;
        res[rlen++] = str[i];
        permutation(str, slen, res, rlen, selected);
        selected[i] = 0;
        rlen--;
    }

    return;
}

int main(int argc, char *argv[])
{
    int ret = EXIT_SUCCESS;
    int i;
    int nlen;
    char *str;
    char *res;
    unsigned char *selected;

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
        ret = EXIT_FAILURE;
        goto out;
    }
    
    if((selected = (unsigned char *) malloc(nlen * sizeof(unsigned char))) == NULL){
        perror("malloc fialed");
        ret = EXIT_FAILURE;
        goto out;
    }

    srand((int)time(NULL));
    for(i = 0; i < nlen; i++){
        selected[i] = 0;
        res[i] = '\0';
        str[i] = argv[1][i];
        putchar(str[i]);
    }
    putchar('\n');

    permutation(str, nlen , res, 0, selected);

out:
    if(str) free(str);
    if(res) free(res);
    if(selected) free(selected);

    exit(ret);
}
