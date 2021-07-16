#ifndef __FUNCTIONTYPE_HPP__
#define __FUNCTIONTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"
#include <iostream>

class FunctionType : public Type {
public:
    FunctionType(Type* from_type, Type* to_type): from_type(from_type), to_type(to_type), Type(TypeTag::Function) {}
    FunctionType(Type* from_type, Type* to_type, AST* parent): from_type(from_type), to_type(to_type), Type(TypeTag::Function, parent) {}
    
    //TODO: Cant delete for these to work fix function type creation.
    ~FunctionType() {
        if (from_type != nullptr)
            delete from_type;
        if (to_type != nullptr)
            delete to_type;
    }

    void set_from_type(TypeTag tag) { this->from_type->set_tag(tag); }
    void set_to_type(TypeTag tag) { this->to_type->set_tag(tag); }
    
    Type* get_from_type() { return this->from_type; }
    Type* get_to_type() { return this->to_type; }

    virtual bool contains(Type* type) override {
        if(from_type != nullptr) {
            if(from_type->contains(type)) return true;
        }
        else if(to_type != nullptr) {
            if(to_type->contains(type)) return true;
        }
        return false;
    }

    virtual void print(std::ostream &out) const override{ 
        if (from_type == nullptr)
            out << "from_type: Null ";
        else
            out << *from_type << " ";
        out << "-> ";
        if (to_type == nullptr)
            out << "to_type: Null ";
        else
            out << *to_type << " ";
    }
    
private:
    Type* from_type;
    Type* to_type;
};

#endif