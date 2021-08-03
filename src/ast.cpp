#include "ast.hpp"
#include "function_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include "semantic_analyzer.hpp"
#include "ref_type.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "type_variable.hpp"
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>
#include <iostream>

std::unique_ptr<SymbolTable> AST::st = std::make_unique<SymbolTable>(20000);
std::unique_ptr<SemanticAnalyzer> AST::sa = std::make_unique<SemanticAnalyzer>();
PassStage AST::pass_stage = PassStage::Other;
std::map<std::string, std::shared_ptr<TypeVariable>>* AST::current_func_def_non_locals = nullptr;
std::unique_ptr<std::vector<std::shared_ptr<TypeVariable>>> AST::created_type_variables = std::make_unique<std::vector<std::shared_ptr<TypeVariable>>>();
std::unique_ptr<ErrorHandler> AST::error_handler = std::make_unique<ErrorHandler>();
std::unique_ptr<std::unordered_map<unsigned int, AST*>> AST::type_variable_owners = std::make_unique<std::unordered_map<unsigned int, AST*>>();

llvm::LLVMContext AST::TheContext;
llvm::IRBuilder<> AST::Builder(TheContext);
std::unique_ptr<llvm::Module> AST::TheModule;
std::unique_ptr<llvm::legacy::FunctionPassManager> AST::FPM;

llvm::Function* AST::printf;

llvm::Function* AST::print_string;
llvm::Function* AST::print_int;
llvm::Function* AST::print_char;
llvm::Function* AST::print_bool;
llvm::Function* AST::print_float;
llvm::Function* AST::read_string;
llvm::Function* AST::read_int;
llvm::Function* AST::read_char;
llvm::Function* AST::read_bool;
llvm::Function* AST::read_float;
llvm::Function* AST::incr;
llvm::Function* AST::decr;
llvm::Function* AST::int_of_char;
llvm::Function* AST::char_of_int;
llvm::Function* AST::strcpy;
llvm::Function* AST::strcmp;
llvm::Function* AST::strcat;
llvm::Function* AST::strlen;
llvm::Function* AST::float_of_int;
llvm::Function* AST::int_of_float;
llvm::Function* AST::round;
llvm::Function* AST::abs;
llvm::Function* AST::fabs;
llvm::Function* AST::sqrt;
llvm::Function* AST::sin;
llvm::Function* AST::cos;
llvm::Function* AST::tan;
llvm::Function* AST::atan;
llvm::Function* AST::exp;
llvm::Function* AST::ln;
llvm::Function* AST::pi;

llvm::Type *AST::i1 = llvm::IntegerType::get(TheContext, 1);
llvm::Type *AST::i8 = llvm::IntegerType::get(TheContext, 8);
llvm::Type *AST::i16 = llvm::IntegerType::get(TheContext, 16);
llvm::Type *AST::i32 = llvm::IntegerType::get(TheContext, 32);
llvm::Type *AST::i64 = llvm::IntegerType::get(TheContext, 64);
llvm::Type *AST::f16 = llvm::Type::getHalfTy(TheContext);
llvm::Type *AST::f32 = llvm::Type::getFloatTy(TheContext);
llvm::Type *AST::f64 = llvm::Type::getDoubleTy(TheContext);

void AST::close_library_function_scope() {
    st->scope_close();
}

void AST::close_all_program_scopes() {
    st->close_all_program_scopes();
}

void AST::clear_inference_structures() { 
    st->clear_inference_structures(); 
}

void AST::unify() { 
    st->unify(); 
}

llvm::Type* AST::map_to_llvm_type(std::shared_ptr<TypeVariable> type_variable) {
    switch (type_variable->get_tag()) {
        case TypeTag::Int:
            return AST::i32;
        break;
        case TypeTag::Float:
            return AST::f64;
        break;
        case TypeTag::Bool:
            return AST::i1;
        break;
        case TypeTag::Char:
            return AST::i8;
        break;
        case TypeTag::Unit:
            return llvm::StructType::get(TheContext);
        break;
        case TypeTag::Unknown:
            return llvm::StructType::get(TheContext);
        break;
        case TypeTag::Function:{
            llvm::Type* return_type;
                return_type = map_to_llvm_type(type_variable->get_function_to_type());
            std::vector<llvm::Type*> par_types;
            map_par_list_to_llvm_type(type_variable->get_function_from_type(), par_types);

            //Pointer to struct containing pointer to function and non local variables struct.
            par_types.push_back(llvm::PointerType::get(i8, 0));

            return llvm::StructType::get(TheContext, { llvm::PointerType::get(llvm::FunctionType::get(return_type, par_types, false), 0), llvm::PointerType::get(i8, 0) });
        }
        break;
        case TypeTag::Reference: {
            auto ref_ptr = type_variable->get_referenced_type();
            auto referenced_llvm_type = map_to_llvm_type(ref_ptr);

            return llvm::PointerType::get(referenced_llvm_type, 0);
        }
        case TypeTag::Array: {
            std::vector<llvm::Type*> array_type;
            //space to store the total array size
            array_type.push_back(i32);
            //space to store the dimension size
            for(unsigned int i = 0; i < type_variable->get_array_dim(); i++) {
                array_type.push_back(i32);
            }
            //space to store the pointer to the first array element
            array_type.push_back(llvm::PointerType::get(map_to_llvm_type(type_variable->get_array_type()),0));

            return llvm::StructType::get(TheContext, array_type);
        }
        break;
        default:
            error_handler->print_error("Uknown type\n", ErrorType::Internal);
            break;
    }
    return nullptr;
}

void AST::map_par_list_to_llvm_type(std::shared_ptr<TypeVariable> type_variable, std::vector<llvm::Type*>& par_types) {
    while(type_variable->get_tag() == TypeTag::Function) {
        if(type_variable->get_function_type_tag() == FunctionTypeTag::Actual) {
            par_types.insert(par_types.begin(), map_to_llvm_type(type_variable));
            return;
        }
        else {
            par_types.insert(par_types.begin(), map_to_llvm_type(type_variable->get_function_to_type()));
            type_variable = type_variable->get_function_from_type();
        }
    }
    par_types.insert(par_types.begin(), map_to_llvm_type(type_variable));
}

void AST::llvm_compile_and_dump(bool optimize) {
    // Initialize
    TheModule = std::make_unique<llvm::Module>("Llama program", TheContext);
   
    FPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
    if(optimize) {
        FPM->add(llvm::createPromoteMemoryToRegisterPass()); //https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl07.html#memory-in-llvm
        FPM->add(llvm::createInstructionCombiningPass());
        FPM->add(llvm::createReassociatePass());
        FPM->add(llvm::createGVNPass());
        FPM->add(llvm::createCFGSimplificationPass());
    }
    FPM->doInitialization();

    //Define llama library functions
    AST::declare_library_functions();

    // Define and start the main function.
    llvm::FunctionType* main_type = llvm::FunctionType::get(i32, {}, false);
    llvm::Function *main =
        llvm::Function::Create(main_type, llvm::Function::ExternalLinkage,
                               "main", TheModule.get());

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
    Builder.SetInsertPoint(BB);

    // Emit the program code.
    this->codegen();
    Builder.CreateRet(c32(0));

    // Verify the IR.
    bool bad = verifyModule(*TheModule, &llvm::errs());
    if (bad) {
        std::cerr << "\nThe IR is bad!\n" << std::endl;
        TheModule->print(llvm::errs(), nullptr);
        std::exit(1);
    }

    // Optimize!
    FPM->run(*main);

    // Print out the IR.
    TheModule->print(llvm::outs(), nullptr);
}

void AST::declare_library_functions() {
    auto printf_type = llvm::FunctionType::get(i32, { llvm::PointerType::get(i8, 0) }, true);
    AST::printf = llvm::Function::Create(printf_type, llvm::Function::LinkageTypes::ExternalLinkage, "printf", TheModule.get());

    //Print Functions
    define_print_functions();

    //Read Functions
    auto read_string_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { i32, llvm::PointerType::get(i8, 0) }, false);
    AST::read_string = llvm::Function::Create(read_string_type, llvm::Function::ExternalLinkage, "readString", TheModule.get());

    auto read_int_type = llvm::FunctionType::get(i32, {  }, false);
    AST::read_int = llvm::Function::Create(read_int_type, llvm::Function::ExternalLinkage, "readInteger", TheModule.get());
    AST::read_int->addAttribute(0, llvm::Attribute::get(TheContext, llvm::Attribute::AttrKind::SExt));

    auto read_char_type = llvm::FunctionType::get(i8, {  }, false);
    AST::read_char = llvm::Function::Create(read_char_type, llvm::Function::ExternalLinkage, "readChar", TheModule.get());

    auto read_bool_type = llvm::FunctionType::get(i1, {  }, false);
    AST::read_bool = llvm::Function::Create(read_bool_type, llvm::Function::ExternalLinkage, "readBoolean", TheModule.get());

    auto read_float_type = llvm::FunctionType::get(f64, {  }, false);
    AST::read_float = llvm::Function::Create(read_float_type, llvm::Function::ExternalLinkage, "readReal", TheModule.get());

    //Reference update Functions
    define_reference_update_functions();

    //Conversion Functions
    auto round_type = llvm::FunctionType::get(i32, { f64 }, false);
    AST::round = llvm::Function::Create(round_type, llvm::Function::LinkageTypes::ExternalLinkage, "round", TheModule.get());

    define_conversion_functions();

    //Math Functions
    auto tan_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::tan = llvm::Function::Create(tan_type, llvm::Function::LinkageTypes::ExternalLinkage, "tan", TheModule.get());
    
    auto atan_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::atan = llvm::Function::Create(atan_type, llvm::Function::LinkageTypes::ExternalLinkage, "atan", TheModule.get());

    auto pi_type = llvm::FunctionType::get(f64, { }, false);
    AST::pi = llvm::Function::Create(pi_type, llvm::Function::LinkageTypes::ExternalLinkage, "pi", TheModule.get());

    auto abs_type = llvm::FunctionType::get(i32, { i32 }, false);
    AST::abs = llvm::Function::Create(abs_type, llvm::Function::LinkageTypes::ExternalLinkage, "abs", TheModule.get());

    auto fabs_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::fabs = llvm::Function::Create(fabs_type, llvm::Function::LinkageTypes::ExternalLinkage, "fabs", TheModule.get());

    auto sqrt_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::sqrt = llvm::Function::Create(sqrt_type, llvm::Function::LinkageTypes::ExternalLinkage, "sqrt", TheModule.get());

    auto cos_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::cos = llvm::Function::Create(cos_type, llvm::Function::LinkageTypes::ExternalLinkage, "cos", TheModule.get());

    auto exp_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::exp = llvm::Function::Create(exp_type, llvm::Function::LinkageTypes::ExternalLinkage, "exp", TheModule.get());

    auto ln_type = llvm::FunctionType::get(f64, { f64 }, false);
    AST::ln = llvm::Function::Create(ln_type, llvm::Function::LinkageTypes::ExternalLinkage, "ln", TheModule.get());

    //String functions
    auto strcpy_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0) }, false);
    AST::strcpy = llvm::Function::Create(strcpy_type, llvm::Function::LinkageTypes::ExternalLinkage, "strcpy", TheModule.get());

    auto strcmp_type = llvm::FunctionType::get(i32, { llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0) }, false);
    AST::strcmp = llvm::Function::Create(strcmp_type, llvm::Function::LinkageTypes::ExternalLinkage, "strcmp", TheModule.get());
    AST::strcmp->addAttribute(0, llvm::Attribute::get(TheContext, llvm::Attribute::AttrKind::SExt));

    auto strcat_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0) }, false);
    AST::strcat = llvm::Function::Create(strcat_type, llvm::Function::LinkageTypes::ExternalLinkage, "strcat", TheModule.get());

    auto strlen_type = llvm::FunctionType::get(i32, { llvm::PointerType::get(i8, 0) }, false);
    AST::strlen = llvm::Function::Create(strlen_type, llvm::Function::LinkageTypes::ExternalLinkage, "strlen", TheModule.get());
    AST::strlen->addAttribute(0, llvm::Attribute::get(TheContext, llvm::Attribute::AttrKind::SExt));

}

void AST::define_print_functions() {
    auto print_string_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), {llvm::PointerType::get(AST::i8, 0)}, false);
    AST::print_string = llvm::Function::Create(print_string_type, llvm::Function::ExternalLinkage, "print_string", TheModule.get());

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "print_string_entry", AST::print_string );
    Builder.SetInsertPoint(function_body_BB);

    auto format_string = Builder.CreateGlobalStringPtr("%s");

    for(auto &par: AST::print_string->args()) {
        Builder.CreateCall(AST::printf, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //*
    auto print_int_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { AST::i32 }, false);
    AST::print_int = llvm::Function::Create(print_int_type, llvm::Function::ExternalLinkage, "print_int", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "print_int_entry", AST::print_int );
    Builder.SetInsertPoint(function_body_BB);

    format_string = Builder.CreateGlobalStringPtr("%i");

    for(auto &par: AST::print_int->args()) {
        Builder.CreateCall(AST::printf, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //*
    auto print_char_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { AST::i8 }, false);
    AST::print_char = llvm::Function::Create(print_char_type, llvm::Function::ExternalLinkage, "print_char", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "print_char_entry", AST::print_char );
    Builder.SetInsertPoint(function_body_BB);

    format_string = Builder.CreateGlobalStringPtr("%c");

    for(auto &par: AST::print_char->args()) {
        Builder.CreateCall(AST::printf, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //*
    auto print_bool_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { AST::i1 }, false);
    AST::print_bool = llvm::Function::Create(print_bool_type, llvm::Function::ExternalLinkage, "print_bool", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "print_bool_entry", AST::print_bool );
    Builder.SetInsertPoint(function_body_BB);

    format_string = Builder.CreateGlobalStringPtr("%i");

    for(auto &par: AST::print_bool->args()) {
        Builder.CreateCall(AST::printf, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //*
    auto print_float_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { AST::f64 }, false);
    AST::print_float = llvm::Function::Create(print_float_type, llvm::Function::ExternalLinkage, "print_float", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "print_float_entry", AST::print_float );
    Builder.SetInsertPoint(function_body_BB);

    format_string = Builder.CreateGlobalStringPtr("%lf");

    for(auto &par: AST::print_float->args()) {
        Builder.CreateCall(AST::printf, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

}

void AST::define_conversion_functions() {
    //Definition of int_of_char function
    auto int_of_char_type = llvm::FunctionType::get(i32, { i8 }, false);
    AST::int_of_char = llvm::Function::Create(int_of_char_type, llvm::Function::LinkageTypes::ExternalLinkage, "int_of_char", TheModule.get());

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "int_of_char_entry", AST::int_of_char );
    Builder.SetInsertPoint(function_body_BB);

    //Get function parameter transform it from char to int and then return it
    for(auto &par: AST::int_of_char->args()) {
        Builder.CreateRet(Builder.CreateZExt(&par, i32));
    }
    Builder.SetInsertPoint(previous_insert_point);

    //Definition of char_of_int function
    auto char_of_int_type = llvm::FunctionType::get(i8, { i32 }, false);
    AST::char_of_int = llvm::Function::Create(char_of_int_type, llvm::Function::LinkageTypes::ExternalLinkage, "char_of_int", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "char_of_int_entry", AST::char_of_int );
    Builder.SetInsertPoint(function_body_BB);

    //Get function parameter transform it from char to int and then return it
    for(auto &par: AST::char_of_int->args()) {
        Builder.CreateRet(Builder.CreateTrunc(&par, i8));
    }
    Builder.SetInsertPoint(previous_insert_point);

    //Definition of float_of_int function
    auto float_of_int_type = llvm::FunctionType::get(f64, { i32 }, false);
    AST::float_of_int = llvm::Function::Create(float_of_int_type, llvm::Function::LinkageTypes::ExternalLinkage, "float_of_int", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "float_of_int_entry", AST::float_of_int );
    Builder.SetInsertPoint(function_body_BB);

    //Get function parameter transform it from char to int and then return it
    for(auto &par: AST::float_of_int->args()) {
        Builder.CreateRet(Builder.CreateSIToFP(&par, f64));
    }
    Builder.SetInsertPoint(previous_insert_point);

    //Definition of int_of_float function
    auto int_of_float_type = llvm::FunctionType::get(i32, { f64 }, false);
    AST::int_of_float = llvm::Function::Create(int_of_float_type, llvm::Function::LinkageTypes::ExternalLinkage, "int_of_float", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "int_of_float_entry", AST::int_of_float );
    Builder.SetInsertPoint(function_body_BB);

    for(auto &par: AST::int_of_float->args()) {
        Builder.CreateRet(Builder.CreateFPToSI(&par, i32));
    }
    Builder.SetInsertPoint(previous_insert_point);
}

void AST::define_reference_update_functions() {
    //Definition of incr function
    auto incr_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { llvm::PointerType::get(i32, 0) }, false);
    AST::incr = llvm::Function::Create(incr_type, llvm::Function::ExternalLinkage, "incr", TheModule.get());
    
    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "incr_entry", AST::incr );
    Builder.SetInsertPoint(function_body_BB);

    //Load pointed to int, increment it and store it back
    for(auto &par: AST::incr->args()) {
        Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(&par, "value"), c32(1)), &par);
    }

    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //Definition of decr function
    auto decr_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { llvm::PointerType::get(i32, 0) }, false);
    AST::decr = llvm::Function::Create(decr_type, llvm::Function::ExternalLinkage, "decr", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "decr_entry", AST::decr );
    Builder.SetInsertPoint(function_body_BB);

    //Load pointed to int, increment it and store it back
    for(auto &par: AST::decr->args()) {
        Builder.CreateStore(Builder.CreateSub(Builder.CreateLoad(&par, "value"), c32(1)), &par);
    }

    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

}

void AST::add_library_functions() {
    std::shared_ptr<TypeVariable> from_type = nullptr;
    std::shared_ptr<TypeVariable> to_type = nullptr;

    st->scope_open();

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_int", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));
   
    //Print Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_bool", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_char", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_float", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_string", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    //Read Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("read_int", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    st->insert_entry(new FunctionEntry("read_bool", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("read_char", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("read_float", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char), 1, DimType::Exact);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("read_string", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("incr", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("decr", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    //Conversion functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_char", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("char_of_int", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("float_of_int", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_float", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("round", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    //String functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strlen", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strcmp", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcpy", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcat", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    //Math functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("abs", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("fabs", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("sqrt", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("sin", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("cos", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("tan", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("atan", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("exp", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("ln", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("pi", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    
}

void AST::bind_to_default_types() {
    for(auto type_it = AST::created_type_variables->begin(); type_it != AST::created_type_variables->end(); type_it++) {
        if((*type_it)->get_tag() == TypeTag::Unknown) {
            (*type_it)->set_tag_to_default();

            AST::error_handler->unbound_type(*type_it);
        }
    }
}