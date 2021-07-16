#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include <iostream>

class Type;

class FunctionType : public Type {
public:
    FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable): from_type_variable(from_type_variable), to_type_variable(to_type_variable), Type(TypeTag::Function) {}
    
    ~FunctionType() {
        delete from_type_variable;
        delete to_type_variable;
    }

    virtual bool contains(TypeVariable* type_variable) override {
        return from_type_variable->contains(type_variable) || to_type_variable->contains(from_type_variable);
    }

    TypeVariable* get_from_type_variable() {
        return from_type_variable;
    }

    TypeVariable* get_to_type_variable() {
        return to_type_variable;
    }

    virtual void print(std::ostream &out) const override{ 
        if (from_type_variable == nullptr)
            out << "from_type: Null ";
        else
            out << *from_type_variable << " ";
        out << "-> ";
        if (to_type_variable == nullptr)
            out << "to_type: Null ";
        else
            out << *to_type_variable << " ";
    }
    
private:
    TypeVariable* from_type_variable;
    TypeVariable* to_type_variable;
};

#endif