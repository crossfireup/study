#include <iostream>
#include <utility>
#include "mergesort.h"

int main(void)
{
    Mergesort<int> msi = std::initializer_list<int>({1, 5, 3, 7, 2, 4});
    msi.print();
    msi.sort();
    msi.print();

    Mergesort<std::string> mss = std::initializer_list<std::string>({"helloc", "how", "what", "if", "lose", "win", "ok"});
    mss.print();
    mss.sort();
    mss.print();

    Mergesort<double> msd = std::initializer_list<double>({4.3, 2.4, 6.2, 8.9, 5.8});
    msd.print();
    msd.sort();
    msd.print();

    return 0;
}
