#ifndef __BOOL_PATTERN_HPP__
#define __BOOL_PATTERN_HPP__

#include "pattern.hpp"
#include <string>
#include <memory>

class TypeVariable;

class BoolPattern : public Pattern {
public:
    BoolPattern(bool value);

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    bool value;
};

#endif