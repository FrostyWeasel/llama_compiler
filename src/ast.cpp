#include "ast.hpp"
#include "function_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include "semantic_analyzer.hpp"
#include "ref_type.hpp"
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>
#include <iostream>

SymbolTable* AST::st = new SymbolTable(20000);
SemanticAnalyzer* AST::sa = new SemanticAnalyzer();
PassStage AST::pass_stage = PassStage::Other;
std::map<std::string, std::shared_ptr<TypeVariable>>* AST::current_func_def_non_locals = nullptr;


llvm::LLVMContext AST::TheContext;
llvm::IRBuilder<> AST::Builder(TheContext);
std::unique_ptr<llvm::Module> AST::TheModule;
std::unique_ptr<llvm::legacy::FunctionPassManager> AST::FPM;

llvm::Type *AST::i1 = llvm::IntegerType::get(TheContext, 1);
llvm::Type *AST::i8 = llvm::IntegerType::get(TheContext, 8);
llvm::Type *AST::i16 = llvm::IntegerType::get(TheContext, 16);
llvm::Type *AST::i32 = llvm::IntegerType::get(TheContext, 32);
llvm::Type *AST::i64 = llvm::IntegerType::get(TheContext, 64);

void AST::close_library_function_scope() {
    st->scope_close();
    delete AST::sa;
    delete AST::st;
}

void AST::close_all_program_scopes() {
    st->close_all_program_scopes();
}

llvm::Type* AST::map_to_llvm_type(std::shared_ptr<TypeVariable> type_variable) {
    switch (type_variable->get_tag()) {
        case TypeTag::Int:
            return AST::i32;
        break;
        case TypeTag::Bool:
            return AST::i1;
        break;
        case TypeTag::Char:
            return AST::i8;
        break;
        case TypeTag::Unit:
            return llvm::Type::getVoidTy(TheContext);
        break;
        case TypeTag::Unknown:
            return llvm::Type::getVoidTy(TheContext);
        break;
        case TypeTag::Function:{
            llvm::Type* return_type;
            if((type_variable->get_function_to_type()->get_tag() != TypeTag::Unit) && (type_variable->get_function_to_type()->get_tag() != TypeTag::Unknown))
                return_type = map_to_llvm_type(type_variable->get_function_to_type());
            else
                return_type = llvm::Type::getVoidTy(TheContext);
            std::vector<llvm::Type*> par_types;
            map_par_list_to_llvm_type(type_variable->get_function_from_type(), par_types);

            //Pointer to non local variable struct.
            par_types.push_back(llvm::PointerType::get(i32, 0));

            return llvm::PointerType::get(llvm::FunctionType::get(return_type, par_types, false), 0);
        }
        break;
        case TypeTag::Reference: {
            auto ref_ptr = type_variable->get_referenced_type();
            auto referenced_llvm_type = map_to_llvm_type(ref_ptr);

            return llvm::PointerType::get(referenced_llvm_type, 0);
        }
        case TypeTag::Array: {
            std::vector<llvm::Type*> array_type;
            for(auto i = 0; i < type_variable->get_array_dim(); i++) {
                array_type.push_back(i32);
            }
            array_type.push_back(llvm::PointerType::get(map_to_llvm_type(type_variable->get_array_type()),0));

            return llvm::StructType::get(TheContext, array_type);
        }
        break;
        default:
            std::cerr << "Uknown type\n";
            exit(1); //TODO: Error handling
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

    // from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    // to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    // st->insert_entry(new FunctionEntry("print_float", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

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

    // from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    // to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    // st->insert_entry(new FunctionEntry("read_float", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
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

    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_char", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("char_of_int", EntryType::ENTRY_FUNCTION, from_type, to_type, 1));

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
    
}