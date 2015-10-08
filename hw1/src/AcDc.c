#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

//#define DEBUG

int main( int argc, char *argv[] )
{
    FILE *source, *target;
    Program program;
    SymbolTable symtab;

    if( argc == 3){
        source = fopen(argv[1], "r");
        target = fopen(argv[2], "w");
        if( !source ){
            printf("can't open the source file\n");
            exit(2);
        }
        else if( !target ){
            printf("can't open the target file\n");
            exit(2);
        }
        else{
		program = parser(source);
		fclose(source);
		symtab = build(program);
		optimize(&program);
		check(&program, &symtab);
		gencode(program, target, symtab);
	}
    }
    else{
	    printf("Usage: %s source_file target_file\n", argv[0]);
    }


    return 0;
}


/********************************************* 
  Constant fold
 *********************************************/
void optimize(Program* prog)
{
	Statements *stmts = prog->statements;
	while(stmts)
	{
		Statement* stmt = &(stmts->first);
		if(stmt->type == Assignment)
		{
			Expression* expr = stmt->stmt.assign.expr;
			stmt->stmt.assign.expr = const_fold(expr);
		}
		stmts = stmts->rest;
	}

}

Expression* const_fold(Expression* expr)
{
	Expression* ret = (Expression*)malloc(sizeof(Expression));
	if(!expr->leftOperand && !expr->rightOperand)
		return expr;
	else
	{	
		Expression* lexp = const_fold(expr->leftOperand);
		Expression* rexp = const_fold(expr->rightOperand);
		if( (lexp->v.type == FloatConst || lexp->v.type == IntConst) &&
		    (rexp->v.type == FloatConst || rexp->v.type == IntConst) )
		{
			switch(expr->v.val.op)
			{
			case Plus:
				if( lexp->v.type == FloatConst || rexp->v.type == FloatConst )
				{
					ret->type = Float;
					ret->leftOperand = ret->rightOperand = NULL;
					if(lexp->v.type == FloatConst)
					{
						ret->v.val.fvalue = lexp->v.val.fvalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue += rexp->v.val.fvalue;
						else
							ret->v.val.fvalue += (float)rexp->leftOperand->v.val.ivalue;
					}
					else
					{
						ret->v.val.fvalue = (float)lexp->v.val.ivalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue += rexp->v.val.fvalue;
						else
				            		ret->v.val.fvalue += (float)rexp->leftOperand->v.val.ivalue;
					}
					ret->v.type = FloatConst;
					return ret;
				}
				else// if(lexp->v.type == IntConst && rexp->v.type == IntConst)
				{
					ret->type = Int;
					ret->leftOperand = ret->rightOperand = NULL;
					ret->v.val.ivalue = lexp->v.val.ivalue + rexp->v.val.ivalue;
					ret->v.type = IntConst;
					return ret;
				}

			case Minus:
				if( lexp->v.type == FloatConst || rexp->v.type == FloatConst )
				{
					ret->type = Float;
					ret->leftOperand = ret->rightOperand = NULL;
					if(lexp->v.type == FloatConst)
					{
						ret->v.val.fvalue = lexp->v.val.fvalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue -= rexp->v.val.fvalue;
						else
							ret->v.val.fvalue -= (float)rexp->leftOperand->v.val.ivalue;
					}
					else
					{
						ret->v.val.fvalue = (float)lexp->v.val.ivalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue -= rexp->v.val.fvalue;
						else
				            		ret->v.val.fvalue -= (float)rexp->leftOperand->v.val.ivalue;
					}
					ret->v.type = FloatConst;
					return ret;
				}
				else// if(lexp->v.type == IntConst && rexp->v.type == IntConst)
				{
					ret->type = Int;
					ret->leftOperand = ret->rightOperand = NULL;
					ret->v.val.ivalue = lexp->v.val.ivalue - rexp->v.val.ivalue;
					ret->v.type = IntConst;
					return ret;
				}

			case Mul:
				if( lexp->v.type == FloatConst || rexp->v.type == FloatConst )
				{
					ret->type = Float;
					ret->leftOperand = ret->rightOperand = NULL;
					if(lexp->v.type == FloatConst)
					{
						ret->v.val.fvalue = lexp->v.val.fvalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue *= rexp->v.val.fvalue;
						else
							ret->v.val.fvalue *= (float)rexp->leftOperand->v.val.ivalue;
					}
					else
					{
						ret->v.val.fvalue = (float)lexp->leftOperand->v.val.ivalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue *= rexp->v.val.fvalue;
						else
				            		ret->v.val.fvalue *= (float)rexp->leftOperand->v.val.ivalue;
					}
					ret->v.type = FloatConst;
					return ret;
				}
				else// if(lexp->v.type == IntConst && rexp->v.type == IntConst)
				{
					ret->type = Int;
					ret->leftOperand = ret->rightOperand = NULL;
					ret->v.val.ivalue = lexp->v.val.ivalue * rexp->v.val.ivalue;
					ret->v.type = IntConst;
					return ret;
				}

			case Div:
				if( lexp->v.type == FloatConst || rexp->v.type == FloatConst )
				{
					ret->type = Float;
					ret->leftOperand = ret->rightOperand = NULL;
					if(lexp->v.type == FloatConst)
					{
						ret->v.val.fvalue = lexp->v.val.fvalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue /= rexp->v.val.fvalue;
						else
							ret->v.val.fvalue /= (float)rexp->leftOperand->v.val.ivalue;
					}
					else
					{
						ret->v.val.fvalue = (float)lexp->leftOperand->v.val.ivalue;
						if(rexp->v.type == FloatConst)
							ret->v.val.fvalue /= rexp->v.val.fvalue;
						else
				            		ret->v.val.fvalue /= (float)rexp->leftOperand->v.val.ivalue;
					}
					ret->v.type = FloatConst;
					return ret;
				}
				else// if(lexp->v.type == IntConst && rexp->v.type == IntConst)
				{
					ret->type = Int;
					ret->leftOperand = ret->rightOperand = NULL;
					ret->v.val.ivalue = lexp->v.val.ivalue / rexp->v.val.ivalue;
					ret->v.type = IntConst;
					return ret;
				}

			default:
				printf("Got Error when constant folding, Unexpect Operation type: %d\n", expr->v.val.op);
				break;
			}
		}	
		else
		{
			expr->leftOperand = lexp;
			expr->rightOperand = rexp;
			return expr;
		}
	}
}

/********************************************* 
  Scanning 
 *********************************************/
Token getNumericToken( FILE *source, char c )
{
	Token token;
	int i = 0;

	while( isdigit(c) ) {
		token.tok[i++] = c;
		c = fgetc(source);
	}

	if( c != '.' ){
		ungetc(c, source);
		token.tok[i] = '\0';
		token.type = IntValue;
		return token;
	}

	token.tok[i++] = '.';

	c = fgetc(source);
	if( !isdigit(c) ){
		ungetc(c, source);
		printf("Expect a digit : %c\n", c);
		exit(1);
	}

	while( isdigit(c) ){
		token.tok[i++] = c;
		c = fgetc(source);
	}

	ungetc(c, source);
	token.tok[i] = '\0';
	token.type = FloatValue;
	return token;
}

Token scanner( FILE *source )
{
	char c;
	Token token;

	while( !feof(source) ){
		c = fgetc(source);
		while( isspace(c) )
			c = fgetc(source);
		
		if( isdigit(c) )
			return getNumericToken(source, c);

		int top = 0;
		if(islower(c))
		{
			while( islower(c) )
			{
				token.tok[top++] = c;
				c = fgetc(source);
			}
			ungetc(c, source);
			token.tok[top] = '\0';
		}
		else
		{
			token.tok[0] = c;
			token.tok[1] = '\0';
			top = 1;
		}

		if( strlen(token.tok) == 1)
		{
			if (islower(token.tok[0]) )
			{
				if( token.tok[0] == 'f' )
					token.type = FloatDeclaration;
				else if( token.tok[0] == 'i' )
					token.type = IntegerDeclaration;
				else if( token.tok[0] == 'p' )
					token.type = PrintOp;
				else
					token.type = Alphabet;
				return token;
			}
			switch(token.tok[0]){
				case '=':
					token.type = AssignmentOp;
					return token;
				case '+':
					token.type = PlusOp;
					return token;
				case '-':
					token.type = MinusOp;
					return token;
				case '*':
					token.type = MulOp;
					return token;
				case '/':
					token.type = DivOp;
					return token;
				case EOF:
					token.type = EOFsymbol;
					token.tok[0] = '\0';
					return token;
				default:
					printf("Invalid character : %c\n", c);
					exit(1);
			}
		}
		else if(top > 0)
		{
			int i=0;
			while(i < top)
			{
				if( !islower(token.tok[i]) && !isupper(token.tok[i]))
				{
					printf("Invalid variable name : %s\n", token.tok);
					exit(1);
				}
				i++;
			}
			token.type = Alphabet;
			return token;
		}
	}

	token.tok[0] = '\0';
	token.type = EOFsymbol;
	return token;
}


/********************************************************
  Parsing
 *********************************************************/
Declaration parseDeclaration( FILE *source, Token token )
{
	Token token2;
	switch(token.type){
		case FloatDeclaration:
		case IntegerDeclaration:
			token2 = scanner(source);
			if (strcmp(token2.tok, "f") == 0 ||
					strcmp(token2.tok, "i") == 0 ||
					strcmp(token2.tok, "p") == 0) {
				printf("Syntax Error: %s cannot be used as id\n", token2.tok);
				exit(1);
			}
			return makeDeclarationNode( token, token2 );
		default:
			printf("Syntax Error: Expect Declaration %s\n", token.tok);
			exit(1);
	}
}

Declarations *parseDeclarations( FILE *source )
{
	Token token = scanner(source);
	Declaration decl;
	Declarations *decls;
	int i;
	switch(token.type){
		case FloatDeclaration:
		case IntegerDeclaration:
			decl = parseDeclaration(source, token);
			decls = parseDeclarations(source);
			return makeDeclarationTree( decl, decls );
		case PrintOp:
			ungetc(token.tok[0], source);
			return NULL;
		case Alphabet:
			for( i = strlen(token.tok)-1; i>=0; i--)
				ungetc(token.tok[i], source);
			return NULL;
		case EOFsymbol:
			return NULL;
		default:
			printf("Syntax Error: Expect declarations %s\n", token.tok);
			exit(1);
	}
}

Expression *parseValue( FILE *source )
{
	Token token = scanner(source);
	Expression *value = (Expression *)malloc( sizeof(Expression) );
	value->leftOperand = value->rightOperand = NULL;

	switch(token.type){
		case Alphabet:
			(value->v).type = Identifier;
			(value->v).val.id = (char*)malloc( sizeof(char) * (strlen(token.tok)+1) );
			strcpy((value->v).val.id, token.tok);
			break;
		case IntValue:
			(value->v).type = IntConst;
			(value->v).val.ivalue = atoi(token.tok);
			break;
		case FloatValue:
			(value->v).type = FloatConst;
			(value->v).val.fvalue = atof(token.tok);
			break;
		default:
			printf("Syntax Error: Expect Identifier or a Number %s\n", token.tok);
			exit(1);
	}

	return value;
}

Expression* nextExpression(FILE* source, Expression* lvalue)
{
	Token token = scanner(source);
	int i;
	Expression* expr = (Expression*)malloc(sizeof(Expression));
	switch(token.type)
	{
		case PlusOp:
		case MinusOp:
			ungetc(token.tok[0], source);
			return lvalue;
		case MulOp:
			expr->v.type = MulNode;
			expr->v.val.op = Mul;
			expr->leftOperand = lvalue;
			expr->rightOperand = parseValue(source);
			return nextExpression(source, expr);
		case DivOp:
			expr->v.type = DivNode;
			expr->v.val.op = Div;
			expr->leftOperand = lvalue;
			expr->rightOperand = parseValue(source);
			return nextExpression(source, expr);
		case Alphabet:
			for( i = strlen(token.tok)-1; i>=0; i--)
				ungetc(token.tok[i], source);
			return lvalue;
		case PrintOp:
			ungetc(token.tok[0], source);
			return lvalue;
		case EOFsymbol:
			return lvalue;
		default:
			printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
			exit(1);
		
	}
}

Expression *parseExpression( FILE *source, Expression *lvalue )
{
	Token token = scanner(source);
	Expression *expr, *next_token, *next_expr;
	int i;
	switch(token.type){
		case PlusOp:
			expr = (Expression *)malloc( sizeof(Expression) );
			(expr->v).type = PlusNode;
			(expr->v).val.op = Plus;
			expr->leftOperand = lvalue;
			next_token = parseValue(source);
			next_expr = nextExpression(source, next_token);
			if(!next_expr)
				expr->rightOperand = next_token;
			else
				expr->rightOperand = next_expr;
			return parseExpression(source, expr);
		case MinusOp:
			expr = (Expression *)malloc( sizeof(Expression) );
			(expr->v).type = MinusNode;
			(expr->v).val.op = Minus;
			expr->leftOperand = lvalue;
			next_token = parseValue(source);
			next_expr = parseExpression(source, next_token);
			if(!next_expr)
				expr->rightOperand = next_token;
			else
				expr->rightOperand = next_expr;
			return parseExpression(source, expr);
		case MulOp:
			expr = (Expression*)malloc( sizeof(Expression) );
			(expr->v).type = MulNode;
			(expr->v).val.op = Mul;
			expr->leftOperand = lvalue;
			expr->rightOperand = parseValue(source);
			return parseExpression(source, expr);
		case DivOp:
			expr = (Expression*)malloc( sizeof(Expression) );
			(expr->v).type = DivNode;
			(expr->v).val.op = Div;
			expr->leftOperand = lvalue;
			expr->rightOperand = parseValue(source);
			return parseExpression(source, expr);
		case Alphabet:
			for( i = strlen(token.tok)-1; i>=0; i--)
				ungetc(token.tok[i], source);
			return lvalue;
		case PrintOp:
			ungetc(token.tok[0], source);
			return lvalue;
		case EOFsymbol:
			return lvalue;
		default:
			printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
			exit(1);
	}
}

Statement parseStatement( FILE *source, Token token )
{
	Token next_token;
	Expression *value, *expr;
	switch(token.type){
		case Alphabet:
			next_token = scanner(source);
			if(next_token.type == AssignmentOp){
				value = parseValue(source);
				expr = parseExpression(source, value);
				return makeAssignmentNode(token.tok, value, expr);
			}
			else{
				printf("Syntax Error: Expect an assignment op %s\n", next_token.tok);
				exit(1);
			}
		case PrintOp:
			next_token = scanner(source);
			if(next_token.type == Alphabet)
				return makePrintNode(next_token.tok);
			else{
				printf("Syntax Error: Expect an identifier %s\n", next_token.tok);
				exit(1);
			}
			break;
		default:
			printf("Syntax Error: Expect a statement %s\n", token.tok);
			exit(1);
	}
}

Statements *parseStatements( FILE * source )
{
	Token token = scanner(source);
	Statement stmt;
	Statements *stmts;

	switch(token.type){
		case Alphabet:
		case PrintOp:
			stmt = parseStatement(source, token);
			stmts = parseStatements(source);
			return makeStatementTree(stmt , stmts);
		case EOFsymbol:
			return NULL;
		default:
			printf("Syntax Error: Expect statements %s\n", token.tok);
			exit(1);
	}
}


/*********************************************************************
  Build AST
 **********************************************************************/
Declaration makeDeclarationNode( Token declare_type, Token identifier )
{
	Declaration tree_node;

	switch(declare_type.type){
		case FloatDeclaration:
			tree_node.type = Float;
			break;
		case IntegerDeclaration:
			tree_node.type = Int;
			break;
		default:
			break;
	}
	tree_node.name = (char*)malloc(sizeof(char)*(strlen(identifier.tok)+1));
	strcpy(tree_node.name, identifier.tok);
	
	return tree_node;
}

Declarations *makeDeclarationTree( Declaration decl, Declarations *decls )
{
	Declarations *new_tree = (Declarations *)malloc( sizeof(Declarations) );
	new_tree->first = decl;
	new_tree->rest = decls;

	return new_tree;
}


Statement makeAssignmentNode( char* id, Expression *v, Expression *expr_tail )
{
	Statement stmt;
	AssignmentStatement assign;

	stmt.type = Assignment;
	assign.id = (char*)malloc( sizeof(char) * (strlen(id)+1) );
	strcpy(assign.id, id);
	if(expr_tail == NULL)
		assign.expr = v;
	else
		assign.expr = expr_tail;
	stmt.stmt.assign = assign;

	return stmt;
}

Statement makePrintNode( char* id )
{
	Statement stmt;
	stmt.type = Print;
	stmt.stmt.variable = (char*)malloc( sizeof(char) * (strlen(id)+1) );
	strcpy(stmt.stmt.variable, id);

	return stmt;
}

Statements *makeStatementTree( Statement stmt, Statements *stmts )
{
	Statements *new_tree = (Statements *)malloc( sizeof(Statements) );
	new_tree->first = stmt;
	new_tree->rest = stmts;

	return new_tree;
}

/* parser */
Program parser( FILE *source )
{
	Program program;

	program.declarations = parseDeclarations(source);
	program.statements = parseStatements(source);
#ifdef DEBUG
	Declaration tmp;
	while(program.declarations)
	{
		tmp = program.declarations->first;
		printf("type = %d, name = %s\n", tmp.type, tmp.name);
		program.declarations = program.declarations->rest;
	}
	
	Statement x;
	while(program.statements)
	{
		x = program.statements->first;
		printf("statement type = %d, id = %s, op = %d, left = %s, right = %s\n", 
			x.type, x.stmt.assign.id, x.stmt.assign.expr->v.val.op, x.stmt.assign.expr->leftOperand->v.val.id, x.stmt.assign.expr->rightOperand->v.val.id);
		program.statements = program.statements->rest;
	}
#endif

	return program;
}


/********************************************************
  Build symbol table
 *********************************************************/
void InitializeTable( SymbolTable *table )
{
	int i;

	for(i = 0 ; i < 1025; i++)
	{
		table->name[i] = '\0';
		table->type[i] = Notype;
	}
}

void add_table( SymbolTable *table, char* name, DataType t )
{
	int i;
	for(i=0; i<table->top;i++)
		if( !strcmp( table->name[i], name ) )
		{
			printf("Error : id %s has been declared\n", name);//error
			table->type[i] = t;
			return;
		}	
	table->name[table->top] = name;
	table->type[table->top] = t;
	table->top++;
}

SymbolTable build( Program program )
{
	SymbolTable table;
	Declarations *decls = program.declarations;
	Declaration current;

	InitializeTable(&table);
	table.top = 0;
	while(decls !=NULL){
		current = decls->first;
		add_table(&table, current.name, current.type);
		decls = decls->rest;
	}

	return table;
}


/********************************************************************
  Type checking
 *********************************************************************/

void convertType( Expression * old, DataType type )
{
	if(old->type == Float && type == Int){
		printf("error : can't convert float to integer\n");
		return;
	}
	if(old->type == Int && type == Float){
		Expression *tmp = (Expression *)malloc( sizeof(Expression) );
		if(old->v.type == Identifier)
			printf("convert to float %s \n",old->v.val.id);
		else
			printf("convert to float %d \n", old->v.val.ivalue);
		tmp->v = old->v;
		tmp->leftOperand = old->leftOperand;
		tmp->rightOperand = old->rightOperand;
		tmp->type = old->type;

		Value v;
		v.type = IntToFloatConvertNode;
		v.val.op = IntToFloatConvert;
		old->v = v;
		old->type = Int;
		old->leftOperand = tmp;
		old->rightOperand = NULL;
		return;
	}
}

DataType generalize( Expression *left, Expression *right )
{
	if(left->type == Float || right->type == Float){
		printf("generalize : float\n");
		return Float;
	}
	printf("generalize : int\n");
	return Int;
}

DataType lookup_table( SymbolTable *table, char* name )
{
	int i = 0;
	while( i<table->top && strcmp(table->name[i], name))
		i++;
	
	if( i == table->top)
	{
		printf("Error : identifier %s is not declared\n", name);//error
		return Notype;
	}
	return table->type[i];
}

void checkexpression( Expression * expr, SymbolTable * table )
{
	char* name;
	if(expr->leftOperand == NULL && expr->rightOperand == NULL){
	//expr is a value, it's integer or float or a variable
		switch(expr->v.type){
			case Identifier:
				name = expr->v.val.id;
				printf("identifier : %s\n",name);
				expr->type = lookup_table(table, name);
				break;
			case IntConst:
				printf("constant : int\n");
				expr->type = Int;
				break;
			case FloatConst:
				printf("constant : float\n");
				expr->type = Float;
				break;
				//case PlusNode: case MinusNode: case MulNode: case DivNode:
			default:
				break;
		}
	}
	else{
		Expression *left = expr->leftOperand;
		Expression *right = expr->rightOperand;

		checkexpression(left, table);
		checkexpression(right, table);
		
		DataType type = generalize(left, right);
		convertType(left, type);//left->type = type;//converto
		convertType(right, type);//right->type = type;//converto
		expr->type = type;
	}
}

void checkstmt( Statement *stmt, SymbolTable * table )
{
	if(stmt->type == Assignment){
		AssignmentStatement assign = stmt->stmt.assign;
		printf("assignment : %s \n",assign.id);
		checkexpression(assign.expr, table);
		stmt->stmt.assign.type = lookup_table(table, assign.id);
		if (assign.expr->type == Float && stmt->stmt.assign.type == Int) {
			printf("error : can't convert float to integer\n");
		} else {
			convertType(assign.expr, stmt->stmt.assign.type);
		}
	}
	else if (stmt->type == Print){
		printf("print : %s \n",stmt->stmt.variable);
		lookup_table(table, stmt->stmt.variable);
	}
	else printf("error : statement error\n");//error
}

void check( Program *program, SymbolTable * table )
{
	Statements *stmts = program->statements;
	while(stmts != NULL){
		checkstmt(&stmts->first,table);
		stmts = stmts->rest;
	}
}


/***********************************************************************
  Code generation
 ************************************************************************/
void fprint_op( FILE *target, ValueType op )
{
	switch(op){
		case MinusNode:
			fprintf(target,	"-\n");
			break;
		case PlusNode:
			fprintf(target,	"+\n");
			break;
		case MulNode:
			fprintf(target, "*\n");
			break;
		case DivNode:
			fprintf(target, "/\n");
			break;
		default:
			fprintf(target,"Error in fprintf_op ValueType = %d\n",op);
			break;
	}
}

void fprint_expr( FILE *target, Expression *expr, SymbolTable table)
{

    if(expr->leftOperand == NULL){
	int i;
        switch( (expr->v).type ){
            case Identifier:
		i = 0;
		while(strcmp(table.name[i], (expr->v).val.id))
			i++;	
                fprintf(target,"l%c\n", (char)(i+65));
                break;
            case IntConst:
                fprintf(target,"%d\n",(expr->v).val.ivalue);
                break;
            case FloatConst:
                fprintf(target,"%f\n", (expr->v).val.fvalue);
                break;
            default:
                fprintf(target,"Error In fprint_left_expr. (expr->v).type=%d\n",(expr->v).type);
                break;
        }
    }
    else{
        if(expr->rightOperand == NULL)
	{	
                fprintf(target,"%f\n", (float)(expr->leftOperand->v).val.ivalue);
        	fprintf(target,"5k\n");
        }
        else
	{
       		fprint_expr(target, expr->leftOperand, table);
            	fprint_expr(target, expr->rightOperand, table);
            	fprint_op(target, (expr->v).type);
        }
    }
}

void gencode(Program prog, FILE * target, SymbolTable table)
{
	Statements *stmts = prog.statements;
	Statement stmt;
	int i;

	while(stmts != NULL){
		stmt = stmts->first;
		switch(stmt.type){
			case Print:
				i = 0;
				while(strcmp(table.name[i], stmt.stmt.variable))
					i++;	
				fprintf(target,"l%c\n", (char)(i+65));
				fprintf(target,"p\n");
				break;
			case Assignment:
				fprint_expr(target, stmt.stmt.assign.expr, table);
				/*
				   if(stmt.stmt.assign.type == Int){
				   fprintf(target,"0 k\n");
				   }
				   else if(stmt.stmt.assign.type == Float){
				   fprintf(target,"5 k\n");
				   }*/
				i = 0;
				while(strcmp(table.name[i], stmt.stmt.assign.id))
					i++;
       			        fprintf(target,"s%c\n", (char)(i+65));
				fprintf(target,"0 k\n");
				break;
		}
		stmts=stmts->rest;
	}

}


/***************************************
  For our debug,
  you can omit them.
 ****************************************/
void print_expr(Expression *expr)
{
	if(expr == NULL)
		return;
	else{
		print_expr(expr->leftOperand);
		switch((expr->v).type){
			case Identifier:
				printf("%s ", (expr->v).val.id);
				break;
			case IntConst:
				printf("%d ", (expr->v).val.ivalue);
				break;
			case FloatConst:
				printf("%f ", (expr->v).val.fvalue);
				break;
			case PlusNode:
				printf("+ ");
				break;
			case MinusNode:
				printf("- ");
				break;
			case MulNode:
				printf("* ");
				break;
			case DivNode:
				printf("/ ");
				break;
			case IntToFloatConvertNode:
				printf("(float) ");
				break;
			default:
				printf("error ");
				break;
		}
		print_expr(expr->rightOperand);
	}
}

void test_parser( FILE *source )
{
	Declarations *decls;
	Statements *stmts;
	Declaration decl;
	Statement stmt;
	Program program = parser(source);

    decls = program.declarations;

    while(decls != NULL){
        decl = decls->first;
        if(decl.type == Int)
            printf("i ");
        if(decl.type == Float)
            printf("f ");
        printf("%s ",decl.name);
        decls = decls->rest;
    }

    stmts = program.statements;

    while(stmts != NULL){
        stmt = stmts->first;
        if(stmt.type == Print){
            printf("p %s ", stmt.stmt.variable);
        }

        if(stmt.type == Assignment){
            printf("%s = ", stmt.stmt.assign.id);
            print_expr(stmt.stmt.assign.expr);
        }
        stmts = stmts->rest;
    }

}
