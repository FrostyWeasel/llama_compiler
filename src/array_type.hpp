#ifndef __ARRAYTYPE_HPP__
#define __ARRAYTYPE_HPP__

#include "enums.hpp"
#include "type_variable.hpp"
#include <memory>

class Type;

class ArrayType : public Type {
public:
    ArrayType(TypeVariable* type_variable, DimType dim_type): dimensions(1), dim_type(dim_type), type_variable(std::make_shared<TypeVariable>(*type_variable)), Type(TypeTag::Array) {}
    ArrayType(TypeVariable* type_variable, unsigned int dimensions, DimType dim_type): dimensions(dimensions), dim_type(dim_type), type_variable(std::make_shared<TypeVariable>(*type_variable)), Type(TypeTag::Array) {}
    ArrayType(std::shared_ptr<TypeVariable> type_variable, DimType dim_type): dimensions(1), type_variable(type_variable), dim_type(dim_type), Type(TypeTag::Array) {}
    ArrayType(std::shared_ptr<TypeVariable> type_variable, unsigned int dimensions, DimType dim_type): dimensions(dimensions), type_variable(type_variable), dim_type(dim_type), Type(TypeTag::Array) {}

    ~ArrayType() { }

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override {
        return this->type_variable->contains(type_variable);
    }

    std::shared_ptr<TypeVariable> get_array_type() {
        return this->type_variable;
    }

    DimType get_dim_type() { return dim_type; }
    void set_dim_type(DimType dim_type) { this->dim_type = dim_type; }
    unsigned int get_dim() { return dimensions; }
    void set_dim(unsigned int dim) { this->dimensions = dim; }


    virtual void print(std::ostream &out) const override{ 
        out << "array "; 
        if(dimensions > 1){
            out << "[";
            for(unsigned int i = 0; i < dimensions; i++){
                if(i == dimensions-1)
                    out << "*";
                else
                    out << "*, ";
            }
            out << "] ";
        }
        out << "of" << *type_variable;
    }

private:
    std::shared_ptr<TypeVariable> type_variable;
    unsigned int dimensions;
    DimType dim_type;
};

#endif