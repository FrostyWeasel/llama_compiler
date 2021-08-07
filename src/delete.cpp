#include "delete.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <memory>
#include <iostream>

Delete::Delete(Expr* expr): expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}
Delete::~Delete()  {}

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
    st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Reference, std::make_shared<TypeVariable>()), this->lineno);

    //Result is always type ()
    return this->type_variable;
}

void Delete::sem() {
    this->expr->sem();
}

llvm::Value* Delete::codegen() {
    //This is a pointer to somewhere in the heap
    auto expr_value = this->expr->codegen();

    auto expr_heap_ptr = Builder.CreateBitCast(expr_value, llvm::PointerType::get(i8, 0));

    Builder.CreateCall(AST::free_function, { expr_heap_ptr });

    return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
}