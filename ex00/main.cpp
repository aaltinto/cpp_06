#include "includes/ScalarConverter.hpp"
#include <iostream>

int main(int ac, char **argv)
{
    std::string arg;
    for (int i = 1; argv[i] != NULL; i++)
    {
        arg = std::string(argv[i]);
        try
        {
            ScalarConverter::convert(arg);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        
    }
}