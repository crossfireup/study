#include <iostream>


template<typename T>
class allocator {
    public:
        using size_type = size_t;
        using different_type = ptrdiff_t;
        using pointer = T *;
        using const_pointer = const T *;
        using referrence = T&;
        using const_referrence = const T&;
        using value_type = T;

        template<typename U>
            struct rebind {
                using other = U;
            };

        allocator() noexcept;
        allocator(const allocator&) noexcept;
        template<typename U>
            allocator(const allocator<U>&) noexcept;

        ~allocator();

        pointer address(referrence x) const noexcept;
        const_pointer addr(const_referrence x) const noexcept;

        pointer allocate(size_type n, allocator<void>::const_pointer hint = 0);
        void deallocate(pointer p, size_type n);

        size_type max_size() const noexcept;

        template<typename U, typename ...Args>
            construct(U* p, Args&& ...args);    // new(p)U(args);

        template<typename U>
            void destroy(U* p);       // p->~U();

};

template<typename T, typename A = allocator<T>>
class list {
    private:
        class Link{};

        using Link_alloc = typename A::template::rebind<Link>::other;

        Link_alloc a;
        A alloc;
};

template<>
class allocator<void> {
    public:
        typedef void* pointer;
        typedef const void* const_pointer;
        typedef void value_type;
        template<typename U> 
            struct rebind { using other = allocator<U>;};

};
