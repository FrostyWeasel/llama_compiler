#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"

class AST;

class RefType : public Type{
public:
    RefType(Type* type) : type(type), Type(TypeTag::Reference) { }
    RefType(Type* type, AST* parent) : type(type), Type(TypeTag::Reference, parent) { }

    ~RefType() {
        delete type;
    }

    virtual void set_tag(TypeTag tag) override { type->set_tag(tag); }

    virtual void print(std::ostream &out) const override{ 
        if (type == nullptr)
            out << "Type: Null";
        else
            out << *type << " ref ";
    }
    
private:
    Type* type;

};

#endif