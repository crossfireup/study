#include <iostream>

#define IS_NUMBER(x) ((x) >= '0' && (x) <= '9')

long strtol(const char *s, const char *endptr)
{
    long l = 0;
    int sign = 1;
    int len = 0;
    int pos = 0;

    endptr = s;

    if(s == NULL || (len = strlen(s)) < 1){
        return l;
    }

    if(s[pos] == '-'){
        sign = -1;
        pos++;
        endptr++;
    }

    while(pos <= len){
        if(IS_NUMBER(s[pos])){
            l = l * 10 + s[pos] - '0';
            endptr++;
            pos++;
        } else {
            endptr = s;
            break;
        }
    }

    l *= sign;

    return l;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage: %s number", argv[0]);
        return(-1);
    }

    char *endptr = NULL;
    long l;

    l = strtol(argv[1], endptr);

    std::cout << l << std::endl;

    return 0;
}
