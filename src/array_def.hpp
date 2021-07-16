#ifndef __ARRAYDEF_HPP__
#define __ARRAYDEF_HPP__

#include "type_variable.hpp"
#include "enums.hpp"

//TODO: TypeCheck: All expressions in expr_list should have type=int.
//TODO: TypeInference: Type is arraytype [*...expr_list->size] of type
//TODO: SymbolTable: Array[expr_list[0]][expr_list[1]]...

class ArrayDef : public Def{
public:
    ArrayDef(std::string* id, Block<Expr>* expr_list): id(*id), Def(new TypeVariable()), expr_list(expr_list) {}
    ArrayDef(std::string* id, Block<Expr>* expr_list, TypeVariable* type_variable): id(*id), expr_list(expr_list), Def(type_variable) {}

    ~ArrayDef() {
	std::cout << "ArrayDef deleted\n";
        delete expr_list;
    }

    virtual void print(std::ostream& out) const override{
        out << "ArrayDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << " Expr_list: ";
        if(expr_list != nullptr)
            expr_list->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif