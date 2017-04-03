#ifndef _CONTAINER_H
#define _CONTAINER_H

class Container {
    public:
        virtual double& operator[](int) = 0; /* pure virtual function */
        virtual int size() const = 0;        /* const member function */
        virtual ~Container() {};
};

#endif /* _CONTAINER_H */
