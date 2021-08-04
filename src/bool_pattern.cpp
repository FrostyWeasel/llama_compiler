#include "bool_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

BoolPattern::BoolPattern(bool value) : value(value), Pattern(PatternType::Bool) {
    
}

void BoolPattern::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> BoolPattern::infer() {

}

void BoolPattern::sem() {

}

llvm::Value* BoolPattern::codegen() {

}