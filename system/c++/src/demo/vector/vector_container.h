#ifndef _VECTOR_CONTAINER_H
#define _VECTOR_CONTAINER_H

#include "container.h"

class Vector_container: public Container {
    public:
        Vector_container(int s): v(s) {};
        Vector_container(std::initializer_list<double> lst): v(lst) {};
        ~Vector_container() {};

        double& operator[](int i) { return v[i];}
        int size() const { return v.size();};
    private:
        Vector v;
};

#endif /* _VECTOR_CONTAINER_H */
