#ifndef __CONSTANTENTRY_HPP__
#define __CONSTANTENTRY_HPP__

#include "includes.hpp"
#include "symbol_entry.hpp"

template <class T>
class ConstantEntry: public SymbolEntry{


private:
   Type*         type;                  
   T*            value;                
};

#endif