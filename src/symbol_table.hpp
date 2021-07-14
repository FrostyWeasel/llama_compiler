#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include "scope.hpp"
#include "symbol_entry.hpp"
#include "enums.hpp"
#include "constraint.hpp"
#include <vector>
#include <string>
#include <utility>

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
    void        scope_hide    (bool flag);


    void            insert_entry   (SymbolEntry* entry);
    SymbolEntry*    lookup_entry   (std::string id, LookupType lookup_type);

    inline void add_constraint (Type* t1, Type* t2) {
        contraints.push_back(Constraint(t1, t2));
    }

    void unify();

private:
    unsigned int    hashtable_size;
    SymbolEntry**   hashtable;
    Scope*          current_scope;

    std::vector<Constraint> contraints;
    std::vector<std::pair<Type*, Type*>> bound_types;

    unsigned int PJW_hash(std::string id);

    void substitute(Type* type_variable, Type* type);

    void bind(Type* type_variable, Type* type);
};

#endif 