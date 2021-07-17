%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "includes.hpp"
#include "lexer.hpp"
#include <memory>

%}

%token T_AND                    "and"                 
%token T_ARRAY                  "array"  
%token T_BEGIN                  "begin"
%token T_BOOL                   "bool"
%token T_CHAR                   "char"
%token T_DELETE                 "delete"
%token T_DIM                    "dim"
%token T_DO                     "do"
%token T_DONE                   "done"
%token T_DOWNTO                 "downto"
%token T_ELSE                   "else"
%token T_END                    "end"
%token T_FALSE                  "false"
%token T_FOR                    "for"
%token T_IF                     "if"
%token T_IN                     "in"
%token T_INT                    "int"
%token T_LET                    "let"
%token T_MATCH                  "match"
%token T_MOD                    "mod"
%token T_MUTABLE                "mutable"
%token T_NEW                    "new"
%token T_NOT                    "not"
%token T_OF                     "of"
%token T_REC                    "rec"
%token T_REF                    "ref"
%token T_THEN                   "then"
%token T_TO                     "to"
%token T_TRUE                   "true"
%token T_TYPE                   "type"
%token T_UNIT                   "unit"
%token T_WHILE                  "while"
%token T_WITH                   "with"
%token T_TYPE_ARROW_OP          "->"
%token T_AND_OP                 "&&"
%token T_OR_OP                  "||"
%token T_NOT_EQ_OP              "<>"
%token T_LESS_THAN_OR_EQ_OP     "<="
%token T_GREATER_THAN_OR_EQ_OP  ">="
%token T_NAT_EQ_OP              "=="
%token T_NAT_NOT_EQ_OP          "!="
%token T_ASSIGNMENT_OP          ":="

%token<id> T_ID    
%token T_CONSTRUCTOR_ID
%token<const_char> T_CONST_CHAR 
%token<number> T_CONST_INT 
%token<string_literal> T_STRING_LITERAL

%expect 1

%nonassoc "let" "in"
%left<op> ';'
%nonassoc IF_THEN IF_THEN_ELSE
%nonassoc<op> ":="
%left<op> "||"
%left<op> "&&"
%nonassoc<op> '=' "<>" '>' '<' "<=" ">=" "==" "!="
%left<op> '+' '-'
%left<op> '*' '/' "mod" 
%right<op> "**"
%left<op> UNOP "not" "delete"
%right "->"
%left "ref"
%right "array" "of"
%nonassoc<op> '!'
%nonassoc "new"

%union{
    LetDef* let_def;
    Def* def;
    Par* par;
    Expr* expr;
    TypeVariable* type;
    Block<Expr>* func_expr_list;
    Block<Expr>* expr_comma_list;
    Block<Par>* par_list;
    Block<Def>* def_list;
    Block<LetDef>* letdef_list;
    OpType op;

    std::string* id;
    std::string* string_literal;
    char const_char;
    int number;
    unsigned int dimension_count;
}

%type<let_def> letdef
%type<def> def
%type<par> par
%type<expr> expr func_expr
%type<type> type
%type<dimension_count> asterisk_list
%type<func_expr_list> func_expr_list
%type<expr_comma_list> expr_comma_list
%type<par_list> par_list
%type<def_list> def_list
%type<letdef_list> program letdef_list

%%

program:
    letdef_list { 
            // AST::make_table(); //Make a static symboltable
            $1->add_library_functions();
            if(debug) std::cout << "AST: " << *$1 << std::endl;
            $1->infer();
            $1->unify();
            if(debug) std::cout << "AST: " << *$1 << std::endl;
            $1->close_library_function_scope();
            delete $1;
        }  
;

letdef_list:
    %empty              { $$ = new Block<LetDef>(BlockType::LetDef); }
|   letdef_list letdef  { $1->append($2); }
;

letdef:
    "let" "rec" def def_list    { $4->insert($4->begin(), $3); $$ = new LetDef($4, LetType::Rec); }
|   "let" def def_list          { $3->insert($3->begin(), $2); $$ = new LetDef($3, LetType::NoRec); }
;

def_list:
    %empty              { $$ = new Block<Def>(BlockType::Def); }
|   def_list "and" def  { $1->append($3); }
;

def:
    T_ID '=' expr                                           { $$ = new ConstDef($1, $3); }
|   T_ID ':' type '=' expr                                  { $$ = new ConstDef($1, std::make_shared<TypeVariable>(*$3), $5); }
|   T_ID par par_list ':' type '=' expr                     { $3->insert($3->begin(), $2); $$ = new FunctionDef($1, $3, $7, std::make_shared<TypeVariable>(*$5)); }
|   T_ID par par_list '=' expr                              { $3->insert($3->begin(), $2); $$ = new FunctionDef($1, $3, $5); }
|   "mutable" T_ID                                          { $$ = new VarDef($2); }
|   "mutable" T_ID ':' type                                 { $$ = new VarDef($2, std::make_shared<TypeVariable>(*$4)); }
|   "mutable" T_ID '[' expr expr_comma_list ']'             { $5->insert($5->begin(), $4); $$ = new ArrayDef($2, $5); }
|   "mutable" T_ID '[' expr expr_comma_list ']' ':' type    { $5->insert($5->begin(), $4); $$ = new ArrayDef($2, $5, std::make_shared<TypeVariable>(*$8)); }
;

par_list:
    %empty          { $$ = new Block<Par>(BlockType::Par); }
|   par_list par    { $1->append($2); }
;

par:
    T_ID                    { $$ = new Par($1); }
|   '(' T_ID ':' type ')'   { $$ = new Par($2, std::make_shared<TypeVariable>(*$4)); }
;

expr_comma_list:
    %empty                      { $$ = new Block<Expr>(BlockType::ExprComma); }
|   expr_comma_list ',' expr    { $1->append($3); }
;

expr:
    func_expr                                               { $$ = $1; }
|   T_ID func_expr func_expr_list                           { $3->insert($3->begin(), $2); $$ = new FunctionCall($1, $3); }
|   "dim" T_ID                                              { $$ = new Dim($2); }
|   "dim" T_CONST_INT T_ID                                  { $$ = new Dim($3, $2); }
|   "new" type                                              { $$ = new New(std::make_shared<TypeVariable>(*$2)); }
|   "delete" expr                                           { $$ = new Delete($2); }
|   letdef "in" expr                                        { $$ = new LetIn($1, $3); }
|   "begin" expr "end"                                      { $$ = $2; }
|   "if" expr "then" expr               %prec IF_THEN       { $$ = new If($2, $4); }
|   "if" expr "then" expr "else" expr   %prec IF_THEN_ELSE  { $$ = new If($2, $4, $6); }
|   "while" expr "do" expr "done"                           { $$ = new While($2, $4); }
|   "for" T_ID '=' expr "to" expr "do" expr "done"          { $$ = new ForTo($2, $4, $6, $8); }
|   "for" T_ID '=' expr "downto" expr "do" expr "done"      { $$ = new ForDownTo($2, $4, $6, $8); }
|   '+' expr    %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   '-' expr    %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   "not" expr                                              { $$ = new UnOp($2, $1); }
|   expr '+' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '-' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '*' expr                                           { $$ = new BinOp($1, $3, $2); }              
|   expr '/' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '=' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr "<>" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr '<' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '>' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr "<=" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr ">=" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "==" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "!=" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "&&" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "||" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr ';' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr ":=" expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "mod" expr                                         { $$ = new BinOp($1, $3, $2); }
;

func_expr:
   '!' func_expr                                            { $$ = new UnOp($2, $1); }
|   '(' expr ')'                                            { $$ = $2; }
|   '(' ')'                                                 { $$ = new Unit(); }
|   T_ID                                                    { $$ = new Id($1); }
|   T_CONST_INT                                             { $$ = new Int($1); }                                         
|   T_CONST_CHAR                                            { $$ = new Char($1); }
|   T_STRING_LITERAL                                        { $$ = new String($1); }
|   "true"                                                  { $$ = new Bool(true); }
|   "false"                                                 { $$ = new Bool(false); }
|   T_ID '[' expr expr_comma_list ']'                       { $4->insert($4->begin(), $3); $$ = new ArrayIndex($1, $4); }


func_expr_list:          
    %empty                                                  { $$ = new Block<Expr>(BlockType::Expr); }
|   func_expr_list func_expr                                { $1->append($2); }

type:
    "unit"                                                  { $$ = new TypeVariable(TypeTag::Unit); }
|   "int"                                                   { $$ = new TypeVariable(TypeTag::Int); }
|   "char"                                                  { $$ = new TypeVariable(TypeTag::Char); }
|   "bool"                                                  { $$ = new TypeVariable(TypeTag::Bool); }
|   '(' type ')'                                            { $$ = $2; }
|   type "->" type                                          { $$ = new TypeVariable(TypeTag::Function, std::make_shared<TypeVariable>(*$1), std::make_shared<TypeVariable>(*$3)); }
|   type "ref"                                              { $$ = new TypeVariable(TypeTag::Reference, std::make_shared<TypeVariable>(*$1)); }
|   "array" "of" type                                       { $$ = new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(*$3), 1, DimType::Exact); }
|   "array" '[' asterisk_list ']' "of" type                 { $$ = new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(*$6), $3, DimType::Exact); }
/* |   T_ID                                            { $$ = }  propably not possible due to no user defined types*/
;

/* ugly replace block? */
asterisk_list:
    '*'                     { $$ = 1; }
|   asterisk_list ',' '*'   { $$ = 1 + $1; }
;

%%

int main(){
    int result = yyparse();
    if(result == 0) 
        printf("Success.\n");
    return result;
}

void yyerror(const char* msg){
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}
