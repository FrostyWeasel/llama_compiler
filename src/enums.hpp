#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum class BoolType     { True, False };
enum class UnOpType     { Plus, Minus, Dereference, Not };
enum class BinOpType    { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, MoreThan, LessOrEqualThan, MoreOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign };
enum class TypeTag      { Unit, Int, Char, Bool };

#endif