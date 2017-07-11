# introduction
  http://www.cplusplus.com/
  https://www.tutorialspoint.com/cplusplus/cpp_overview.htm
  c++ programming language

  - version
    ```
    C++ pre-C++98: __cplusplus is 1.
    C++98: __cplusplus is 199711L.
    C++98 + TR1: This reads as C++98 and there is no way to check that I know of.
    C++11: __cplusplus is 201103L.
    C++14: __cplusplus is 201402L.
    ```

# consists
  - core language including variables, data types, and literatals, etc

  - c++ standart library: 
    - IO
    - strings
    - math
    - time, date, localization
    - dynamic allocation
    - Miscellaneous
    - Wide-character functions

  - STL(standart template library): 
    - container
    - iterators
    - algorithms
    - allocators
    - function
    - Standard C++ I/O Classes
    - String class
    - numberic class
    - Localization library
    - exception handling
    - miscellaneous

# basic
  - ansi standard 
  - C++ fully supports object-oriented programming, including the four pillars of object-oriented development:
    - Encapsulation
    - Data hiding
    - Inheritance
    - Polymorphism
  
  - apply catagory
    - application
    - device driver and other direct manipulation of hardware uder realtime constraints
    - system interfaces are writen in c++

  - types
    - bool // Boolean, possible values are true and false

    - constants
      - const: no change of this value
      - constexpr: evaluated at __compile time__, to specify constants, to allow placement of data in memory where it is unlikely to be corrupted, and for performance
      ```c++
      const int c_var = 17;
      int var = 17;
      constexpr double max1 = 1.4 * square(c_var);  // ok
      constexpr double max2 = 1.4 * square(var);    // error: var is not a constant expression
      const double     max3 = 1.4 * square(var);    // ok: may be evaluated at run time

      double sum(const vector<double>&); // sum will not modify its argument (§2.2.5)
      vector<double> v {1.2, 3.4, 4.5}; // v is not a constant
      const double s1 = sum(v); // OK: evaluated at run time
      constexpr double s2 = sum(v); // error : sum(v) not constant expression

      constexpr double square(double x) { return x∗x; }
      ```

    - pointer and reference
      - nullptr (‘‘the null pointer’’)
      
    - structure
      ```c++
      struct Vector {
        int sz; // number of elements
        double∗ elem; // pointer to elements
        };

      // can use directly
      Verctor v;
      ```

    - class
      - public: interface
      - private: accessible only through that interface.
      - protected: accessible throught interface and child interface

    - enumaration
      ```c++
      enum class Color { red, blue, green };
      enum class Traffic_light { green, yellow, red };
      Color col = Color::red;
      Traffic_light light = Traffic_light::red;
      ```
      - class after enume means
        - enumaration type are strong typed
        - enumerators are scoped
        ```c++
        Color x = red; // error : which red?
        Color y = Traffic_light::red; // error : that red is not a Color
        Color z = Color::red; // OK
        ```        

      - enumerators are not int values
        ```c++
        int i = Color::red; // error : Color ::red is not an int
        Color c = 2; // error : 2 is not a Color
        ```
        
      - By default, an enum class has only assignment, initialization, and comparisons defined
        ```c++
        Traffic_light& operator++(Traffic_light& t)
        // prefix increment: ++
        {
          switch (t) {
          case Traffic_light::green: return t=Traffic_light::yellow;
          case Traffic_light::yellow: return t=Traffic_light::red;
          case Traffic_light::red: return t=Traffic_light::green;
          }
        }

        Traffic_light next = ++light; // next becomes Traffic_light::green
        ```

      - separate compilation
        - class declarations in header
        - class implements in cpp file
        - use instance of a class by include header

      - namespace
        - features
          - express a logically coherent set of features
          - no access to unrelated features
          - not impose a signifacant notational burden on users

        - a mechanism show some declarations belong together and their names shouldn’t clash with others
          ```c++
          namespace My_code {
            class complex { /* ... */ };
            complex sqrt(complex);
            // ...
            int main();
          }

          int My_code::main()
          {
            complex z {1,2};
            auto z2 = sqrt(z);
            std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
            // ...
          };

          int main()
          {
            return My_code::main();
          }
          ```
        
        - using directive: global, local
          ```c++
          using namespace std;
          ```
      
        - namespace alias
          ```C++
          namespace Telephone_And_Telegraph {
            // ...
          }

          namespace TAT = Telephone_And_Telegraph;
          ```

        - composition using namespace
          ```
          namespace X {
            int i, j, k;
          }

          int k;

          void f1()
          {
            int i = 0;
            using namespace X;
            i++;  // local i
            j++;  // X::j
            k++;  // error, global k ? X::k
            ::k++;// global k
            X::k++; 
          }

          void f2()
          {
            int i = 0;
            using X::i; // error: i declares twice
            using X::j;
            using X::k; // hide global k

            i++;
            j++; // X::j++
            k++; // X::k++
          }
          ```

      - Error Handling
      
      - exception
        - Exceptions report errors found at run time
        - try catch

      - static assertions
        - error can be found at compile time
        - static_assert: static_assert(A,S) prints S as a compiler error message if A is not true.
          ```
          static_assert(4<=sizeof(int), "integers are too small"); // check integer size
          ```

      - Postscript

      - advice
        - don't panic, all will became clear in time;
        - you don't have to know everty detail of c++ to write good programs;
        - focus on programming technics, not the language features;

  - class
    - concrete classes
      - behave "just like built-in types"

      - defining characteristic: represention is part of definition
        - vector 
          - represention: one or more pointers to more data stored elsewhere
          - reprent each object of a concrete class

      - to be optimally efficent in time and space:
        - place object of concrete types on the stack, in statical allocated memory, or other objects
        - refer to object directly(not just through pointer or reference)
        - initialize object immediately and completely usinge constructor and copy objects

      - price: representation changes, a user must recompile

      - usage:
        - for types that don't change often, and where local variable provide much-needed clarity and efficiency
        - increase flexibility: 
          - keep major of its represention on the free store(dynamic memory, heep) and access throught the part stored in class

      - tips
        - Functions defined in a class are inlined by default
        
        - constructor that can be invoked without an argument is called a __default constructor__
          - eliminate the possibility of uninitialized variables of that type.
        
        - const specifiers on the functions returning: functions do not modify the object for which they are called

        - destructor is the complement operator, ˜, followed by the name of the class

    - abstract classes: A class with a pure virtual function
      - A class that provides the interface to a variety of __other classes__ is often called a polymorphic typ
      ```c++
      class Container {
        public:
          virtual double& operator[](int) = 0; // pure virtual function
          virtual int size() const = 0; // const member function (§3.2.1.1)
          virtual ˜Container() {} // destructor (§3.2.1.2)
      };

      void use(Container& c)
      {
        const int sz = c.size();
        for (int i=0; i!=sz; ++i)
          cout << c[i] << '\n';
      }
      ```
      - virtual means "may be redefined later in a class derived from this one"
      - =0 syntax says the function is pure virtual, some derived class must define the function
      - not possible to define an object that is just a Container
      - Container can only serve as the interface to a class that implements its operator[]() and size() functions
      - Container does not have a constructor , does not have any data to initialize

    - mutable
      - means it can be modified even in a const object

    - classes 
      - initailization order
        - for most-derived class, virtual base classes -> depth-first left-to-right of the base class declaration
        - direct base classes left->right in base-specifier list
        - non-static data members -> declaration in the class definition
        - the body being excuted

      - constructor and destructor
        - constructor: how an object initialize
      
      - smart pointer
        - unique_ptr
          ```c++
          std::unique_ptr<int> p1(new int(5));
          std::unique_ptr<int> p2 = p1; //Compile error.
          std::unique_ptr<int> p3 = std::move(p1); //Transfers ownership. p3 now owns the memory and p1 is rendered invalid.

          p3.reset(); //Deletes the memory.
          p1.reset(); //Does nothing.
          ```
          - a container for a raw pointer, belong to unique_ptr
          - explicitly prevents copying of its contained pointer
          - std::move can be used to transfer ownership of the contained pointer to another unique_ptr

        - shared_ptr
          ```c++
          std::shared_ptr<int> p1(new int(5));
          std::shared_ptr<int> p2 = p1; //Both now own the memory.

          p1.reset(); //Memory still exists, due to p2.
          p2.reset(); //Deletes the memory, since no one else owns the memory.
          ```
          - a container for a raw pointer
          - maintains reference counting ownership of its contained pointer in cooperation with all copies of the shared_ptr
          - destroyed when and only when all copies of the shared_ptr have been destroyed. 

        - weak_ptr
          ```c++
          std::shared_ptr<int> p1(new int(5));
          std::weak_ptr<int> wp1 = p1; //p1 owns the memory.

          {
            std::shared_ptr<int> p2 = wp1.lock(); //Now p1 and p2 own the memory.
            if(p2) // As p2 is initialized from a weak pointer, you have to check if the memory still exists!
            {
              //Do something with p2
            }
          } //p2 is destroyed. Memory is owned by p1.

          p1.reset(); //Memory is deleted.

          std::shared_ptr<int> p3 = wp1.lock(); //Memory is gone, so we get an empty shared_ptr.
          if(p3)
          {
            //Will not execute this.
          }
          ```
          - a container for a raw pointer. It is created as a copy of a shared_ptr
          - existence or destruction of weak_ptr copies of a shared_ptr have no effect on the shared_ptr or its other copies
          - all copies of a shared_ptr have been destroyed, all weak_ptr copies become empty.

        - copy and move
          - copy 
            ```
            Vector(const Vector& a); // copy constr uctor
            Vector& operator=(const Vector& a); // copy assignment
            ```

          - move 
            ```
            Vector(Vector&& a); // move constructor
            Vector& operator=(Vector&& a); // move assignment
            ```
            - && means "rvalue reference" and is a reference to which we can bind an rvalue

        - Suppressing Operation
          ```c++
          class Shape {
            public:
              Shape(const Shape&) =delete; // no copy operations
              Shape& operator=(const Shape&) =delete;
              Shape(Shape&&) =delete; // no move operations
              Shape& operator=(Shape&&) =delete;
              ˜Shape();
              // ...
            };
          ```
        
        - template
          - Parameterized Types:
            ```c++
            template<typename T>
            class Vector {
              public:
                  Vector(int n);

              private:
                  T *elem;
                  int sz;
            }

            template<typename T>
            Vector<T>::Vector(int n){
              if(n < 0) throw Negative_size();
              
              elem = new T[n];
              sz = n;
            }
            ```

          - function template
            ```c++
            template<typename Container, typename Value>
            Value sum(const Container& c, Value v)
            {
              for (auto x : c)
                v+=x;
              return v;
            }

            void user(Vector<int>& vi, std::list<double>& ld, std::vector<complex<double>>& vc)
            {
              int x = sum(vi,0); // the sum of a vector of ints (add ints)
              double d = sum(vi,0.0); // the sum of a vector of ints (add doubles)
              double dd = sum(ld,0.0); // the sum of a list of doubles
              auto z = sum(vc,complex<double>{}); // the sum of a vector of complex<double>
              // the initial value is {0.0,0.0}
            }
            ```
          
          - function object
            ```
            template<typename T>
            class Less_than {
                const T val; // value to compare against
              public:
                Less_than(const T& v) :val(v) { }
                bool operator()(const T& x) const { return x<val; } // call operator
            }; 

            Less_than<int> lti {42}; // lti(i) will compare i to 42 using < (i<42)
            Less_than<string> lts {"Backus"}; // lts(s) will compare s to "Backus" using < (s<"Backus")

            void fct(int n, const string & s)
            {
              bool b1 = lti(n); // true if n<42
              bool b2 = lts(s); // true if s<"Backus"
              // ...
            }
            ```
          
          - Variadic Templates
            ```
            template<typename T, typename... Tail>
            void f(T head, Tail... tail)
            {
              g(head); // do something to head
              f(tail...); // try again with tail
            }

            void f() { } // do nothing

            template<typename T>
            void g(T x)
            {
              cout << x << " ";
            }

            f(1,2.2,"hello"); // -->go(1) -> f(2.2, "hello") ->g(2.2) --> f("hello") ->g("hello") -> f()

            output:  1 2.2 hello
            ```

          - aliases
            - using size_t = unsigned int;
            ```c++
            template<typename T>
            class Vector {
              public:
                using value_type = T;
              // ...
            };

            template<typename C>
            using Element_type = typename C::value_type;

            template<typename Container>
            void algo(Container& c)
            {
              Vector<Element_type<Container>> vec; // keep results here
              // ...
            }
            ```
    - Standard Library: the most common fundamental data structures together with the fundamental algorithms used on them
      - Run-time language support
      - The C standard library
      - Strings and I/O streams: <string>, <sstream>, <fstream>, <iostream>
      - STL: container, algorithm
      - Numeric compulation: standard mathmatical functions, complex numbers, vector with arithmetical ops and random generation
      - regular expression matching
      - concurrent programming: thread, lock
      - utilities support template metaprogramming, STL-style generic programming, general programming
      - "smart pointer" support resource management and interface to garbage collectors: <memory> unique_ptr, shared_ptr,
      - special-purpose containers: array, bitset, pair, tuple

      - string and IO
        - cin<< c will skip whitespace and cin.get() doesn't   

      - container
        - vector
          - 

    - lvalue and rvalue
      - forward
        ```C++
        template<class T, class... U>
        std::unique_ptr<T> make_unique(U&&... u)
        {
            return std::unique_ptr<T>(new T(std::forward<U>(u)...));
        }

        string a;
        make_unique(1, a, 2);
        ```

    - allocators
      - provide a source of memory for a given type and a place to return that memory to once it is no longer needed
    
    - dynamic allocation
      - new and delete
        - C++ provide two standart mechanism to check if the allocation was successful
          - throw bad_alloc exception whe memory allocation fails

          - return a nullptr 
            ```
            foo = new (nothrow) int [5];
            if (foo == nullptr) {
              // error assigning memory. Take measures.
            }
            ```
        - why overload new and delete
          - take charge or control over the memory allocation
          - aid in debugging: trace allocation and deallocation
          - other operation at allocation and deallocation
          ```
          void* operator new(size_t num, char x)
          {
              void *ptr;
          
              if (ptr = malloc(num)) *ptr = x;
              return ptr;
          }
          
          int main()
          {
              char *p = new('*') char;
          }
          ```

        - why using new instead of mallloc
          - new can't accidentally allocate the wrong amount of memory,
          - new implicitly checks for memory exhaustion, and
          - new provides for initialization 

    - Explicit Type Conversion
      Casts are generally best avoided. With the exception of dynamic_cast, their use implies the possibility of a type error or the truncation of a numeric value
      ```
      int a = 7;
	    double* p1 = (double*) &a;			// ok (but a is not a double)
	    double* p2 = static_cast<double*>(&a);	// error
	    double* p2 = reinterpret_cast<double*>(&a);	// ok: I really mean it

	    const int c = 7;
	    int* q1 = &c;			// error
	    int* q2 = (int*)&c;		// ok (but *q2=2; is still invalid code and may fail)
	    int* q3 = static_cast<int*>(&c);	// error: static_cast doesn't cast away const
	    int* q4 = const_cast<int*>(&c);	// I really mean it
      ```

    - lock
      - std::lock_guard
        ```
        void push(T new_value)
        {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(data));
        data_cond.notify_one();
        }
        ```
      - std::unique_lock
        ```
        std::mutex m;
        std::condition_variable cv;
        std::string data;
        bool ready = false;
        bool processed = false;

        void worker_thread()
        {
            // Wait until main() sends data
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, []{return ready;});
          
            // after the wait, we own the lock.
            std::cout << "Worker thread is processing data\n";
            data += " after processing";
          
            // Send data back to main()
            processed = true;
            std::cout << "Worker thread signals data processing completed\n";
          
            // Manual unlocking is done before notifying, to avoid waking up
            // the waiting thread only to block again (see notify_one for details)
            lk.unlock();
            cv.notify_one();
        }
        ```
      - std::scoped_lock      

    - lock free
      - why
        - enable maximum concurrency
        - robustness
          - thread dies while holding a lock, that data structure is broken forever
          - thread dies partway on a lock-free data structure, nothing is lost except that thread’s data; other threads can proceed normally.
          
      - definition
        - blocking
          Algorithms and data structures that use mutexes, condition variables, and futures to synchronize the data are called blocking data structures and algorithms

        - blocking call
          library calls are termed blocking calls because the thread can’t progress past this point until the block is removed

        - non-blocking
          Data structures and algorithms that don’t use blocking library functions are said to be nonblocking
          ```
          class spinlock_mutex
          {
            std::atomic_flag flag;
            public:
              spinlock_mutex():
                flag(ATOMIC_FLAG_INIT)
              {}
              void lock()
              {
                while(flag.test_and_set(std::memory_order_acquire));
              }
              void unlock()
              {
                flag.clear(std::memory_order_release);
              }
          };
          ```
    
  - [usage](http://www.stroustrup.com/bs_faq2.html#finally)
    - make function local
      - static
      - put function into anonymous namespace
      - usinge __attribute__ ((visiblity("hidden")))

    - Definition of const member in general, needs initialization of the variable too..

      - Inside the class , if you want to initialize the const the syntax is like this
        ```
        static const int a = 10; //at declaration
        ```
      - Second way can be
        ``` 
        class A
        {
          static const int a; //declaration
        };
        
        const int A::a = 10; //defining the static member outside the class
        ```
      - Well if you don't want to initialize at declaration, then the other way is to through constructor, the variable needs to be initialized in the initialization list(not in the body of the constructor). It has to be like this
        ``` 
        class A
        {
          const int b;
          A(int c) : b(c) {} //const member initialized in initialization list
        };
        ```
    - placement new:
      - don't use placement new unless you have to
      - use it only when you really care that an object is placed at particular memory location
    - default parameter value should only be defined in the function declaration.

    - Member functions that do not modify the class instance should be declared as const:
      error: passing ‘const String’ as ‘this’ argument of ‘const char* String::c_str()’ discards qualifiers

    - windows C++ use static to cast dialog procedure in DialogBox
      - CreateDialogParam takes a pointer to a simple function, not a pointer to member-function of some class.

      - Window and dialog procedures (and other Win32 callback functions) need to be static or global functions - they can't be non-static class functions. Win32 is fundamentally a C-based API and it has no concept of the hidden this pointer that class functions require.(http://stackoverflow.com/questions/25678892/calling-a-win32-api-and-giving-a-callback-to-a-class-function)

    - [C and C++ mixing](http://www.oracle.com/technetwork/articles/servers-storage-dev/mixingcandcpluspluscode-305840.html, https://isocpp.org/wiki/faq/mixing-c-and-cpp)
    
    - pmr (Polymorphic Memory Resource)
    - cppunit
      ```
      test:
              Test
        TestCase TestCompsite 
                      TestSuite

      equals: equal, double, 
          TestAssert

      line info:
          LineSource

      msg:
          Message 

      exception:
        Exception

      assert:
        Asserter: fail, failIF
      ```

    - sandbox in chromium
      - broker
        - set policy to target
        
        - spawn the target process
        
        - host sandbox policy engine service

        - host sandbox interception service:
          forward windows API calls via IPC to the broker.

        - host sandbox IPC service

        - perform the policy-allowed action on behalf of the target process

      - target
        - all code to be sandboxed
        - sandbox IPC client
        - sandbox policy client
        - sandbox interceptions:
          - the interceptions (also known as hooks) are how Windows API calls are forwarded via the sandbox IPC to the broker
          - It is up to the broker to re-issue the API calls and return the results or simply fail the calls.

     - qt create
      - set spec
        
  - multithread
    - passing reference to a thread 
      ```
      thread t(update_data_for_widget, w, std::ref(data));
      ```
    
    - avoid dangling pointer
      ```
      void not_oops(int some_param)
      {
      char buffer[1024];
      sprintf(buffer,"%i",some_param);
      // error: std::thread t(f,3,buffer); 
      // oops will exit before the buffer has been converted to a std::string on the new thread, 
      // thus leading to undefined behavior.
      std::thread t(f,3,std::string(buffer)); // avoid dangling pointer
      t.detach();
      }
      ```

    - arguments can’t be copied but can only be moved
      ```
      void process_big_object(std::unique_ptr<big_object>);
      std::unique_ptr<big_object> p(new big_object);
      p->prepare_data(42);
      std::thread t(process_big_object,std::move(p));
      ```
    
    - number of threads
      ```
      std::thread::hardware_
      concurrency()
      ```

    - thread id
      ```
      std::thread::id
      std::thread t;
      t.get_id();

      std::this_thread::get_id()

- com
  - midl (Microsoft Interface Define Language)[https://en.wikipedia.org/wiki/Interface_description_language]
    ```
                midl vss.idl
    vss.h         vss_i.h         vss.tlb
    C/C++           GUID          VB, Java
          vss_p.c         dlldata.c

    ```