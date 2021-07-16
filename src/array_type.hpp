#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "type.hpp"
#include "enums.hpp"

class ArrayType : public Type{
public:
    ArrayType(Type* type): dimensions(1), type(type), Type(TypeTag::Array) {}
    ArrayType(Type* type, int dimensions): dimensions(dimensions), type(type), Type(TypeTag::Array) {}
    ArrayType(Type* type, AST* parent): dimensions(1), type(type), Type(TypeTag::Array, parent) {}
    ArrayType(Type* type, int dimensions, AST* parent): dimensions(dimensions), type(type), Type(TypeTag::Array, parent) {}

    ~ArrayType() { }

    virtual void print(std::ostream &out) const override{ 
        out << "array "; 
        if(dimensions > 1){
            out << "[";
            for(int i = 0; i < dimensions; i++){
                out << "*";
            }
            out << "]";
        }
        out << "of " << *type << " ";
    }
private:
    Type* type;
    int dimensions;
};

#endif