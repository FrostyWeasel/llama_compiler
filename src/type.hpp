#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include "enums.hpp"

class Type{
public:
    Type() : tag(TypeTag::Unknown) {}
    Type(TypeTag type) : tag(type) {}

    virtual ~Type() {}
    
    virtual void print(std::ostream& out) const { 
        out << "Type(";
        switch(tag){
            case TypeTag::Bool:
                out << "Bool";
                break;
            case TypeTag::Char:
                out << "Char";
                break;
            case TypeTag::Int:
                out << "Int";
                break;
            case TypeTag::Unit:
                out << "Unit";
                break;
            case TypeTag::Unknown:
                out << "Unknown";
                break;
        }
        out << ") ";
    }


private:
    TypeTag tag;
};

inline std::ostream& operator<<(std::ostream& out, const Type& type){
    type.print(out);
    return out;
}

#endif