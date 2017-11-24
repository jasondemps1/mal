#include <iostream>
#include <string>
#include "types.hpp"
#include "reader.hpp"
#include "printer.hpp"
#include "debug.hpp"

MalType* read(std::string const & input)
{
        FUNC_OUT;
        return Read_Str(input);
}

MalType* eval(MalType* t)
{
        FUNC_OUT;
        return t;
}

std::string print(MalType* t)
{
        FUNC_OUT;
//        return input;
        return pr_str(t);
}

std::string rep(std::string const & input)
{
        FUNC_OUT;
        std::string ret;
        try {
                ret = print(eval(read(input)));
        } catch (const char* e) {
                ret = "ERROR: ";// + e;
                ret += e;
        }

        return ret;
}

int main ()
{
        const char* prompt = "user>";
        std::string input;

        while (1) {
                std::cout << prompt << " ";
                if (std::getline(std::cin, input)) {
                        //std::cout << "SAW: " << input << std::endl;
                        std::cout << rep(input) << std::endl;
                }
                else
                        break;
        }

        return 0;
}
