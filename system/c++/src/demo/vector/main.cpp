#include <iostream>

#include "vector.h"

int main(void)
{
    Vector v(4);

    v[0] = 0.1;
    v[1] = 0.2;
    v[2] = 0.3;
    v[3] = 0.4;

    std::cout << "v: " << std::endl;

    for(int i = 0; i < 4; i++){
        std::cout << v[i]<<"\t";
    }

    std::cout << std::endl;

    return 0;
}

