#ifndef __REFTYPE_HPP__
#define __REFTYPE_HPP__

#include "enums.hpp"
#include "type_variable.hpp"
#include <memory>
#include <iostream>

class Type;

class RefType : public Type {
public:
    RefType(TypeVariable* type_variable) : type_variable(std::shared_ptr<TypeVariable>(type_variable)), Type(TypeTag::Reference) { 
        if(this->type_variable->get_tag() == TypeTag::Array) {
            std::cerr << "Referenced type can not be array.\n";
            exit(1); // TODO: Error handling + Should i do this?
        }
    }
    RefType(std::shared_ptr<TypeVariable> type_variable) : type_variable(type_variable), Type(TypeTag::Reference) { 
        if(this->type_variable->get_tag() == TypeTag::Array) {
            std::cerr << "Referenced type can not be array.\n";
            exit(1); // TODO: Error handling + Should i do this?
        }
    }

    virtual ~RefType() {  }

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
            out << " (" << *type_variable << ") ref ";
    }

    unsigned int get_depth() {
        return (this->type_variable->get_tag() == TypeTag::Reference) ? (1 + this->type_variable->get_complex_type_depth()) : (1);
    }

    TypeTag get_bottom_tag() {
        return (this->type_variable->get_tag() != TypeTag::Reference) ? (this->type_variable->get_bottom_tag()) : (this->type_variable->get_tag());
    }
    
private:
    std::shared_ptr<TypeVariable> type_variable;
};

#endif