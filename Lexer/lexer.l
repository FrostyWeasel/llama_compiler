%{
#define T_EOF           0
#define T_AND           1000       
#define T_ARRAY         1001
#define T_BEGIN         1002
#define T_BOOL          1003
#define T_CHAR          1004
#define T_DELETE        1005
#define T_DIM           1006
#define T_DO            1007
#define T_DONE          1008
#define T_DOWNTO        1009
#define T_ELSE          1010
#define T_END           1011
#define T_FALSE         1012
#define T_FOR           1013
#define T_IF            1014
#define T_IN            1015
#define T_INT           1016 
#define T_LET           1017
#define T_MATCH         1018
#define T_MOD           1019
#define T_MUTABLE       1020
#define T_NEW           1021
#define T_NOT           1022
#define T_OF            1023
#define T_REC           1024
#define T_REF           1025
#define T_THEN          1026
#define T_TO            1027
#define T_TRUE          1028
#define T_TYPE          1029
#define T_UNIT          1030
#define T_WHILE         1031
#define T_WITH          1032
#define T_TYPE_ARROW_OP 1033
#define T_AND_OP        1034
#define T_OR_OP         1035
#define T_NOT_EQ_OP     1036
#define T_LESS_THAN_OR_EQ_OP 1037
#define T_GREATER_THAN_OR_EQ_OP 1038
#define T_NAT_EQ_OP     1039
#define T_NAT_NOT_EQ_OP 1040
#define T_ASSIGNMENT_OP 1041
#define T_ID            1042
#define T_CONSTRUCTOR_ID 1043
#define T_CONST_CHAR    1044
#define T_CONST_INT     1045
#define T_STRING_CONST  1046

void ERROR();
%}

L [a-zA-Z]
L_lower [a-z]
L_upper [A-Z]
D [0-9]
W [ \t\n\r]

%option 8bit
%option noyywrap
%option yylineno

%%
"and"		{ return T_AND; }
"array"		{ return T_ARRAY; }
"begin"		{ return T_BEGIN; }
"bool"		{ return T_BOOL; }
"char"		{ return T_CHAR; }
"delete"	{ return T_DELETE; }
"dim"		{ return T_DIM; }
"do"		{ return T_DO; }
"done"		{ return T_DONE; }
"downto"	{ return T_DOWNTO; }
"else"		{ return T_ELSE; }
"end"		{ return T_END; }
"false"		{ return T_FALSE; }
"for"		{ return T_FOR; }
"if"		{ return T_IF; }
"in"		{ return T_IN; }
"int"		{ return T_INT; }        
"let"		{ return T_LET; }
"match"		{ return T_MATCH; }
"mod"		{ return T_MOD; }
"mutable"	{ return T_MUTABLE; }
"new"		{ return T_NEW; }
"not"		{ return T_NOT; }
"of"		{ return T_OF; }
"rec"		{ return T_REC; }
"ref"		{ return T_REF; }
"then"		{ return T_THEN; }
"to"		{ return T_TO; }
"true"		{ return T_TRUE; }
"type"		{ return T_TYPE; }
"unit"		{ return T_UNIT; }
"while"		{ return T_WHILE; }
"with"		{ return T_WITH; }

[\=\|\+\-\*\/\!\;\<\>\(\)\[\]\,\:]		{ return yytext[0]; }

"->"		{ return T_TYPE_ARROW_OP; }
"&&"		{ return T_AND_OP; }
"||"		{ return T_OR_OP; }
"<>"		{ return T_NOT_EQ_OP; }
"<="		{ return T_LESS_THAN_OR_EQ_OP; }
">="		{ return T_GREATER_THAN_OR_EQ_OP; }
"=="		{ return T_NAT_EQ_OP; }
"!="		{ return T_NAT_NOT_EQ_OP; }
":="		{ return T_ASSIGNMENT_OP; }

{L_lower}({L}|{D}|_)*       { return T_ID; }
{L_upper}({L}|{D}|_)*       { return T_CONSTRUCTOR_ID; }


{D}+                { return T_CONST_INT; }
\"[^\"\n\r]*\"        { return T_STRING_CONST; }
\'([^\'\"\\]|\\n|\\t|\\r|\\0|\\\\|\\\'|\\\"|\\x[{D}A-Fa-f][{D}A-Fa-f])\'      { return T_CONST_CHAR; }

{W}+        { /* nothing */ }   /*White space*/

--.*\n      { /* nothing */ }   /*One line comment*/

"(*"([^*]+|\*+[^*)])*\*+")"     { /* nothing */ }

.       { ERROR(); }

%%

int main(){
    int token;

    do{
        token = yylex();
        printf("token = %d, lexeme = \"%s\", line = %d\n", token, yytext, yylineno);
    }while(token != T_EOF);

    return 0;
}

void ERROR(){
    fprintf(stderr, "Illegal character: \"%c\" (ASCII: %d) at line %d\n", yytext[0], yytext[0], yylineno);
    exit(1);
}
