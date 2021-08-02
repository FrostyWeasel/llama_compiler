#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include "enums.hpp"
#include <iostream>
#include <memory>

class TypeVariable;
class ErrorHandler;

class Type {
public:
    Type();
    Type(TypeTag type);

    virtual ~Type();

    virtual TypeTag get_tag();
    virtual void set_tag(TypeTag tag);

    
    virtual void print(std::ostream& out) const;

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable);

protected:
    TypeTag tag;
    static std::unique_ptr<ErrorHandler> error_handler;
};

inline std::ostream& operator<<(std::ostream& out, const Type& type){
    type.print(out);
    return out;
}

#endif