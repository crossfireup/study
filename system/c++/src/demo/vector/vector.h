#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
    public:
        Vector(int n);
        Vector(std::initializer_list<double>);
        ~Vector() { delete [] elem;}

        double& operator[](int i);

        int size() const;

        void push_back(double d);

    private:
        double *elem;
        int sz;
};

#endif /* _VECTOR_H */
