#include "symbol_table.hpp"
#include "function_type.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "expr.hpp"
#include "par.hpp"
#include "def.hpp"
#include "ast.hpp"

void SymbolTable::scope_open() {
    this->current_scope = new Scope(this->current_scope, nullptr, 
        this->current_scope != nullptr ? this->current_scope->get_nesting_level() + 1 : 1, false);
}

void SymbolTable::scope_close() {
    auto current_scope = this->current_scope;

    if(this->current_scope == nullptr) {
        std::cerr << "Can't close null Scope\n";
        exit(1); //TODO: Error Handling
    }

    for(auto entry = current_scope->get_entries(); entry != nullptr; entry = entry->get_next_in_scope()){
        hashtable[entry->get_hash_value()] = entry->get_next_hash();
        delete entry;
    }

    this->current_scope = current_scope->get_parent();

    delete current_scope;
}

void SymbolTable::scope_hide(Scope* scope, bool flag) {
    if(scope == nullptr)
        exit(1); //TODO: Error Handling

    scope->set_is_hidden(flag);
}

void SymbolTable::scope_hide(bool flag) {
    if(this->current_scope == nullptr)
        exit(1); //TODO: Error Handling

    this->current_scope->set_is_hidden(flag);
}

void SymbolTable::insert_entry(SymbolEntry* entry){
    //Check if entry already in table
    for(auto e = this->current_scope->get_entries(); e != nullptr; e = e->get_next_in_scope()){
        if(e->get_id() == entry->get_id()){
            std::cerr << "Identifier already exists in scope: " << e->get_id();
            exit(1); //TODO: Already exists error handling
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

    //TODO: Error if unknown identifier.
    std::cerr << "Unkown identifier: " << id << "\n";
    exit(1);
    return nullptr;
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

        Constraint constraint = this->contraints[this->contraints.size()-1]; 
        this->contraints.pop_back();

        std::shared_ptr<TypeVariable> t1 = constraint.get_t1();
        std::shared_ptr<TypeVariable> t2 = constraint.get_t2();

        t1 = this->find_substitute(t1);
        t2 = this->find_substitute(t2);

        if(!matched_rule && ((t1->get_tag() == TypeTag::Function) && (t2->get_tag() == TypeTag::Function))) {
            matched_rule = true;

            std::shared_ptr<TypeVariable> from_type_t1 = t1->get_function_from_type();
            std::shared_ptr<TypeVariable> to_type_t1 = t1->get_function_to_type();

            std::shared_ptr<TypeVariable> from_type_t2 = t2->get_function_from_type();
            std::shared_ptr<TypeVariable> to_type_t2 = t2->get_function_to_type();

            this->add_constraint(from_type_t1, from_type_t2);
            this->add_constraint(to_type_t1, to_type_t2);
        }

      if(!matched_rule && ((t1->get_tag() == TypeTag::Reference) && (t2->get_tag() == TypeTag::Reference))) {
            matched_rule = true;

            std::shared_ptr<TypeVariable> referenced_type_t1 = t1->get_referenced_type();
            std::shared_ptr<TypeVariable> referenced_type_t2 = t2->get_referenced_type();

            this->add_constraint(referenced_type_t1, referenced_type_t2);
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
                        std::cerr << "Failed to unify : " << *t1 << "and " << *t2 << '\n'; 
                        exit(1); //TODO: Handle errors.
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
                        std::cerr << "Failed to unify arrays : " << *t1 << "and " << *t2 << '\n'; 
                        exit(1); //TODO: Handle errors.
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
                        std::cerr << "Failed to unify arrays : " << *t1 << "and " << *t2 << '\n'; 
                        exit(1); //TODO: Handle errors.
                    }
                }
            }

            std::shared_ptr<TypeVariable> array_type_t1 = t1->get_array_type();
            std::shared_ptr<TypeVariable> array_type_t2 = t2->get_array_type();

            this->add_constraint(array_type_t1, array_type_t2);
        }

        if(!matched_rule && ((t1->get_tag() == TypeTag::Unknown))) {
            matched_rule = true;
            if(!t2->contains(t1))
                this->substitute(t1, t2);
            this->bind(t1, t2);
        }

        if(!matched_rule && ((t2->get_tag() == TypeTag::Unknown))) {
            matched_rule = true;
            if(!t1->contains(t2))
                this->substitute(t2, t1);
            this->bind(t2, t1);
        }

        if(!matched_rule && ((((t1->get_tag() != TypeTag::Unknown) && (t2->get_tag() != TypeTag::Unknown)) && (t1->get_tag() == t2->get_tag())) || (t1 == t2))) {
            matched_rule = true;
        }

        if(!matched_rule){
            std::cerr << "Failed to unify : " << *t1 << "and " << *t2 << '\n'; 
            exit(1);
        }
    }

    //All contraints unified now set inferred values to all bindings. (type_variable, type)
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        bound_pair->first->bind(bound_pair->second);
    }
}

void SymbolTable::substitute(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type) {
    this->substitutions.insert({type_variable, type});
}


std::shared_ptr<TypeVariable> SymbolTable::find_substitute(std::shared_ptr<TypeVariable> type) {
    while (this->substitutions.find(type) != this->substitutions.end()) {
        type = this->substitutions.find(type)->second;
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