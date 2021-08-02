#include "dim.hpp"
#include "variable_entry.hpp"
#include "type_variable.hpp"
#include "symbol_entry.hpp"
#include "symbol_table.hpp"

void Dim::print(std::ostream &out) const {
    out << " dim " << dimension << " " << id;
}

std::shared_ptr<TypeVariable> Dim::infer() {
    this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

    SymbolEntry* entry = st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);

    st->add_constraint(entry->get_type(), std::make_shared<TypeVariable>(TypeTag::Array,
        std::make_shared<TypeVariable>(TypeTag::Unknown), this->dimension, DimType::AtLeast), this->lineno);

    return this->type_variable;
}

void Dim::sem() {
    if(this->dimension < 1) {
        std::cerr << "Array dimensions are indexed starting from 1";
        exit(1);
    }   

    //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
    if(this->pass_stage == PassStage::FunctionDef) {
        auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        
        // If id not in the same scope as the parameters of the function
        if(entry->get_nesting_level() != this->st->get_current_nesting_level()) {
            this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
        }
    }
}

llvm::Value* Dim::codegen() {
    auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
    auto array_alloc = entry->get_allocation();

    //First position of array struct holds the total size of the array
    auto dim_size = Builder.CreateStructGEP(array_alloc, this->dimension, "dim_size_ptr");

    return Builder.CreateLoad(dim_size, this->id+"_dim_size_"+std::to_string(this->dimension));
}