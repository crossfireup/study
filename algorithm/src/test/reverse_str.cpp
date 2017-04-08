#include <iostream>

char *reverse_str(char *s)
{
    int n = strlen(s);
    char temp = '\0';

    if(n < 0)
        return NULL;

    for(int i = 0; i < n / 2; i++){
        temp = s[i];
        s[i] = s[n - i - 1];
        s[n -i - 1] = temp;
    }

    return s;
}

int main(void)
{
    char s[] = "helloc";

    std::cout << reverse_str(s) << std::endl;

    return 0;
}
