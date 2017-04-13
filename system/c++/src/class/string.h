#ifndef _MY_STRING_H
#define _MY_STRING_H

class String {
    public:
        String(const char *s = NULL);
        String(const String& other);

        ~String();

        String& operator=(const String& other);

        char *c_str() const;

    private:
        char *m_str;

};

#endif /* _MY_STRING_H */
