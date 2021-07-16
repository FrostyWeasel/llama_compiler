#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "enums.hpp"
#include "type_variable.hpp"

class Type;

class RefType : public Type {
public:
    RefType(TypeVariable* type_variable) : type_variable(type_variable), Type(TypeTag::Reference) { }

    ~RefType() {
        delete type_variable;
    }

    virtual bool contains(TypeVariable* type_variable) override {
        return this->type_variable->contains(type_variable);
    }

    virtual void print(std::ostream &out) const override{ 
        if (type_variable == nullptr)
            out << "TypeVariable: Null";
        else
            out << *type_variable << " ref ";
    }
    
private:
    TypeVariable* type_variable;
};

#endif