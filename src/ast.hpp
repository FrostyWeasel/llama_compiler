#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include "symbol_table.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include "semantic_analyzer.hpp"


class AST{
public:

    AST() = default;
    AST(NodeType node_type) : node_type(node_type) { }
    virtual ~AST() = default;
    virtual void print(std::ostream& out) const = 0;
    virtual std::shared_ptr<TypeVariable> infer() = 0;
    virtual void sem() = 0;
    virtual void close_all_program_scopes();

    void unify() { st->unify(); }
    void add_library_functions();
    void close_library_function_scope();

    virtual NodeType get_node_type() { return node_type; }

    virtual void add_to_symbol_table() { }


protected:
    static SymbolTable* st;
    static SemanticAnalyzer* sa;
    NodeType node_type;

// private:
    // static unsigned int tab_level;
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif