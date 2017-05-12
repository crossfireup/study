#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if(argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *fname = argv[1];
    struct stat f_stat = {0};

    if(stat(fname, &f_stat) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if(unlink(fname) == -1){
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "delete %s success\n", fname);

    exit(EXIT_SUCCESS);
}
