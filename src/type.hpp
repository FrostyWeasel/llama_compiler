#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include "enums.hpp"
#include "includes.hpp"

class Type{
public:
    Type() : tag(TypeTag::Unkown) {}
    Type(TypeTag type) : tag(type) {}
    
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
            case TypeTag::Unkown:
                out << "Unkown";
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