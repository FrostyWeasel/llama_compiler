#ifndef __PATTERN_HPP__
#define __PATTERN_HPP__

#include "ast.hpp"
#include "enums.hpp"

class Pattern : public AST {
public:
    Pattern(PatternType pattern_type, std::shared_ptr<TypeVariable> type_variable) : pattern_type(pattern_type), type_variable(type_variable) {  }
    
    ~Pattern() = default;

    virtual void print(std::ostream& out) const override = 0;

    virtual std::shared_ptr<TypeVariable> infer() override = 0;

    virtual void sem() override = 0;

    virtual llvm::Value* codegen() override = 0;

    virtual std::string get_id() override { return ""; }

protected:
    PatternType pattern_type;
    std::shared_ptr<TypeVariable> type_variable;

};

#endif