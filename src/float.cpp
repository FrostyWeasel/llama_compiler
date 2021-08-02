
#include "float.hpp"
#include "type_variable.hpp"
#include <iostream>

Float::Float(float value) : value(value), Expr(new TypeVariable(TypeTag::Float)) { }

void Float::print(std::ostream& out) const{
    out << value;
}

std::shared_ptr<TypeVariable> Float::infer() { 
    return this->type_variable;
}

void Float::sem() { /* No need for further checks */ }

llvm::Value* Float::codegen() {
    return cf32(this->value);
}
