#include <cstdlib>
#include <iostream>
#include <regex>

int main()
{
    std::string content("hello world!");

    std::smatch sm;
    std::regex re("llo(?= )");
    if(std::regex_search(content, sm, re))
    {
        std::cout << "content= " << content << std::endl;
        std::cout << "prefix= " << sm.prefix() << " matched" << std::endl;
        std::cout << "suffix= " << sm.suffix() << " matched" << std::endl;
    }

    exit(EXIT_SUCCESS);
}
