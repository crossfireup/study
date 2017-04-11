#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
    public:
        Vector(int n);
        Vector(std::initializer_list<double>);
        ~Vector() { delete [] elem;}

        Vector(const Vector& a); // copy constructor
        Vector& operator=(const Vector& a);  // copy assignment

        Vector(Vector&& a);      // move constructor   
        Vector& operator=(Vector&& a); // move assignment

        Vector operator+(const Vector& b); 

        int size() const;
        double& operator[](int i);

        void push_back(double d);

    private:
        double *elem;
        int sz;
};

#endif /* _VECTOR_H */
