#include "var_def.hpp"
    
void VarDef::print(std::ostream& out) const {
    out << "VarDef(";
    out << " Id: " << id;
    out << " TypeVariable: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << ") ";
}

void VarDef::add_to_symbol_table() {
    VariableEntry* entry = new VariableEntry(id, EntryType::ENTRY_VARIABLE, this->type_variable);
    
    st->insert_entry(entry);

    this->entry = entry;
}

void VarDef::allocate() {
    llvm::AllocaInst* alloc_ptr = nullptr;
    auto referenced_value = Builder.CreateAlloca(map_to_llvm_type(this->type_variable->get_referenced_type()), nullptr, id);
    alloc_ptr = Builder.CreateAlloca(map_to_llvm_type(this->type_variable), nullptr, id+"_ref");
    Builder.CreateStore(referenced_value, alloc_ptr);
    this->entry->set_allocation(alloc_ptr);
}

std::shared_ptr<TypeVariable> VarDef::infer() {        
    return this->type_variable;
}

void VarDef::sem() { 
        
}

llvm::Value* VarDef::codegen() {
    return this->entry->get_allocation();
}