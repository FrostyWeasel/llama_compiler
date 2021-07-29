#include "for.hpp"
    
std::shared_ptr<TypeVariable> For::infer() {
    auto first_condition_type = this->first_condition->infer();
    auto second_condition_type = this->second_condition->infer();

    st->scope_open();

    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, std::make_shared<TypeVariable>(TypeTag::Int));
    st->insert_entry(entry);

    auto expr_type = this->expr->infer();        

    st->scope_close();
    
    st->add_constraint(first_condition_type, std::make_shared<TypeVariable>(TypeTag::Int));
    st->add_constraint(second_condition_type, std::make_shared<TypeVariable>(TypeTag::Int));
    st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Unit));

    return this->type_variable;
}

void For::sem() {
    this->first_condition->sem();
    this->second_condition->sem();

    //Only expression is in scope of iterator
    st->scope_open();

    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, std::make_shared<TypeVariable>(TypeTag::Int));
    st->insert_entry(entry);

    this->expr->sem();        

    st->scope_close();
}