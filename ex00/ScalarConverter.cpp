#include "includes/ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>

ScalarConverter::ScalarConverter()
{
    std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(ScalarConverter const &copy)
{
    *this = copy;
    std::cout << "ScalarConverter copy constructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &copy)
{
    std::cout << "ScalarConverter copy assignment operator called" << std::endl;
    if (this == &copy)
        return *this;
    return *this;
}

ScalarConverter::~ScalarConverter()
{
    std::cout << "ScalarConverter destructor called" << std::endl;
}

const char *ScalarConverter::notValid::what() const throw()
{
    return "Convertion argument not valid!";
}

void printChar(int c)
{
    if (c >= 0 && c <= 127)
    {
        if (c >= 32 && c <= 126)
            std::cout << "char: '" << static_cast<char>(c) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
}

void printInt(int i);

void    charConv(std::string convert)
{
    std::string cStr;
    char c = convert[0];
    std::string temp;
    temp = c;
    cStr = "'" + temp + "'";
    int i = static_cast<int>(c);
    float f = static_cast<float>(i);
    double d = static_cast<double>(i);

    printOutput(cStr, std::to_string(i), std::to_string(f), std::to_string(d));
}

void    intConv(std::string convert)
{
    std::string cStr;
    int i = std::atoi(convert.c_str());
    float f = static_cast<float>(i);
    double d = static_cast<double>(i);
    std::string iStr = std::to_string(i);
    std::string fStr = std::to_string(f);
    std::string dStr = std::to_string(d);
    
    printOutput(cStr, iStr, fStr, dStr);
}

static void countBody(std::string num, int count[2])
{
    int c = 0;

    count[0] = 0;
    count[1] = 0;
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == '.')
        {
            c = 1;
            continue;
        }
        if (num[i] == 'f')
            break;
        count[c]++;
    }
}

static float   strFloat(std::string const convert)
{
     int p[2];
    countBody(convert, p);

    float f = static_cast<float>(std::atoi(convert.substr(0, p[0]).c_str()));;
    int sign = convert[0] == '-' ? -1 : 1;
    float fractionalPart = 0.0f;
    for (int i = 0; i < p[1]; i++)
    {
        float pow = std::pow(10, -(i + 1));
        int digit = convert[p[0] + 1 + i] - '0';

        fractionalPart += digit * pow;
    }

    f += sign * fractionalPart;
    std::cout << "Float: " << f << std::endl;
    return f;
}

void    floatConv(std::string convert)
{
    float f = strFloat(convert);
    int i = static_cast<int>(f);
    double d = static_cast<double>(f);

    std::string cStr;
    std::string iStr = std::to_string(i);
    std::string fStr = std::to_string(f);
    std::string dStr = std::to_string(d);
    if (i >= 0 && i <= 127)
    {
        if (i >= 32 && i <= 126)
        {
            char c = static_cast<char>(i);
            std::cout << c << std::endl;
            std::string temp;
            temp = c;
            cStr = "'" + temp + "'";
        }
        else
            cStr = "Non displayable";
    }
    else
        cStr = "impossible";
    printOutput(cStr, iStr, fStr, dStr);
}
void    doubleConv(std::string convert)
{

}

void ScalarConverter::convert(std::string convert)
{
    switch (checkInput(convert))
    {
        case 0:
            std::cout << "Convertion can't be done" << std::endl;
            break;
        case 1:
            charConv(convert);
            break;
        case 2:
            std::cout << "It's int" << std::endl;
            intConv(convert);
            break;
        case 3:
            std::cout << "It's float" << std::endl;
            floatConv(convert);
            break;
        case 4:
            std::cout << "It's double" << std::endl;
            break;
    }
}