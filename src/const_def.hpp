#ifndef __CONSTANTDEF_HPP__
#define __CONSTANTDEF_HPP__

#include "expr.hpp"
#include "def.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "constant_entry.hpp"
#include <string>

class ConstDef : public Def{
public:
    ConstDef(std::string* id, Expr* expr): id(*id), expr(expr), Def(new TypeVariable()) {}
    ConstDef(std::string* id, std::shared_ptr<TypeVariable> type_variable, Expr* expr): id(*id), Def(type_variable), expr(expr) {}

    virtual ~ConstDef() {
        delete expr;
    }

    virtual void print(std::ostream& out) const override{
        out << " " << id;
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << " = ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << " null";
    }

    virtual void add_to_symbol_table() override {
        ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);
        
        st->insert_entry(entry);

        this->entry = entry;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto expr_type = this->expr->infer();

        st->add_constraint(this->type_variable, expr_type);

        return this->type_variable;
    }

    virtual void sem() override { 
        this->expr->sem();
    }

    virtual llvm::Value* codegen() const override {
        auto value = this->expr->codegen();
        auto type_tag = this->type_variable->get_tag();

        llvm::AllocaInst* const_alloc_ptr = nullptr;

        //TODO: Type might still be uknown
        const_alloc_ptr = Builder.CreateAlloca(value->getType(), value, id);
        this->entry->set_allocation(const_alloc_ptr);

        return const_alloc_ptr;
    }

private:
    std::string id;
    Expr* expr;
};

#endif