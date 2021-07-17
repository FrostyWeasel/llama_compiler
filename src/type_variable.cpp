#include "type_variable.hpp"
#include "type.hpp"
#include "function_type.hpp"
#include "array_type.hpp"
#include "ref_type.hpp"
#include "enums.hpp"
#include <memory>

unsigned int TypeVariable::counter = 0;

TypeVariable::TypeVariable() : type(std::make_shared<Type>(TypeTag::Unknown)), tag(TypeVariableTag::Free), id(++TypeVariable::counter) {  }

TypeVariable::TypeVariable(TypeTag type_tag) { 
    switch (type_tag) {
        case TypeTag::Unknown:
            this->type = std::make_shared<Type>(TypeTag::Unknown);
            this->tag = TypeVariableTag::Free;
            this->id = ++TypeVariable::counter;
            break;
        
        default:
            this->type = std::make_shared<Type>(type_tag);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* t1) {
    switch (type_tag) {
        case TypeTag::Reference:
            this->type = std::make_shared<RefType>(t1);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;
        
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, DimType::AtLeast);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* from_type, TypeVariable* to_type) {
    switch (type_tag) {
        case TypeTag::Function:
            this->type = std::make_shared<FunctionType>(from_type, to_type);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag non Function for constractor two type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* t1, unsigned int dim) {
    switch (type_tag) {
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, dim, DimType::Exact);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1) {
    switch (type_tag) {
        case TypeTag::Reference:
            this->type = std::make_shared<RefType>(t1);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            
            break;
        
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, DimType::AtLeast);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> from_type, std::shared_ptr<TypeVariable> to_type) {
    switch (type_tag) {
        case TypeTag::Function:
            this->type = std::make_shared<FunctionType>(from_type, to_type);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag non Function for constractor two type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, unsigned int dim, DimType dim_type) {
    switch (type_tag) {
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, dim, dim_type);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;

            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, std::shared_ptr<TypeVariable> t1, DimType dim_type) {
    switch (type_tag) {
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, dim_type);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking DimType\n";
            exit(1);
            break;
    }
}

bool TypeVariable::contains(std::shared_ptr<TypeVariable> type_variable) {
    if (this->id == type_variable->id)
        return true;
    else 
        return this->type->contains(type_variable);
}

void TypeVariable::bind(std::shared_ptr<TypeVariable> bound_type) {
    //TODO: Remove from free list if i make one during error handling.
    this->type = bound_type->type;
    this->tag = bound_type->tag;
}

std::shared_ptr<TypeVariable> TypeVariable::get_function_from_type() {
    if (this->type->get_tag() == TypeTag::Function) {
        auto function_ptr = std::dynamic_pointer_cast<FunctionType>(this->type);
        return function_ptr->get_from_type_variable();
    }
    else{
        std::cerr << "Requesting get_function_from_type but type is not a function\n";
        exit(1); //TODO: Error handling
    }
}

std::shared_ptr<TypeVariable> TypeVariable::get_function_to_type() {
    if (this->type->get_tag() == TypeTag::Function) {
        auto function_ptr = std::dynamic_pointer_cast<FunctionType>(this->type);
        return function_ptr->get_to_type_variable();
    }
    else{
        std::cerr << "Requesting get_function_to_type but type is not a function\n";
        exit(1); //TODO: Error handling
    }
}

std::shared_ptr<TypeVariable> TypeVariable::get_referenced_type() {
    if (this->type->get_tag() == TypeTag::Reference) {
        auto reference_ptr = std::dynamic_pointer_cast<RefType>(this->type);
        return reference_ptr->get_referenced_variable();
    }
    else{
        std::cerr << "Requesting get_referenced_variable but type is not a reference\n";
        exit(1); //TODO: Error handling
    }
}

std::shared_ptr<TypeVariable> TypeVariable::get_array_type() {
    if (this->type->get_tag() == TypeTag::Array) {
        auto array_ptr = std::dynamic_pointer_cast<ArrayType>(this->type);
        return array_ptr->get_array_type();
    }
    else{
        std::cerr << "Requesting get_array_type but type is not an array\n";
        exit(1); //TODO: Error handling
    }
}

TypeTag TypeVariable::get_tag() { return type->get_tag(); }
TypeVariableTag TypeVariable::get_variable_tag() { return this->tag; }

void TypeVariable::print(std::ostream& out) const { 
    switch(tag){
        case TypeVariableTag::Free:
            out << " @" << id << ":" << *this->type;
            break;
        case TypeVariableTag::Bound:
            out << " " << *this->type;
            break;
        default:
            std::cerr << "Unknown TypeVariableTag\n";
            exit(1);
            break;
    }
}

bool TypeVariable::is_bound() {
    return this->tag == TypeVariableTag::Bound;
}


unsigned int TypeVariable::get_array_dim() {
    if(this->type->get_tag() == TypeTag::Array) {
        auto array_ptr = std::dynamic_pointer_cast<ArrayType>(this->type);
        return array_ptr->get_dim();
    }
    else{
        std::cerr << "Requesting get_array_dim but type is not an array\n";
        exit(1); //TODO: Error handling
    }
}

void TypeVariable::set_array_dim(unsigned int dim) {
    if(this->type->get_tag() == TypeTag::Array) {
        auto array_ptr = std::dynamic_pointer_cast<ArrayType>(this->type);
        return array_ptr->set_dim(dim);
    }
    else{
        std::cerr << "Requesting set_array_dim but type is not an array\n";
        exit(1); //TODO: Error handling
    }
}

DimType TypeVariable::get_array_dim_type() {
    if(this->type->get_tag() == TypeTag::Array) {
        auto array_ptr = std::dynamic_pointer_cast<ArrayType>(this->type);
        return array_ptr->get_dim_type();
    }
    else{
        std::cerr << "Requesting get_array_dim_type but type is not an array\n";
        exit(1); //TODO: Error handling
    }
}

void TypeVariable::set_array_dim_type(DimType dim_type) {
    if(this->type->get_tag() == TypeTag::Array) {
        auto array_ptr = std::dynamic_pointer_cast<ArrayType>(this->type);
        return array_ptr->set_dim_type(dim_type);
    }
    else{
        std::cerr << "Requesting set_array_dim_type but type is not an array\n";
        exit(1); //TODO: Error handling
    }
}
