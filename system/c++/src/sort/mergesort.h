#ifndef _MERGESORT_H
#define _MERGESORT_H

template<typename T>
class Mergesort {
    private:
        T *elem;
        T *tmp;
        int sz;

    public:
        Mergesort(int n)
            : elem{new T[sz]}, tme{new T[sz]}, sz{n}
        {}

        Mergesort(std::initializer_list<T> lst);

        Mergesort(const Mergesort& m);
        
        Mergesort& operator=(const Mergesort& m);

        ~Mergesort() 
        { 
            delete [] elem;
            sz = 0;
        }

        T *sort();
        T *sort(int left, int right);

        void merge(int left, int mid, int right);

        void print();
};

#endif /* _MERGESORT_H */


