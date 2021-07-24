#ifndef __VARIABLEENTRY_HPP__
#define __VARIABLEENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class VariableEntry: public SymbolEntry {
public:

    VariableEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type) : type(type),
        dim(0), SymbolEntry(id, entry_type) { }
    
    VariableEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type, unsigned int dim) : type(type),
        dim(dim), SymbolEntry(id, entry_type) { }
    
    virtual ~VariableEntry() { }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type; }
    unsigned int get_dim() { return dim; }

    void set_dim_sizes(std::vector<llvm::Value*> dim_sizes) { this->dim_sizes = dim_sizes; }
    std::vector<llvm::Value*>& get_dim_sizes() { return dim_sizes; }

private:
    std::shared_ptr<TypeVariable> type;   
    unsigned int dim;
    std::vector<llvm::Value*> dim_sizes;               
};

#endif