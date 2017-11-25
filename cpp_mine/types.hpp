#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <vector>
#include <string>
#include <unordered_map>

class MalType
{
public:
        enum T {Nil, Bool, Number, String, Symbol, List, Vector, Map};

        MalType(T type) :
                _type(type) {}
        virtual ~MalType() {}
        T Type() const { return _type; }

protected:
        T _type;
};

class MalSymbol : public MalType
{
public:
        MalSymbol(std::string str) :
                MalType(MalType::Symbol), data(str) {}
        virtual ~MalSymbol() {}
        std::string data;
};

class MalNil : public MalType
{
public:
        MalNil() :
                MalType(MalType::Nil)/* , data() */ {}
        virtual ~MalNil() {}
        //char data;
};

class MalBool : public MalType
{
public:
        MalBool(bool val) :
                MalType(MalType::Bool), data(val ? 't' : 'f') {}
        virtual ~MalBool() {}
        char data;
};


class MalNumber : public MalType
{
public:
        MalNumber(int num) :
                MalType(MalType::Number), data(num) {}
        virtual ~MalNumber() {}
        int data;
};

struct MalString : public MalType
{
public:
        MalString(std::string str) :
                MalType(MalType::String), data(str) {}
        virtual ~MalString() {}
        std::string data;
};

struct MalList : public MalType
{
public:
        MalList() :
                MalType(MalType::List) {}
        MalList(std::vector<MalType*> vec) :
                MalType(MalType::List), data(vec) {}
        virtual ~MalList() { data.clear(); }
        std::vector<MalType*> data;
};

struct MalVector : public MalType
{
public:
        MalVector() :
                MalType(MalType::Vector) {}
        MalVector(std::vector<MalType*> vec) :
                MalType(MalType::Vector), data(vec) {}
        virtual ~MalVector() { data.clear(); }
        std::vector<MalType*> data;
};

struct MalMap : public MalType
{
public:
        MalMap() :
                MalType(MalType::Map) {}
        MalMap(std::unordered_map<MalType*, MalType*> vec) :
                MalType(MalType::Map), data(vec) {}
        virtual ~MalMap() { data.clear(); }
        std::unordered_map<MalType*, MalType*> data;
        //std::vector<MalType*> data;
};

#endif
