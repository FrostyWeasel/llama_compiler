#ifndef __AST_HPP__
#define __AST_HPP__

#include "symbol_table.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include "semantic_analyzer.hpp"
#include <iostream>
#include <string>
#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

//TODO: Check types in llama panflet for more type restrictions

//TODO: In case i implement float
/*

    During codegen in binary expressions CreateFAdd(etc.) needs to be used instead of CreateAdd.
    

*/

class AST{
public:

    AST() = default;
    AST(NodeType node_type) : node_type(node_type) { }
    virtual ~AST() = default;
    virtual void print(std::ostream& out) const = 0;
    virtual std::shared_ptr<TypeVariable> infer() = 0;
    virtual void sem() = 0;
    virtual llvm::Value* codegen() { std::cout << "Unimplemented codeged!\n"; }

    //TODO: Set to true
    virtual void llvm_compile_and_dump(bool optimize=false);

    void close_all_program_scopes();
    void unify() { st->unify(); }
    void add_library_functions();
    void close_library_function_scope();
    void clear_inference_structures() { st->clear_inference_structures(); };

    virtual NodeType get_node_type() { return node_type; }

    virtual void add_to_symbol_table() { }

    virtual void allocate() { }


protected:
    static SymbolTable* st;
    static SemanticAnalyzer* sa;
    NodeType node_type;
    
    static PassStage pass_stage;

    //Points to similar structure of function definition to store non local variables that appear in the functions body.
    static std::map<std::string, std::shared_ptr<TypeVariable>>* current_func_def_non_locals;

    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> FPM;

    static llvm::Type *i1;
    static llvm::Type *i8;
    static llvm::Type *i16;
    static llvm::Type *i32;
    static llvm::Type *i64;

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
    static llvm::ConstantInt *c64(int n)
    {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(64, n, true));
    }

    static llvm::Type* map_to_llvm_type(std::shared_ptr<TypeVariable> type_variable);
    static void map_par_list_to_llvm_type(std::shared_ptr<TypeVariable> type_variable, std::vector<llvm::Type*>& par_types);
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif