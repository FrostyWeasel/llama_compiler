#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include "includes.hpp"

class SymbolTable{


private:
    unsigned int hashtable_size;
    SymbolTableEntry* hashtable;
    Scope current_scope;

};

#endif