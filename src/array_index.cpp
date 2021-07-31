#include "array_index.hpp"

void ArrayIndex::print(std::ostream &out) const {
    out << "ArrayIndex( ";
    out << "Id: " << id << ", ";
    out << "Type: ";
    if (this->type_variable != nullptr)
        this->type_variable->print(out);
    else
        out << "null ";
    out << "Expr_list: ";
    if(expr_list != nullptr)
        expr_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> ArrayIndex::infer() {
    SymbolEntry* entry = st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);        

    //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
    this->expr_list->infer();

    auto array_element_type = std::make_shared<TypeVariable>();

    this->type_variable = std::make_shared<TypeVariable>(TypeTag::Reference, array_element_type);

    st->add_constraint(entry->get_type(), std::make_shared<TypeVariable>(TypeTag::Array,
        array_element_type, this->expr_list->block_size(), DimType::Exact));

    return this->type_variable;
}

void ArrayIndex::sem() {

    //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
    if(this->pass_stage == PassStage::FunctionDef) {
        auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        
        // If id not in the same scope as the parameters of the function
        if(entry->get_nesting_level() != this->st->get_current_nesting_level()) {
            this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
        }
    }   

    //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
    this->expr_list->sem();
}

// ? the first element of the array type holds the total size and could be used to implement out-of-bounds checking
llvm::Value* ArrayIndex::codegen() {
    //example: let mutable a[5, 3, 2] -> a[2, 1, 0] => access array at offset: 2*(3*2) + 1*(2) + 0
    SymbolEntry* entry = st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);

    auto dim_count = entry->get_type()->get_array_dim();

    //Get all the array dimension size values
    std::vector<llvm::Value*> dim_sizes;
    llvm::Value* dim_size_ptr;
    for (auto i = 1; i <= dim_count; i++) {
        dim_size_ptr = Builder.CreateStructGEP(entry->get_allocation(), i, "dim_size_ptr");
        dim_sizes.push_back(Builder.CreateLoad(dim_size_ptr, "dim_size"));
    }
    
    //Calculate the total size of lower array dimensions
    //example: let mutable a[5, 3, 2] -> partial_dim_size_mults = { 2, 3*2, 3*2*5 <-useless }
    std::vector<llvm::Value*> partial_dim_size_mults;
    partial_dim_size_mults.push_back(dim_sizes[dim_sizes.size() - 1]);
    for(auto dim_size_it = ++dim_sizes.rbegin(); dim_size_it != dim_sizes.rend(); dim_size_it++) {
        partial_dim_size_mults.push_back(Builder.CreateMul(partial_dim_size_mults[partial_dim_size_mults.size() - 1], *dim_size_it));
    }
    
    auto expr_list_vector = this->expr_list->get_list();
    auto index = expr_list_vector[0]->codegen();
    auto partial_dim_size_mults_it = ++partial_dim_size_mults.rbegin(); //last entry is useless
    
    llvm::Value* offset = nullptr;
    if(partial_dim_size_mults_it != partial_dim_size_mults.rend()) {
        offset = Builder.CreateMul(index, *partial_dim_size_mults_it);
        partial_dim_size_mults_it++;
    }
    else
        offset = index;
    
    
    for(auto expr_it = ++expr_list_vector.begin(); expr_it != expr_list_vector.end(); expr_it++) {
        if(partial_dim_size_mults_it != partial_dim_size_mults.rend()) {
            index = Builder.CreateMul((*expr_it)->codegen(), *partial_dim_size_mults_it);
            offset = Builder.CreateAdd(offset, index);
            partial_dim_size_mults_it++;
        }
        else
            offset = Builder.CreateAdd(offset, (*expr_it)->codegen());
    }
    
    auto array_data_ptr = Builder.CreateLoad(Builder.CreateStructGEP(entry->get_allocation(), dim_count + 1), "array_data_ptr");

    return Builder.CreateGEP(array_data_ptr, { offset }, "array_element_ptr");
}