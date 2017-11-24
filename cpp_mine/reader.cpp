#include "reader.hpp"
#include <regex>
#include <cctype>
#include <iostream>
#include "debug.hpp"
//#include <stdio.h>

std::string & Reader::Next()
{
        return tokens[position++];
}

std::string & Reader::Peek()
{
        return tokens[position];
}

MalType* Read_Str(std::string const & input)
{
        FUNC_OUT;
        Reader r = Tokenizer(input);
        return Read_Form(r);
}

MalType* Read_Form(Reader & r)
{
        FUNC_OUT;
        std::string tok = r.Peek();
        MalType* ret;

        switch(tok[0]) {
        case '(': ret = Read_List(r); break;
        default:  ret = Read_Atom(r);
        }

        return ret;
}

MalType* Read_Atom(Reader & r)
{
        // Determine the atom type:
        // * Symbol: contains at least one alpha character
        FUNC_OUT;
        //std::string & tok = r.Next();
        std::string & tok = r.Peek();
        if (DEBUG)
                std::cout << "Token is: " << tok << std::endl;
        bool isNumber = true;
        MalType* atom = nullptr;

        if (tok == ")")
                throw "')' found without opening brace";

        for (size_t i = 0; i < tok.length(); ++i)
                if (std::isalpha(tok[i]) || std::ispunct(tok[i])) {
                        isNumber = false;
                        break;
                }

        if (isNumber)
                atom = new MalNumber(std::stoi(tok));
        else
                atom = new MalSymbol(tok);

        return atom;
}

MalList* Read_List(Reader & r)
{
        FUNC_OUT;
        if (r.End())
                throw "No ')' to close List.";
        std::string tok = r.Next();
        MalList* list = new MalList();

        while (!r.End() && r.Peek() != ")") {
                list->data.push_back(Read_Form(r));
                if (!r.End())
                        tok = r.Next();
        }

        if (r.Peek() != ")") {
                const char* str = "No ')' to close List.";
                if (DEBUG)
                        std::cout << str << std::endl;
                throw str;
        }

        return list;
}

std::vector<std::string> Tokenizer(std::string const & input)
{
        FUNC_OUT;
        // std::regex r("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"|;.*|[^\\s\\[\\]{}('\"`,;)]*)");
        // //std::regex r("[\\s ,]*(~@|[\\[\\]{}()'`~@]|\"(?:[\\\\].|[^\\\\\"])*\"|;.*|[^\\s \\[\\]{}()'\"`~@,;]*)");
        // std::smatch m;
        // //std::regex_search(input, m, r);
        std::vector<std::string> tokens;
        // //std::regex_match(input, m, r, std::regex_constants::match_default);

        // if (std::regex_search(input, m, r)) {
        //         std::cout << "Matches: " << m.size() << std::endl;
        //         for (size_t i = 1; i < m.size(); ++i) {
        //                 std::cout << "Tokenized: " << m[i] << std::endl;
        //                 tokens.push_back(m[i]);
        //         }
        // }

        // for (auto p : m) {
        //         //printf("Tokenized: %s\n", p.str());
        //         std::cout << "Tokenized: " << p << std::endl;
        //         tokens.push_back(p);
        // }

        enum class Mode {None, Macro, Splice};
        static Mode mode = Mode::None;

        // Regex sucks
        std::string match;
        for (size_t i = 0; i < input.length(); ++i) {
                switch (input[i]) {
                case '(':
                case '[':
                case '{':
                        tokens.push_back(std::string(1, input[i]));
                        break;
                case ')':
                case ']':
                case '}':
                case ';':
                        if (match.length() > 0) {
                                tokens.push_back(match);
                                match.clear();
                        }
                        tokens.push_back(std::string(1, input[i]));
                        break;
                case ' ':
                case ',':
                        if (match.length() > 0) {
                                tokens.push_back(match);
                                match.clear();
                        }
                        break;
                /* READER MACRO TRANSFORMS */
                case '\'':
                        mode = Mode::Macro;
                        tokens.push_back("(");
                        tokens.push_back("quote");
                        break;
                case '`':
                        mode = Mode::Macro;
                        tokens.push_back("(");
                        tokens.push_back("quasiquote");
                        break;
                case '~':
                        mode = Mode::Splice;
                        tokens.push_back("(");
                        tokens.push_back("unquote");
                        break;
                case '@':
                        if (mode == Mode::Splice) {
                                tokens[i] = "splice-unquote";
                                break;
                        }
                        // tokens.push_back("(");
                        // tokens.push_back("unquote");
                default:
                        match += input[i];
                }
        }

        if (match.length() > 0) {
                tokens.push_back(match);
                if (mode != Mode::None) {
                        tokens.push_back(")");
                        mode = Mode::None;
                }
        }

        if (DEBUG) {
                std::cout << "Found Tokens: ";
                for (auto t : tokens)
                        std::cout << t << " ";
                std::cout << std::endl;
        }

        return tokens;
}

