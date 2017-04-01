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

        
