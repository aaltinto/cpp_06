#include "includes/ScalarConverter.hpp"

static int isDouble(std::string rawData)
{
    int isDecimal = 0;
    int isNegative = 0;

    for (int i = 0; rawData[i] != '\0'; i++)
    {
        if (rawData[i] == '-' && i == 0)
        {
            isNegative = 1;
            continue ;
        }
        if (rawData[i] == '.')
        {
            if (isDecimal)
                return 0;
            isDecimal = 1;
            continue ;
        }
        if (!std::isdigit(rawData[i]))
            return 0;
    }
    return 1;
}

static int isChar(std::string rawData)
{
    if (rawData.size() == 1 && !std::isdigit(rawData[0]))
       return 1;
    return 0;
}

static int isNum(std::string rawData)
{
    std::string maxInt = std::to_string(std::numeric_limits<int>::max());
    std::string minInt = std::to_string(std::numeric_limits<int>::min());

    int isNegative = 0;

    if (rawData.size() > 11)
        return 0;
    for (unsigned int i = 0; i < rawData.size(); i++)
    {
        if (i == 0 && rawData[i] == '-')
        {
            isNegative = 1;
            continue;
        }
        if (!std::isdigit(rawData[i]))
            return 0;
        if ((isNegative && rawData.size() == 11 && rawData[i] > minInt[i]))
                return 0;
        if (rawData.size() == 10 && rawData[i] > maxInt[i])
                return 0;
    }
    return 1;
}

static int  isFloat(std::string rawData)
{
    int isDecimal = 0;
    int isNegative = 0;

    for (int i = 0; rawData[i] != '\0'; i++)
    {
        if (rawData[i] == '-' && i == 0)
        {
            isNegative = 1;
            continue ;
        }
        if (rawData[i] == '.')
        {
            if (isDecimal)
                return 0;
            isDecimal = 1;
            continue ;
        }
        if (std::isdigit(rawData[i]))
            continue;
        else if (isDecimal && rawData[i] == 'f' && rawData[i + 1] == '\0')
            return 1;
        else
            return 0;
    }
    return 0;
}

int checkInput(std::string rawData)
{
    std::string pseudo[] = {"-inff", "+inff", "-inf", "+inf", "nan", "nanf"};
    int (*checkers[])(std::string rawData) = {isChar, isNum, isFloat, isDouble};
    for (int i = 0; i < 4; i++)
    {
        if (checkers[i](rawData) == 1)
            return i + 1;
    }
    return 0;
}