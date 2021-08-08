#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include "scope.hpp"
#include "enums.hpp"
#include "constraint.hpp"
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

class ErrorHandler;
class TypeVariable;
class SymbolEntry;

class SymbolTable{
public:

    SymbolTable(unsigned int size);

    ~SymbolTable();

    void        scope_open    ();
    void        scope_close   ();
    void        scope_hide    (Scope* scope, bool flag);
    void        scope_hide    (bool flag);
    void        close_all_program_scopes();
    void        clear_inference_structures();

    unsigned int get_current_nesting_level() { return this->current_scope->get_nesting_level(); }


    void            insert_entry   (SymbolEntry* entry);
    SymbolEntry*    lookup_entry   (std::string id, LookupType lookup_type);
    SymbolEntry*    lookup_entry_of_type(std::string id, EntryType entry_type);
    bool            contains       (std::string id, LookupType lookup_type);

    inline void add_constraint (std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2, unsigned int lineno) {
        contraints.push_back({ Constraint(t1, t2), lineno });
    }

    void unify();

private:
    unsigned int    hashtable_size;
    SymbolEntry**   hashtable;
    Scope*          current_scope;

    //Holds a list of type constraints and the line number of the program source that caused the contraint(for error handling)
    std::vector<std::pair<Constraint, unsigned int>> contraints;
    std::vector<std::pair<std::shared_ptr<TypeVariable>, std::shared_ptr<TypeVariable>>> bound_types;
    std::unordered_map<std::shared_ptr<TypeVariable>, std::shared_ptr<TypeVariable>> substitutions;

    unsigned int PJW_hash(std::string id);

    void substitute(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type);
    void bind(std::shared_ptr<TypeVariable> type_variable, std::shared_ptr<TypeVariable> type);
    std::shared_ptr<TypeVariable> find_substitute(std::shared_ptr<TypeVariable> type);

    static std::unique_ptr<ErrorHandler> error_handler;
};

#endif 