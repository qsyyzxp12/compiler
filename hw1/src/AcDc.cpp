#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stack>
#include "header.h"

std::stack<char> operatorStack;

Expression* handlePlusOp(FILE* source, Expression* lvalue);
Expression* handleMinusOp(FILE* source, Expression* lvalue);
Expression* handleMulOp(FILE* source, Expression* lvalue);
Expression* handleDivOp(FILE* source, Expression* lvalue);
bool isConst(ValueType t){
  return t == IntConst || t == FloatConst;
}
bool isLeaf(Expression* expr){
  return expr->leftOperand == NULL && expr->rightOperand == NULL;
}



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
            check(&program, &symtab);
            gencode(program, target);
        }
    }
    else{
        printf("Usage: %s source_file target_file\n", argv[0]);
    }


    return 0;
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
      //printf("start scanning, now position is %d\n", int(ftell(source)));
        c = fgetc(source);

        while( isspace(c) )
	  c = fgetc(source);

        if( isdigit(c) )
            return getNumericToken(source, c);

        token.tok[0] = c;
        token.tok[1] = '\0';
        if( islower(c) ){
            if( c == 'f' )
                token.type = FloatDeclaration;
            else if( c == 'i' )
                token.type = IntegerDeclaration;
            else if( c == 'p' )
                token.type = PrintOp;
            else{
	      token.type = Alphabet;
	      int nowi = 1;
	      while((c = fgetc(source)) != EOF  && isalpha(c)){
		token.tok[nowi++] = c;
	      }
	      printf("next word is %d. Stop, ", c);
	      printf("now position is %d.\n", int(ftell(source)));
	      token.tok[nowi] = '\0';

	      printf("scan variable (%s)\n", token.tok);
	      if(c != EOF){//space
		fseek(source, -1, SEEK_CUR);//back 1 character
		printf("back 1 character, now position is %d.\n", int(ftell(source)));
	      }
	    }
            return token;
        }
        switch(c){
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
	  fseek(source, -strlen(token.tok), SEEK_CUR);
	  //ungetc(token.tok[0], source);
	  //printf("ungetc alpha = %c\n", token.tok[0]);
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
	    (value->v).val.id = (char*)malloc(VARIABLE_LENGTH);
            strncpy((value->v).val.id, token.tok, VARIABLE_LENGTH);
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

Expression *parseExpressionTail( FILE *source, Expression *lvalue )
{
  Token token = scanner(source);
  Expression *expr, *newexpr;

  switch(token.type){
  case PlusOp:
    return handlePlusOp(source, lvalue);
  case MinusOp:
    return handleMinusOp(source, lvalue);
  case MulOp:
    return handleMulOp(source, lvalue);
  case DivOp:
    return handleDivOp(source, lvalue);
  case Alphabet:
    fseek(source, -strlen(token.tok), SEEK_CUR);
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

Expression* handlePlusOp(FILE* source, Expression* lvalue){
  Expression *expr, *newexpr;
  operatorStack.push('+');
  expr = (Expression *)malloc( sizeof(Expression) );
  (expr->v).type = PlusNode;
  (expr->v).val.op = Plus;
  expr->leftOperand = lvalue;

  Expression* value = parseValue(source);
  newexpr = parseExpression(source, value);
  if(newexpr == NULL){
    expr->rightOperand = value;
  } else {
    expr->rightOperand = newexpr;
  }
  return expr;
}
Expression* handleMinusOp(FILE* source, Expression* lvalue){
  Expression *expr, *newexpr;
  operatorStack.push('-');
  expr = (Expression *)malloc( sizeof(Expression) );
  (expr->v).type = MinusNode;
  (expr->v).val.op = Minus;
  expr->leftOperand = lvalue;

  Expression* value = parseValue(source);
  newexpr = parseExpression(source, value);
  if(newexpr == NULL){
    expr->rightOperand = value;
  } else {
    expr->rightOperand = newexpr;
  }
  return expr;
}
Expression* handleMulOp(FILE* source, Expression* lvalue){
  Expression *expr, *newexpr;
  expr = (Expression *)malloc( sizeof(Expression) );
  (expr->v).type = MulNode;
  (expr->v).val.op = Mul;
  expr->leftOperand = lvalue;
  expr->rightOperand = parseValue(source);
  operatorStack.push('*');
  return parseExpressionTail(source, expr);
}
Expression* handleDivOp(FILE* source, Expression* lvalue){
  Expression *expr, *newexpr;
  expr = (Expression *)malloc( sizeof(Expression) );
  (expr->v).type = DivNode;
  (expr->v).val.op = Div;
  expr->leftOperand = lvalue;
  expr->rightOperand = parseValue(source);
  operatorStack.push('/');
  return parseExpressionTail(source, expr);
}
Expression *parseExpression( FILE *source, Expression *lvalue )
{
  while(!operatorStack.empty()){
    operatorStack.pop();
  }
    Token token = scanner(source);
    Expression *expr, *newexpr;

    switch(token.type){// TODO: + - 在樹的較高層//this is the same as parseExpressiontail ..., can functionize
    case PlusOp:
      return handlePlusOp(source, lvalue);
    case MinusOp:
      return handleMinusOp(source, lvalue);
    case MulOp:
      return handleMulOp(source, lvalue);
    case DivOp:
      return handleDivOp(source, lvalue);
    case Alphabet:
      fseek(source, -strlen(token.tok), SEEK_CUR);
      return NULL;
    case PrintOp:
      ungetc(token.tok[0], source);
      return NULL;
    case EOFsymbol:
      return NULL;
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
      next_token = scanner(source);//second token
      if(next_token.type == AssignmentOp){
	value = parseValue(source);
	expr = parseExpression(source, value);
	int operatorCount = 1;
	while(!operatorStack.empty()){
	  printf("stack[%d]: %c\n", operatorCount++, operatorStack.top());
	  operatorStack.pop();
	}
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
    case Alphabet://assign
    case PrintOp://print
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
    if(tree_node.name == NULL){
      tree_node.name = (char*)malloc(VARIABLE_LENGTH);
    }
    strncpy(tree_node.name, identifier.tok, VARIABLE_LENGTH);

    return tree_node;
}

Declarations *makeDeclarationTree( Declaration decl, Declarations *decls )
{
    Declarations *new_tree = (Declarations *)malloc( sizeof(Declarations) );
    new_tree->first = decl;
    new_tree->rest = decls;

    return new_tree;
}


Statement makeAssignmentNode( char* id, Expression *v, Expression *expr_tail )//do constant folding
{
    Statement stmt;
    AssignmentStatement assign;

    stmt.type = Assignment;
    //if(assign.id == NULL) //sure to be null
    assign.id = (char*)malloc(VARIABLE_LENGTH);
    
    strncpy(assign.id, id, VARIABLE_LENGTH);
    if(expr_tail == NULL)
        assign.expr = v;
    else{
        assign.expr = expr_tail;
    }

    std::stack<ValueOperand> vstack;
    Expression* head = assign.expr;
    while(head != NULL && head->leftOperand != NULL && head->leftOperand->v.isConst() && isLeaf(head->leftOperand)){
      vstack.push(ValueOperand(head->leftOperand->v, head->v));
      head = head->rightOperand;
    }
    while(!vstack.empty()){
      vstack.top().print();
      vstack.pop();
      
    }
    stmt.stmt.assign = assign;

    return stmt;
}

Statement makePrintNode( char* id )
{
    Statement stmt;
    stmt.type = Print;
    stmt.stmt.variable = (char*)malloc(sizeof(char)*VARIABLE_LENGTH);
    strncpy(stmt.stmt.variable, id, VARIABLE_LENGTH);

    return stmt;
}

Statements *makeStatementTree( Statement stmt, Statements *stmts )//許多statment
{
    Statements *new_tree = (Statements *)malloc( sizeof(Statements) );
    new_tree->first = stmt;
    new_tree->rest = stmts;

    return new_tree;
}


void foldExpression(Expression* expr){
  if(expr->leftOperand == NULL){
    switch( (expr->v).type ){
    case Identifier:
      //fprintf(target,"l%s\n",(expr->v).val.id);
      break;
    case IntConst:
      //      fprintf(target,"%d\n",(expr->v).val.ivalue);
      break;
    case FloatConst:
      //fprintf(target,"%f\n", (expr->v).val.fvalue);
      break;
    default:
      //fprintf(target,"Error In fprint_left_expr. (expr->v).type=%d\n",(expr->v).type);
      break;
    }
  }
  else{
    //fprint_expr(target, expr->leftOperand);
    if(expr->rightOperand == NULL){
      //fprintf(target,"5k\n");
    }
    else{
      //	fprint_right_expr(expr->rightOperand);
      //fprint_expr(target, expr->rightOperand);
      //fprint_op(target, (expr->v).type);
    }
  }
}
void constantFolding(Statements* stmts){//TODO:
  //iterate all statement, find constant to fold
  Statements* statePointer = stmts;
  Statement toFold;
  
  while(statePointer != NULL){
    toFold = statePointer->first;
    switch(toFold.type){
    case Print:
      break;
    case Assignment:
      print_expr(toFold.stmt.assign.expr);
      //foldExpression(toFold.stmt.assign.expr);
      break;
    }
    statePointer=statePointer->rest;
  }
  
  /*while(isConst(toFold->value.type)){
    printf("fold %lf", double(toFold->leftOperand.Value));
    toFold = toFold->rightOperand;
    }*/
}

/* parser */
Program parser( FILE *source )
{
    Program program;

    program.declarations = parseDeclarations(source);
    program.statements = parseStatements(source);
    return program;
}


/********************************************************
  Build symbol table
 *********************************************************/
void InitializeTable( SymbolTable *table )
{
  table->clear();
}

void add_table( SymbolTable *table, char* s, DataType t )
{
  if(table->table.find(s) != table->table.end())
        printf("Error : id %s has been declared\n", s);//error
    table->table[s] = t;
}

SymbolTable build( Program program )
{
    SymbolTable table;
    Declarations *decls = program.declarations;
    Declaration current;

    InitializeTable(&table);

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

DataType lookup_table( SymbolTable *table, char* s )
{
  std::map<char*, DataType>::iterator it = table->table.find(s);
  if(it == table->table.end()){
    printf("Error : identifier %s is not declared\n", s);//error
    return Notype;
  }
  return table->table[s];
}

void checkexpression( Expression * expr, SymbolTable * table )
{
  char s[VARIABLE_LENGTH];
    if(expr->leftOperand == NULL && expr->rightOperand == NULL){
        switch(expr->v.type){
            case Identifier:
	      strncpy(s, expr->v.val.id, VARIABLE_LENGTH);
                printf("identifier : %s\n",s);
                expr->type = lookup_table(table, s);
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
    fprintf(target,"-\n");
    break;
  case PlusNode:
    fprintf(target,"+\n");
    break;
  case MulNode:
    fprintf(target,"*\n");
    break;
  case DivNode:
    fprintf(target,"/\n");
    break;
  default:
    fprintf(target,"Error in fprintf_op ValueType = %d\n",op);
    break;
  }
}

void fprint_expr( FILE *target, Expression *expr)
{

    if(expr->leftOperand == NULL){
        switch( (expr->v).type ){
            case Identifier:
                fprintf(target,"l%s\n",(expr->v).val.id);
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
        fprint_expr(target, expr->leftOperand);
        if(expr->rightOperand == NULL){
            fprintf(target,"5k\n");
        }
        else{
            //	fprint_right_expr(expr->rightOperand);
            fprint_expr(target, expr->rightOperand);
            fprint_op(target, (expr->v).type);
        }
    }
}

void gencode(Program prog, FILE * target)
{
    Statements *stmts = prog.statements;
    constantFolding(stmts);//TODO:
    Statement stmt;

    while(stmts != NULL){
      stmt = stmts->first;
      switch(stmt.type){
      case Print:
	fprintf(target,"l%s\n",stmt.stmt.variable);
	fprintf(target,"p\n");
	break;
      case Assignment:
	fprint_expr(target, stmt.stmt.assign.expr);
	/*
	  if(stmt.stmt.assign.type == Int){
	  fprintf(target,"0 k\n");
	  }
	  else if(stmt.stmt.assign.type == Float){
	  fprintf(target,"5 k\n");
	  }*/
	fprintf(target,"s%s\n",stmt.stmt.assign.id);
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
