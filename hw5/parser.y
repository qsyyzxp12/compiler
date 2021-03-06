/* ===== Definition Section ===== */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
#include "symbolTable.h"
int linenumber = 1;
AST_NODE *prog;

extern int g_anyErrorOccur;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;

    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;
}

%}



%union{
	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;
};

%token <lexeme>ID
%token <const1>CONST
%token VOID
%token INT
%token FLOAT
%token IF
%token ELSE
%token WHILE
%token FOR
%token TYPEDEF
%token OP_ASSIGN
%token OP_OR
%token OP_AND
%token OP_NOT
%token OP_EQ
%token OP_NE
%token OP_GT
%token OP_LT
%token OP_GE
%token OP_LE
%token OP_PLUS
%token OP_MINUS
%token OP_TIMES
%token OP_DIVIDE
%token MK_LB
%token MK_RB
%token MK_LPAREN
%token MK_RPAREN
%token MK_LBRACE
%token MK_RBRACE
%token MK_COMMA
%token MK_SEMICOLON
%token MK_DOT
%token ERROR
%token RETURN

%type <node> program global_decl_list global_decl function_head function_decl block stmt_list decl_list decl var_decl type init_id_list init_id  stmt relop_expr relop_term relop_factor expr term factor var_ref
%type <node> opt_param_list param_list param dim_fn expr_null id_list dim_decl cexpr mcexpr cfactor assign_expr_list test assign_expr rel_op relop_expr_list nonempty_relop_expr_list
%type <node> add_op mul_op dim_list type_decl nonempty_assign_expr_list


%start program

%%

/* ==== Grammar Section ==== */

/* Productions */               /* Semantic actions */
program		: global_decl_list { $$=Allocate(PROGRAM_NODE);  makeChild($$,$1); prog=$$;}
		| { $$=Allocate(PROGRAM_NODE); prog=$$;}
		;

global_decl_list: global_decl_list global_decl
                    {
                        $$ = makeSibling($1, $2);
                    }	
                | global_decl
                    {
                        $$ = $1;
                    }
                ;

global_decl	: decl_list function_decl
                {
                    $$ = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), $1), $2);
                }
            | function_decl
                {
                    $$ = $1;
                }
            ;

function_decl	: function_head MK_LPAREN opt_param_list MK_RPAREN MK_LBRACE block MK_RBRACE
                    {
                        $$ = $1;
                        makeChild($$, $3);
                        makeChild($$, $6);
                    }
                ;
function_head   : type ID
                    {
                        $$ = makeDeclNode(FUNCTION_DECL);
                        makeFamily($$, 2, $1, makeIDNode($2, NORMAL_ID));
                    }
                | VOID ID
                    {
                        $$ = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                        makeFamily($$, 2, voidNode, makeIDNode($2, NORMAL_ID));
                    }
                | ID ID
                    {
                        $$ = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* idNode = makeIDNode($1, NORMAL_ID);
                        makeFamily($$, 2, idNode, makeIDNode($2, NORMAL_ID));
                    }
                ;
opt_param_list  : param_list
                    {
                        $$ = Allocate(PARAM_LIST_NODE);
                        makeChild($$, $1);
                    }
                |
                    {
                        $$ = Allocate(PARAM_LIST_NODE);
                    }
                ;

param_list	: param_list MK_COMMA  param
                {
                    $$ = makeSibling($1, $3);
                }
            | param	
                {
                    $$ = $1;
                }
            ;

param		: type ID
                {
                    $$ = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily($$, 2, $1, makeIDNode($2, NORMAL_ID));
                }
            | ID ID
                {
                    $$ = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily($$, 2, makeIDNode($1, NORMAL_ID), makeIDNode($2, NORMAL_ID));
                }
            | type ID dim_fn
                {
                    $$ = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily($$, 2, $1, makeChild(makeIDNode($2, ARRAY_ID), $3));
                }
            | ID ID dim_fn
                {
                    $$ = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily($$, 2, makeIDNode($1, NORMAL_ID), makeChild(makeIDNode($2, ARRAY_ID), $3));
                }
            ;
dim_fn		: MK_LB expr_null MK_RB
                {
                    $$ = $2;
                }
            | dim_fn MK_LB expr MK_RB
                {
                    $$ = makeSibling($1, $3);
                }
		;

expr_null	:expr
                {
                    $$ = $1;
                }
            |
                {
                    $$ = Allocate(NUL_NODE);
                }
            ;

block           : decl_list stmt_list
                    {
                        $$ = Allocate(BLOCK_NODE);
                        makeFamily($$, 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), $1), makeChild(Allocate(STMT_LIST_NODE), $2));
                    }
                | stmt_list
                    {
                        $$ = Allocate(BLOCK_NODE);
                        makeChild($$, makeChild(Allocate(STMT_LIST_NODE), $1));
                    }
                | decl_list
                    {
                        $$ = Allocate(BLOCK_NODE);
                        makeChild($$, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), $1));
                    }
                |   {
                        $$ = Allocate(BLOCK_NODE);
                    }
                ;

decl_list	: decl_list decl
                {
                    $$ = makeSibling($1, $2);
                }
            | decl
                {
                    $$ = $1;
                }
            ;

decl		: type_decl
                {
                    $$ = $1;
                }
            | var_decl
                {
                    $$ = $1;
                }
            ;

type_decl 	: TYPEDEF type id_list MK_SEMICOLON
                {
                    $$ = makeDeclNode(TYPE_DECL);
                    makeFamily($$, 2, $2, $3);
                }
            | TYPEDEF VOID id_list MK_SEMICOLON
                {
                    $$ = makeDeclNode(TYPE_DECL);
                    AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                    makeFamily($$, 2, voidNode, $3);
                }
            ;

var_decl	: type init_id_list MK_SEMICOLON
                {
                    $$ = makeDeclNode(VARIABLE_DECL);
                    makeFamily($$, 2, $1, $2);
                }
            | ID init_id_list MK_SEMICOLON
                {
                    $$ = makeDeclNode(VARIABLE_DECL);
                    makeFamily($$, 2, makeIDNode($1, NORMAL_ID), $2);
                }
            ;

type		: INT
                {
                    $$ = makeIDNode("int", NORMAL_ID);
                }
            | FLOAT
                {
                    $$ = makeIDNode("float", NORMAL_ID);
                }
            ;

id_list		: ID
                {
                    $$ = makeIDNode($1, NORMAL_ID);
                }
            | id_list MK_COMMA ID
                {
                    $$ = makeSibling($1, makeIDNode($3, NORMAL_ID));
                }
            | id_list MK_COMMA ID dim_decl
                {
                    $$ = makeSibling($1, makeChild(makeIDNode($3, ARRAY_ID), $4));
                }
            | ID dim_decl
                {
                    $$ = makeChild(makeIDNode($1, ARRAY_ID), $2);
                }
		;
dim_decl	: MK_LB cexpr MK_RB
                {
                    $$ = $2;
                }
            | dim_decl MK_LB cexpr MK_RB
                {
                    $$ = makeSibling($1, $3);
                }
            ;
cexpr		: cexpr OP_PLUS mcexpr
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily($$, 2, $1, $3);
                }
            | cexpr OP_MINUS mcexpr
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily($$, 2, $1, $3);
                }
            | mcexpr
                {
                    $$ = $1;
                }
            ;
mcexpr		: mcexpr OP_TIMES cfactor
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily($$, 2, $1, $3);
                }
            | mcexpr OP_DIVIDE cfactor
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily($$, 2, $1, $3);
                }
            | cfactor
                {
                    $$ = $1;
                }
            ;

cfactor:	CONST
                {
                    $$ = Allocate(CONST_VALUE_NODE);
                    $$->semantic_value.const1 = $1;
                }
            |MK_LPAREN cexpr MK_RPAREN
                {
                    $$ = $2;
                }
            ;

init_id_list	: init_id
                    {
                        $$ = $1;
                    }
                | init_id_list MK_COMMA init_id
                    {
                        $$ = makeSibling($1, $3);
                    }
                ;

init_id		: ID
                {
                    $$ = makeIDNode($1, NORMAL_ID);
                }
            | ID dim_decl
                {
                    $$ = makeChild(makeIDNode($1, ARRAY_ID), $2);
                }
            | ID OP_ASSIGN relop_expr
                {
                    $$ = makeChild(makeIDNode($1, WITH_INIT_ID), $3);
                }
            ;

stmt_list	: stmt_list stmt
                {
                    $$ = makeSibling($1, $2);
                }
            | stmt
                {
                    $$ = $1;
                }
            ;



stmt		: MK_LBRACE block MK_RBRACE
                {
                    $$ = $2;
                }
            | WHILE MK_LPAREN test MK_RPAREN stmt
                {
                    $$ = makeStmtNode(WHILE_STMT);
                    makeFamily($$, 2, $3, $5);
                }
            | FOR MK_LPAREN assign_expr_list MK_SEMICOLON relop_expr_list MK_SEMICOLON assign_expr_list MK_RPAREN stmt
                {
                    $$ = makeStmtNode(FOR_STMT);
                    makeFamily($$, 4, $3, $5, $7, $9);
                }
            | var_ref OP_ASSIGN relop_expr MK_SEMICOLON
                {
                    $$ = makeStmtNode(ASSIGN_STMT);
                    makeFamily($$, 2, $1, $3);
                }
            | IF MK_LPAREN test MK_RPAREN stmt
                {
                    $$ = makeStmtNode(IF_STMT);
                    makeFamily($$, 3, $3, $5, Allocate(NUL_NODE));
                }
            | IF MK_LPAREN test MK_RPAREN stmt ELSE stmt
                {
                    $$ = makeStmtNode(IF_STMT);
                    makeFamily($$, 3, $3, $5, $7);
                }
            | ID MK_LPAREN relop_expr_list MK_RPAREN MK_SEMICOLON
                {
                    $$ = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily($$, 2, makeIDNode($1, NORMAL_ID), $3);
                }
            | MK_SEMICOLON
                {
                    $$ = Allocate(NUL_NODE);
                }
            | RETURN MK_SEMICOLON
                {
                    $$ = makeStmtNode(RETURN_STMT);
                    makeChild($$, Allocate(NUL_NODE));
                }
            | RETURN relop_expr MK_SEMICOLON
                {
                    $$ = makeStmtNode(RETURN_STMT);
                    makeChild($$, $2);
                }
            ;

assign_expr_list : nonempty_assign_expr_list
                     {
                        $$ = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), $1);
                     }
                 |
                     {
                         $$ = Allocate(NUL_NODE);
                     }
                 ;

nonempty_assign_expr_list        : nonempty_assign_expr_list MK_COMMA assign_expr
                                    {
                                        $$ = makeSibling($1, $3);
                                    }
                                 | assign_expr
                                    {
                                        $$ = $1;
                                    }
                                 ;

test		: assign_expr
                {
                    $$ = $1;
                }
            ;

assign_expr     : ID OP_ASSIGN relop_expr
                    {
                        //TODO: for simpler implementation, use ASSIGN_STMT for now
                        $$ = makeStmtNode(ASSIGN_STMT);
                        makeFamily($$, 2, makeIDNode($1, NORMAL_ID), $3);
                    }
                | relop_expr
                    {
                        $$ = $1;
                    }
		;

relop_expr	: relop_term
                {
                    $$ = $1;
                }
            | relop_expr OP_OR relop_term
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily($$, 2, $1, $3);
                }
            ;

relop_term	: relop_factor
                {
                    $$ = $1;
                }
            | relop_term OP_AND relop_factor
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily($$, 2, $1, $3);
                }
            ;

relop_factor	: expr
                    {
                        $$ = $1;
                    }
                | expr rel_op expr
                    {
                        $$ = makeFamily($2, 2, $1, $3);
                    }
                ;

rel_op		: OP_EQ
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
            | OP_GE
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
            | OP_LE
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
            | OP_NE
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
            | OP_GT
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
            | OP_LT
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
            ;


relop_expr_list	: nonempty_relop_expr_list
                    {
                        $$ = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), $1);
                    }
                |
                    {
                        $$ = Allocate(NUL_NODE);
                    }
                ;

nonempty_relop_expr_list	: nonempty_relop_expr_list MK_COMMA relop_expr
                                {
                                    $$ = makeSibling($1, $3);
                                }
                            | relop_expr
                                {
                                    $$ = $1;
                                }
                            ;

expr		: expr add_op term
                {
                    $$ = makeFamily($2, 2, $1, $3);
                }
            | term
                {
                    $$ = $1;
                }
            ;

add_op		: OP_PLUS
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
            | OP_MINUS
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
            ;

term		: term mul_op factor
                {
                    $$ = makeFamily($2, 2, $1, $3);
                }
            | factor
                {
                    $$ = $1;
                }
            ;

mul_op		: OP_TIMES
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
            | OP_DIVIDE
                {
                    $$ = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
            ;

factor		: MK_LPAREN relop_expr MK_RPAREN
                {
                    $$ = $2;
                }
            | OP_MINUS MK_LPAREN relop_expr MK_RPAREN
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild($$, $3);
                }
            | OP_NOT MK_LPAREN relop_expr MK_RPAREN
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild($$, $3);
                }
            | CONST
                {
                    $$ = Allocate(CONST_VALUE_NODE);
                    $$->semantic_value.const1=$1;
                }
            | OP_MINUS CONST
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = $2;
                    makeChild($$, constNode);
                }
            | OP_NOT CONST
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = $2;
                    makeChild($$, constNode);
                }
            | ID MK_LPAREN relop_expr_list MK_RPAREN
                {
                    $$ = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily($$, 2, makeIDNode($1, NORMAL_ID), $3);
                }
            | OP_MINUS ID MK_LPAREN relop_expr_list MK_RPAREN
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode($2, NORMAL_ID), $4);
                    makeChild($$, functionCallNode);
                }
            | OP_NOT ID MK_LPAREN relop_expr_list MK_RPAREN
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode($2, NORMAL_ID), $4);
                    makeChild($$, functionCallNode);
                }
            | var_ref
                {
                    $$ = $1;
                }
            | OP_MINUS var_ref
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild($$, $2);
                }
            | OP_NOT var_ref
                {
                    $$ = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild($$, $2);
                }
            ;

var_ref		: ID
                {
                    $$ = makeIDNode($1, NORMAL_ID);
                }
            | ID dim_list
                {
                    $$ = makeIDNode($1, ARRAY_ID);
                    makeChild($$,$2);
                }
            ;


dim_list	: dim_list MK_LB expr MK_RB
                {
                    $$ = makeSibling($1, $3);
                }
            | MK_LB expr MK_RB
                {
                    $$ = $2;
                }
		;


%%

#include "lex.yy.c"
#include <string.h>
#include <stdarg.h>
#include "codeGenerate.h"
    FILE* outputFile;
    int ifCount;
    int whileCount;
    int constCount;
	int forCount;
	int shortCutCount;
	int AROffset;
	int regStat[15] = {0};

    //label number should be maintained on a stack.

#define writeV8(s, b...)			\
  {						\
    fprintf(outputFile, s, ##b);		\
  }

void gen_prologue(char* name, int paramCount)
{
	int paramOffset = -8 * paramCount;
    writeV8("\t.text\n");
    writeV8("_start_%s:\n", name);
    writeV8("\tstr x30, [sp, #%d]\n", paramOffset);
    writeV8("\tstr x29, [sp, #%d]\n", paramOffset-8);
    writeV8("\tadd x29, sp, #%d\n", paramOffset-8);
    writeV8("\tadd sp, sp, #%d\n", paramOffset-16);
    writeV8("\tldr x30, =_frameSize_%s\n", name);
    writeV8("\tldr x30, [x30, #0]\n");
    writeV8("\tsub sp, sp, w30\n");
	writeV8("\tstr x9, [sp, #8]\n");
	writeV8("\tstr x10, [sp, #16]\n");
	writeV8("\tstr x11, [sp, #24]\n");
	writeV8("\tstr x12, [sp, #32]\n");
	writeV8("\tstr x13, [sp, #40]\n");
	writeV8("\tstr x14, [sp, #48]\n");
	writeV8("\tstr x15, [sp, #56]\n");
	writeV8("\tstr x16, [sp, #64]\n");
	writeV8("\tstr x17, [sp, #68]\n");
	writeV8("\tstr x18, [sp, #72]\n");
	writeV8("\tstr x19, [sp, #76]\n");
	writeV8("\tstr x20, [sp, #80]\n");
	writeV8("\tstr x21, [sp, #84]\n");
	writeV8("\tstr x22, [sp, #88]\n");
	writeV8("\tstr x23, [sp, #92]\n\n");
}

void gen_epilogue(char* name, int paramCount)
{
	int paramOffset = 8 * paramCount;
	writeV8("\n_end_%s:\n", name);
	writeV8("\tldr x9, [sp, #8]\n");
	writeV8("\tldr x10, [sp, #16]\n");
	writeV8("\tldr x11, [sp, #24]\n");
	writeV8("\tldr x12, [sp, #32]\n");
	writeV8("\tldr x13, [sp, #40]\n");
	writeV8("\tldr x14, [sp, #48]\n");
	writeV8("\tldr x15, [sp, #56]\n");
	writeV8("\tldr x16, [sp, #64]\n");
	writeV8("\tldr x17, [sp, #68]\n");
	writeV8("\tldr x18, [sp, #72]\n");
	writeV8("\tldr x19, [sp, #76]\n");
	writeV8("\tldr x20, [sp, #80]\n");
	writeV8("\tldr x21, [sp, #84]\n");
	writeV8("\tldr x22, [sp, #88]\n");
	writeV8("\tldr x23, [sp, #92]\n");
	writeV8("\tldr x30, [x29, #8]\n");
	writeV8("\tmov sp, x29\n");
	writeV8("\tadd sp, sp, #%d\n", paramOffset + 8);
	writeV8("\tldr x29, [x29, #0]\n");
	writeV8("\tRET x30\n");
	writeV8("\t.data\n");
}

void gen_frameSizeLabel(char* name, int size)
{
	writeV8("_frameSize_%s:\n", name);
	writeV8("\t.word %d\n", size);
}

void codeGenConvertFromIntToFloat(Reg* reg){
  Reg newReg;
  newReg.c = 's';
  newReg.no = getFreeReg(FLOAT_TYPE);
  writeV8("SCVTF %c%d, %c%d\n#convert int to float\n", newReg.c, newReg.no, reg->c, reg->no)//scvtf s, w
  freeReg(reg->no);
  reg->no = newReg.no;
  reg->c = newReg.c;
}

Reg doMath(AST_NODE* node)
{
	Reg reg;
	if(node->nodeType == CONST_VALUE_NODE)
	{
		int regNo;
		switch(node->semantic_value.const1->const_type)
		{
			case INTEGERC:
				writeV8("\t.data\n");
				writeV8("_CONSTANT_%d:\n", constCount);
				writeV8("\t.word %d\n", node->semantic_value.const1->const_u.intval);
				writeV8("\t.align 3\n");
				writeV8("\t.text\n");
				regNo = getFreeReg(INT_TYPE);
				writeV8("\tldr w%d, _CONSTANT_%d\n", regNo, constCount);
				constCount++;
				reg.c = 'w';
				break;
			case FLOATC:
				writeV8("\t.data\n");
				writeV8("_CONSTANT_%d:\n", constCount);
				writeV8("\t.float %f\n", node->semantic_value.const1->const_u.fval);
				writeV8("\t.align 3\n");
				writeV8("\t.text\n");
				regNo = getFreeReg(FLOAT_TYPE);
				writeV8("\tldr s%d, _CONSTANT_%d\n", regNo, constCount);
				constCount++;
				reg.c = 's';
				break;
		}
		reg.no = regNo;
		return reg;
	}
	else if(node->nodeType == IDENTIFIER_NODE)
	{
		int regNo;
		char* name = node->semantic_value.identifierSemanticValue.identifierName;
		DATA_TYPE type;

		SymbolTableEntry* entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
		if(node->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
		{
			int arrayElemRegNo = ldrArrayElem(node);
			type = entry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
			
			if(type == INT_TYPE)
			{
				regNo = getFreeReg(INT_TYPE);
				writeV8("\tldr w%d, [x%d, #0]\n", regNo, arrayElemRegNo);
				reg.c = 'w';
			}
			else if(type == FLOAT_TYPE)
			{
				regNo = getFreeReg(FLOAT_TYPE);
				writeV8("\tldr s%d, [x%d, #0]\n", regNo, arrayElemRegNo);
				reg.c = 's';
			}		
			freeReg(arrayElemRegNo);
			reg.no = regNo;
			return reg;
		}
		else if(node->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
		{
			type = entry->attribute->attr.typeDescriptor->properties.dataType;
			if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
			{
				if(entry->nestingLevel == 0)
				{
					char* label = entry->address.label;
					int labelReg = getFreeReg(INT_TYPE);
					writeV8("\tldr x%d, =%s\n", labelReg, label)
					if(type == INT_TYPE)
					{
						regNo = getFreeReg(INT_TYPE);
						writeV8("\tldr w%d, [x%d, #0]\n", regNo, labelReg);
						reg.c = 'w';
					}
					else if(type == FLOAT_TYPE)
					{
						regNo = getFreeReg(FLOAT_TYPE);
						writeV8("\tldr s%d, [x%d, #0]\n", regNo, labelReg);
						reg.c = 's';
					}
					freeReg(labelReg);
				}
				else
				{
					int FpOffset = entry->address.FpOffset;
//					printf("id %s FpOffset = %d\n", name, FpOffset);
					if(type == INT_TYPE)
					{
						regNo = getFreeReg(INT_TYPE);
						writeV8("\tldr w%d, [x29, #%d]\n", regNo, FpOffset);
						reg.c = 'w';
					}
					else if(type == FLOAT_TYPE)
					{
						regNo = getFreeReg(FLOAT_TYPE);
						writeV8("\tldr s%d, [x29, #%d]\n", regNo, FpOffset);
						reg.c = 's';
					}
				}
				reg.no = regNo;
			}
			else //if(entry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
			{	
				reg.no = getFreeReg(INT_TYPE);
				if(entry->nestingLevel == 0)
				{
					char* label = entry->address.label;
					writeV8("\tldr x%d, =%s\n", reg.no, label);
				}
				else
				{
					writeV8("\tadd x%d, x29, #%d\n", reg.no, entry->address.FpOffset);
				}
				reg.c = 'x';
			}
			return reg;
		}
	}
	else if(node->nodeType == EXPR_NODE)
	{
		if(node->semantic_value.exprSemanticValue.kind == BINARY_OPERATION)
		{
			if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_AND ||
			   node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_OR)
			{
				Reg resultReg;
				resultReg.c = 'w';
				resultReg.no = getFreeReg(INT_TYPE);
				Reg LHSReg = doMath(node->child);
				if(LHSReg.c == 'w')
				{
					writeV8("\tcmp %c%d, 0\n", LHSReg.c, LHSReg.no);
				} 
				else 
				{
					writeV8("\tfcmp %c%d, 0\n", LHSReg.c, LHSReg.no);
				}
				writeV8("\tcset w%d, ne\n", resultReg.no);
				freeReg(LHSReg.no);
				if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_AND)
				{
					writeV8("\tcmp w%d, 0\n", resultReg.no);
					writeV8("\tbeq shortCut%d\n", shortCutCount);
					Reg RHSReg = doMath(node->child->rightSibling);
					if(RHSReg.c == 'w')
					{
						writeV8("\tcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					} 
					else 
					{
						writeV8("\tfcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					}
					writeV8("\tcset w%d, ne\n", resultReg.no);
					freeReg(RHSReg.no);
				}
				else if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_OR)
				{
					writeV8("\tcmp w%d, 0\n", resultReg.no);
					writeV8("\tbne shortCut%d\n", shortCutCount);
					Reg RHSReg = doMath(node->child->rightSibling);
					if(RHSReg.c == 'w')
					{
						writeV8("\tcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					} 
					else 
					{
						writeV8("\tfcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					}
					writeV8("cset w%d, eq\n", resultReg.no);
					freeReg(RHSReg.no);
				}
				writeV8("shortCut%d:\n", shortCutCount++);
				return resultReg;
			}
			else
			{
				Reg LHSReg = doMath(node->child);
				Reg RHSReg = doMath(node->child->rightSibling);
				
				//handle implicit type conversion
				if(LHSReg.c == 'w' && RHSReg.c == 's')
					codeGenConvertFromIntToFloat(&LHSReg);
				else if(LHSReg.c == 's' && RHSReg.c == 'w')
					codeGenConvertFromIntToFloat(&RHSReg);
				
				switch(node->semantic_value.exprSemanticValue.op.binaryOp)
				{
					case BINARY_OP_ADD:
						if(LHSReg.c == 'w')
						{
							writeV8("\tadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}	
						break;
					case BINARY_OP_SUB:
						if(LHSReg.c == 'w')
						{
							writeV8("\tsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_MUL:
						if(LHSReg.c == 'w')
						{
							writeV8("\tmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_DIV:
						if(LHSReg.c == 'w')
						{
							writeV8("\tsdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_EQ:	// ==	
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, eq\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, eq\n", LHSReg.no);
						}
						break;
					case BINARY_OP_GE:	// >=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, ge\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, ge\n", LHSReg.no);
						}
						break;
					case BINARY_OP_LE:	// <=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, le\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, le\n", LHSReg.no);
						}
						break;
					case BINARY_OP_NE:	// !=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, ne\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, ne\n", LHSReg.no);
						}
						break;
					case BINARY_OP_GT:	// >
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, gt\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, gt\n", LHSReg.no);
						}
						break;
					case BINARY_OP_LT:	// <
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, lt\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, lt\n", LHSReg.no);
						}
						break;
					default:
						break;
				}
				freeReg(RHSReg.no);
				return LHSReg;
			}
		}
		else if(node->semantic_value.exprSemanticValue.kind == UNARY_OPERATION)
		{
			AST_NODE* valueNode = node->child;
			reg = doMath(valueNode);
			if(node->semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_NEGATIVE)
			{
				if(reg.c == 'w')
				{
					writeV8("\tneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
				}
				else
				{
					writeV8("\tfneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
				}
			}
			else if(node->semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_LOGICAL_NEGATION)
			{
				if(reg.c == 'w')
				{
					writeV8("\tcmp %c%d, #0\n", reg.c, reg.no);
					writeV8("\tcset w%d, eq\n", reg.no);
				}
				else
				{
					Reg resultReg;
					resultReg.no = getFreeReg(INT_TYPE);
					resultReg.c = 'w';
					writeV8("\tfcmp %c%d, #0.0\n", reg.c, reg.no);
					writeV8("\tcset w%d, eq\n", resultReg.no);
					freeReg(reg.no);
					return resultReg;
				}	
			}
			return reg;
		}
	}
	else if(node->nodeType == STMT_NODE && node->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
	{
		doFuncCallStmt(node);
		AST_NODE* funcNameNode = node->child;
		SymbolTableEntry* entry = funcNameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		DATA_TYPE type = entry->attribute->attr.functionSignature->returnType;
		int retReg;
		if(type == INT_TYPE)
		{
			retReg = getFreeReg(INT_TYPE);
			writeV8("\tmov w%d, w0\n", retReg);
			reg.c = 'w';
		}
		else if(type == FLOAT_TYPE)
		{
			retReg = getFreeReg(FLOAT_TYPE);
			writeV8("\tfmov s%d, s0\n", retReg);
			reg.c = 's';
		}
		reg.no = retReg;
		return reg;
	}
}

int getFreeReg(DATA_TYPE type)
{
	int i;
	if(type == INT_TYPE)
	{
		i = 0;
		while(regStat[i] && i<7)
			i++;
		if(i == 7)
			return -1;
	}
	else
	{
		i = 7;
		while(regStat[i] && i<15)
			i++;
		if(i == 15)
			return -1;
	}
	regStat[i] = 1;
	return i+9;
}

void freeReg(int no, ...)
{
	regStat[no-9] = 0;
	
	va_list ap;
	int arg;
	
	va_start(ap, no);
	while(!(arg = va_arg(ap, int)))
	{
		printf("arg = %d\n", arg);
		regStat[arg-9] = 0;
	}
	va_end(ap);
}

int ldrArrayElem(AST_NODE* arrayIDNode)
{
	SymbolTableEntry* entry = arrayIDNode->semantic_value.identifierSemanticValue.symbolTableEntry;
	
	int dimension = entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
	int* sizeInEachDimension = entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension;
	
	int ctn;
	AST_NODE* indexNode = arrayIDNode->child;
	int offsetRegNo = getFreeReg(INT_TYPE);
	writeV8("\tmov w%d, #0\n", offsetRegNo);
	for(ctn=0; ctn < dimension; ctn++)
	{
		Reg indexReg = doMath(indexNode);
		int i = ctn+1;
		while(i < dimension)
		{
			int dimensionSizeRegNo = getFreeReg(INT_TYPE);
			writeV8("\tmov w%d, #%d\n", dimensionSizeRegNo, sizeInEachDimension[i++]);
			writeV8("\tmul w%d, w%d, w%d\n", indexReg.no, indexReg.no, dimensionSizeRegNo);
			freeReg(dimensionSizeRegNo);
		}
		writeV8("\tadd w%d, w%d, w%d\n", offsetRegNo, offsetRegNo, indexReg.no);
		freeReg(indexReg.no);
		indexNode = indexNode->rightSibling;
	}
	writeV8("\tlsl w%d, w%d, #2\n", offsetRegNo, offsetRegNo);
	
	int addressRegNo = getFreeReg(INT_TYPE);
	if(entry->nestingLevel == 0)
	{
		char* label = entry->address.label;
		writeV8("\tldr x%d, =%s\n", addressRegNo, label);
		writeV8("\tadd x%d, x%d, x%d\n", addressRegNo, addressRegNo, offsetRegNo);
	}
	else
	{
		if(entry->address.FpOffset > 0)
		{
			writeV8("\tldr x%d, [x29, #%d]\n", addressRegNo, entry->address.FpOffset);
		}
		else
		{
			writeV8("\tadd x%d, x29, #%d\n", addressRegNo, entry->address.FpOffset);
		}
		writeV8("\tsub x%d, x%d, x%d\n", addressRegNo, addressRegNo, offsetRegNo);
	}
	freeReg(offsetRegNo);
	return addressRegNo;
}

void doAssignStmt(AST_NODE* assignStatNode)
{
	AST_NODE* LHS = assignStatNode->child;
	AST_NODE* RHS = LHS->rightSibling;
	Reg RHSReg = doMath(RHS);
	
	SymbolTableEntry* LHSEntry = LHS->semantic_value.identifierSemanticValue.symbolTableEntry;
	DATA_TYPE type;
	if(LHS->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	{
		type = LHSEntry->attribute->attr.typeDescriptor->properties.dataType;
	}
	if(LHS->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	{
		type = LHSEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
	}
	if((type == FLOAT_TYPE) && (RHSReg.c == 'w'))	//type conversion
	{
		codeGenConvertFromIntToFloat(&RHSReg);
	}
	
	if(LHS->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	{

		if(LHSEntry->nestingLevel == 0)
		{
			char* label = LHSEntry->address.label;
			int labelRegNo = getFreeReg(INT_TYPE);
			writeV8("\tldr x%d, =%s\n", labelRegNo, label);
			writeV8("\tstr %c%d, [x%d, #0]\n", RHSReg.c, RHSReg.no, labelRegNo);
			freeReg(labelRegNo);
		}
		else
		{
			writeV8("\tstr %c%d, [x29, #%d]\n", RHSReg.c, RHSReg.no, LHSEntry->address.FpOffset);		
//			constCount++;
		}
	}
	else if(LHS->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	{
		int arrayElemRegNo = ldrArrayElem(LHS);
		
		writeV8("\tstr %c%d, [x%d, #0]\n", RHSReg.c, RHSReg.no, arrayElemRegNo);
		freeReg(arrayElemRegNo);	
	}

	freeReg(RHSReg.no);
}

void writeString(char* strName, char* strValue)
{
	//data part
	writeV8("\t.data\n");

	char* newStrValue = (char*)malloc(sizeof(strValue)*2);
	int count = 0;
	int newcount = 0;
	int length = 0;
	while(strValue[count] != '\0')
	{
    /*if(strValue[count] == '\n'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 'n';
    } else if(strValue[count] == '\t'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 't';
    } else if(strValue[count] == '\\'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = '\\';
    } else if(strValue[count] == '\r'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 'r';
    } else if(strValue[count] == '\0'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = '0';
      } else {*/
		newStrValue[newcount++] = strValue[count];
		count++;
	}
	newStrValue[newcount] = '\0';
	fprintf(stderr, "original strvalue = [%s], after = [%s]\n", strValue, newStrValue);

	writeV8("%s: .ascii %s\n", strName, newStrValue);

	int alignNum = 4-((strlen(newStrValue)+2)%4);
	if(alignNum == 4)
		alignNum = 0;
	writeV8("\t.align %d\n", alignNum);//align is 4 times
    
	//test part
	writeV8("\t.text\n");
	writeV8("\tldr x0, =%s\n", strName);//"_CONSTANT_0" or what?
	//mov x0, x9 //TODO: check is needed or not
	writeV8("\tbl _write_str\n");
}

void writeInt(Reg reg)//reg will read the value from local stack and write
{
	//if directly give a reg to write, it's value will be deleted(?) after called write()
	writeV8("\tmov w0, %c%d\n", reg.c, reg.no);
	writeV8("\tbl _write_int\n");
}

void writeFloat(Reg reg)
{
	writeV8("\tfmov s0, %c%d\n", reg.c, reg.no);
	writeV8("\tbl _write_float\n");
}

void readInt()//will read value into reg and write into local stack
{
	int i = getFreeReg(INT_TYPE);
	writeV8("\tbl _read_int\n");
	writeV8("\tmov w%d, w0\n", i);
	//writeV8("str w%d, [x29, #-4]\n", i);
}

void readFloat()
{
	int i = getFreeReg(FLOAT_TYPE);
	writeV8("\tbl _read_float\n");
	writeV8("\tfmov s%d, s0\n", i);
	//writeV8("str s%d, [x29, #-8]\n", i);
}

void doFuncCallStmt(AST_NODE* funcCallStmtNode)
{
	AST_NODE* funcNameNode = funcCallStmtNode->child;
	char* funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;

	AST_NODE* parameterListNode = funcNameNode->rightSibling;
	AST_NODE* paramNode = parameterListNode->child;
	if(strcmp(funcName, "fread") == 0)
	{//TODO: 1. how to assign(he use w0 as return val) 2. send parameter
		readFloat();
	} 
	else if(strcmp(funcName, "read") == 0)
	{
		readInt();
	} 
	else if(strcmp(funcName, "write") == 0)
	{
		Reg reg;
		char strName[20];
		switch(paramNode->dataType)
		{
			case INT_TYPE:
				reg = doMath(paramNode);
				writeInt(reg);
				freeReg(reg.no);
				break;
			case FLOAT_TYPE:
				reg = doMath(paramNode);
				writeFloat(reg);
				freeReg(reg.no);
				break;
			case CONST_STRING_TYPE:
				sprintf(strName, "_CONSTANT_%d", constCount++);//TODO: check data declare twice
				writeString(strName, paramNode->semantic_value.const1->const_u.sc);
				break;
		}
	} 
	else
	{
		SymbolTableEntry* funcEntry = funcNameNode->semantic_value.identifierSemanticValue.symbolTableEntry; 
		int paramCount = funcEntry->attribute->attr.functionSignature->parametersCount;
		while(paramCount > 0)
		{
			Reg paramReg = doMath(paramNode);
			writeV8("\tstr %c%d, [sp, #%d]\n", paramReg.c, paramReg.no, (paramCount-1)*(-8));
			paramNode = paramNode -> rightSibling;
			paramCount--;
		}
		writeV8("\tbl _start_%s\n", funcName);
	}
}

void doRetStmt(AST_NODE* stmtNode, char* funcName)
{
	AST_NODE* retValNode = stmtNode->child;
	Reg retReg = doMath(retValNode);
	writeV8("\tmov %c0, %c%d\n", retReg.c, retReg.c, retReg.no);
	writeV8("\tb _end_%s\n", funcName);
	freeReg(retReg.no);
}

void doStmtLst(AST_NODE* stmtLstNode, char* funcName)
{
	AST_NODE* stmtNode = stmtLstNode->child;
	while(stmtNode)
	{
		switch(stmtNode->semantic_value.stmtSemanticValue.kind)
		{
			case ASSIGN_STMT:
				doAssignStmt(stmtNode);
				break;
			case FUNCTION_CALL_STMT:
				doFuncCallStmt(stmtNode);
				break;
			case RETURN_STMT:
				doRetStmt(stmtNode, funcName);
				break;
			case WHILE_STMT:
				doWhileStmt(stmtNode, funcName);
				break;
			case FOR_STMT:
	 			doForStmt(stmtNode, funcName);
				break;
			case IF_STMT:
				doIfStmt(stmtNode, funcName);
				break;
		}
		stmtNode = stmtNode->rightSibling;
	}
}

inline void genLabel(char* name)
{
	writeV8("%s:\n", name);
}

inline void genGoto(char* name)
{
	writeV8("b %s\n", name);
}

inline void genBranch(Reg reg, char* tname, char* fname)
{
	if(reg.c == 'w')
	{
		writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
	} 
	else
	{
		writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
	}
	freeReg(reg.no);
	writeV8("\tbeq %s\n", fname);
	writeV8("\tb %s\n", tname);
}

void doForStmt(AST_NODE* stmtNode, char* funcName)
{
	forCount++;
	char testName[15];
	sprintf(testName, "ForTest%d", forCount);
	char incName[15];
	sprintf(incName, "ForInc%d", forCount);
	char bodyName[15];
	sprintf(bodyName, "ForBody%d", forCount);
	char exitName[15];
	sprintf(exitName, "ForExit%d", forCount);

	AST_NODE* initNode = stmtNode->child;
	AST_NODE* testNode = initNode->rightSibling;
	AST_NODE* incNode = testNode->rightSibling;
	AST_NODE* bodyNode = incNode->rightSibling;
	//init
	writeV8("# forinit\n");
	doStmtLst(initNode, funcName);
	//test
	writeV8("# fortest\n");
	genLabel(testName);
	Reg reg = doMath(testNode->child);  //generate xxx
	genBranch(reg, bodyName, exitName);

	//inc
	writeV8("# forinc\n");
	genLabel(incName);
	doStmtLst(incNode, funcName);
	genGoto(testName);
	//body
	writeV8("# forbody\n");
	genLabel(bodyName);
	doBlock(bodyNode, funcName);
	genGoto(incName);
	//exit
	genLabel(exitName);
}

void doWhileStmt(AST_NODE* stmtNode, char* funcName)
{
	whileCount++;
	char testName[15];
	sprintf(testName, "WhileTest%d", whileCount);
	char exitName[15];
	sprintf(exitName, "WhileExit%d", whileCount);

	writeV8("%s:\n", testName);
	Reg reg = doMath(stmtNode->child);  //generate xxx
	//I wish to get result register 
	if(reg.c == 'w')
	{
		writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
  	}
	else
	{
    	writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
  	}
	freeReg(reg.no);

	writeV8("\tbeq %s\n", exitName);
	doBlock(stmtNode->child->rightSibling, funcName);  //generate yyy
	writeV8("\tb %s\n", testName);
	writeV8("%s:\n", exitName);
}

void doIfStmt(AST_NODE* ifStmtNode, char* funcName)
{
	ifCount++;
	int elsePartCount = 0;
	char exitLabel[14];
	sprintf(exitLabel, "IfStmt%d_exit", ifCount);
		
	while(ifStmtNode->nodeType == STMT_NODE)
	{
		char beforeStartLabel[14] = {'\0'};
		char startLabel[14] = {'\0'};
		char elseIfLabel[14] = {'\0'};
		sprintf(beforeStartLabel, "IfStmt%d_%d", ifCount, elsePartCount++);
		sprintf(elseIfLabel, "IfStmt%d_%d", ifCount, elsePartCount);

		writeV8("%s:\n", beforeStartLabel);
		Reg conditionReg = doMath(ifStmtNode->child);
		writeV8("\tcmp %c%d, 0\n", conditionReg.c, conditionReg.no);
		writeV8("\tbeq %s\n", elseIfLabel);
		doBlock(ifStmtNode->child->rightSibling, funcName);
		writeV8("\tb %s\n", exitLabel);  

		ifStmtNode = ifStmtNode->child->rightSibling->rightSibling;
	}

	writeV8("IfStmt%d_%d:\n", ifCount, elsePartCount);
	if(ifStmtNode->nodeType == BLOCK_NODE)
	{
		doBlock(ifStmtNode, funcName);
	}
	writeV8("%s:\n", exitLabel);
}

void doBlock(AST_NODE* blockNode, char* funcName)
{
	AST_NODE* content = blockNode->child;
	while(content)
    {
		switch(content->nodeType)
		{
			case STMT_LIST_NODE:
				doStmtLst(content, funcName);
				break;
			case VARIABLE_DECL_LIST_NODE:
				doVarDeclLst(content, 1);
				break;
		}
		content = content->rightSibling;
    }
}

void doDeclFunc(AST_NODE* declNode)
{
	AST_NODE* funcNameNode = declNode->child->rightSibling;
	AST_NODE* paramLstNode = funcNameNode->rightSibling;
	AST_NODE* blockNode = paramLstNode->rightSibling;
	AST_NODE* content = blockNode->child;
	
	char* funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;	
	int frameSize = 92;
	AROffset = 0;
	
	AST_NODE* paramNode = paramLstNode->child;
	int paramCount = 0;
	while(paramNode)
	{
		AST_NODE* paramIDNode = paramNode->child->rightSibling;
		paramIDNode->semantic_value.identifierSemanticValue.symbolTableEntry->address.FpOffset = (paramCount+2) * 8;
		paramNode = paramNode->rightSibling;
		paramCount++;
	}
	
	gen_prologue(funcName, paramCount);

	while(content)
	{
		switch(content->nodeType)
		{
			case STMT_LIST_NODE:
				doStmtLst(content, funcName);
				break;
			case VARIABLE_DECL_LIST_NODE:
				doVarDeclLst(content, 1);
				break;
		}
		content = content->rightSibling;
	}

	gen_epilogue(funcName, paramCount);
	gen_frameSizeLabel(funcName, frameSize-AROffset);
	AROffset = 0;
}

void doVarDeclLst(AST_NODE* varDeclNode, int lv)
{
	varDeclNode = varDeclNode->child;
	while(varDeclNode)
	{
		AST_NODE* typeNode = varDeclNode->child;
		AST_NODE* nameNode = typeNode->rightSibling;
		while(nameNode)
		{
			char* name = nameNode->semantic_value.identifierSemanticValue.identifierName;
//			printf("Decl id %s\n", name);
			SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
			if(nameNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID || 
			   nameNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID)
			{
				if(lv == 0) //global var decl
				{
					char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
					sprintf(label, "_g_%s", name);
					label[strlen(name)+3] = '\0';
	
					writeV8("\t.data\n");
					writeV8("%s:\n", label);
					if(typeNode->dataType == INT_TYPE)
					{
						if(nameNode->child)
						{
							writeV8("\t.word %d\n", nameNode->child->semantic_value.const1->const_u.intval);
						}
						else
						{
							writeV8("\t.word 0\n");
						}
					}
					else if(typeNode->dataType == FLOAT_TYPE)
					{
						if(nameNode->child)
						{
							writeV8("\t.float %f\n", nameNode->child->semantic_value.const1->const_u.fval);
						}
						else
						{
							writeV8("\t.float 0\n");
						}
					}
					writeV8("\t.align 3\n");
					writeV8("\t.text\n");
					entry->address.label = label;
				}
				else
				{
					AROffset -= 4;
					entry->address.FpOffset = AROffset;
					if(nameNode->child)
					{
						Reg valReg = doMath(nameNode->child);
					
						if((typeNode->dataType == FLOAT_TYPE) && (valReg.c == 'w'))
						{
							codeGenConvertFromIntToFloat(&valReg);
						}	
						writeV8("\tstr %c%d, [x29, #%d]\n", valReg.c, valReg.no, AROffset);
						freeReg(valReg.no);
					}
				}
			}

			else if(nameNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
			{
				AST_NODE* arraySizeNode = nameNode->child;
				int arraySize = arraySizeNode->semantic_value.const1->const_u.intval;
				SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
				if(lv == 0)
				{
					char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
					sprintf(label, "_g_%s", name);
					label[strlen(name)+3] = '\0';
	
					writeV8("\t.data\n");
					writeV8("%s:\n", label);
					writeV8("\t.place %d\n", arraySize);
					writeV8("\t.text\n");
					entry->address.label = label;
				}
				else
				{
					entry->address.FpOffset = AROffset-4;
					AROffset -= 4*arraySize;
				}
			}
//			printf("AROffset = %d, entry->address.FpOffset = %d\n", AROffset, entry->address.FpOffset);
			nameNode = nameNode->rightSibling;
		}
		varDeclNode = varDeclNode->rightSibling;
	}
}

void doDeclLst(AST_NODE* declNode)
{
	switch(declNode->semantic_value.declSemanticValue.kind)
	{
		case FUNCTION_DECL:
			doDeclFunc(declNode);
			break;
	}
}

void printCode(AST_NODE *root)
{
//frame information: temporarily added
    outputFile = fopen("output.s", "w");
    ifCount = 0;
    whileCount = 0;
    constCount = 0;
	forCount = 0;
	shortCutCount = 0;

	AST_NODE* child = root->child;
	while(child)
	{
		if(child->nodeType == VARIABLE_DECL_LIST_NODE)
		{
			doVarDeclLst(child, 0);
		}
		else if(child->nodeType == DECLARATION_NODE);
		{
			doDeclLst(child);
		}
		child = child->rightSibling;
	}
}

main (argc, argv)
int argc;
char *argv[];
{
	yyin = fopen(argv[1],"r");
	yyparse();
	printGV(prog, NULL);

	initializeSymbolTable();

	semanticAnalysis(prog);	

	symbolTableEnd();

	printCode(prog);
     
	if (!g_anyErrorOccur) {
		printf("Parsing completed. No errors found.\n");
	}
} /* main */



int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
