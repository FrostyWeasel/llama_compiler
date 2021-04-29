#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum class BoolType     { True, False };
enum class OpType       { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, MoreThan, LessOrEqualThan, MoreOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not };
enum class TypeTag      { Unit, Int, Char, Bool };
enum class LetType      { Rec, NoRec };

#endif