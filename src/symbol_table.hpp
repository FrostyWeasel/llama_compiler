#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include "scope.hpp"
#include "symbol_entry.hpp"
#include "enums.hpp"
#include <string>

class SymbolTable{
public:

    SymbolTable(unsigned int size) : hashtable_size(size), current_scope(nullptr) {
        hashtable = new SymbolEntry*[size];

        for(unsigned int i = 0; i < size; i++) {
            hashtable[i] = nullptr;
        }
    }

    ~SymbolTable() {
        delete[] hashtable;
        delete current_scope;
    }

    void        scope_open    ();
    void        scope_close   ();
    void        scope_hide    (Scope* scope, bool flag);

    void            insert_entry   (SymbolEntry* entry);
    SymbolEntry*    lookup_entry   (std::string id, LookupType lookup_type);

private:
    unsigned int    hashtable_size;
    SymbolEntry**   hashtable;
    Scope*          current_scope;

    unsigned int PJW_hash(std::string id);
};

#endif 