#include "function_call.hpp"
#include <vector>

void FunctionCall::print(std::ostream &out) const {
    out << "FunctionCall(";
    out << " Id: " << id << ", ";
    out << "Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << "Expr_list: ";
    if(expr_list != nullptr)
        expr_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> FunctionCall::infer() {
    auto entry = this->st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);
    
    std::shared_ptr<TypeVariable> func_type = entry->get_type();
    std::shared_ptr<TypeVariable> par_list_type = this->expr_list->infer();
    std::shared_ptr<TypeVariable> correct_type = std::make_shared<TypeVariable>(TypeTag::Function, par_list_type, this->type_variable, this->expr_list->block_size()); 

    this->st->add_constraint(func_type, correct_type);

    return this->type_variable;
}

void FunctionCall::sem() {  
    //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
    if(this->pass_stage == PassStage::FunctionDef) {
        auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        
        // If id not in the same scope as the parameters of the function
        if(entry->get_nesting_level() != this->st->get_current_nesting_level()) {
            this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
        }
    }   
        
    this->expr_list->sem();
}

llvm::Value* FunctionCall::codegen() {
    auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
    auto function_struct = entry->get_allocation();

    auto function_declaration_ptr = Builder.CreateStructGEP(function_struct, 0, this->id+"_function_declaration_ptr");
    auto function_declaration_load = Builder.CreateLoad(function_declaration_ptr, this->id+"_function_declaration_load");

    auto function_type = llvm::dyn_cast<llvm::FunctionType>(function_declaration_load->getType()->getPointerElementType());

    std::vector<llvm::Value*> par_values;
    for(auto exp: expr_list->get_list()) {
        par_values.push_back(exp->codegen());
    }

    par_values.push_back(Builder.CreateBitCast(function_struct, llvm::PointerType::get(llvm::Type::getVoidTy(TheContext), 0)));


    // * Unnamed because it is not allowed for calls to have names if return type is void
    return Builder.CreateCall(function_type, function_declaration_load, par_values);
}