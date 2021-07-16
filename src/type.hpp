#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include "enums.hpp"

class AST;

class Type{
public:
    Type() : tag(TypeTag::Unknown) { count = counter++; }
    Type(TypeTag type) : tag(type) { count = counter++; }
    Type(AST* parent) : tag(TypeTag::Unknown), parent(parent) { count = counter++; }
    Type(TypeTag type, AST* parent) : tag(type), parent(parent) { count = counter++; }

    virtual ~Type() { }

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
        out << ") ";
    }

    virtual bool contains(Type* t1) {
        return t1 == this;
    }

    virtual AST* get_parent() { return this->parent; }
    virtual void set_parent(AST* parent) { this->parent = parent; }

protected:
    TypeTag tag;
    AST* parent;

private:
    unsigned int count;
    static unsigned int counter;
};

inline std::ostream& operator<<(std::ostream& out, const Type& type){
    type.print(out);
    return out;
}

#endif