#include "string.hpp"
#include "type_variable.hpp"
#include <string>
#include <iostream>
    
String::String(std::string* value): value(*value), Expr(new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char))) {  }

void String::print(std::ostream& out) const {
    out << value;
}

std::shared_ptr<TypeVariable> String::infer() { 
    return this->type_variable;
}

void String::sem() { /* No need for further checks */ }

llvm::Value* String::codegen() {
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

    auto array_data_heap_ptr = Builder.CreateCall(AST::malloc_function, { c32(TheDataLayout->getTypeAllocSize(data_type).getValue()) }, "array_data_heap_ptr");
    auto array_data_ptr = Builder.CreateBitCast(array_data_heap_ptr, llvm::PointerType::get(data_type, 0), "array_data");
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