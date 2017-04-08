#ifndef _COMPLEX_H
#define _COMPLEX_H

class complex {
    public:
        complex(double r, double i): re(r), im(i) {}
        complex(double r): re(r), im(0) {}
        complex(): re(0), im(0) {}

        double real() const { return re;}
        void real(double d) { re = d;}
        void image() const  { return in;}
        void image(double d) { im = d;}
        
        complex& operator+=(complex z) { re += z.re; im += z.im;}
        complex& operator-=(complex z) { re -= z.re; im -= z.im;}

        complex& operator*=(complex z);
        complex& operator/=(complex z);

    private:
        double re, im;
};

#endif /* _COMPLEX_H */
