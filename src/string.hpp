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

    //TODO: Change to match all other arrays
    virtual llvm::Value* codegen() {
        llvm::StructType* array_type;
        std::vector<llvm::Constant*> array_data;
        llvm::ArrayType* data_type;
        std::vector<llvm::Constant*> data;

        //Array of char: [dim1, first_elmnt_ptr]
        array_type = llvm::StructType::get(TheContext, { i32, i32, llvm::PointerType::get(i8,0) }); 
        
        //Array of char elements are of type i8, optimization for string because its values are already known
        data_type = llvm::ArrayType::get(i8, value.size() + 1); 

        for(char c : value) {
            data.push_back(c8(c));
        }
        data.push_back(c8('\0'));

        auto array_data_ptr = Builder.CreateAlloca(data_type, nullptr, "string_data");
        Builder.CreateStore(llvm::ConstantArray::get(data_type, data), array_data_ptr);

        //To be compatible with array_type
        auto first_element = Builder.CreateBitCast(array_data_ptr, llvm::PointerType::get(i8, 0));
        auto first_element_ptr = Builder.CreateGEP(i8, first_element, { c32(0) }, "first_element_ptr");
                
        auto array_ptr = Builder.CreateAlloca(array_type, nullptr, "array_struct");
        auto array_type_size_ptr = Builder.CreateStructGEP(array_ptr, 0, "string_size");
        auto array_type_dim_ptr = Builder.CreateStructGEP(array_ptr, 1, "dim_size");
        auto array_type_array_ptr = Builder.CreateStructGEP(array_ptr, 2, "string_data_ptr");

        Builder.CreateStore(c32(data.size()), array_type_size_ptr);
        Builder.CreateStore(c32(data.size()), array_type_dim_ptr);
        Builder.CreateStore(first_element_ptr, array_type_array_ptr);

        return Builder.CreateLoad(array_ptr, "array_struct");
    }

private:
    std::string value;    
};

#endif