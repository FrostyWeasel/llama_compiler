#include "new.hpp"
    
void New::print(std::ostream &out) const {
    out << " new";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
}

std::shared_ptr<TypeVariable> New::infer() {
    return this->type_variable;
}

void New::sem() {
    if((sa->is_same_tag(this->new_type_variable, TypeTag::Array))) {
        std::cerr << "New expression type can not be of type array\n" << "offending type is: " << *this->new_type_variable;
        exit(1); //TODO: Error handling.
    }
}

llvm::Value* New::codegen() {
    return Builder.CreateAlloca(map_to_llvm_type(this->new_type_variable), nullptr, "new_assignment");
}