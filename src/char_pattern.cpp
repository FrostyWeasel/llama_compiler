#include "char_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

CharPattern::CharPattern(char value) : value(value), Pattern(PatternType::Char, std::make_shared<TypeVariable>(TypeTag::Char)) {
    
}

void CharPattern::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> CharPattern::infer() {
    return this->type_variable;
}

void CharPattern::sem() {

}

llvm::Value* CharPattern::codegen() {
    this->llvm_type = i8;
    return c8(value);
}