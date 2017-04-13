#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>

class Singleton {
    private:
        Singleton(){};
        Singleton(Singleton& );
        Singleton& operator=(Singleton& );

    public:
        static Singleton& getInstance(){
            static Singleton instance;
            return instance;
        }

        void log(std::string msg){
            std::cout << msg << std::endl;
        }
};

#endif /* _SINGLETON_H */
