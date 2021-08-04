#include "id_pattern.hpp"
#include "type_variable.hpp"
#include <string>
#include <memory>

IdPattern::IdPattern(std::string* id) : id(*id), Pattern(PatternType::Id) {

}

void IdPattern::print(std::ostream& out) const {
    out << id;
}

std::shared_ptr<TypeVariable> IdPattern::infer() {

}

void IdPattern::sem() {

}

llvm::Value* IdPattern::codegen() {

}