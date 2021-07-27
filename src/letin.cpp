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

    //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
    if(this->pass_stage == PassStage::FunctionDef) {
        this->parent_function_non_locals = AST::current_func_def_non_locals;
    }   

    //Opens but does not close scope.
    this->let_def->sem(); 

    // * Location of code must be here to allow the existence of more let in expressions in this ones expression
    if(this->pass_stage == PassStage::FunctionDef) {
        for(auto non_local_variable: *AST::current_func_def_non_locals) {
            this->parent_function_non_locals->insert(non_local_variable);
        }
        AST::current_func_def_non_locals = this->parent_function_non_locals;
    }

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