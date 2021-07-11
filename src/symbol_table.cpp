#include "symbol_table.hpp"

void SymbolTable::scope_open() {
    this->current_scope = new Scope(this->current_scope, nullptr, 
        this->current_scope != nullptr ? this->current_scope->get_nesting_level() + 1 : 1, false);
}

void SymbolTable::scope_close() {
    auto current_scope = this->current_scope;

    if(this->current_scope == nullptr)
        exit(1); //TODO: Error Handling

    for(auto entry = current_scope->get_entries(); entry != nullptr; entry = entry->get_next_in_scope()){
        hashtable[entry->get_hash_value()] = entry->get_next_hash();
        delete entry;
    }

    delete current_scope;
}

void SymbolTable::scope_hide(Scope* scope, bool flag) {
    if(scope == nullptr)
        exit(1); //TODO: Error Handling

    scope->set_is_hidden(flag);
}

void SymbolTable::insert_entry(SymbolEntry* entry){
    //Check if entry already in table
    for(auto e = this->current_scope->get_entries(); e != nullptr; e = e->get_next_in_scope()){
       while (e != nullptr && e->get_nesting_level() == this->current_scope->get_nesting_level()) {
                if(e->get_id() == entry->get_id())
                    exit(1); //TODO: Already exists error handling
                else
                    entry = entry->get_next_hash();
       }
    }

    //Add entry to table
    unsigned int hash_value = PJW_hash(entry->get_id()) % hashtable_size;
    entry->set_hash_value(hash_value);

    entry->set_nesting_level(this->current_scope->get_nesting_level());

    entry->set_next_hash(this->hashtable[hash_value]);
    this->hashtable[hash_value] = entry;
    entry->set_next_in_scope(this->current_scope->get_entries());
    this->current_scope->set_entries(entry);

}

// SymbolEntry* SymbolTable::entry_lookup(ID* id, LookupType lookup_type) {
//     unsigned int hash_value = PJW_hash(id->get_id()) % hashtable_size;
//     SymbolEntry* entry = hashtable[hash_value];

//     switch(lookup_type) {
//         case LookupType::LOOKUP_CURRENT_SCOPE:
//             while (entry != nullptr && entry->get_nesting_level() == this->current_scope->get_nesting_level()) {
//                 if(entry->get_id() == id->get_id())
//                     return entry;
//                 else
//                     entry = entry->get_next_hash();
//             }
//             break;
//         case LookupType::LOOKUP_ALL_SCOPES:
//             while (entry != nullptr) {
//                 if(entry->get_id() == id->get_id())
//                     return entry;
//                 else
//                     entry = entry->get_next_hash();
//             }           
//             break;
//     }

//     //TODO: Error if unknown identifier.
//     exit(1);
//     return nullptr;
// }

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