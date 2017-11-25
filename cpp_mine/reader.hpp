#ifndef _READER_H_
#define _READER_H_

#include <string>
#include <vector>
#include <memory>

#include "types.hpp"

// Reader object for lexing and parsing

class Reader
{
public:
        Reader() :
                tokens(), position(0) {}
        Reader(std::vector<std::string> && tokens) :
                tokens(std::move(tokens)), position(0) {}
        std::string & Next();
        std::string & Peek();

        bool End() const { return position == tokens.size()-1; }
private:
        std::vector<std::string> tokens;
        size_t position;
};

MalType* Read_Str(std::string const & input);
MalType* Read_Form(Reader & r);
MalType* Read_Atom(Reader & r);
MalList* Read_List(Reader & r);
MalVector* Read_Vector(Reader & r);
std::vector<std::string> Tokenizer(std::string const & input);

#endif
