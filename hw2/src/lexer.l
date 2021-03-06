%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
int haveComment = 0;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	 printSymTab();
%}

/*	example		*/
letter		[A-Za-z]
digit		[0-9]
ID		{letter}({letter}|{digit}|"_")*
WS		[ \t]+

/*	constants	*/
Int_constant	{digit}+
Fraction	{digit}+\.{digit}*|{Int_constant}
Float_constant	{Fraction}|{Fraction}[eE]-?{Int_constant}
String_constant	\"("\""|[^\"])*\"

/*	Reserve Word	*/
RWInt		"int"
RWFloat		"float"
RWreturn	"return"
RWif		"if"
RWelse		"else"
RWfor		"for"
RWvoid		"void"
RWwhile		"while"

/*	comments	*/
Comment_block	\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/

/*	Arithmetic Operators	*/

OP_assign       "="
OP_plus		"+"
OP_minus	"-"
OP_mul		"*"
OP_div		"/"

/*	Relational Operators	*/
OP_less		"<"
OP_greater	">"
OP_notLess	">="
OP_notGreater	"<="
OP_equal	"=="
OP_notEqual	"!="

/*	Logical Operators	*/
OP_or  		"||"
OP_and		"&&"
OP_not		"!"


/*	Separators	*/
newline  	\n
DL_lparen	"("
DL_rparen 	")"
DL_lbracket	"["
DL_rbracket	"]"
DL_lbrace 	"{"
DL_rbrace 	"}"
DL_comma  	","
DL_semicol 	";"
DL_dot  	"."

/*	Error	*/
error    	.

%%

{WS}			{}
{RWInt}			{}
{RWFloat}		{}
{RWreturn}		{}
{RWif}			{}
{RWelse}		{}
{RWfor}			{}
{RWwhile}		{}
{RWvoid}		{}

{Comment_block}		{ 
				printf("%s\n", yytext);
				haveComment = 1;
			}

{ID}            	{ 
				ptr = lookup(yytext);
				if (ptr == NULL)
				     insertID(yytext);	
				else 
				     ptr->counter++;
			}
{Int_constant}		{}
{Float_constant}	{}
{String_constant}	{}

{OP_assign}     	{}
{OP_plus}	     	{}
{OP_minus}     		{}
{OP_mul}     		{}
{OP_div}     		{}

{OP_less}		{}
{OP_greater}		{}
{OP_notLess}		{}
{OP_notGreater}		{}
{OP_equal}		{}
{OP_notEqual}		{}

{OP_and}     		{}
{OP_or}        		{}
{OP_not}		{}

{DL_lparen}    		{}
{DL_rparen}     	{}
{DL_lbracket}		{}
{DL_rbracket}		{}
{DL_lbrace}     	{}
{DL_rbrace}     	{}
{DL_comma}      	{}
{DL_semicol}    	{}
{newline}       	{ linenumber += 1; }
{error}         	{
				printf("ERR: %s\n", yytext);/* return ERROR; */
				exit(1);
			}


%%

main(int argc, char **argv)
{
	argc--; ++argv;
	if (argc > 0)
		yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
	yylex();
	if(haveComment)
		printf("\n");
	printf("Frequency of identifiers:\n");
	sort();
	if(head)
		printFreqOfSymb(head);
//	printSymTab();
}

