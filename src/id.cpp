#include "id.hpp"

void Id::print(std::ostream& out) const {
    out << " " << id;
}

std::shared_ptr<TypeVariable> Id::infer() {
    auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
    this->entry = id_entry;

    this->type_variable = id_entry->get_type();

    return id_entry->get_type();
}

void Id::sem() {
    //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
    if(this->pass_stage == PassStage::FunctionDef) {
        auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        this->entry = entry;
        
        // If id not in the same scope as the parameters of the function
        if(entry->get_nesting_level() != this->st->get_current_nesting_level()) {
            this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
        }
    }
}

llvm::Value* Id::codegen() {
    auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
    auto allocation = id_entry->get_allocation();

    if(allocation != nullptr)
        return Builder.CreateLoad(allocation->getAllocatedType(), allocation, id);

    return nullptr;
}