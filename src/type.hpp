#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include "enums.hpp"
#include "type_variable.hpp"

class TypeVariable;

class Type {
public:
    Type() : tag(TypeTag::Unknown) {  }
    Type(TypeTag type) : tag(type) {  }

    virtual ~Type() { }

    virtual TypeTag get_tag() { return tag; };
    virtual void set_tag(TypeTag tag) { this->tag = tag; }

    
    virtual void print(std::ostream& out) const { 
        switch(tag){
            case TypeTag::Bool:
                out << "bool";
                break;
            case TypeTag::Char:
                out << "char";
                break;
            case TypeTag::Int:
                out << "int";
                break;
            case TypeTag::Unit:
                out << "unit";
                break;
            case TypeTag::Unknown:
                out << "unknown";
                break;
            case TypeTag::Array:
                this->print(out);
                break;
            case TypeTag::Function:
                this->print(out);
                break;
            case TypeTag::Reference:
                this->print(out);
                break;
            default:
                std::cerr << "Unknown typetag\n";
                exit(1);
                break;
        }
        out << " ";
    }

    virtual bool contains(TypeVariable* type_variable) {
        return false;
    }

protected:
    TypeTag tag;
};

inline std::ostream& operator<<(std::ostream& out, const Type& type){
    type.print(out);
    return out;
}

#endif