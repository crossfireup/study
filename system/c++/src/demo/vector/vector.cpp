#include "vector.h"

Vector::Vector(int n)
    :elem{new double[n]}, sz{n}
{
}

double &Vector::operator[](int i)
{
    return elem[i];
}

int Vector::size()
{
    return sz;
}
