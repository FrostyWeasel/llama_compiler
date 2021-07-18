#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include "scope.hpp"
#include "symbol_entry.hpp"
#include "enums.hpp"
#include "constraint.hpp"
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

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
    void        close_all_program_scopes();


    void            insert_entry   (SymbolEntry* entry);
    SymbolEntry*    lookup_entry   (std::string id, LookupType lookup_type);

    inline void add_constraint (std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2) {
        contraints.push_back(Constraint(t1, t2));
    }

    void unify();

private:
    unsigned int    hashtable_size;
    SymbolEntry**   hashtable;
    Scope*          current_scope;

    std::vector<Constraint> contraints;
    std::vector<std::pair<std::shared_ptr<TypeVariable>, std::shared_ptr<TypeVariable>>> bound_types;
    std::unordered_map<std::shared_ptr<TypeVariable>, std::shared_ptr<TypeVariable>> substitutions;

    unsigned int PJW_hash(std::string id);

    void substitute(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type);
    void bind(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type);
    std::shared_ptr<TypeVariable> find_substitute(std::shared_ptr<TypeVariable> type);

};

#endif 