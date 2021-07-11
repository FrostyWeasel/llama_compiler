#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

// enum class BoolType     { True = true, False = false };
enum class OpType       { Plus, Minus, Times, Divide, Equals, NotEquals, LessThan, GreaterThan, LessOrEqualThan, GreaterOrEqualThan, NatEquals, NatNotEquals, And, Or, Concat, Assign, Dereference, Not, Modulo };
enum class TypeTag      { Unit, Int, Char, Bool, Unknown };
enum class LetType      { Rec, NoRec };
enum class DefType      { Mutable, NonMutable };

//SymbolTable enums

/* Τύποι εγγραφών του πίνακα συμβόλων */
enum class EntryType    {   ENTRY_VARIABLE,                       /* Μεταβλητές                 */
                            ENTRY_CONSTANT,                       /* Σταθερές                   */
                            ENTRY_FUNCTION,                       /* Συναρτήσεις                */
                            ENTRY_PARAMETER,                      /* Παράμετροι συναρτήσεων     */
                            // ENTRY_TYPE,                        /* User defined Types         */
                            ENTRY_IDENTIFIER

                        }

/* Τύποι περάσματος παραμετρων */
// enum class PassMode     {
//                             PASS_BY_VALUE,                        /* Κατ' αξία                  */
//                             PASS_BY_REFERENCE                     /* Κατ' αναφορά               */
//                         }

/* Τύπος αναζήτησης στον πίνακα συμβόλων */
enum class LookupType   {
                            LOOKUP_CURRENT_SCOPE,
                            LOOKUP_ALL_SCOPES
                        }

/* Κατάσταση παραμέτρων συνάρτησηςs  */
// enum class ParDef       {                               
//                             PARDEF_COMPLETE,                    /* Πλήρης ορισμός     */
//                             PARDEF_DEFINE,                      /* Εν μέσω ορισμού    */
//                             PARDEF_CHECK                        /* Εν μέσω ελέγχου    */
//                         }
#endif