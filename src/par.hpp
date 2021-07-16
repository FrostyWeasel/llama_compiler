#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "symbol_entry.hpp"
#include "parameter_entry.hpp"
#include <string>

class Par : public AST{
public:
    Par(std::string* id): id(*id), type_variable(new TypeVariable()), AST(NodeType::Par) {}
    Par(std::string* id, TypeVariable* type_variable): id(*id), type_variable(type_variable), AST(NodeType::Par) {  }

    ~Par() {
        delete type_variable;
    }

    virtual void print(std::ostream &out) const override { 
        out << "Par(";
        out << "Id: " << id << " ";
        out << "TypeVariable: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual TypeVariable* infer() override {
        ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

        st->insert_entry(entry);

        return this->type_variable;
    }

    virtual void set_type(TypeVariable* type_variable) { this->type_variable = type_variable; }

private:
    std::string id;
    TypeVariable* type_variable;
};

#endif