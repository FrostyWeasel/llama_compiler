#include "delete.hpp"

void Delete::print(std::ostream &out) const {
    out << " delete";
    if(expr != nullptr)
        expr->print(out);
    else
        out << " null";
}

std::shared_ptr<TypeVariable> Delete::infer() {
    auto expr_type = this->expr->infer();

    //Expr must be t ref
    st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Reference, std::make_shared<TypeVariable>()));

    //Result is always type ()
    return this->type_variable;
}

void Delete::sem() {
    this->expr->sem();
}

llvm::Value* Delete::codegen() {
    auto allocation_ptr = this->expr->codegen();
    return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
}