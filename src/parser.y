%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "block.hpp"
#include "constructor.hpp"
#include "pattern.hpp"
#include "clause.hpp"
#include "int_pattern.hpp"
#include "float_pattern.hpp"
#include "char_pattern.hpp"
#include "bool_pattern.hpp"
#include "id_pattern.hpp"
#include "match.hpp"
#include "definition.hpp"
#include "type_def.hpp"
#include "constructor_pattern.hpp"
#include "constructor_call.hpp"
#include "t_def.hpp"
#include "includes.hpp"
#include "lexer.hpp"
#include <memory>
#include <vector>
#include <unistd.h>
#include <cstdio>

std::vector<std::string*> str_to_delete;
constexpr bool debug = false;

std::string compiler_path;
std::string input_filename;

bool intermediate_flag;
bool final_flag;
bool optimizations_flag;

extern FILE* yyin;
extern int yylineno;

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
%token T_FLOAT                  "float"
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
%token T_PLUS_FLOAT             "+."
%token T_MINUS_FLOAT            "-."  
%token T_TIMES_FLOAT            "*."  
%token T_DIVIDE_FLOAT           "/."  
%token T_EXPONENTIATE_FLOAT     "**"      

%token<id> T_ID    
%token<id> T_CONSTRUCTOR_ID
%token<const_char> T_CONST_CHAR 
%token<number> T_CONST_INT
%token<float_value> T_CONST_FLOAT 
%token<string_literal> T_STRING_LITERAL

%expect 1

%nonassoc "let" "in"
%left<op> ';'
%nonassoc IF_THEN IF_THEN_ELSE
%nonassoc<op> ":="
%left<op> "||"
%left<op> "&&"
%nonassoc<op> '=' "<>" '>' '<' "<=" ">=" "==" "!="
%left<op> '+' '-' "+." "-."
%left<op> '*' '/' "mod" "*." "/." 
%right<op> "**"
%left<op> UNOP "not" "delete"
%nonassoc<op> '!'
%nonassoc "new"

%right "->"
%right "of"
%left "ref"

%union{
    LetDef* let_def;
    TypeDef* type_def;
    Def* def;
    TDef* t_def;
    Constructor* constructor;
    Par* par;
    Expr* expr;
    TypeVariable* type;
    Pattern* pattern;
    Clause* clause;
    Block<Expr>* func_expr_list;
    Block<Expr>* expr_comma_list;
    Block<Par>* par_list;
    Block<Def>* def_list;
    Block<TDef>* t_def_list;
    Block<Definition>* definition_list;
    std::vector<std::shared_ptr<TypeVariable>>* type_list;
    Block<Constructor>* constructor_list;
    Block<Pattern>* pattern_list;
    Block<Clause>* clause_list;
    OpType op;

    std::string* id;
    std::string* string_literal;
    char const_char;
    int number;
    double float_value;
    unsigned int dimension_count;
}

%type<definition_list> program definition_list

%type<let_def> letdef
%type<type_def> typedef

%type<def> def
%type<t_def> tdef

%type<constructor> constr

%type<par> par
%type<expr> expr func_expr
%type<type> type
%type<pattern> pattern_high pattern
%type<clause> clause
%type<dimension_count> asterisk_list

%type<t_def_list> tdef_list
%type<constructor_list> constr_list
%type<type_list> type_list

%type<pattern_list> pattern_high_list
%type<clause_list> clause_list

%type<func_expr_list> func_expr_list
%type<expr_comma_list> expr_comma_list
%type<par_list> par_list
%type<def_list> def_list

%%

program:
    definition_list { 
            $1->add_library_functions();
            if(debug) std::cout << "AST: " << *$1 << std::endl;
            
            $1->infer();
            $1->unify();
            $1->clear_inference_structures();
            $1->close_all_program_scopes();

            $1->sem();
            $1->bind_to_default_types();
            if(debug) std::cout << "AST: " << *$1 << std::endl;
            $1->close_all_program_scopes();

            $1->llvm_compile_and_dump(optimizations_flag, intermediate_flag, final_flag, input_filename, compiler_path);

            $1->close_all_program_scopes();
            $1->close_library_function_scope();
            
            delete $1;
        }  
;

definition_list:
    %empty                      { $$ = new Block<Definition>(BlockType::Definition); }
|   definition_list letdef      { $1->append($2); }
|   definition_list typedef     { $1->append($2); }
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
    T_ID '=' expr                                           { $$ = new ConstDef($1, $3); str_to_delete.push_back($1); }
|   T_ID ':' type '=' expr                                  { $$ = new ConstDef($1, std::shared_ptr<TypeVariable>($3), $5); str_to_delete.push_back($1); }
|   T_ID par par_list ':' type '=' expr                     { $3->insert($3->begin(), $2); $$ = new FunctionDef($1, $3, $7, std::shared_ptr<TypeVariable>($5)); str_to_delete.push_back($1); }
|   T_ID par par_list '=' expr                              { $3->insert($3->begin(), $2); $$ = new FunctionDef($1, $3, $5); str_to_delete.push_back($1); }
|   "mutable" T_ID                                          { $$ = new VarDef($2); str_to_delete.push_back($2); }
|   "mutable" T_ID ':' type                                 { $$ = new VarDef($2, std::shared_ptr<TypeVariable>($4)); str_to_delete.push_back($2); }
|   "mutable" T_ID '[' expr expr_comma_list ']'             { $5->insert($5->begin(), $4); $$ = new ArrayDef($2, $5); str_to_delete.push_back($2); }
|   "mutable" T_ID '[' expr expr_comma_list ']' ':' type    { $5->insert($5->begin(), $4); $$ = new ArrayDef($2, $5, std::shared_ptr<TypeVariable>($8)); str_to_delete.push_back($2); }
;

typedef:
    "type" tdef tdef_list   { $3->insert($3->begin(), $2); $$ = new TypeDef($3); }
;

tdef_list:
    %empty                  { $$ = new Block<TDef>(BlockType::TDef); }
|   tdef_list "and" tdef    { $1->append($3); }
;

tdef:
    T_ID '=' constr constr_list     { $4->insert($4->begin(), $3); $$ = new TDef($1, $4); }
;

constr_list:
    %empty                  { $$ = new Block<Constructor>(BlockType::Constructor); }
|   constr_list '|' constr  { $1->append($3); }
;

constr:
    T_CONSTRUCTOR_ID                        { $$ = new Constructor($1); }
|   T_CONSTRUCTOR_ID "of" type type_list    { $4->insert($4->begin(), std::shared_ptr<TypeVariable>($3)); $$ = new Constructor($1, $4); }
;

par_list:
    %empty          { $$ = new Block<Par>(BlockType::Par); }
|   par_list par    { $1->append($2); }
;

par:
    T_ID                    { $$ = new Par($1); str_to_delete.push_back($1); }
|   '(' T_ID ':' type ')'   { $$ = new Par($2, std::shared_ptr<TypeVariable>($4)); str_to_delete.push_back($2); }
;

expr_comma_list:
    %empty                      { $$ = new Block<Expr>(BlockType::ExprComma); }
|   expr_comma_list ',' expr    { $1->append($3); }
;

expr:
    T_ID func_expr func_expr_list                           { $3->insert($3->begin(), $2); $$ = new FunctionCall($1, $3); str_to_delete.push_back($1); }
|   T_CONSTRUCTOR_ID func_expr func_expr_list               { $3->insert($3->begin(), $2); $$ = new ConstructorCall($1, $3); str_to_delete.push_back($1); }
|   "dim" T_ID                                              { $$ = new Dim($2); str_to_delete.push_back($2); }
|   "dim" T_CONST_INT T_ID                                  { $$ = new Dim($3, $2); str_to_delete.push_back($3); }
|   "new" type                                              { $$ = new New(std::shared_ptr<TypeVariable>($2)); }
|   "delete" expr                                           { $$ = new Delete($2); }
|   letdef "in" expr                                        { $$ = new LetIn($1, $3); }
|   "begin" expr "end"                                      { $$ = $2; }
|   "if" expr "then" expr               %prec IF_THEN       { $$ = new If($2, $4); }
|   "if" expr "then" expr "else" expr   %prec IF_THEN_ELSE  { $$ = new If($2, $4, $6); }
|   "while" expr "do" expr "done"                           { $$ = new While($2, $4); }
|   "for" T_ID '=' expr "to" expr "do" expr "done"          { $$ = new ForTo($2, $4, $6, $8); str_to_delete.push_back($2); }
|   "for" T_ID '=' expr "downto" expr "do" expr "done"      { $$ = new ForDownTo($2, $4, $6, $8); str_to_delete.push_back($2); }
|   '+' expr    %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   '-' expr    %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   "+." expr   %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   "-." expr   %prec UNOP                                  { $$ = new UnOp($2, $1); }
|   "not" expr                                              { $$ = new UnOp($2, $1); }
|   expr '+' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '-' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr '*' expr                                           { $$ = new BinOp($1, $3, $2); }              
|   expr '/' expr                                           { $$ = new BinOp($1, $3, $2); }
|   expr "+." expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "-." expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "*." expr                                          { $$ = new BinOp($1, $3, $2); }              
|   expr "/." expr                                          { $$ = new BinOp($1, $3, $2); }
|   expr "**" expr                                          { $$ = new BinOp($1, $3, $2); }
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
|   "match" expr "with" clause clause_list "end"            { $5->insert($5->begin(), $4); $$ = new Match($2, $5); }  
|   func_expr                                               { $$ = $1; }
;

func_expr:
    '!' func_expr                                           { $$ = new UnOp($2, $1); }
|   '(' expr ')'                                            { $$ = $2; }
|   '(' ')'                                                 { $$ = new Unit(); }
|   T_ID                                                    { $$ = new Id($1); str_to_delete.push_back($1); }
|   T_CONSTRUCTOR_ID                                        { $$ = new ConstructorCall($1); str_to_delete.push_back($1); }
|   T_CONST_INT                                             { $$ = new Int($1); }
|   T_CONST_FLOAT                                           { $$ = new Float($1); }                                        
|   T_CONST_CHAR                                            { $$ = new Char($1); }
|   T_STRING_LITERAL                                        { $$ = new String($1); str_to_delete.push_back($1); }
|   "true"                                                  { $$ = new Bool(true); }
|   "false"                                                 { $$ = new Bool(false); }
|   T_ID '[' expr expr_comma_list ']'                       { $4->insert($4->begin(), $3); $$ = new ArrayIndex($1, $4); str_to_delete.push_back($1); }
;

func_expr_list:          
    %empty                                                  { $$ = new Block<Expr>(BlockType::Expr); }
|   func_expr_list func_expr                                { $1->append($2); }
;

type_list:
    %empty                                                  { $$ = new std::vector<std::shared_ptr<TypeVariable>>(); }
|   type_list type                                          { $1->push_back(std::shared_ptr<TypeVariable>($2)); }
;

type:
    "unit"                                                  { $$ = new TypeVariable(TypeTag::Unit); }
|   "int"                                                   { $$ = new TypeVariable(TypeTag::Int); }
|   "char"                                                  { $$ = new TypeVariable(TypeTag::Char); }
|   "bool"                                                  { $$ = new TypeVariable(TypeTag::Bool); }
|   "float"                                                 { $$ = new TypeVariable(TypeTag::Float); }
|   '(' type ')'                                            { $$ = $2; }
|   type "->" type                                          { $$ = new TypeVariable(TypeTag::Function, std::shared_ptr<TypeVariable>($1), std::shared_ptr<TypeVariable>($3), FunctionTypeTag::Actual); }
|   type "ref"                                              { $$ = new TypeVariable(TypeTag::Reference, std::shared_ptr<TypeVariable>($1)); }
|   "array" "of" type                                       { $$ = new TypeVariable(TypeTag::Array, std::shared_ptr<TypeVariable>($3), 1, DimType::Exact); }
|   "array" '[' asterisk_list ']' "of" type                 { $$ = new TypeVariable(TypeTag::Array, std::shared_ptr<TypeVariable>($6), $3, DimType::Exact); }
|   T_ID                                                    { $$ = new TypeVariable(TypeTag::UserType, $1); }
;

asterisk_list:
    '*'                     { $$ = 1; }
|   asterisk_list ',' '*'   { $$ = 1 + $1; }
;

clause_list:
    %empty                      { $$ = new Block<Clause>(BlockType::Clause); }
|   clause_list '|' clause      { $1->append($3); }
;

clause:
    pattern "->" expr           { $$ = new Clause($1, $3); }
;

pattern:
    pattern_high                        { $$ = $1; }                     
|   T_CONSTRUCTOR_ID pattern_high_list  { $$ = new ConstructorPattern($1, $2); }
;

pattern_high_list:
    %empty                              { $$ = new Block<Pattern>(BlockType::Pattern); }
|   pattern_high_list pattern_high      { $1->append($2); }
;

pattern_high:
    '+' T_CONST_INT %prec UNOP          { $$ = new IntPattern($2);      }
|   '-' T_CONST_INT %prec UNOP          { $$ = new IntPattern(-$2);     }
|   T_CONST_INT                         { $$ = new IntPattern($1);      }
|   "+." T_CONST_FLOAT  %prec UNOP      { $$ = new FloatPattern($2);    }
|   "-." T_CONST_FLOAT  %prec UNOP      { $$ = new FloatPattern(-$2);   }
|   T_CONST_FLOAT                       { $$ = new FloatPattern($1);    }
|   T_CONST_CHAR                        { $$ = new CharPattern($1);     }
|   "true"                              { $$ = new BoolPattern(true);   }
|   "false"                             { $$ = new BoolPattern(false);  }
|   T_ID                                { $$ = new IdPattern($1);       }
|   '(' pattern ')'                     { $$ = $2;                      }
;

%%

std::string get_file_name(std::string file_path, char seperator = '/') {
    auto dot_position = file_path.rfind('.');
    auto sep_position = file_path.rfind(seperator);

    if(sep_position != std::string::npos) {
        return file_path.substr(0, dot_position);
    }
    return "a";
}

void yyerror(const char* msg){
    fprintf(stderr, "Error in line %i: %s\n", yylineno, msg);
    exit(1);
}

int main(int argc, char** argv) {
    int option;
	compiler_path = argv[0];

    //If no option was given output help and exit
	if (argc == 1) {
		std::cerr <<
			"OVERVIEW: llama compiler\n"
            "USAGE: llamac [OPTIONS] [FILE]\n"
            "OPTIONS:\n"
			"-O:    enable optimizations\n"
			"-i:    the input must be given on standard input and the intermediate code will be printed on standard output\n"
			"-f:    the input must be given on standard input and the final code will be printed on standard output\n"
			"\n"
			"If no -i or -f options are selected the input file must be given as an argument\n";
		exit(1);
	}

	optimizations_flag = intermediate_flag = final_flag = false;
	while ((option = getopt(argc, argv, "Ofi")) != -1) {
		switch(option) {
			case 'O':
				optimizations_flag = true;
				break;
			case 'f':
				final_flag = true;
				break;
			case 'i':
				intermediate_flag = true;
				break;
			case '?':
				std::cerr << "Enter ./llamac to see usage information\n";
				exit(1);
			default:
				break;
		}
	}

	if(intermediate_flag || final_flag)
		yyin = stdin;
	else {
		yyin = fopen(argv[optind], "r");
		input_filename = get_file_name(std::string(argv[optind]));
	}

    int result = yyparse();

    //delete all allocated strings
    for(auto string_ptr: str_to_delete) {
        delete string_ptr;
    }

    return result;
}