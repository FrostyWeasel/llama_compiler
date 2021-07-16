#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "enums.hpp"
#include "type_variable.hpp"

class Type;

class ArrayType : public Type {
public:
    ArrayType(TypeVariable* type_variable): dimensions(1), type_variable(type_variable), Type(TypeTag::Array) {}
    ArrayType(TypeVariable* type_variable, int dimensions): dimensions(dimensions), type_variable(type_variable), Type(TypeTag::Array) {}

    ~ArrayType() { }

    virtual bool contains(TypeVariable* type_variable) override {
        return this->type_variable->contains(type_variable);
    }

    virtual void print(std::ostream &out) const override{ 
        out << "array "; 
        if(dimensions > 1){
            out << "[";
            for(int i = 0; i < dimensions; i++){
                out << "*";
            }
            out << "]";
        }
        out << "of " << *type_variable << " ";
    }

private:
    TypeVariable* type_variable;
    int dimensions;
};

#endif