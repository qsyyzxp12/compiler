%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	 printSymTab();
/* You need to define for all tokens in C--, here are some examples */
#define INT		10
#define FLOAT 		11 
#define OP_ASSIGN 	12 
#define OP_OR 		13 
#define MK_LPAREN 	14 
#define MK_RPAREN 	15 
#define ERROR 		100 

%}

letter		[A-Za-z]
digit		[0-9]
ID		{letter}({letter}|{digit}|"_")*
WS		[ \t]+

/*	constants	*/
Int_constant	{digit}+
Float_constant	{digit}+.{digit}+
String_constant	\"([^\"])*\"

/*	Reserve Word	*/

RWInt		"int"
RWFloat		"float"
RWreturn	"return"
RWif		"if"
RWelse		"else"
RWfor		"for"
RWvoid		"void"
RWwhile		"while"

/* You need to define the following RE's 
Float_constant
String_constant
comment
*/

/*Operators*/

OP_assign       "="
OP_plus		"+"
OP_minus	"-"
OP_mul		"*"
OP_div		"/"
OP_or  		"||"
OP_and		"&&"


/* Other separators appear here */

newline  	"\n"
DL_lparen	"("
DL_rparen 	")"
DL_lbrace 	"{"
DL_rbrace 	"}"
DL_comma  	","
DL_semicol 	";"
DL_colon	":"
DL_dot  	"."


error    	.

%%

{WS}            { printf("%s", yytext);}
{RWInt}         { printf("%s",yytext);}
{RWFloat}       { printf("%s",yytext);}
{RWreturn}	{ printf("%s",yytext);}
{RWif}		{ printf("%s", yytext);}
{RWelse}	{ printf("%s", yytext);}
{RWfor}		{ printf("%s", yytext);}
{RWwhile}	{ printf("%s", yytext);}
{RWvoid}	{ printf("%s", yytext);}
{ID}            { 
		  	printf("%s",yytext);;
/*			ptr = lookup(yytext);
			if (ptr == NULL)
			     insertID(yytext);	
			else 
			     ptr->counter++;
*/		}
{Int_constant}		{ printf("%s", yytext);}
{Float_constant}	{ printf("%s", yytext);}
{String_constant}	{ printf("%s", yytext);}

{OP_assign}     	{ printf("%s", yytext);}
{OP_plus}	     	{ printf("%s", yytext);}
{OP_minus}     		{ printf("%s", yytext);}
{OP_mul}     		{ printf("%s", yytext);}
{OP_div}     		{ printf("%s", yytext);}
{OP_and}     		{ printf("%s", yytext);}
{OP_or}        		{ printf("%s", yytext);}
{DL_lparen}    		{ printf("%s", yytext);}
{DL_rparen}     	{ printf("%s", yytext);}
{DL_lbrace}     	{ printf("%s", yytext);}
{DL_rbrace}     	{ printf("%s", yytext);}
{DL_comma}      	{ printf("%s", yytext);}
{DL_colon}		{ printf("%s", yytext);}
{DL_semicol}    	{ printf("%s", yytext);}
{newline}       	{ 
				linenumber += 1;
				printf("%s", yytext);
			}
{error}         	printf("ERR: %s\n", yytext);/* return ERROR; */


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

