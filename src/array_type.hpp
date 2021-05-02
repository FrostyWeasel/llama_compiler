#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "type.hpp"
#include "includes.hpp"


class ArrayType : public Type{
public:
    ArrayType(Type* type): type(type), dimensions(1) {}
    ArrayType(Type* type, int dimensions): type(type), dimensions(dimensions) {}

    virtual void print(std::ostream &out) const { 
        out << "array "; 
        if(dimensions > 1){
            out << "[";
            for(int i = 0; i < dimensions; i++){
                out << "*";
            }
            out << "]";
        }
        if (type == nullptr)
            out << "Type: Null";
        else
        out << "of " << *type << " ";
    }
private:
    Type* type;
    int dimensions;
};

#endif