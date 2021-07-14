#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"


class RefType : public Type{
public:
    RefType(Type* type) : type(type), Type(TypeTag::Reference) { }

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