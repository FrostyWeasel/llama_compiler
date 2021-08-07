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
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

//TODO: All values passed as pointers to allocas must have the allocas replaced with heap allocation because allocas are local and if the def has been done in a function then they are deallocated upon the function return
/*
    !This should happen to:
        1.The new expression (the delete expr should clean the heap)
        2.Mutable variables and array elements
        3.User type constructor structs
        4.(Functions would be necessary if we could return them from functions but now they are not?)
*/

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
std::unique_ptr<llvm::DataLayout> AST::TheDataLayout;

llvm::Function* AST::runtime_error_function;

llvm::Function* AST::printf_function;
llvm::Function* AST::scanf_function;
llvm::Function* AST::exit_function;
llvm::Function* AST::malloc_function;
llvm::Function* AST::free_function;

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
        case TypeTag::UserType:
            //Pointer to constructor struct
            return llvm::PointerType::get(i8, 0);
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

void AST::llvm_compile_and_dump(bool optimizations_flag, bool intermediate_flag, bool final_flag, std::string input_filename, std::string compiler_path) {
    // Initialize
    TheModule = std::make_unique<llvm::Module>("Llama program", TheContext);

    //Initialize Data layout
    TheDataLayout = std::make_unique<llvm::DataLayout>(TheModule.get());
   
    FPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
    if(optimizations_flag) {
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

    if(intermediate_flag) {
        //Print out the IR.
        TheModule->print(llvm::outs(), nullptr);
        return;
    }

    if(final_flag) {
        //Print out the final code.
        auto output_error =  std::error_code();
        auto output_ir_file = std::make_unique<llvm::raw_fd_ostream>("a.imm", output_error);

        TheModule->print(*output_ir_file, nullptr);

        std::string compile_to_assembly = "llc-12 -o a.asm a.imm";
        std::system(compile_to_assembly.c_str());

        std::ifstream input_asm_file_stream;
        input_asm_file_stream.open("a.s");
        std::stringstream buffer;

        buffer << input_asm_file_stream.rdbuf();
        std::cout << buffer.str() << std::endl;

        return;
    }
    else {
        //Compile and store executable in ./a.out
        std::ifstream input_source_file_stream;
        input_source_file_stream.open(input_filename);

        if(input_filename.empty() || input_filename == " ")
            input_filename = "a";

        std::string ir_file_name = input_filename + ".imm";
        std::string asm_file_name = input_filename + ".asm";
        std::string exec_file_name = input_filename + ".out";

        auto output_error =  std::error_code();
        auto output_ir_file = std::make_unique<llvm::raw_fd_ostream>(ir_file_name.c_str(), output_error);

        TheModule->print(*output_ir_file, nullptr);
        
        std::stringstream compile_to_assembly;
        compile_to_assembly << "llc-12 -o " << asm_file_name << " " << ir_file_name;
        std::cout << compile_to_assembly.str() << "\n";
        std::system(compile_to_assembly.str().c_str());

        std::stringstream compile_to_object_code;
        compile_to_object_code << "clang++ -O3 -o " << exec_file_name << " " << asm_file_name;
        std::cout << compile_to_object_code.str() << "\n";
        std::system(compile_to_object_code.str().c_str());
    }
}

void AST::declare_library_functions() {
    //libc functions
    auto printf_type = llvm::FunctionType::get(i32, { llvm::PointerType::get(i8, 0) }, true);
    AST::printf_function = llvm::Function::Create(printf_type, llvm::Function::LinkageTypes::ExternalLinkage, "printf", TheModule.get());

    auto scanf_type = llvm::FunctionType::get(i32, { llvm::PointerType::get(i8, 0) }, true);
    AST::scanf_function = llvm::Function::Create(scanf_type, llvm::Function::LinkageTypes::ExternalLinkage, "scanf", TheModule.get());

    auto exit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), { i32 }, false);
    AST::exit_function = llvm::Function::Create(exit_type, llvm::Function::LinkageTypes::ExternalLinkage, "exit", TheModule.get());

    auto malloc_type = llvm::FunctionType::get(llvm::PointerType::get(i8, 0), { i32 }, false);
    AST::malloc_function = llvm::Function::Create(malloc_type, llvm::Function::LinkageTypes::ExternalLinkage, "malloc", TheModule.get());

    auto free_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), { llvm::PointerType::get(i8, 0) }, false);
    AST::free_function = llvm::Function::Create(free_type, llvm::Function::LinkageTypes::ExternalLinkage, "free", TheModule.get());

    //Runtime library functions
    define_runtime_library_functions();

    //Print Functions
    define_print_functions();

    //Read Functions
    define_read_functions();

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

    define_pi();

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

void AST::define_runtime_library_functions() {
    auto runtime_error_function_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { llvm::PointerType::get(i8, 0) }, false);
    AST::runtime_error_function = llvm::Function::Create(runtime_error_function_type, llvm::Function::LinkageTypes::ExternalLinkage, "__runtime_error", TheModule.get());

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "__runtime_error_entry", AST::runtime_error_function );
    Builder.SetInsertPoint(function_body_BB);

    auto format_string = Builder.CreateGlobalStringPtr("%s");

    for(auto &par: AST::runtime_error_function->args()) {
        Builder.CreateCall(AST::printf_function, { format_string, &par });
    }

    Builder.CreateCall(AST::exit_function, { c32(1) });

    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);
}

void AST::define_pi() {
    auto pi_type = llvm::FunctionType::get(f64, { }, false);
    AST::pi = llvm::Function::Create(pi_type, llvm::Function::LinkageTypes::ExternalLinkage, "pi", TheModule.get());

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "pi_entry", AST::pi );
    Builder.SetInsertPoint(function_body_BB);

    Builder.CreateRet(cf64(M_PIf64));
    Builder.SetInsertPoint(previous_insert_point);
}

void AST::define_read_functions() {
    //Reads characters into array until array is full or \n is encountered.
    {
        auto read_string_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), {  i32, llvm::PointerType::get(AST::i8, 0) }, false);
        AST::read_string = llvm::Function::Create(read_string_type, llvm::Function::ExternalLinkage, "read_string", TheModule.get());

        auto previous_insert_point = Builder.GetInsertBlock();
        auto function_body_BB = llvm::BasicBlock::Create(TheContext, "read_string_entry", AST::read_string );
        Builder.SetInsertPoint(function_body_BB);

        auto array_size_par = AST::read_string->getArg(0);
        auto array_elements_ptr = AST::read_string->getArg(1);

        auto format_string = Builder.CreateGlobalStringPtr("%c");
        auto input_character_alloca = Builder.CreateAlloca(i8, nullptr, "input_character_alloca");

        //Get initial value of iterator variable
        auto start_value = c32(0);

        auto current_function = Builder.GetInsertBlock()->getParent();

        //Current BB
        auto header_BB = Builder.GetInsertBlock();

        //Create BB for the loop
        auto loop_start_BB = llvm::BasicBlock::Create(TheContext, "loop_start", current_function);
        auto loop_body_BB = llvm::BasicBlock::Create(TheContext, "loop_body");
        auto loop_body_store_input_BB = llvm::BasicBlock::Create(TheContext, "loop_body_store_input_BB");
        auto loop_end_BB = llvm::BasicBlock::Create(TheContext, "loop_end");
        auto function_end_BB = llvm::BasicBlock::Create(TheContext, "function_end");

        auto iterator_alloca = Builder.CreateAlloca(i32, nullptr, "iterator_alloca");

        //Go to function end immediately in the spacial case that array size is zero
        auto array_size_zero_check = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, array_size_par, c32(0), "array_size_zero_check");
        Builder.CreateCondBr(array_size_zero_check, function_end_BB, loop_start_BB);

        //Enter the loop
        Builder.SetInsertPoint(loop_start_BB);

        auto phi_node = Builder.CreatePHI(i32, 2, "iterator");
        phi_node->addIncoming(start_value, header_BB);
        Builder.CreateStore(phi_node, iterator_alloca);

        //array_size_check = (iterator == array_size - 1 ) ? 1 : 0
        auto array_size_check = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, phi_node, Builder.CreateSub(array_size_par, c32(1)), "array_size_check");

        Builder.CreateCondBr(array_size_check, loop_end_BB, loop_body_BB);

        //Start loop body BB
        current_function->getBasicBlockList().push_back(loop_body_BB);
        Builder.SetInsertPoint(loop_body_BB);

        //Read a character from stdin
        Builder.CreateCall(AST::scanf_function, { format_string, input_character_alloca });
        auto input_char = Builder.CreateLoad(input_character_alloca, "input_char");

        //Check if character is '\n'
        //read_new_line_check = (input_character == '\n') ? 1 : 0
        auto read_new_line_check = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, input_char, c8('\n'), "read_new_line_check");

        Builder.CreateCondBr(read_new_line_check, loop_end_BB, loop_body_store_input_BB);

        //Start loop body store input BB
        current_function->getBasicBlockList().push_back(loop_body_store_input_BB);
        Builder.SetInsertPoint(loop_body_store_input_BB);

        //Store character just read in array
        auto input_destination_ptr = Builder.CreateGEP(array_elements_ptr, phi_node, "input_destination_ptr");
        Builder.CreateStore(input_char, input_destination_ptr);

        auto next_value = Builder.CreateAdd(phi_node, c32(1), "increment_iterator");
        loop_body_BB = Builder.GetInsertBlock();
        phi_node->addIncoming(next_value, loop_body_BB);
        Builder.CreateBr(loop_start_BB);

        //end of loop
        current_function->getBasicBlockList().push_back(loop_end_BB);
        Builder.SetInsertPoint(loop_end_BB);

        //Put '\0' at end of array
        auto null_termination_destination_ptr = Builder.CreateGEP(array_elements_ptr, Builder.CreateLoad(iterator_alloca), "null_termination_destination_ptr");
        Builder.CreateStore(c8('\0'), null_termination_destination_ptr);    

        Builder.CreateBr(function_end_BB);

        current_function->getBasicBlockList().push_back(function_end_BB);
        Builder.SetInsertPoint(function_end_BB);

        Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
        Builder.SetInsertPoint(previous_insert_point);
    }

    //*
    {
        auto read_int_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Int)), {  }, false);
        AST::read_int = llvm::Function::Create(read_int_type, llvm::Function::ExternalLinkage, "read_int", TheModule.get());

        auto previous_insert_point = Builder.GetInsertBlock();
        auto function_body_BB = llvm::BasicBlock::Create(TheContext, "read_int_entry", AST::read_int );
        Builder.SetInsertPoint(function_body_BB);

        auto format_string = Builder.CreateGlobalStringPtr("%i");
        auto return_value_ptr = Builder.CreateAlloca(i32, nullptr, "input_integer_ptr");

        Builder.CreateCall(AST::scanf_function, { format_string, return_value_ptr });

        Builder.CreateRet(Builder.CreateLoad(return_value_ptr));
        Builder.SetInsertPoint(previous_insert_point);
    }
    //*
    {    
        auto read_char_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Char)), {  }, false);
        AST::read_char = llvm::Function::Create(read_char_type, llvm::Function::ExternalLinkage, "read_char", TheModule.get());

        auto previous_insert_point = Builder.GetInsertBlock();
        auto function_body_BB = llvm::BasicBlock::Create(TheContext, "read_char_entry", AST::read_char );
        Builder.SetInsertPoint(function_body_BB);

        auto format_string = Builder.CreateGlobalStringPtr("%c");
        auto return_value_ptr = Builder.CreateAlloca(i8, nullptr, "input_character_ptr");

        Builder.CreateCall(AST::scanf_function, { format_string, return_value_ptr });

        Builder.CreateRet(Builder.CreateLoad(return_value_ptr));
        Builder.SetInsertPoint(previous_insert_point);
    }

    //*
    {
        //Return 1 if first character of input is t (for true) was read and 0 otherwise
        auto read_bool_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Bool)), {  }, false);
        AST::read_bool = llvm::Function::Create(read_bool_type, llvm::Function::ExternalLinkage, "read_bool", TheModule.get());

        auto previous_insert_point = Builder.GetInsertBlock();
        auto function_body_BB = llvm::BasicBlock::Create(TheContext, "read_bool_entry", AST::read_bool );
        Builder.SetInsertPoint(function_body_BB);

        auto format_string = Builder.CreateGlobalStringPtr("%s");
        auto return_value_ptr = Builder.CreateAlloca(i8, c32(10), "input_boolean_ptr");

        Builder.CreateCall(AST::scanf_function, { format_string, return_value_ptr });

        auto first_character_of_input_ptr = Builder.CreateGEP(return_value_ptr, c32(0), "first_character_of_inpu_ptr");
        auto condition_result = Builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, Builder.CreateLoad(first_character_of_input_ptr), c8('t')); 

        auto current_fuction = Builder.GetInsertBlock()->getParent();
        auto then_BB = llvm::BasicBlock::Create(TheContext, "then", current_fuction);
        auto else_BB = llvm::BasicBlock::Create(TheContext, "else");
        auto if_end_BB = llvm::BasicBlock::Create(TheContext, "endif");

        Builder.CreateCondBr(condition_result, then_BB, else_BB);

        //Generate code for the then clause
        Builder.SetInsertPoint(then_BB);
        auto then_value = c1(true);
        Builder.CreateBr(if_end_BB);
        //Codegen for the then block can change the basic block but it is needed for the phi expression
        then_BB = Builder.GetInsertBlock();

        //A bunch of new basic blocks could have been inserted by the then expression above, now we also add the else BB after them
        current_fuction->getBasicBlockList().push_back(else_BB);
        Builder.SetInsertPoint(else_BB);

        //Generate code for the else clause
        Builder.SetInsertPoint(else_BB);
        auto else_value = c1(false);
        Builder.CreateBr(if_end_BB);
        else_BB = Builder.GetInsertBlock();

        current_fuction->getBasicBlockList().push_back(if_end_BB);
        Builder.SetInsertPoint(if_end_BB);

        auto phi_node = Builder.CreatePHI(i1, 2, "iftmp");
        phi_node->addIncoming(then_value, then_BB);
        phi_node->addIncoming(else_value, else_BB);

        Builder.CreateRet(phi_node);
        Builder.SetInsertPoint(previous_insert_point);
    }
    //*
    {
        auto read_float_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Float)), {  }, false);
        AST::read_float = llvm::Function::Create(read_float_type, llvm::Function::ExternalLinkage, "read_float", TheModule.get());

        auto previous_insert_point = Builder.GetInsertBlock();
        auto function_body_BB = llvm::BasicBlock::Create(TheContext, "read_float_entry", AST::read_float );
        Builder.SetInsertPoint(function_body_BB);

        auto format_string = Builder.CreateGlobalStringPtr("%lf");
        auto return_value_ptr = Builder.CreateAlloca(f64, nullptr, "input_float_ptr");

        Builder.CreateCall(AST::scanf_function, { format_string, return_value_ptr });

        Builder.CreateRet(Builder.CreateLoad(return_value_ptr));
        Builder.SetInsertPoint(previous_insert_point);
    }
}

void AST::define_print_functions() {
    auto print_string_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), {llvm::PointerType::get(AST::i8, 0)}, false);
    AST::print_string = llvm::Function::Create(print_string_type, llvm::Function::ExternalLinkage, "print_string", TheModule.get());

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "print_string_entry", AST::print_string );
    Builder.SetInsertPoint(function_body_BB);

    auto format_string = Builder.CreateGlobalStringPtr("%s");

    for(auto &par: AST::print_string->args()) {
        Builder.CreateCall(AST::printf_function, { format_string, &par });
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
        Builder.CreateCall(AST::printf_function, { format_string, &par });
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
        Builder.CreateCall(AST::printf_function, { format_string, &par });
    }
    Builder.CreateRet(llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { }));
    Builder.SetInsertPoint(previous_insert_point);

    //*
    //Print false if boolean is 0 and true otherwise 
    auto print_bool_type = llvm::FunctionType::get(map_to_llvm_type(std::make_shared<TypeVariable>(TypeTag::Unit)), { AST::i1 }, false);
    AST::print_bool = llvm::Function::Create(print_bool_type, llvm::Function::ExternalLinkage, "print_bool", TheModule.get());

    previous_insert_point = Builder.GetInsertBlock();
    function_body_BB = llvm::BasicBlock::Create(TheContext, "print_bool_entry", AST::print_bool );
    Builder.SetInsertPoint(function_body_BB);

    format_string = Builder.CreateGlobalStringPtr("%s");

    auto par = AST::print_bool->getArg(0);

    auto current_fuction = Builder.GetInsertBlock()->getParent();
    auto then_BB = llvm::BasicBlock::Create(TheContext, "then", current_fuction);
    auto else_BB = llvm::BasicBlock::Create(TheContext, "else");
    auto if_end_BB = llvm::BasicBlock::Create(TheContext, "endif");

    Builder.CreateCondBr(par, then_BB, else_BB);

    //Generate code for the then clause
    Builder.SetInsertPoint(then_BB);
    auto then_value = Builder.CreateGlobalStringPtr("true");
    Builder.CreateBr(if_end_BB);
    //Codegen for the then block can change the basic block but it is needed for the phi expression
    then_BB = Builder.GetInsertBlock();

    //A bunch of new basic blocks could have been inserted by the then expression above, now we also add the else BB after them
    current_fuction->getBasicBlockList().push_back(else_BB);
    Builder.SetInsertPoint(else_BB);

    //Generate code for the else clause
    Builder.SetInsertPoint(else_BB);
    auto else_value = Builder.CreateGlobalStringPtr("false");
    Builder.CreateBr(if_end_BB);
    else_BB = Builder.GetInsertBlock();

    current_fuction->getBasicBlockList().push_back(if_end_BB);
    Builder.SetInsertPoint(if_end_BB);

    auto phi_node = Builder.CreatePHI(llvm::PointerType::get(i8, 0), 2, "iftmp");
    phi_node->addIncoming(then_value, then_BB);
    phi_node->addIncoming(else_value, else_BB);

    Builder.CreateCall(AST::printf_function, { format_string, phi_node });

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
        Builder.CreateCall(AST::printf_function, { format_string, &par });
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

    unsigned int function_count = 0;

    st->scope_open();

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_int", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));
   
    //Print Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_bool", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_char", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_float", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("print_string", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    //Read Functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("read_int", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Bool);
    st->insert_entry(new FunctionEntry("read_bool", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("read_char", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("read_float", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char), 1, DimType::Exact);
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("read_string", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("incr", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Reference, 
        std::make_shared<TypeVariable>(TypeTag::Int));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("decr", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    //Conversion functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Char);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_char", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Char);
    st->insert_entry(new FunctionEntry("char_of_int", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("float_of_int", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("int_of_float", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("round", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    //String functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Array, 
        std::make_shared<TypeVariable>(TypeTag::Char));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strlen", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("strcmp", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcpy", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Function, 
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)),
        std::make_shared<TypeVariable>(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char)));
    to_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    st->insert_entry(new FunctionEntry("strcat", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    //Math functions
    from_type = std::make_shared<TypeVariable>(TypeTag::Int);
    to_type = std::make_shared<TypeVariable>(TypeTag::Int);
    st->insert_entry(new FunctionEntry("abs", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("fabs", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("sqrt", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("sin", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("cos", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("tan", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("atan", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("exp", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Float);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("ln", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    from_type = std::make_shared<TypeVariable>(TypeTag::Unit);
    to_type = std::make_shared<TypeVariable>(TypeTag::Float);
    st->insert_entry(new FunctionEntry("pi", EntryType::ENTRY_FUNCTION, function_count++, from_type, to_type, 1));

    
}

void AST::bind_to_default_types() {
    for(auto type_it = AST::created_type_variables->begin(); type_it != AST::created_type_variables->end(); type_it++) {
        if((*type_it)->get_tag() == TypeTag::Unknown) {
            (*type_it)->set_tag_to_default();

            AST::error_handler->unbound_type(*type_it);
        }
    }
}