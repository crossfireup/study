# introduction
  http://www.cplusplus.com/
  https://www.tutorialspoint.com/cplusplus/cpp_overview.htm
  c++ programming language

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

        -  destructor is the complement operator, ˜, followed by the name of the class

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

    - classes in hierarchies
             
  - usage:
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
        
