#include "constructor_pattern.hpp"
#include "type_variable.hpp"
#include "block.hpp"
#include <string>
#include <memory>

ConstructorPattern::ConstructorPattern(std::string* id, Block<Pattern>* pattern_list) : id(*id), pattern_list(pattern_list), Pattern(PatternType::Constructor) {

}

void ConstructorPattern::print(std::ostream& out) const {
    out << id;
    out << " Pattern list(";
    if(pattern_list != nullptr) {
        pattern_list->print(out);
    }
    else {
        out << " null";
    }
    out << ") ";
}

std::shared_ptr<TypeVariable> ConstructorPattern::infer() {

}

void ConstructorPattern::sem() {

}

llvm::Value* ConstructorPattern::codegen() {

}