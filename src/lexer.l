%{
#define T_EOF           0
%}

L [a-zA-Z]
L_lower [a-z]
L_upper [A-Z]
D [0-9]
W [ \t\n\r]

%option 8bit
%option noyywrap
%option yylineno

/* %x STRING_LITERAL */
%x MULTILINE_COMMENT

%%

    int comment_nesting = 0;

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
"type"		{ fprintf(stderr, "User defined types not currently supported\n"); exit(1); }
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


{D}+    { return T_CONST_INT; }
\'([^\'\"\\]|\\n|\\t|\\r|\\0|\\\\|\\\'|\\\"|\\x[{D}A-Fa-f][{D}A-Fa-f])\'      { return T_CONST_CHAR; }

\"([^\n\r\"]|\\\")*\"   { return T_STRING_LITERAL; }

{W}+        { /* nothing */ }   /*White space*/

--.*\n      { /* nothing */ }   /*One line comment*/

"(*"                        { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"(*"     { ++comment_nesting; }
<MULTILINE_COMMENT>"*)"     { if (comment_nesting != 0) --comment_nesting; else BEGIN(INITIAL); }
<MULTILINE_COMMENT>"*"      { /* nothing */ }
<MULTILINE_COMMENT>"("      { /* nothing */ } 
<MULTILINE_COMMENT>[^\(\*]+ { /* nothing */ }
<MULTILINE_COMMENT><<EOF>>  { fprintf(stderr, "EOF reached with open comment\n"); exit(1);}

.       { fprintf(stderr, "Illegal character: \"%c\" (ASCII: %d) at line %d\n", yytext[0], yytext[0], yylineno); exit(1); }

%%
