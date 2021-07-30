#include "array_def.hpp"

void ArrayDef::print(std::ostream &out) const {
    out << "ArrayDef(";
    out << " Id: " << id;
    out << " Type: ";
    if (type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << " Expr_list: ";
    if (expr_list != nullptr)
        expr_list->print(out);
    else
        out << "null ";
    out << ") ";
}

void ArrayDef::add_to_symbol_table()  {
    VariableEntry* entry = new VariableEntry(id, EntryType::ENTRY_VARIABLE, this->type_variable, this->expr_list->block_size());
    
    st->insert_entry(entry);

    this->entry = entry;
}

void ArrayDef::allocate()  {
    llvm::AllocaInst* alloc_ptr = Builder.CreateAlloca(map_to_llvm_type(this->type_variable), nullptr, id+"_array");
    this->entry->set_allocation(alloc_ptr);
}

std::shared_ptr<TypeVariable> ArrayDef::infer() {
    //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
    this->expr_list->infer();

    return this->type_variable;
}

void ArrayDef::sem() {
    //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
    this->expr_list->sem();
}

// ? store array size in stack to use for index in bounds checks
llvm::Value* ArrayDef::codegen() {
    auto expr_list_vector = this->expr_list->get_list();
    llvm::Value* dim_size_ptr;
    llvm::Value* dim_size;

    llvm::Value* array_size = c32(1);

    unsigned int i = 1;
    for(auto expr_it = expr_list_vector.begin(); expr_it != expr_list_vector.end(); expr_it++) {
        dim_size_ptr = Builder.CreateStructGEP(this->entry->get_allocation(), i++, "dim_size_ptr");
        dim_size = (*expr_it)->codegen();
        Builder.CreateStore(dim_size, dim_size_ptr, "dim_size");
        array_size = Builder.CreateMul(array_size, dim_size);
    }

    //Allocate space for the array elements in the heap and store the pointer to the first element in the array struct
    auto array_ptr = Builder.CreateStructGEP(this->entry->get_allocation(), i, "array_ptr");
    auto array_alloca = Builder.CreateAlloca(map_to_llvm_type(this->type_variable->get_array_type()), array_size, "array");
    Builder.CreateStore(array_alloca, array_ptr);

    //Store the array size in the first position of the array struct
    auto array_size_pt = Builder.CreateStructGEP(this->entry->get_allocation(), 0, "array_size_ptr");
    Builder.CreateStore(array_size, array_size_pt, "array_size");

    return this->entry->get_allocation();
}