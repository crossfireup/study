#ifndef _MERGESORT_H
#define _MERGESORT_H

#include <utility>
#include <string>

template<typename T>
class Mergesort {
    private:
        size_t sz = 0;
        T *elem = NULL;
        T *tmp = NULL;

    public:
        Mergesort(int n)
            : elem{new T[sz]}, sz{n}
        {}

        Mergesort(std::initializer_list<T> lst);

        Mergesort(const Mergesort& m);
        
        Mergesort& operator=(const Mergesort& m);

        ~Mergesort() 
        { 
            delete [] elem;
            delete [] tmp;
            sz = 0;
        }

        T* sort();
        T* sort(int left, int right);

        T* merge(int left, int mid, int right);

        void print();
};

template<typename T>
Mergesort<T>::Mergesort(std::initializer_list<T> lst)
    : elem {new T[sz]}, sz{lst.size()}
{
    std::move(lst.begin(), lst.end(), elem);
}

template<typename T>
Mergesort<T>::Mergesort(const Mergesort<T>& m)
{
    if( this == &m)
        return;

    elem = new T[m.sz];
    for(int i = 0; i < m.sz; i++){
        elem[i] = m.elem[i];
    }
    
    return;
}

template<typename T>
Mergesort<T>& Mergesort<T>::operator=(const Mergesort<T>& m)
{
    if(this == &m)
        return *this;

    delete [] elem;
    elem = new T[m.sz];

    for(int i = 0; i < m.sz; i++){
        elem[i] = m.elem[i];
    }

    sz = m.sz;

    return *this;
}

template<typename T>
T* Mergesort<T>::sort()
{
    if(tmp == NULL)
        tmp = new T[sz];

    sort(0, sz-1);

    return elem;
}

template<typename T>
T* Mergesort<T>::sort(int left, int right)
{
    if(left == right)
        return elem;

    int mid = left + (right - left) / 2;

    sort(left, mid);
    sort(mid+1, right);
    merge(left, mid, right);

    return elem;
}

template<typename T>
T* Mergesort<T>::merge(int left, int mid, int right)
{
    if(left == right)
        return elem;

    for(int i = left; i <= right; i++){
        tmp[i] = elem[i];
    }

    for(int i = left, j = mid+1, k = left; i <= mid || j <= right; ){
        if(i > mid) 
            elem[k++] = tmp[j++];
        else if( j > right) 
            elem[k++] = tmp[i++];
        else if(tmp[i] > tmp[j])
            elem[k++] = tmp[j++];
        else
            elem[k++] = tmp[i++];
    }

    return elem;
}

template<typename T>
void Mergesort<T>::print()
{
    for(int i = 0; i < sz; i++)
        std::cout << elem[i] << "\t";

    std::cout << std::endl;

    return;
}

#endif /* _MERGESORT_H */
