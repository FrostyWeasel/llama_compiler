#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "enums.hpp"
#include "type_variable.hpp"
#include <memory>

class Type;

class RefType : public Type {
public:
    RefType(TypeVariable* type_variable) : type_variable(std::make_shared<TypeVariable>(*type_variable)), Type(TypeTag::Reference) { }
    RefType(std::shared_ptr<TypeVariable> type_variable) : type_variable(type_variable), Type(TypeTag::Reference) { }

    ~RefType() {  }

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override {
        return this->type_variable->contains(type_variable);
    }

    std::shared_ptr<TypeVariable> get_referenced_variable() {
        return this->type_variable;
    }

    virtual void print(std::ostream &out) const override{ 
        if (type_variable == nullptr)
            out << "TypeVariable: Null";
        else
            out << " " << *type_variable << " ref ";
    }
    
private:
    std::shared_ptr<TypeVariable> type_variable;
};

#endif