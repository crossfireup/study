#include <stdexcept> 
#include "vector.h"

Vector::Vector(int n)
{
    if(n < 0)
        throw std::length_error{"vecotr initialize"};

    elem = new double[n];
    for(int i = 0; i < n; i++){
        elem[i] = 0;
    }

    sz = n;
}

Vector::Vector(std::initializer_list<double> lst)
    : elem{new double[lst.size()]}, sz{lst.size()}
{
    std::copy(lst.begin(), lst.end(), elem);
}

double &Vector::operator[](int i)
{
    if( i < 0 || i > sz)
        throw std::out_of_range{"Vector::operator[]"};

    return elem[i];
}

int Vector::size() const
{
    return sz;
}
