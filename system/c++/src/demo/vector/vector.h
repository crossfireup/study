#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
    public:
        Vector(int n);
        double& operator[](int i);
        int size();

    private:
        double *elem;
        int sz;
};

#endif /* _VECTOR_H */
