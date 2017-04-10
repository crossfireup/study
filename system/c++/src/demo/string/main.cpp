#include <string>
#include <iostream>
#include <ios>
#include <cctype>

struct Entry {
    std::string name;
    int number;

};

std::ostream& operator<<(std::ostream& os, const Entry& e) 
{
    return os << "{\"" << e.name << "\"," << e.number << "}";
}

std::istream& operator>>(std::istream& is, Entry& e)
{
    char c0, c1;
    if(is>>c0 && c0 == '{' && is>>c1 && c1=='"'){
        std::string name;
        while(is.get(c0) && c0 != '"')
            name += c0;

        if(is>>c0 && c0 == ',') {
            int number = 0;
            if(is>>number>>c0 && c0 == '}'){
                e = {name, number};
                return is;
            }
        }
    }

    is.setf(std::ios_base::failbit);
    return is;
}

int main(void)
{
    std::string name = "hello world !";

    std::cout << name.substr(0, 5) << std::endl;
    std::cout << name.replace(0, 5, "there") << std::endl;
    name[0] = toupper(name[0]);
    std::cout << name << std::endl;

    std::cout << "please input your name:\n";
    getline(std::cin, name);
    std::cout << name << " you are the best!"  << std::endl;

    Entry e;
    std::cout << "please input entry:" << std::endl;
    std::cin >> e;
    std::cout << "your input is:" << e << std::endl;
    return 0;
}
