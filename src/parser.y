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
%token T_TYPE_ARROW_OP          
%token T_AND_OP                 
%token T_OR_OP                  
%token T_NOT_EQ_OP              
%token T_LESS_THAN_OR_EQ_OP 
%token T_GREATER_THAN_OR_EQ_OP 
%token T_NAT_EQ_OP     
%token T_NAT_NOT_EQ_OP 
%token T_ASSIGNMENT_OP 
%token T_ID            
%token T_CONSTRUCTOR_ID
%token T_CONST_CHAR    
%token T_CONST_INT     
%token T_STRING_LITERAL

%left '+' '-'
%left '*' '/'

%%

program:
    /* empty */
|   letdef program
;

letdef:
    "let" def
;

def:
    T_ID '=' expr
;

expr:
    "while" expr "do" expr "done"
;

%%

int main(){
    int result = yyparse();
    if(result == 0) 
        printf("Success.\n");
    return result;
}