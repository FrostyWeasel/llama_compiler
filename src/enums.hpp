#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum class OpType           { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, GreaterThan, LessOrEqualThan, GreaterOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not, Modulo, PlusFloat, MinusFloat, TimesFloat, DivideFloat, ExponentiateFloat };
enum class TypeTag          { Unit, Int, Float, Char, Bool, Unknown, Array, Function, Reference, UserType };
enum class TypeVariableTag  { Free, Bound };
enum class LetType          { Rec, NoRec };
enum class DefType          { Mutable, NonMutable };


/* Τύποι εγγραφών του πίνακα συμβόλων */
enum class EntryType    {   ENTRY_VARIABLE,                       /* Μεταβλητές                 */
                            ENTRY_CONSTANT,                       /* Σταθερές                   */
                            ENTRY_FUNCTION,                       /* Συναρτήσεις                */
                            ENTRY_PARAMETER,                      /* Παράμετροι συναρτήσεων     */
                            ENTRY_IDENTIFIER,
                            ENTRY_TYPE,                             /* User defined type */
                            ENTRY_CONSTRACTOR                       /* Constractor of user defined type */
                        };

/* Τύπος αναζήτησης στον πίνακα συμβόλων */
enum class LookupType   {
                            LOOKUP_CURRENT_SCOPE,
                            LOOKUP_ALL_SCOPES
                        };

enum class BlockType    {
                            LetDef,
                            Def,
                            Par,
                            Expr,
                            ExprComma,
                            Definition,
                            TDef,
                            Constructor,
                            Clause,
                            Pattern
                        };

enum class NodeType     {
                            Par,
                            Expr,
                            Def,
                            BinOp,
                            UnOp,
                            New
                        };   

enum class DimType      {
                            Exact, //Array has exactly this dimension
                            AtLeast //Array has at least this dimension
                        };

enum class FunctionTypeTag  {
                                Curry, //FunctionType simply binds two parameters together
                                Actual //FunctionType is actually a function
                            };

enum class PassStage        {
                                FunctionDef, //Currently doing a pass in function body
                                Other
                            };

enum class ErrorType        {
                                User,
                                Internal,
                                Warning
                            };

enum class PatternType      {
                                Int,
                                Float,
                                Bool,
                                Id,
                                Constructor
                            }; 

#endif