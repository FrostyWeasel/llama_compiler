#ifndef __FLOAT_PATTERN_HPP__
#define __FLOAT_PATTERN_HPP__

#include "pattern.hpp"
#include <string>
#include <memory>

class TypeVariable;

class FloatPattern : public Pattern {
public:
    FloatPattern(float value);

    virtual ~FloatPattern() {
        
    }

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    float value;
};

#endif