#ifndef __TYPE_ENTRY_HPP__
#define __TYPE_ENTRY_HPP__

#include "symbol_entry.hpp"
#include "enums.hpp"
#include "constructor.hpp"

class TypeEntry : public SymbolEntry {
public:

    TypeEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type, std::vector<Constructor*> constructors) : type(type), 
        constructors(constructors), SymbolEntry(id, entry_type) { count = TypeEntry::counter++; }
    
    virtual ~TypeEntry() {  }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type; }
    unsigned int get_count() { return this->count; }

    // llvm::GlobalVariable* get_type_struct() { return this->type_struct; }
    // void set_type_struct(llvm::GlobalVariable* type_struct) { this->type_struct = type_struct; }

    std::vector<Constructor*>& get_constructors() { return this->constructors; }

private:
    std::shared_ptr<TypeVariable>       type;
    std::vector<Constructor*> constructors;
    // llvm::GlobalVariable* type_struct;
    unsigned int        count;
    static unsigned int counter;    /* Unique counter to differentiate between user types of the same name */
};

#endif