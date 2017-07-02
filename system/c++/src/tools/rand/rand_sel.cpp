#include <iostream>
#include <string>
#include <vector>

void str_vec_print()
{
    std::vector<std::string *> *pvecStr = nullptr;
    //std::string strA[] = {new std::string("hello"), new std::string("c"), };
    std::string strA[] = {"hello", "c" };
    //std::string strB[] = {new std::string("c++ program"), new std::string("c++ program")};
    std::string strB[] = {"c++ program", "c++ program"};
    
    pvecStr = new std::vector<std::string*> ();
    pvecStr->push_back(strA);
    pvecStr->push_back(strB);

    std::string *a = nullptr;
    std::string *b = nullptr;
    for(int i = 0; i < pvecStr->size(); i++)
    {
        a = &(*pvecStr)[i][0];
        b = &(*pvecStr)[i][1];
        std::cout << a << "\t" << b << std::endl;
    }

    return;
}


int main()
{
    std::vector<double *> *pvecT = nullptr;
    double a[] = {40.0, 30.0};
    double b[] = {50.0, 40.0};

    pvecT = new std::vector<double *> ();
    pvecT->push_back(a);
    pvecT->push_back(b);

    // double dl = 0.0, dr = 0.0;
    for(int i = 0; i < pvecT->size(); i++)
    {
        double dl = (*pvecT)[i][0];
        double dr = (*pvecT)[i][1];
        std::cout << dl << "\t" << dr << std::endl;
    }

    return 0;
}
    


