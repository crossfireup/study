#include <iostream>

int (*f)(int, int);

int max(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    f = max;
    
    std::cout << (int *)f << std::endl;
    std::cout << (int *)(*f) << std::endl;
    std::cout << (*f)(1, 2) << std::endl;

    return 0;
}
