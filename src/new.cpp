#include "new.hpp"
#include "constant_entry.hpp"
#include "semantic_analyzer.hpp"
#include "symbol_table.hpp"
#include "error_handler.hpp"
#include "type_variable.hpp"
#include <iostream>
#include <string>
#include <memory>

New::New(std::shared_ptr<TypeVariable> type_variable): new_type_variable(type_variable), Expr(new TypeVariable(TypeTag::Reference, type_variable)) { }
    
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
        error_handler->non_allowed_type(this->new_type_variable, this->lineno, ErrorType::User, NodeType::New);
    }
}

llvm::Value* New::codegen() {
    //Allocate space in heap for the reference type and then store the pointer to that element in the new expr alloca 
    auto llvm_type = map_to_llvm_type(this->type_variable);
    
    auto referenced_type = llvm_type->getPointerElementType();
    auto referenced_value_heap_void_ptr = Builder.CreateCall(AST::malloc_function, { c32(TheDataLayout->getTypeAllocSize(referenced_type).getValue()) }, "new_expr_heap_ptr");

    auto referenced_value_ptr = Builder.CreateBitCast(referenced_value_heap_void_ptr, llvm_type, "new_value_ptr");

    return referenced_value_ptr;
}