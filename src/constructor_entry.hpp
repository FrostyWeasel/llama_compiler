#ifndef __CONSTRUCTOR_ENTRY_HPP__
#define __CONSTRUCTOR_ENTRY_HPP__

#include "symbol_entry.hpp"
#include "enums.hpp"

class ConstructorEntry : public SymbolEntry {
public:

    ConstructorEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type_constructed, unsigned int count, std::vector<std::shared_ptr<TypeVariable>>* type_list) : 
        type_constructed(type_constructed), SymbolEntry(id, entry_type), type_list(type_list), count(count) { 

    }
    
    virtual ~ConstructorEntry() {  }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type_constructed; }
    unsigned int get_count() { return this->count; }

    std::vector<std::shared_ptr<TypeVariable>>* get_constructor_type_list() { return this->type_list; }

    inline llvm::Type* get_llvm_type() { return this->llvm_type; }
    inline void set_llvm_type(llvm::Type* llvm_type) { this->llvm_type = llvm_type; }

    inline llvm::Function* get_constructor_structural_cmp_function() { return this->constructor_structural_cmp_function; }
    inline void set_constructor_structural_cmp_function(llvm::Function* constructor_structural_cmp_function) { this->constructor_structural_cmp_function = constructor_structural_cmp_function; }

private:
    std::shared_ptr<TypeVariable> type_constructed;
    std::vector<std::shared_ptr<TypeVariable>>* type_list;

    llvm::Type* llvm_type;

    llvm::Function* constructor_structural_cmp_function;

    unsigned int count;
};

#endif