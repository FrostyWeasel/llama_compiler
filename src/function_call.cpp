#include "function_call.hpp"
#include <vector>
#include <string>
#include <iostream>

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

    this->st->add_constraint(func_type, correct_type, this->lineno);

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

    //If nesting level is 1 then it is a library function
    if(entry->get_nesting_level() == 1) {
        return FunctionCall::library_function_codegen();
    }
    else {
        auto function_struct = entry->get_allocation();

        auto function_declaration_ptr = Builder.CreateStructGEP(function_struct, 0, this->id+"_function_declaration_ptr");
        auto function_declaration_load = Builder.CreateLoad(function_declaration_ptr, this->id+"_function_declaration_load");

        auto function_type = llvm::dyn_cast<llvm::FunctionType>(function_declaration_load->getType()->getPointerElementType());

        std::vector<llvm::Value*> par_values;
        for(auto exp: expr_list->get_list()) {
            par_values.push_back(exp->codegen());
        }

        par_values.push_back(Builder.CreateBitCast(function_struct, llvm::PointerType::get(i8, 0)));

        return Builder.CreateCall(function_type, function_declaration_load, par_values, this->id+"_function_return");
    }
}

llvm::Value* FunctionCall::library_function_codegen() {
    std::vector<llvm::Value*> par_values;
    for(auto exp: expr_list->get_list()) {
        par_values.push_back(exp->codegen());
    }

    if(this->id == "print_string") {
        auto string_struct = par_values[0];
        auto string_struct_alloca = Builder.CreateAlloca(string_struct->getType(), nullptr, "string_struct_alloca");
        Builder.CreateStore(string_struct, string_struct_alloca);
        auto string_pointer = Builder.CreateStructGEP(string_struct_alloca, 2, "string_ptr");

        return Builder.CreateCall(AST::print_string, { Builder.CreateLoad(string_pointer) }, "print_string_function_return");
    }
    if(this->id == "print_int") {
        auto number = par_values[0];
        return Builder.CreateCall(AST::print_int, { number }, "print_int_function_return");
    }
    if(this->id == "print_char") {
        auto character = par_values[0];
        return Builder.CreateCall(AST::print_char, { character }, "print_char_function_return");
    }
    if(this->id == "print_bool") {
        auto boolean = par_values[0];
        return Builder.CreateCall(AST::print_bool, { boolean }, "print_bool_function_return");
    }
    if(this->id == "print_float") {
        auto float_value = par_values[0];
        return Builder.CreateCall(AST::print_float, { float_value }, "print_float_function_return");
    }
    if(this->id == "read_string") {
        auto string_struct = par_values[0];
        auto string_struct_element_count = string_struct->getType()->getStructNumElements();
        auto string_struct_alloca = Builder.CreateAlloca(string_struct->getType(), nullptr, "string_struct_alloca");
        Builder.CreateStore(string_struct, string_struct_alloca);

        //String is last element of struct
        auto string_ptr = Builder.CreateStructGEP(string_struct_alloca, string_struct_element_count - 1, "string_ptr");
        auto array_size_ptr = Builder.CreateStructGEP(string_struct_alloca, 0, "array_size_ptr");

        return Builder.CreateCall(AST::read_string, { Builder.CreateLoad(array_size_ptr), Builder.CreateLoad(string_ptr) }, "read_string_function_return");
    }
    if(this->id == "read_int") {
        return Builder.CreateCall(AST::read_int, {  });
    }
    if(this->id == "read_char") {
        return Builder.CreateCall(AST::read_char, {  });
    }
    if(this->id == "read_bool") {
        return Builder.CreateCall(AST::read_bool, {  });
    }
    if(this->id == "read_float") {
        return Builder.CreateCall(AST::read_float, {  });
    }
    if(this->id == "strlen") {
        //Get pointer to string
        auto string_struct = par_values[0];
        auto string_struct_alloca = Builder.CreateAlloca(string_struct->getType(), nullptr, "string_struct_alloca");
        Builder.CreateStore(string_struct, string_struct_alloca);
        auto string_ptr = Builder.CreateStructGEP(string_struct_alloca, 2, "string_ptr");

        return Builder.CreateCall(AST::strlen, { Builder.CreateLoad(string_ptr) }, "strlen_function_return");
    }
    if(this->id == "strcmp") {
        /*
            -1 : if string_1 < string_2
            0 : if string_1 = string_2
            1 : if string_1 > string_2
        */

        //Get pointer to target array
        auto string_1_struct = par_values[0];
        auto string_1_struct_alloca = Builder.CreateAlloca(string_1_struct->getType(), nullptr, "string_1_struct_alloca");
        Builder.CreateStore(string_1_struct, string_1_struct_alloca);
        auto string_1_ptr = Builder.CreateStructGEP(string_1_struct_alloca, 2, "string_1_ptr");

        //Get pointer to source array
        auto string_2_struct = par_values[1];
        auto string_2_struct_alloca = Builder.CreateAlloca(string_2_struct->getType(), nullptr, "string_2_struct_alloca");
        Builder.CreateStore(string_2_struct, string_2_struct_alloca);
        auto string_2_ptr = Builder.CreateStructGEP(string_2_struct_alloca, 2, "string_2_ptr");

        return Builder.CreateCall(AST::strcmp, { Builder.CreateLoad(string_1_ptr), Builder.CreateLoad(string_2_ptr) }, "strcmp_function_return");
    }
    if(this->id == "strcpy") {
        //Get pointer to target array
        auto target_struct = par_values[0];
        auto target_struct_alloca = Builder.CreateAlloca(target_struct->getType(), nullptr, "target_struct_alloca");
        Builder.CreateStore(target_struct, target_struct_alloca);
        auto target_ptr = Builder.CreateStructGEP(target_struct_alloca, 2, "target_ptr");

        //Get pointer to source array
        auto source_struct = par_values[1];
        auto source_struct_alloca = Builder.CreateAlloca(source_struct->getType(), nullptr, "source_struct_alloca");
        Builder.CreateStore(source_struct, source_struct_alloca);
        auto source_ptr = Builder.CreateStructGEP(source_struct_alloca, 2, "source_ptr");

        return Builder.CreateCall(AST::strcpy, { Builder.CreateLoad(target_ptr), Builder.CreateLoad(source_ptr) }, "strcpy_function_return");
    }
    if(this->id == "strcat") {
        //Source string is concatenated to target string

        //Get pointer to target array
        auto target_struct = par_values[0];
        auto target_struct_alloca = Builder.CreateAlloca(target_struct->getType(), nullptr, "target_struct_alloca");
        Builder.CreateStore(target_struct, target_struct_alloca);
        auto target_ptr = Builder.CreateStructGEP(target_struct_alloca, 2, "target_ptr");

        //Get pointer to source array
        auto source_struct = par_values[1];
        auto source_struct_alloca = Builder.CreateAlloca(source_struct->getType(), nullptr, "source_struct_alloca");
        Builder.CreateStore(source_struct, source_struct_alloca);
        auto source_ptr = Builder.CreateStructGEP(source_struct_alloca, 2, "source_ptr");

        return Builder.CreateCall(AST::strcat, { Builder.CreateLoad(target_ptr), Builder.CreateLoad(source_ptr) }, "strcat_function_return");
    }
    if(this->id == "int_of_char") {
        auto character = par_values[0];
        return Builder.CreateCall(AST::int_of_char, { character }, "int_of_char_function_return");
    }
    if(this->id == "char_of_int") {
        auto ascii_value = par_values[0];
        return Builder.CreateCall(AST::char_of_int, { ascii_value }, "char_of_int_function_return");
    }
    if(this->id == "incr") {
        auto int_ref = par_values[0];
        return Builder.CreateCall(AST::incr, { int_ref }, "incr_function_return");
    }
    if(this->id == "decr") {
        auto int_ref = par_values[0];
        return Builder.CreateCall(AST::decr, { int_ref }, "decr_function_return");
    }
    if(this->id == "int_of_float") {
        auto float_value = par_values[0];
        return Builder.CreateCall(AST::int_of_float, { float_value }, "int_of_float_function_return");
    }
    if(this->id == "float_of_int") {
        auto int_value = par_values[0];
        return Builder.CreateCall(AST::float_of_int, { int_value }, "float_of_int_function_return");
    }
    if(this->id == "round") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::llround, { i32, f64 }, { float_value }, nullptr);
    }
    if(this->id == "abs") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::abs, { i32 }, { float_value, c1(0) }, nullptr);
    }
    if(this->id == "fabs") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::fabs, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "sqrt") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::sqrt, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "sin") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::sin, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "cos") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::cos, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "tan") {
        auto float_value = par_values[0];
        return Builder.CreateCall(AST::tan, { float_value }, "tan_function_return");
    }
    if(this->id == "atan") {
        auto float_value = par_values[0];
        return Builder.CreateCall(AST::atan, { float_value }, "atan_function_return");
    }
    if(this->id == "exp") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::exp, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "ln") {
        auto float_value = par_values[0];
        return Builder.CreateIntrinsic(llvm::Intrinsic::log, { f64 }, { float_value }, nullptr);
    }
    if(this->id == "pi") {
        return Builder.CreateCall(AST::pi, {  }, "pi_function_return");
    }
    else {
        error_handler->print_error("Library function: " + this->id + " is not implemented", ErrorType::Internal);
    }
    
    return nullptr;
}