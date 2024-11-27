#include <string>
#include <exception>

class   ScalarConverter
{
    public:
        ScalarConverter();
        ScalarConverter(ScalarConverter const &copy);
        virtual ~ScalarConverter() = 0;
        ScalarConverter &operator=(ScalarConverter const &copy);
        static void convert(std::string convert);

        class notValid : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};

int checkInput(std::string rawData);