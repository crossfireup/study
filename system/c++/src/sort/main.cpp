#include <iostream>
#include "mergesort.h"

int main(void)
{
    Mergesort<int> ms = std::initializer_list<int>({1, 5, 3, 7, 2, 4});

    ms.sort();
    ms.print();

    return 0;
}
