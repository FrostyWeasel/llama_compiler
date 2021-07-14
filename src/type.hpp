#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include "enums.hpp"

class Type{
public:
    Type() : tag(TypeTag::Unknown) {}
    Type(TypeTag type) : tag(type) {}

    virtual ~Type() {}

    virtual TypeTag get_tag() { return tag; };
    virtual void set_tag(TypeTag tag) { this->tag = tag; }

    
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
            case TypeTag::Array:
                out << "Array";
                break;
            case TypeTag::Function:
                out << "Function";
                break;
            case TypeTag::Reference:
                out << "Reference";
                break;
        }
        out << ") ";
    }

protected:
    TypeTag tag;
};

inline std::ostream& operator<<(std::ostream& out, const Type& type){
    type.print(out);
    return out;
}

#endif