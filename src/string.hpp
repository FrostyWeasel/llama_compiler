#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include "enums.hpp"
#include "expr.hpp"
#include "type_variable.hpp"
#include <vector>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

class String : public Expr{
public:
    String(std::string* value): value(*value), Expr(new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char))) {  }
    virtual void print(std::ostream& out) const override{
        out << value;
    }

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }

    virtual void sem() override { /* No need for further checks */ }

    virtual llvm::Value* codegen() {
        std::vector<llvm::Constant*> chars;

        for(char c : value) {
            chars.push_back(c8(c));
        }
        chars.push_back(c8('\0'));

        auto char_array = llvm::ArrayType::get(i8, chars.size());

        //Memory managed by the module
        auto global_string = new llvm::GlobalVariable(*TheModule.get(), char_array, true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, 
            llvm::ConstantArray::get(char_array, chars), "string");

        return llvm::GetElementPtrInst::CreateInBounds(char_array, global_string, { c32(0), c32(0) }, "string_ptr", Builder.GetInsertBlock());
    }

private:
    std::string value;    
};

#endif