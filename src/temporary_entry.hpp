#ifndef __TEMPORARYENTRY_HPP__
#define __TEMPORARYENTRY_HPP__

#include "includes.hpp"
#include "symbol_entry.hpp"

// !Propably not needed in llama
class TemporaryEntry: public SymbolEntry{


private:
    Type*         type;                  
    int           offset;                
    int           number;
};

#endif