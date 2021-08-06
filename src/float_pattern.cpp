#include "float_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

FloatPattern::FloatPattern(float value) : value(value), Pattern(PatternType::Float, std::make_shared<TypeVariable>(TypeTag::Float)) {
    
}

void FloatPattern::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> FloatPattern::infer() {
    return this->type_variable;
}

void FloatPattern::sem() {

}

llvm::Value* FloatPattern::codegen() {

}