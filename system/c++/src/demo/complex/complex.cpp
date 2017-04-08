#include "complex.h"

complex& operator*=(complex z)
{
}

complex& operator/=(complex z)
{
}

complex operator+(complex a, complex b) { return a+=b; }
complex operator-(complex a, complex b) { return a-=b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; } // unar y minus
complex operator*(complex a, complex b) { return a*=b; }
complex operator/(complex a, complex b) { return a/=b; }

bool operator==(complex a, complex b) // equal
{
	return a.real()==b.real() && a.imag()==b.imag();
}

bool operator!=(complex a, complex b) // not equal
{
	return !(a==b);
}
