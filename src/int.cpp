
#include "int.hpp"
#include "type_variable.hpp"
#include <iostream>

Int::Int(int value) : value(value), Expr(new TypeVariable(TypeTag::Int)) { }
void Int::print(std::ostream& out) const{
    out << value;
}

std::shared_ptr<TypeVariable> Int::infer() { 
    return this->type_variable;
}

void Int::sem() { /* No need for further checks */ }

llvm::Value* Int::codegen() {
    return c32(this->value);
}
