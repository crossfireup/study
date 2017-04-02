#include <iostream>
#include <stdexcept>
#include "vector.h"

int main(void)
{
    Vector v(4);

    v[0] = 0.1;
    v[1] = 0.2;
    v[2] = 0.3;
    v[3] = 0.4;

    try {
        Vector v1(-27);
    } catch (std::length_error){
        std::cout << "length_error" << std::endl;
    } catch (std::bad_alloc) {
        std::cout << "bad_alloc" << std::endl;
    }

    std::cout << "v: " << std::endl;

    for(int i = 0; i < 4; i++){
        std::cout << v[i]<<"\t";
    }
    std::cout << std::endl;

    Vector v1 = {1.0, 2.0, 3.0, 4.0};

    for(int i = 0; i < 4; i++){
        std::cout << v1[i]<<"\t";
    }

    std::cout << std::endl;

    try {
        v[5];
    } catch (std::out_of_range) {
        std::cout << "out_of_range" << std::endl;
    }

    std::cout << std::endl;

    return 0;
}

