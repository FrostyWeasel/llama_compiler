#include "symbol_table.hpp"

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

//if function type then contraint(from type1, from type 2) and constraint(to type 1, to type 2)
//if t1 array then make sure that t2 is also array
//think about the possibility that one is a function and one is not(can the constraint be satisfied? do i need contains?)
//if one is a ref? should the other be a reference too?
//make enum that tells me what type it is t1 and t2 are
 
void SymbolTable::unify() {
    bool matched_rule;

    while(!this->contraints.empty()) {
        matched_rule = false;

        Constraint constraint = this->contraints[this->contraints.size()-1]; 
        this->contraints.pop_back();

        Type* t1 = constraint.get_t1();
        Type* t2 = constraint.get_t2();

        //Check that they are not functions
        if(t1->get_tag() != TypeTag::Unknown && t2->get_tag() != TypeTag::Unknown && (t1->get_tag() == t2->get_tag())){
            matched_rule = true;
        }

        if(!matched_rule && (t1->get_tag() == TypeTag::Unknown /*&& !t2->contains(t1)*/)) {
            matched_rule = true;
            this->substitute(t1, t2);
            this->bind(t1, t2);
        }

        if(!matched_rule && (t2->get_tag() == TypeTag::Unknown /*&& !t1->contains(t1)*/)) {
            matched_rule = true;
            this->substitute(t2, t1);
            this->bind(t2, t1);
        }

        if(!matched_rule){
            std::cerr << "Failed to unify : " << *t1 << "and " << *t2 << '\n'; 
            exit(1);
        }
    }

    //All contraints unified now set inferred values to all bindings.
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        bound_pair->first->set_tag(bound_pair->second->get_tag());
    }
}

//Substitute every instance of type_variable in constraints with type.
void SymbolTable::substitute(Type* type_variable, Type* type) {
    for(auto constraint_it = this->contraints.begin(); constraint_it != this->contraints.end(); constraint_it++) {
        if (constraint_it->get_t1() == type_variable) 
            constraint_it->set_t1(type);
        
        if (constraint_it->get_t2() == type_variable) 
            constraint_it->set_t2(type);
    }
}

void SymbolTable::bind(Type* type_variable, Type* type) {
    //If t1->t2 and now we bind t2->t3 then make sure that you make t1->t3 so that when t3 gets a value both t2 and t1 copy it.
    for(auto bound_pair = this->bound_types.begin(); bound_pair != this->bound_types.end(); bound_pair++){
        if(bound_pair->second == type_variable)
            bound_pair->second = type;
    }

    //Add new binding type_variable->type.
    bound_types.push_back(std::pair<Type*, Type*>(type_variable, type));
}