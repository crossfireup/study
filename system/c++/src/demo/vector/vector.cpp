#include <iostream>
#include <stdexcept> 
#include "vector.h"

Vector::Vector(int n)
{
    std::cout << "constructor called:Vector(int)" << std::endl;

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
    std::cout << "constructor called:Vector(std::initializer_list<double>)" << std::endl;
    std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& a)
    :elem{new double[sz]}, sz{a.size()}
{
    std::cout << "copy constructor called:Vector(const Vector&)" << std::endl;
    for(int i = 0; i < sz; i++){
        elem[i] = a.elem[i];
    }
}

Vector::Vector(Vector&& a)
    :elem{new double[sz]}, sz{a.sz}
{
    std::cout << "move constructor called:Vector(Vector&&)" << std::endl;
    a.elem = nullptr;
    a.sz = 0;
}

Vector& Vector::operator=(const Vector& a)
{
    std::cout << "copy assignment called:Vector::operator=(const Vector&)" << std::endl;
    if(this != &a){
        double *p = new double[a.size()];

        for(int i = 0; i < a.size(); i++){
            p[i] = a.elem[i];
        }
        delete [] elem;
        elem = p;
        sz = a.size();
    }

    return *this;
}

Vector& Vector::operator=(Vector&& a)
{
    std::cout << "Move assignment called:Vector::operator=(Vector&&)" << std::endl;
    if(this != &a){
        delete [] elem;
        // elem = std::exchange(a.elem, nullptr)
        elem = a.elem;
        a.elem = nullptr;
        // sz = std::exchange(a.sz, 0);
        sz = a.sz;
        a.sz = 0;
    }

    return *this;
}

Vector Vector::operator+(const Vector& a)
{
    if(sz != a.sz)
        throw std::length_error{"Vector size mismatch"};

    Vector res(sz);
    for(int i = 0; i < sz; i++){
        res[i] = elem[i] + a.elem[i];
    }

    return res;
}

double& Vector::operator[](int i)
{
    if( i < 0 || i > sz)
        throw std::out_of_range{"Vector::operator[]"};

    return elem[i];
}

int Vector::size() const
{
    return sz;
}
