%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
int IDcount;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	 printSymTab();

/* TODO */
#define INT		10
#define FLOAT 		11
#define STRING 		99
#define OP_ASSIGN 	12 
#define OP_OR 		13
#define OP_AND 		14
#define OP_NOT 		15
#define OP_GEQ 1321
#define OP_LEQ 123123
#define OP_NEQ 12312
#define OP_EQEQ 1231
#define OP_LESS 3131
#define OP_GREATER 123123
#define OP_ADD 123123
#define OP_MINUS 123123
#define OP_DIV 12313
#define OP_MUL 1231

#define MK_LPAREN 	16 
#define MK_RPAREN 	17
#define MK_LBRACE       211
#define MK_RBRACE        122
#define MK_LBRACKET 232
#define MK_RBRACKET 123
#define MK_COMMA  321
#define MK_SEMICOL 321
#define MK_DOT  321

#define NEWLINE  123112321

#define COMMENT 20

#define ERROR 		100 

/* http://stackoverflow.com/questions/2039795/regular-expression-for-a-string-literal-in-flex-lex */
/* http://stackoverflow.com/questions/13569827/complete-comments-regex-for-lex */

%}

letter   [A-Za-z]
digit    [0-9]
ID	 {letter}({letter}|{digit}|"_")*
WS	 [ \t]+
Int_constant {digit}+
Float_constant {digit}+(e[+-]?{digit}+)|({digit}+(\.{digit}+)(e[+-]?{digit}+)?)|({digit}+)?(\.{digit}+)(e[+-]?{digit}+)?
String_constant \"(\\.|[^"])*\"
comment "/*"([^*]|\*+[^*/])*\*+"/"

OP_geq ">="
OP_leq "<="
OP_neq "!="
OP_eqeq "=="

OP_add "+"
OP_minus "-"
OP_div "/"
OP_mul "*"

OP_less "<"
OP_greater ">"
OP_assign "="
OP_or   "||"
OP_and   "&&"
OP_not   "!"

newline  "\n"

DL_lparen "("
DL_rparen ")"
DL_lbrace "{"
DL_rbrace "}"
DL_lbracket "["
DL_rbracket "]"
DL_comma  ","
DL_semicol ";"
DL_dot  "."

/* Other separators appear here */

error    .

%%

{WS}            {}
{Int_constant}  { printf("int %s\n", yytext);   }
{Float_constant} { printf("float %s\n", yytext);  }
{String_constant} { printf("string %s\n", yytext); }
{comment} { insertComment(yytext);}
{ID}            {
			ptr = lookup(yytext);
			if (ptr == NULL){
                             IDcount++;
                             printf("new id [%s]", yytext);
			     insertID(yytext);
                        }
			else 
			     ptr->counter++;
		}

{OP_geq} /* return OP_ASSIGN; */ 
{OP_leq} /* return OP_ASSIGN; */ 
{OP_neq} /* return OP_ASSIGN; */ 
{OP_eqeq} /* return OP_ASSIGN; */ 
{OP_add}  /* return OP_ASSIGN; */  
{OP_minus} /* return OP_ASSIGN; */ 
{OP_div} /* return OP_ASSIGN; */ 
{OP_mul} /* return OP_ASSIGN; */ 
{OP_less} /* return OP_ASSIGN; */ 
{OP_greater} /* return OP_ASSIGN; */ 
{OP_assign}     /* return OP_ASSIGN; */ 
{OP_or}         /* return OP_OR; */
{OP_and}         /* return OP_AND; */
{OP_not}         /* return OP_NOT; */
{DL_lparen}     /* return MK_LPAREN; */
{DL_rparen}     /* return MK_RPAREN; */
{DL_lbrace}     /* return MK_LBRACE; */
{DL_rbrace}     /* return MK_RBRACE; */
{DL_lbracket}     /* return MK_LBRACKET; */
{DL_rbracket}     /* return MK_RBRACKET; */
{DL_comma}      {}
{DL_semicol}    {}
{newline}       linenumber += 1;
{error}         {printf("ERROR : Unrecognized Token %s\n", yytext);}

%%

main(int argc, char **argv)
{
 argc--; ++argv;
   if (argc > 0)
      yyin = fopen(argv[0], "r");
   else
      yyin = stdin;
   yylex();
   printComment();
   printf("Frequency of identifiers:\n");
   printIDFrequency();
   //printSymTab();
  return 0;
}

