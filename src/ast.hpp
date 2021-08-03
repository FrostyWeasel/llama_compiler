#ifndef __AST_HPP__
#define __AST_HPP__

#include "enums.hpp"
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

extern int yylineno;

//TODO: In case i implement float
/*

    During codegen in binary expressions CreateFAdd(etc.) needs to be used instead of CreateAdd.
    

*/

class SemanticAnalyzer;
class ErrorHandler;
class TypeVariable;
class SymbolTable;

class AST {
public:

    AST() {
        this->lineno = yylineno;

    }
    AST(NodeType node_type) : node_type(node_type) {
        this->lineno = yylineno;

    }
    virtual ~AST() = default;
    virtual void print(std::ostream& out) const = 0;
    virtual std::shared_ptr<TypeVariable> infer() = 0;
    virtual void sem() = 0;
    virtual llvm::Value* codegen() = 0;

    virtual void llvm_compile_and_dump(bool optimizations_flag, bool intermediate_flag, bool final_flag, std::string input_filename, std::string compiler_path);

    void close_all_program_scopes();
    void unify();
    void add_library_functions();
    void close_library_function_scope();
    void clear_inference_structures();
    static void bind_to_default_types();

    virtual NodeType get_node_type() { return node_type; }

    virtual void add_to_symbol_table() { }

    virtual void allocate() { }

    virtual void make_non_local_variable_stack() { }


protected:
    static std::unique_ptr<SymbolTable> st;
    static std::unique_ptr<SemanticAnalyzer> sa;
    static std::unique_ptr<ErrorHandler> error_handler;
    NodeType node_type;

    //Every last expression in a line is seen as belonging to the next line, because flex increments the yylineno upon seeing /n and before returning the type
    unsigned int lineno;

    friend ErrorHandler;
    friend SymbolTable;

    //Map from type variable ids to nodes of the ast with that type so that we can print informative error messages for unbound variables and type errors.
    static std::unique_ptr<std::unordered_map<unsigned int, AST*>> type_variable_owners;

    //Vector of type variables to find unknown types left after inference
    static std::unique_ptr<std::vector<std::shared_ptr<TypeVariable>>> created_type_variables;

    //Used to differentiate between stages of AST pass (for example function definition)
    static PassStage pass_stage;

    //Points to similar structure of function definition to store non local variables that appear in the functions body.
    static std::map<std::string, std::shared_ptr<TypeVariable>>* current_func_def_non_locals;

    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> FPM;

    //libc is used to do the printing and reading, llama functions format the input and then give it to printf to output it and scanf to input
    static llvm::Function* printf;
    static llvm::Function* scanf;

    static llvm::Function* print_string;
    static llvm::Function* print_int;
    static llvm::Function* print_char;
    static llvm::Function* print_bool;
    static llvm::Function* print_float;

    static llvm::Function* read_string;
    static llvm::Function* read_int;
    static llvm::Function* read_char;
    static llvm::Function* read_bool;
    static llvm::Function* read_float;

    static llvm::Function* incr;
    static llvm::Function* decr;

    static llvm::Function* int_of_char;
    static llvm::Function* char_of_int;

    static llvm::Function* strcpy;
    static llvm::Function* strcmp;
    static llvm::Function* strcat;
    static llvm::Function* strlen;

    static llvm::Function* float_of_int;
    static llvm::Function* int_of_float;
    static llvm::Function* round;
    static llvm::Function* abs;
    static llvm::Function* fabs;
    static llvm::Function* sqrt;
    static llvm::Function* sin;
    static llvm::Function* cos;
    static llvm::Function* tan;
    static llvm::Function* atan;
    static llvm::Function* exp;
    static llvm::Function* ln;
    static llvm::Function* pi;

    static llvm::Type *i1;
    static llvm::Type *i8;
    static llvm::Type *i16;
    static llvm::Type *i32;
    static llvm::Type *i64;
    static llvm::Type *f16;
    static llvm::Type *f32;
    static llvm::Type *f64;

    static llvm::ConstantInt *c1(bool b)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(1, b, true));
    }
    static llvm::ConstantInt *c8(char c)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
    }
    static llvm::ConstantInt *c16(int n)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(16, n, true));
    }
    static llvm::ConstantInt *c32(int n)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
    }
    static llvm::ConstantInt *c64(long n)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(64, n, true));
    }

    static llvm::ConstantFP *cf32(float n)
    {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(n));
    }

    static llvm::ConstantFP *cf64(double n)
    {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(n));
    }

    static llvm::Type* map_to_llvm_type(std::shared_ptr<TypeVariable> type_variable);

private:
    static void map_par_list_to_llvm_type(std::shared_ptr<TypeVariable> type_variable, std::vector<llvm::Type*>& par_types);
    static void declare_library_functions();
    static void define_conversion_functions();
    static void define_reference_update_functions();
    static void define_print_functions();
    static void define_read_functions();
    static void define_pi();
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif