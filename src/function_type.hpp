#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include <iostream>
#include <memory>

class Type;

class FunctionType : public Type {
public:
    FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable): from_type_variable(std::make_shared<TypeVariable>(*from_type_variable)), to_type_variable(std::make_shared<TypeVariable>(*to_type_variable)), Type(TypeTag::Function) {}
    FunctionType(std::shared_ptr<TypeVariable> from_type_variable, std::shared_ptr<TypeVariable> to_type_variable): from_type_variable(from_type_variable), to_type_variable(to_type_variable), Type(TypeTag::Function) {}


    ~FunctionType() { }

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override {
        return from_type_variable->contains(type_variable) || to_type_variable->contains(type_variable);
    }

    std::shared_ptr<TypeVariable> get_from_type_variable() {
        return from_type_variable;
    }

    std::shared_ptr<TypeVariable> get_to_type_variable() {
        return to_type_variable;
    }

    virtual void print(std::ostream &out) const override{ 
        if (from_type_variable == nullptr)
            out << "from_type: Null";
        else
            out << " " << *from_type_variable;
        out << " ->";
        if (to_type_variable == nullptr)
            out << " to_type: Null";
        else
            out << *to_type_variable;
    }
    
private:
    std::shared_ptr<TypeVariable> from_type_variable;
    std::shared_ptr<TypeVariable> to_type_variable;
};

#endif