#include "bool_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

BoolPattern::BoolPattern(bool value) : value(value), Pattern(PatternType::Bool, std::make_shared<TypeVariable>(TypeTag::Bool)) {
    
}

void BoolPattern::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> BoolPattern::infer() {
    return this->type_variable;
}

void BoolPattern::sem() {

}

llvm::Value* BoolPattern::codegen() {
    this->llvm_type = i1;
    return c1(value);
}