#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "string.h"

String::String(const char *s )
{
    if(s == NULL){
       m_str = new char;
       m_str[0] = '\0';
    } else {
        int n = strlen(s) + 1;
        m_str = new char[n ];
        strncpy(m_str, s, n);
    }
}

String::String(const String& other)
{
    if(this == &other)
        return;

    int n = strlen(other.m_str) + 1;
    m_str = new char[n];
    strncpy(m_str, other.m_str, n + 1);

    return;
}

String& String::operator=(const String& other)
{
    if(this == &other)
        return *this;

    int n = strlen(other.m_str) + 1;
    m_str = new char[n];
    strncpy(m_str, other.m_str, n);

    return *this;
}

char *String::c_str() const 
{
    return m_str;
}

String::~String()
{
#ifdef DEBUG
    std::cout << "call destructor: " << m_str << std::endl;
#endif
    delete [] m_str;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
   // os << static_cast<const void *>(s.c_str());
   os << s.c_str() << "\n";

   return os;
}

int main(void)
{
    const char *a = "you are the best!";

    String s0(a);
    std::cout << s0;

    String s1(s0);
    std::cout << s0;

    String s2 = s1;
    std::cout << s0;

    int n = strlen(a);

    printf("length: %d\n", n);

    return EXIT_SUCCESS;
}
