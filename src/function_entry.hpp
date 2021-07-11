#ifndef __FUNCTIONENTRY_HPP__
#define __FUNCTIONENTRY_HPP__

#include "symbol_entry.hpp"
#include "function_type.hpp"
#include "enums.hpp"


class FunctionEntry: public SymbolEntry{
public:

    FunctionEntry(std::string id, EntryType entry_type, FunctionType* type) : type(type), 
        SymbolEntry(id, entry_type) { this->counter++; }
    
    ~FunctionEntry() { }

private:
    // bool                isForward;
    // SymbolEntry*        firstArgument;
    // SymbolEntry*        lastArgument;
    // Type*               resultType;
    FunctionType*       type;
    // ParDef              pardef;
    static unsigned int counter;    /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε αυτές που έχουν το ίδιο όνομα */
};

#endif