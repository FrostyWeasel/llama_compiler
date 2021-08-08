#include "symbol_table.hpp"
#include "function_type.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "expr.hpp"
#include "par.hpp"
#include "def.hpp"
#include "ast.hpp"
#include "constraint.hpp"
#include "error_handler.hpp"
#include "symbol_entry.hpp"
#include <memory>

std::unique_ptr<ErrorHandler> SymbolTable::error_handler = std::make_unique<ErrorHandler>();

SymbolTable::SymbolTable(unsigned int size) : hashtable_size(size), current_scope(nullptr) {
    hashtable = new SymbolEntry*[size];

    for(unsigned int i = 0; i < size; i++) {
        hashtable[i] = nullptr;
    }
}

SymbolTable::~SymbolTable() {
    for(unsigned int i = 0; i < hashtable_size; i++) {
        auto entry = hashtable[i];
        if(entry != nullptr)
            delete entry;
    }
    delete[] hashtable;
    delete current_scope;
}

void SymbolTable::scope_open() {
    this->current_scope = new Scope(this->current_scope, nullptr, 
        this->current_scope != nullptr ? this->current_scope->get_nesting_level() + 1 : 1, false);
}

void SymbolTable::scope_close() {
    auto current_scope = this->current_scope;

    if(this->current_scope == nullptr) {
        error_handler->print_error("Can't close null Scope\n", ErrorType::Internal);
    }

    for(auto entry = current_scope->get_entries(); entry != nullptr; entry = entry->get_next_in_scope()){
        hashtable[entry->get_hash_value()] = entry->get_next_hash();
        delete entry;
    }

    this->current_scope = current_scope->get_parent();

    delete current_scope;
}

void SymbolTable::close_all_program_scopes() {
    if(this->current_scope != nullptr) {
        while(this->current_scope->get_nesting_level() > 1) {
            this->scope_close();
        }
    }
}

void SymbolTable::clear_inference_structures() {
    this->contraints.clear();
    this->contraints.shrink_to_fit();
    this->bound_types.clear();
    this->bound_types.shrink_to_fit();
    this->substitutions.clear();
}

void SymbolTable::scope_hide(Scope* scope, bool flag) {
    if(scope == nullptr)
        error_handler->print_error("Attempting to hide current scope but there is no open scope\n", ErrorType::Internal);

    scope->set_is_hidden(flag);
}

void SymbolTable::scope_hide(bool flag) {
    if(this->current_scope == nullptr)
        error_handler->print_error("Attempting to hide current scope but there is no open scope\n", ErrorType::Internal);

    this->current_scope->set_is_hidden(flag);
}

void SymbolTable::insert_entry(SymbolEntry* entry){
    //Check if entry already in table
    for(auto e = this->current_scope->get_entries(); e != nullptr; e = e->get_next_in_scope()){
        if(e->get_id() == entry->get_id()){
            error_handler->redefining_variable(e->get_id());
        }
    }

    //Add entry to table
    unsigned int hash_value = PJW_hash(entry->get_id()) % hashtable_size;
    entry->set_hash_value(hash_value);

    entry->set_nesting_level(this->current_scope->get_nesting_level());
    entry->set_scope(this->current_scope);

    entry->set_next_hash(this->hashtable[hash_value]);
    this->hashtable[hash_value] = entry;     //Set current entry as first with this hash value so that its id is the first to be found on lookup from now on.
    entry->set_next_in_scope(this->current_scope->get_entries());
    this->current_scope->set_entries(entry);     //Set current entry as first with this scope so that its id is the first to be found on lookup from now on.

}

SymbolEntry* SymbolTable::lookup_entry(std::string id, LookupType lookup_type) {
    unsigned int hash_value = PJW_hash(id) % hashtable_size;
    SymbolEntry* entry = hashtable[hash_value];

    switch(lookup_type) {
        case LookupType::LOOKUP_CURRENT_SCOPE:
            while (entry != nullptr && entry->get_nesting_level() == this->current_scope->get_nesting_level()) {
                if(entry->get_id() == id)
                    return entry;
                else
                    entry = entry->get_next_hash();
            }
            break;
        case LookupType::LOOKUP_ALL_SCOPES:
            while (entry != nullptr) {
                if(entry->get_id() == id && !entry->get_scope()->get_hidden())
                    return entry;
                else
                    entry = entry->get_next_hash();
            }           
            break;
    }

    error_handler->out_of_scope(id);

    return nullptr;
}

SymbolEntry* SymbolTable::lookup_entry_of_type(std::string id, EntryType entry_type) {
    unsigned int hash_value = PJW_hash(id) % hashtable_size;
    SymbolEntry* entry = hashtable[hash_value];

    while (entry != nullptr) {
        if((entry->get_id() == id) && (!entry->get_scope()->get_hidden()) && (entry->get_entry_type() == entry_type))
            return entry;
        else
            entry = entry->get_next_hash();
    }           

    error_handler->out_of_scope(id);

    return nullptr;
}

bool SymbolTable::contains(std::string id, LookupType lookup_type) {
    unsigned int hash_value = PJW_hash(id) % hashtable_size;
    SymbolEntry* entry = hashtable[hash_value];

    switch(lookup_type) {
        case LookupType::LOOKUP_CURRENT_SCOPE:
            while (entry != nullptr && entry->get_nesting_level() == this->current_scope->get_nesting_level()) {
                if(entry->get_id() == id)
                    return true;
                else
                    entry = entry->get_next_hash();
            }
            break;
        case LookupType::LOOKUP_ALL_SCOPES:
            while (entry != nullptr) {
                if(entry->get_id() == id && !entry->get_scope()->get_hidden())
                    return true;
                else
                    entry = entry->get_next_hash();
            }           
            break;
    }

    return false;
}

typedef unsigned long int HashType;
unsigned int SymbolTable::PJW_hash(std::string id) {
    /*
     *  P.J. Weinberger's hashing function. See also:
     *  Aho A.V., Sethi R. & Ullman J.D, "Compilers: Principles,
     *  Techniques and Tools", Addison Wesley, 1986, pp. 433-437.
     */

    const char* key = id.c_str(); 
    const HashType PJW_OVERFLOW =
        (((HashType) 0xf) << (8 * sizeof(HashType) - 4));
    const int PJW_SHIFT = (8 * (sizeof(HashType) - 1));
    
    HashType h, g;
    
    for (h = 0; *key != '\0'; key++) {
        h = (h << 4) + (*key);
        if ((g = h & PJW_OVERFLOW) != 0) {
            h ^= g >> PJW_SHIFT;
            h ^= g;
        }
    }
    return h;
}

void SymbolTable::unify() {
    bool matched_rule;

    while(!this->contraints.empty()) {
        matched_rule = false;

        Constraint constraint = this->contraints[this->contraints.size()-1].first;
        unsigned int lineno = this->contraints[this->contraints.size()-1].second;
        this->contraints.pop_back();

        std::shared_ptr<TypeVariable> t1 = constraint.get_t1();
        std::shared_ptr<TypeVariable> t2 = constraint.get_t2();

        t1 = this->find_substitute(t1);
        t2 = this->find_substitute(t2);

        if(t1 == t2)
            matched_rule = true;

        if(!matched_rule && ((t1->get_tag() == TypeTag::UserType) && (t2->get_tag() == TypeTag::UserType))) {

            if(TypeVariable::are_user_types_the_same(t1, t2)) {
                matched_rule = true;
            }
            else {
                error_handler->incompatible_types(t1, t2, lineno);
            }

        }

        if(!matched_rule && ((t1->get_tag() == TypeTag::Function) && (t2->get_tag() == TypeTag::Function))) {
            matched_rule = true;

            std::shared_ptr<TypeVariable> from_type_t1 = t1->get_function_from_type();
            std::shared_ptr<TypeVariable> to_type_t1 = t1->get_function_to_type();

            std::shared_ptr<TypeVariable> from_type_t2 = t2->get_function_from_type();
            std::shared_ptr<TypeVariable> to_type_t2 = t2->get_function_to_type();

            this->add_constraint(from_type_t1, from_type_t2, lineno);
            this->add_constraint(to_type_t1, to_type_t2, lineno);
        }

      if(!matched_rule && ((t1->get_tag() == TypeTag::Reference) && (t2->get_tag() == TypeTag::Reference))) {
            matched_rule = true;

            std::shared_ptr<TypeVariable> referenced_type_t1 = t1->get_referenced_type();
            std::shared_ptr<TypeVariable> referenced_type_t2 = t2->get_referenced_type();

            this->add_constraint(referenced_type_t1, referenced_type_t2, lineno);
        }

      if(!matched_rule && ((t1->get_tag() == TypeTag::Array) && (t2->get_tag() == TypeTag::Array))) {
            matched_rule = true;

            DimType dim_type_t1 = t1->get_array_dim_type();
            DimType dim_type_t2 = t2->get_array_dim_type();

            unsigned int dim_t1 = t1->get_array_dim();
            unsigned int dim_t2 = t2->get_array_dim();

            if(dim_type_t1 == dim_type_t2) {
                //t1 and t2 are exact
                if(dim_type_t1 == DimType::Exact){
                    if(dim_t1 != dim_t2) {
                        error_handler->incompatible_types(t1, t2, lineno);
                    }
                }
                else {
                    //t1 and t2 are AtLeast
                    if(dim_t1 > dim_t2){
                        t1->set_array_dim(dim_t1);
                        t2->set_array_dim(dim_t1);
                    }
                    else {
                        t1->set_array_dim(dim_t2);
                        t2->set_array_dim(dim_t2);
                    }
                }
            }
            else {
                //t1 is exact and t2 is atleast
                if(dim_type_t1 == DimType::Exact) {
                    if(dim_t1 >= dim_t2) {
                        t1->set_array_dim(dim_t1);
                        t2->set_array_dim(dim_t1);
                        t1->set_array_dim_type(DimType::Exact);
                        t2->set_array_dim_type(DimType::Exact);
                    }
                    else {
                        error_handler->incompatible_types(t1, t2, lineno);
                    }
                }
                //t2 is exact and t1 is atleast
                else {
                  if(dim_t2 >= dim_t1) {
                        t1->set_array_dim(dim_t2);
                        t2->set_array_dim(dim_t2);
                        t1->set_array_dim_type(DimType::Exact);
                        t2->set_array_dim_type(DimType::Exact);
                    }
                    else {
                        error_handler->incompatible_types(t1, t2, lineno);
                    }
                }
            }

            std::shared_ptr<TypeVariable> array_type_t1 = t1->get_array_type();
            std::shared_ptr<TypeVariable> array_type_t2 = t2->get_array_type();

            this->add_constraint(array_type_t1, array_type_t2, lineno);
        }

        if((!matched_rule) && ((t1->get_tag() == TypeTag::Unknown)) && (!t2->contains(t1))) {
            matched_rule = true;

            this->substitute(t1, t2);
            this->bind(t1, t2);
        }

        if((!matched_rule) && ((t2->get_tag() == TypeTag::Unknown)) && (!t1->contains(t2))) {
            matched_rule = true;

            this->substitute(t2, t1);
            this->bind(t2, t1);
        }

        if(!matched_rule && ((((t1->get_tag() != TypeTag::Unknown) && (t2->get_tag() != TypeTag::Unknown)) && (t1->get_tag() == t2->get_tag())))) {
            matched_rule = true;
        }

        if(!matched_rule){
            error_handler->incompatible_types(t1, t2, lineno);
        }
    }

    //All contraints unified now set inferred values to all bindings. (type_variable, type)
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        bound_pair->first->bind(bound_pair->second);
    }
}

//Substitute all occurrences of the type variable with the type
void SymbolTable::substitute(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type) {
    this->substitutions.insert({type_variable, type});
}


std::shared_ptr<TypeVariable> SymbolTable::find_substitute(std::shared_ptr<TypeVariable> type) {
    auto substitute = this->substitutions.find(type);

    while (substitute != this->substitutions.end()) {
        type = substitute->second;
        substitute = this->substitutions.find(type);
    }

    return type;
}

void SymbolTable::bind(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type) {
    //If t1->t2 and now we bind t2->t3 then make sure that you make t1->t3 so that when t3 gets a value both t2 and t1 copy it.
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        if(bound_pair->second == type_variable)
            bound_pair->second = type;
    }

    //Add new binding type_variable->type.
    bound_types.push_back(std::pair<std::shared_ptr<TypeVariable>, std::shared_ptr<TypeVariable>>(type_variable, type));
}