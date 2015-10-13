%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	 printSymTab();

/* TODO */
#define INT		10
#define FLOAT 		11 
#define OP_ASSIGN 	12 
#define OP_OR 		13
#define OP_AND 		14
#define OP_NOT 		15
#define MK_LPAREN 	16 
#define MK_RPAREN 	17

#define COMMENT 20

#define ERROR 		100 

%}

letter   [A-Za-z]
digit    [0-9]
/* TODO Reserved words: return typedef if else int float for void while */
ID	 {letter}({letter}|{digit}|"_")*
WS	 [ \t]+
Int_constant {digit}+

/*
TODO
b. Floating point literals: The same as defined in ANSI C.1
c. String literals: String literal consist of a sequence of characters
between double quotes (i.e. “ and “).
*/
Float_constant {digit}+.?{digit}+
/* http://stackoverflow.com/questions/2039795/regular-expression-for-a-string-literal-in-flex-lex */
String_constant \"(\\.|[^"])*\"
comment "/*"([^*]|\*+[^*/])*\*+"/"

/* ok */
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
{Int_constant}  { return INT;  }
{Float_constant} { return FLOAT; }
{ID}            { 
			ptr = lookup(yytext);
			if (ptr == NULL)
			     insertID(yytext);	
			else 
			     ptr->counter++;
		}


/* TODO */
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
{error}         printf("ERR \n");/* return ERROR; */

%%

main(int argc, char **argv)
{
 argc--; ++argv;
   if (argc > 0)
      yyin = fopen(argv[0], "r");
   else
      yyin = stdin;
   yylex();
   printSymTab();
}

