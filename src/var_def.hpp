#ifndef __VARDEF_HPP__
#define __VARDEF_HPP__

#include "type_variable.hpp"
#include "variable_entry.hpp"
#include "enums.hpp"

//TODO: Symboltable: Should have a memory slot capable of holding an elements of its type.
//TODO: TypeCheck: Type can be whatever.
//TODO: TypeInference: Type is type ref

class VarDef : public Def{
public:
    VarDef(std::string* id): id(*id), Def(new TypeVariable(TypeTag::Reference, new TypeVariable(TypeTag::Unknown))) {}
    VarDef(std::string* id, TypeVariable* type_variable): id(*id), Def(new TypeVariable(TypeTag::Reference, type_variable)) {}

    virtual void print(std::ostream& out) const override{
        out << "VarDef(";
        out << " Id: " << id;
        out << " TypeVariable: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual TypeVariable* infer() override {
        VariableEntry* entry = new VariableEntry(id, EntryType::ENTRY_VARIABLE, this->type_variable);
        
        st->insert_entry(entry);

        return this->type_variable;
    }

    virtual void sem() override {
        
    }

private:
    std::string id;
};

#endif