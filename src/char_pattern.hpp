#ifndef __CHAR_PATTERN_HPP__
#define __CHAR_PATTERN_HPP__

#include "pattern.hpp"
#include <string>
#include <memory>

class TypeVariable;

class CharPattern : public Pattern {
public:
    CharPattern(char value);

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    char value;
};

#endif