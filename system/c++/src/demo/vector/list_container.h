#ifndef _LIST_CONTAINER_H
#define _LIST_CONTAINER_H

#include <list>
#include "container.h"

class List_container:public Container {
    public:
        List_container() {};
        List_container(std::initializer_list<double> lst): ld(lst) {}
        double& operator[](int i);
        int size() const { return ld.size();}

        ~List_container() {}

    private:
        std::list<double> ld;
};

#endif /* _LIST_CONTAINER_H */
