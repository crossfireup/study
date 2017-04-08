/*
Test case for sharing virtual bases.
In Derived_too,
the primary base class is NewShareme,
The bases Base and Shareme share vptr's
with Derived and are allocated at the
same offset as Derived.
Should get:
60% a.out
(long)(NewShareme *)dd - (long)dd = 0
(long)(Derived *)dd - (long)dd = 8
(long)(Base *)dd - (long)dd = 8
(long)(Shareme *)dd - (long)dd = 8
*/

struct Shareme {
    virtual void foo();
};
struct Base : virtual Shareme {
        virtual void bar();
};
struct Derived : virtual Base {
        virtual void baz();
};

struct NewShareme {
        virtual void foo();
};

struct Derived_too : virtual NewShareme, virtual Derived {
        virtual void bar();
};

void Shareme::foo() { }
void Base::bar() { }
void Derived::baz() { }
void NewShareme::foo() { }
void Derived_too::bar() { }


extern "C" int printf(const char *,...);
#define EVAL(EXPR) printf( #EXPR " = %d\n", (EXPR) );
int main()
{
  Derived_too *dd = new Derived_too;
  EVAL((long)(NewShareme *)dd - (long)dd);
  EVAL((long)(Derived *)dd - (long)dd);
  EVAL((long)(Base *)dd - (long)dd);
  EVAL((long)(Shareme *)dd - (long)dd);
}
