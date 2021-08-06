#include "int_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

IntPattern::IntPattern(int value) : value(value), Pattern(PatternType::Int, std::make_shared<TypeVariable>(TypeTag::Int)) {
    
}

void IntPattern::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> IntPattern::infer() {
    return this->type_variable;
}

void IntPattern::sem() {

}

llvm::Value* IntPattern::codegen() {

}