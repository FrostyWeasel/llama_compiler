#include "letin.hpp"

void LetIn::print(std::ostream &out) const {
    out << "LetIn(";
    out << "LetDef: ";
    if(let_def != nullptr)
        let_def->print(out);
    else
        out << "null ";
    out << "Expr: ";
    if(expr != nullptr)
        expr->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> LetIn::infer() {
    //Opens but does not close scope.
    //* Let def type thrown away.
    this->let_def->infer(); 

    this->type_variable = this->expr->infer();

    //Letdef scope only encompasses expression.
    st->scope_close();

    return this->type_variable;
}

void LetIn::sem() {
    //Opens but does not close scope.
    this->let_def->sem(); 

    this->expr->sem();

    //Letdef scope only encompasses expression.
    st->scope_close();
}

llvm::Value* LetIn::codegen() {
    //Opens but does not close scope.
    this->let_def->codegen(); 
    
    auto expr_value = this->expr->codegen();

    //Letdef scope only encompasses expression.
    st->scope_close();

    return expr_value;
}