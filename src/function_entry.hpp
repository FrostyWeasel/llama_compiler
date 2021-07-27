#ifndef __FUNCTIONENTRY_HPP__
#define __FUNCTIONENTRY_HPP__

#include "symbol_entry.hpp"
#include "function_type.hpp"
#include "enums.hpp"


class FunctionEntry : public SymbolEntry{
public:

    FunctionEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> from_type, std::shared_ptr<TypeVariable> to_type, unsigned int parameter_count) : from_type(from_type), to_type(to_type), 
        parameter_count(parameter_count), SymbolEntry(id, entry_type) { count = FunctionEntry::counter++; }
    
    virtual ~FunctionEntry() { }

    void set_from_type(std::shared_ptr<TypeVariable> from_type) { this->from_type = from_type; }
    void set_to_type(std::shared_ptr<TypeVariable> to_type) { this->to_type = to_type; }

    std::shared_ptr<TypeVariable> get_from_type() { return this->from_type; }
    std::shared_ptr<TypeVariable> get_to_type() { return this->to_type; }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return std::make_shared<TypeVariable>(TypeTag::Function, this->from_type, this->to_type, this->parameter_count); }

    void set_function_declaration(llvm::Function* function_declaration) { this->function_declaration = function_declaration; }
    llvm::Function* get_function_declaration() { return this->function_declaration; }

    unsigned int get_count() { return this->count; }

    unsigned int get_parameter_count() { return this->parameter_count; }

private:
    std::shared_ptr<TypeVariable>       from_type;
    std::shared_ptr<TypeVariable>       to_type;
    llvm::Function*     function_declaration;
    unsigned int        parameter_count;
    unsigned int        count;
    static unsigned int counter;    /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε αυτές που έχουν το ίδιο όνομα */
};

#endif