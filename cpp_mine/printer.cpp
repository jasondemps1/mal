#include "printer.hpp"
#include <iostream>
#include "debug.hpp"

std::string pr_str(MalType* t)
{
        FUNC_OUT;
        std::string strItem;

        switch (t->Type()) {
        case MalType::Number:
                strItem = std::to_string(static_cast<MalNumber*>(t)->data);
                if (DEBUG)
                        std::cout << "NUMBER: " << strItem.c_str() << std::endl;;
                break;
        case MalType::Symbol:
                strItem = static_cast<MalSymbol*>(t)->data;
                if (strItem == ";")
                        strItem = "";

                if (DEBUG)
                        std::cout << "SYMBOL: " << strItem.c_str() << std::endl;
                //std::printf("SYMBOL: %s", strItem.c_str());
                break;

        case MalType::List:
        {
                MalList* listType = static_cast<MalList*>(t);
                if (DEBUG)
                        std::cout << "LIST!" << std::endl;

                strItem += "(";
                for (size_t i = 0; i < listType->data.size(); ++i) {
                        strItem += pr_str(listType->data[i]);
                        strItem += " ";
                }
                if (listType->data.size() > 0)
                        strItem[strItem.find_last_of(" ")] = ')';
                else
                        strItem += ")";
        }
        break;

        case MalType::Vector:
        {
                MalVector* coll = static_cast<MalVector*>(t);
                if (DEBUG)
                        std::cout << "VECTOR!" << std::endl;

                strItem += "[";
                for (size_t i = 0; i < coll->data.size(); ++i) {
                        strItem += pr_str(coll->data[i]);
                        strItem += " ";
                }
                if (coll->data.size() > 0)
                        strItem[strItem.find_last_of(" ")] = ']';
                else
                        strItem += "]";
        }
        break;

        default:
                std::cout << "Unhandled Type currently" << std::endl;
        }

        return strItem;
}
