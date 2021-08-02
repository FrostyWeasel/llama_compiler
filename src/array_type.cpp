
#include "array_type.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include <iostream>
#include <string>

ArrayType::ArrayType(TypeVariable* type_variable, DimType dim_type): dimensions(1), dim_type(dim_type), type_variable(std::shared_ptr<TypeVariable>(type_variable)), Type(TypeTag::Array) {
    if(this->type_variable->get_tag() == TypeTag::Array) {
        error_handler->print_error("Array type can not be array.\n", ErrorType::User);
    }
}
ArrayType::ArrayType(TypeVariable* type_variable, unsigned int dimensions, DimType dim_type): dimensions(dimensions), dim_type(dim_type), type_variable(std::shared_ptr<TypeVariable>(type_variable)), Type(TypeTag::Array) {
    if(this->type_variable->get_tag() == TypeTag::Array) {
        error_handler->print_error("Array type can not be array.\n", ErrorType::User);
    }
}
ArrayType::ArrayType(std::shared_ptr<TypeVariable> type_variable, DimType dim_type): dimensions(1), type_variable(type_variable), dim_type(dim_type), Type(TypeTag::Array) {
    if(this->type_variable->get_tag() == TypeTag::Array) {
        error_handler->print_error("Array type can not be array.\n", ErrorType::User);
    }
}
ArrayType::ArrayType(std::shared_ptr<TypeVariable> type_variable, unsigned int dimensions, DimType dim_type): dimensions(dimensions), type_variable(type_variable), dim_type(dim_type), Type(TypeTag::Array) {
    if(this->type_variable->get_tag() == TypeTag::Array) {
        error_handler->print_error("Array type can not be array.\n", ErrorType::User);
    }
}

ArrayType::~ArrayType() { }

bool ArrayType::contains(std::shared_ptr<TypeVariable> type_variable) {
    return this->type_variable->contains(type_variable);
}

std::shared_ptr<TypeVariable> ArrayType::get_array_type() {
    return this->type_variable;
}

DimType ArrayType::get_dim_type() { return dim_type; }
void ArrayType::set_dim_type(DimType dim_type) { this->dim_type = dim_type; }
unsigned int ArrayType::get_dim() { return dimensions; }
void ArrayType::set_dim(unsigned int dim) { this->dimensions = dim; }


void ArrayType::print(std::ostream &out) const{ 
    out << " array "; 
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