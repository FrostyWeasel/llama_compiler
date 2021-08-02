#include "function_type.hpp"
#include "type_variable.hpp"
#include <memory>
#include <iostream>

FunctionType::FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable, FunctionTypeTag function_type): from_type_variable(std::shared_ptr<TypeVariable>(from_type_variable)), to_type_variable(std::shared_ptr<TypeVariable>(to_type_variable)), Type(TypeTag::Function), parameter_count(0), function_type_tag(function_type) {}
FunctionType::FunctionType(std::shared_ptr<TypeVariable> from_type_variable, std::shared_ptr<TypeVariable> to_type_variable, FunctionTypeTag function_type): from_type_variable(from_type_variable), to_type_variable(to_type_variable), Type(TypeTag::Function), parameter_count(0), function_type_tag(function_type) {}
FunctionType::FunctionType(TypeVariable* from_type_variable, TypeVariable* to_type_variable, unsigned int parameter_count, FunctionTypeTag function_type): from_type_variable(std::shared_ptr<TypeVariable>(from_type_variable)), to_type_variable(std::shared_ptr<TypeVariable>(to_type_variable)), Type(TypeTag::Function), parameter_count(parameter_count), function_type_tag(function_type) {}
FunctionType::FunctionType(std::shared_ptr<TypeVariable> from_type_variable, std::shared_ptr<TypeVariable> to_type_variable, unsigned int parameter_count, FunctionTypeTag function_type): from_type_variable(from_type_variable), to_type_variable(to_type_variable), Type(TypeTag::Function), parameter_count(parameter_count), function_type_tag(function_type) {}

FunctionType::~FunctionType() { }

bool FunctionType::contains(std::shared_ptr<TypeVariable> type_variable) {
    return from_type_variable->contains(type_variable) || to_type_variable->contains(type_variable);
}

std::shared_ptr<TypeVariable> FunctionType::get_from_type_variable() {
    return from_type_variable;
}

std::shared_ptr<TypeVariable> FunctionType::get_to_type_variable() {
    return to_type_variable;
}

void FunctionType::print(std::ostream &out) const{ 
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

unsigned int FunctionType::get_parameter_count() { return this->parameter_count; }
void FunctionType::set_parameter_count(unsigned int parameter_count) { this->parameter_count = parameter_count; }
    