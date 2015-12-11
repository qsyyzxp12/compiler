#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
int g_anyErrorOccur = 0;
DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
DATA_TYPE toPointer(DATA_TYPE dt);

// TODO: while, for, if ...'s block || refact existing functions


void semanticAnalysis(AST_NODE *root){
  root->processProgramNode();
}
void AST_NODE::processProgramNode(){
  AST_NODE *nowc = child;
  while(nowc){//global_decl: decl_list func_decl | func_decl
    if(nowc->nodeType == VARIABLE_DECL_LIST_NODE){//decl_list: process all children
      processChildren(&AST_NODE::processDeclarationNode);
    } else{//func_decl
      nowc->processDeclarationNode();
    }
    nowc = nowc->rightSibling;
  }
}
void AST_NODE::processChildren(void(AST_NODE::*fn)()){
  AST_NODE* nowc = child;
  while(nowc != NULL){
    (nowc->*fn)();
    nowc = nowc->rightSibling;
  }  
}
void AST_NODE::processDeclarationNode(){
  //including func_decl, type_decl, var_decl + param_list
  node* typeNode = child;
  typeNode->processTypeNode();
  if(typeNode->dataType == ERROR_TYPE)
    return;

  TypeDescriptor* typeTypeDescriptor = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;

  switch(semantic_value.declSemanticValue.kind){
  case VARIABLE_DECL:
    declareIdList(typeTypeDescriptor, VARIABLE_ATTRIBUTE, false);
    break;
  case TYPE_DECL:
    declareIdList(typeTypeDescriptor, TYPE_ATTRIBUTE, false);
    break;
  case FUNCTION_DECL:
    declareFunction();
    break;
  case FUNCTION_PARAMETER_DECL:
    declareIdList(typeTypeDescriptor, VARIABLE_ATTRIBUTE, true);//ignore first dim of array
    break;
  }
}
void AST_NODE::declareIdList(TypeDescriptor* typeTypeDescriptor, int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize){//ok
  //id_list, init_id_list
  node* nowc = child->rightSibling;//except type node
  while(nowc != NULL){
    nowc->declareId(isVariableOrTypeAttribute, ignoreArrayFirstDimSize, typeTypeDescriptor);
    nowc = nowc->rightSibling;
  }
}
void AST_NODE::declareId(int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize, TypeDescriptor* typeTypeDescriptor){//ok
  //KNOWN: ast_node's attr(typenode's information), TOFILL: symbolentry's attr(SymbolAttribute)
  //FORMAT: var_decl: init_id: a(normal), a[10](array), a = 10(with_init_id)
  //FORMAT: type_decl: type a, type a[10], (type only has int, float, void)
  //FORMAT: param_list: the same as type_decl 
  //TODO: no type=ID?
  if(typeTypeDescriptor->properties.dataType == VOID_TYPE && isVariableOrTypeAttribute == VARIABLE_ATTRIBUTE){
    printErrorMsg(VOID_VARIABLE);
    setError();
    return;
  }

  IdentifierSemanticValue& semVal = semantic_value.identifierSemanticValue;
  if(declaredLocally(semVal.identifierName)){
    printErrorMsg(SYMBOL_REDECLARE);
    return;
  }

  SymbolAttribute* idAttr = new SymbolAttribute;
  idAttr->attributeKind = SymbolAttributeKind(isVariableOrTypeAttribute);
  TypeDescriptor* idTypeDescriptor;
  //fprintf(stderr, "try to declare %s\n", semVal.identifierName);
  switch(semVal.kind){
  case NORMAL_ID:
    idAttr->attr.typeDescriptor = typeTypeDescriptor;
    break;
  case ARRAY_ID:// dim_decl
    dataType = typeTypeDescriptor->properties.arrayProperties.elementType;
    idTypeDescriptor = new TypeDescriptor;
    idTypeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
    processDeclDimList(idTypeDescriptor, ignoreArrayFirstDimSize);
    
    if(dataType == ERROR_TYPE){
      delete idTypeDescriptor;
    } else {
      idTypeDescriptor->properties.arrayProperties.elementType = typeTypeDescriptor->properties.dataType;
      idAttr->attr.typeDescriptor = idTypeDescriptor;
    }
    break;
  case WITH_INIT_ID: // = relop_expr
    idAttr->attr.typeDescriptor = typeTypeDescriptor;
    child->processNodeWithValue();
    if (child->dataType == INT_PTR_TYPE || child->dataType == FLOAT_PTR_TYPE) {//cannot assign pointer
      printErrorMsg(INCOMPATIBLE_ARRAY_DIMENSION);
      setError();
    } else if(typeTypeDescriptor->properties.dataType == INT_TYPE && child->dataType == FLOAT_TYPE){
      printErrorMsg(ASSIGN_FLOAT_TO_INT);
      setError();
    } else if(child->dataType == CONST_STRING_TYPE){
      printErrorMsg(STRING_OPERATION);
      setError();
    } else if(child->dataType == VOID_TYPE){
      printErrorMsg(VOID_ASSIGNMENT);
      setError();
    }
    break;
  default:
    fprintf(stderr, "error: declareIdList()\n");
    setError();
    break;
  }
      
  if(dataType == ERROR_TYPE){
    delete idAttr;
  } else {
    semVal.symbolTableEntry = enterSymbol(semVal.identifierName, idAttr);
  }
}
void AST_NODE::processTypeNode(){
  SymbolTableEntry* symbolTableEntry = retrieveSymbol(semantic_value.identifierSemanticValue.identifierName);
  if (symbolTableEntry == NULL){
    printErrorMsg(SYMBOL_UNDECLARED);
    setError();
  } else {
    semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;

    switch (symbolTableEntry->attribute->attr.typeDescriptor->kind){
    case SCALAR_TYPE_DESCRIPTOR:
      dataType = symbolTableEntry->attribute->attr.typeDescriptor->properties.dataType;
      break;
    case ARRAY_TYPE_DESCRIPTOR:
      dataType = symbolTableEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
      break;
    }
    if(symbolTableEntry->attribute->attributeKind == FUNCTION_SIGNATURE){
      printErrorMsg(DECLARED_AS_FUNCTION);
      setError();
    }
  }
}
void AST_NODE::processDeclDimList(TypeDescriptor* typeDescriptor, int ignoreFirstDimSize){//TODO: unlimited array dimension size
  //dim_decl: expr
  AST_NODE* nowDim = child;
  int dimension = 0;
  if(ignoreFirstDimSize){//maybe ignored
    if(nowDim->nodeType == NUL_NODE){
      typeDescriptor->properties.arrayProperties.sizeInEachDimension[0] = 0;// if [], set to 0
      nowDim = nowDim->rightSibling;
      dimension++;
    }
  }

  int dimSize;
  while(nowDim){
    if(dimension >= MAX_ARRAY_DIMENSION)//array full 
      break;
    nowDim->processNodeWithValue();
    switch(nowDim->dataType){
    case INT_TYPE:
      dimSize = nowDim->semantic_value.exprSemanticValue.constEvalValue.iValue;
      if(dimSize <= 0){
	printErrorMsg(ARRAY_SIZE_NEGATIVE);
	setError();
      } else {
	typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = dimSize;
      }
      break;
    case ERROR_TYPE:
      break;
    default:
      nowDim->parent->printErrorMsg(ARRAY_SIZE_NOT_INT);
      setError();
      break;
    }
    nowDim = nowDim->rightSibling;
    dimension++;
  }

  if(dimension >= MAX_ARRAY_DIMENSION){
    printErrorMsg(EXCESSIVE_ARRAY_DIM_DECLARATION);
    setError();
  } else {
    typeDescriptor->properties.arrayProperties.dimension = dimension;
  }
}
void AST_NODE::processNodeWithValue(){
  switch(nodeType){
  case EXPR_NODE:
    processExprNode();
    break;
  case STMT_NODE:
    checkFunctionCall();
    break;
  case IDENTIFIER_NODE:
    processIDExpr();
    break;
  case CONST_VALUE_NODE:
    processConstExpr();
    break;
  default:
    fprintf(stderr, "ERROR: cannot get value\n");
    setError();
    break;
  }
}
void AST_NODE::declareFunction(){
  //FORMAT: int a(...){}
  //INCLUDE: return(type), functionname(ID), param_list(similar to declareidlist, but without with_init_id), block(block)

  //1. return type
  AST_NODE* returnNode = child;

  SymbolAttribute* funcAttr = new SymbolAttribute;
  funcAttr->attr.functionSignature = new FunctionSignature;
  funcAttr->attributeKind = FUNCTION_SIGNATURE;
  funcAttr->attr.functionSignature->returnType = returnNode->dataType;
  funcAttr->attr.functionSignature->parameterList = NULL;

  //2. function name
  AST_NODE* idNode = returnNode->rightSibling;
  char* functionName = idNode->semantic_value.identifierSemanticValue.identifierName;
  if(declaredLocally(functionName)){
    idNode->printErrorMsg(SYMBOL_REDECLARE);
    idNode->setError();//TODO: redeclare and undeclared seterror in retreieve symbol or entersymbol
    setError();
    return;
  } else {
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry = enterSymbol(functionName, funcAttr);
  }

  //3. parameter
  openScope();
    
  AST_NODE *parameterListNode = idNode->rightSibling;
  AST_NODE *nowParameter = parameterListNode->child;
  funcAttr->attr.functionSignature->parametersCount = 0;
  bool parameterError = false;
  while(nowParameter){
    funcAttr->attr.functionSignature->parametersCount++;
    nowParameter->processDeclarationNode();

    if(nowParameter->dataType == ERROR_TYPE){
      parameterError = true;
      break;
    } else {
      Parameter *parameter = new Parameter;
      parameter->next = NULL;
      IdentifierSemanticValue& idSemanticValue = nowParameter->child->rightSibling->semantic_value.identifierSemanticValue;
      parameter->parameterName = idSemanticValue.identifierName;
      parameter->type = idSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
      if(funcAttr->attr.functionSignature->parameterList == NULL){//first
	funcAttr->attr.functionSignature->parameterList = parameter;
      } else {
	funcAttr->attr.functionSignature->parameterList->next = parameter;//add to the end of list
	funcAttr->attr.functionSignature->parameterList = parameter;
      }
    }
    nowParameter = nowParameter->rightSibling;
  }
  if(parameterError){//clean all 
    removeSymbol(functionName);
    Parameter* parameter = funcAttr->attr.functionSignature->parameterList;
    while(parameter){
      Parameter* todelete = parameter;
      parameter = parameter->next;
      delete todelete;
    }
    delete funcAttr->attr.functionSignature;
    delete funcAttr;
    closeScope();//not so good
    return;
  }

  //4. block, share the same scope as parameters
  AST_NODE *blockNode = parameterListNode->rightSibling;
  blockNode->processChildren(&AST_NODE::processBlock);
  AST_NODE *inBlockNode = blockNode->child;
  bool hasReturnStmt = false;
  while(inBlockNode){
    if(inBlockNode->nodeType == STMT_LIST_NODE){
      node* nows = inBlockNode->child;
      while(nows){
	if(nows->nodeType == STMT_NODE && nows->semantic_value.stmtSemanticValue.kind == RETURN_STMT){
	  hasReturnStmt = true;
	  break;
	}
	nows = nows->rightSibling;
      }
      if(hasReturnStmt)
	break;
    }
    inBlockNode = inBlockNode->rightSibling;
  }
  if(!hasReturnStmt && returnNode->dataType != VOID_TYPE){//no return value in int/float function
    printErrorMsg(RETURN_TYPE_UNMATCH);
    setError();
  }

  closeScope();
}
void AST_NODE::processExprNode(){
  // +-*/ , relop_expr
  if(semantic_value.exprSemanticValue.kind == BINARY_OPERATION){//binary
    AST_NODE* leftExp = this->child;
    AST_NODE* rightExp = leftExp->rightSibling;
    leftExp->processNodeWithValue();
    rightExp->processNodeWithValue();
    leftExp->checkExprType();
    rightExp->checkExprType();

    if((dataType != ERROR_TYPE) && leftExp->isConst() && rightExp->isConst()){//if const, evaluate it's value
      evaluateBinaryExprValue();
      semantic_value.exprSemanticValue.isConstEval = 1;
    } else {
      if(dataType != ERROR_TYPE){//not sure it const or not
	switch(semantic_value.exprSemanticValue.op.binaryOp){
	case BINARY_OP_EQ:
	case BINARY_OP_GE:
	case BINARY_OP_LE:
	case BINARY_OP_NE:
	case BINARY_OP_GT:
	case BINARY_OP_LT: 
	case BINARY_OP_AND:
	case BINARY_OP_OR:
	  dataType = INT_TYPE;//bool TODO: it's dangerous because (a && b) + c is correct, but C also admit this
	  break;
	default:
	  dataType = getBiggerType(leftExp->dataType, rightExp->dataType);
	  break;
	}
      }
    }
  } else {//unary
    child->processNodeWithValue();
    if(semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_LOGICAL_NEGATION)
      dataType = INT_TYPE;//bool
    else 
      dataType = child->dataType;
    child->checkExprType();
    if((dataType != ERROR_TYPE) && child->isConst()){//needed because a[3+3]
      evaluateUnaryExprValue();
      semantic_value.exprSemanticValue.isConstEval = 1;
    }
  }
}
void AST_NODE::checkExprType(){
  switch(dataType){
  case INT_PTR_TYPE:
  case FLOAT_PTR_TYPE:
    printErrorMsg(INCOMPATIBLE_ARRAY_DIMENSION);
    setError();
    break;
  case VOID_TYPE:
    printErrorMsg(VOID_ASSIGNMENT);
    setError();
    break;
  case ERROR_TYPE:
    setError();
    break;
  }
}
void AST_NODE::evaluateBinaryExprValue(){
  AST_NODE* leftOp = child;
  AST_NODE* rightOp = leftOp->rightSibling;
  float leftValue = leftOp->getValue();
  float rightValue = rightOp->getValue();

  switch(semantic_value.exprSemanticValue.op.binaryOp){//if it's relation operator, calculate and return
  case BINARY_OP_EQ:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue == rightValue;
    break;
  case BINARY_OP_GE:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue >= rightValue;
    break;
  case BINARY_OP_LE:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue <= rightValue;
    break;
  case BINARY_OP_NE:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue != rightValue;
    break;
  case BINARY_OP_GT:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue > rightValue;
    break;
  case BINARY_OP_LT:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue < rightValue;
    break;
  case BINARY_OP_AND:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue && rightValue;
    break;
  case BINARY_OP_OR:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue || rightValue;
    break;
  default:
    evaluateNonRelationExpr(leftOp, rightOp, leftValue, rightValue);
    break;
  }
}
void AST_NODE::evaluateNonRelationExpr(node* leftOp, node* rightOp, float lvalue, float rvalue){
  float value;
  switch(semantic_value.exprSemanticValue.op.binaryOp){
  case BINARY_OP_ADD:
    value = lvalue + rvalue;
    break;
  case BINARY_OP_SUB:
    value = lvalue - rvalue;
    break;
  case BINARY_OP_MUL:
    value = lvalue * rvalue;
    break;
  case BINARY_OP_DIV:
    value = lvalue / rvalue;
    break;
  default:
    break;
  }
  if(leftOp->dataType == INT_TYPE && rightOp->dataType == INT_TYPE){
    dataType = INT_TYPE;
    value = semantic_value.exprSemanticValue.constEvalValue.iValue = value;
  } else {
    dataType = FLOAT_TYPE;
    value = semantic_value.exprSemanticValue.constEvalValue.fValue = value;
  }
}
void AST_NODE::evaluateUnaryExprValue(){
  AST_NODE* operand = child;
  float operandValue = operand->getValue();
  float value;
  dataType = INT_TYPE;
  switch(semantic_value.exprSemanticValue.op.unaryOp){
  case UNARY_OP_POSITIVE:
    value = operandValue;
    break;
  case UNARY_OP_NEGATIVE:
    value = -operandValue;
    break;
  case UNARY_OP_LOGICAL_NEGATION:
    value = !operandValue;
    break;
  default:
    break;
  }
  if(operand->dataType == INT_TYPE){
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = value;
  } else {
    dataType = FLOAT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.fValue = value;
  }
}
float AST_NODE::getValue(){
  if(nodeType == CONST_VALUE_NODE){
    if(dataType == INT_TYPE)
      return semantic_value.const1->const_u.intval;
    else
      return semantic_value.const1->const_u.fval;
  } else {//expr
    if(dataType == INT_TYPE)
      return semantic_value.exprSemanticValue.constEvalValue.iValue;
    else
      return semantic_value.exprSemanticValue.constEvalValue.fValue;
  } 
}
bool AST_NODE::isConst(){
  return nodeType == CONST_VALUE_NODE || (nodeType == EXPR_NODE && semantic_value.exprSemanticValue.isConstEval);
}

void AST_NODE::checkReturnStmt(){
  AST_NODE* parentNode = parent;
  while(parentNode){//get return datatype
    if(parentNode->nodeType == DECLARATION_NODE){
      if(parentNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL)
	dataType = parentNode->child->dataType;
      break;
    }
    parentNode = parentNode->parent;
  }

  if(child->nodeType == NUL_NODE){
    if(dataType != VOID_TYPE){//return nothing in non-void function
      printErrorMsg(RETURN_TYPE_UNMATCH);
      setError();
    }
  } else {
    child->processNodeWithValue();
    if((dataType != child->dataType) && !((dataType == FLOAT_TYPE) && (child->dataType == INT_TYPE))){
      printErrorMsg(RETURN_TYPE_UNMATCH);
      setError();
    }
  }
}
void AST_NODE::processBlockNode(){//in-function block
  openScope();
  processChildren(&AST_NODE::processBlock);
  closeScope();
}
void AST_NODE::processBlock(){//including decl, stmt, assign
  AST_NODE *nowc = child;
  switch(nodeType){//TODO: use class polynomial
  case VARIABLE_DECL_LIST_NODE:
    //fprintf(stderr, "VARIABLE_DECL_LIST_NODE\n");
    processChildren(&AST_NODE::processDeclarationNode);
    break;
  case STMT_LIST_NODE:
    //fprintf(stderr, "STMT_LIST_NODE\n");
    processChildren(&AST_NODE::processStmtNode);
    break;
  case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
    //fprintf(stderr, "NONEMPTY_ASSIGN_EXPR_LIST_NODE\n");
    processChildren(&AST_NODE::processAssignOrExpr);
    break;
  case NONEMPTY_RELOP_EXPR_LIST_NODE:
    //fprintf(stderr, "NONEMPTY_RELOP_EXPR_LIST_NODE\n");
    processChildren(&AST_NODE::processNodeWithValue);
    break;
  case NUL_NODE:
    break;
  default:
    setError();
    break;
  }  
}

void AST_NODE::processStmtNode(){
  /*
exception  MK_LBRACE block MK_RBRACE  : $$ = $2;
           MK_SEMICOLON : $$ = Allocate(NUL_NODE);
  */
  if(nodeType == NUL_NODE){
    return;
  } else if(nodeType == BLOCK_NODE){
    //fprintf(stderr, "BLOCK_NODE\n");
    processBlockNode();
  } else{
    switch(semantic_value.stmtSemanticValue.kind){
    case WHILE_STMT:
      checkWhileStmt();
      break;
    case FOR_STMT:
      checkForStmt();
      break;
    case ASSIGN_STMT:
      //fprintf(stderr, "assign stmt\n");
      checkAssignmentStmt();
      break;
    case IF_STMT:
      checkIfStmt();
      break;
    case FUNCTION_CALL_STMT:
      //fprintf(stderr, "func call stmt\n");
      checkFunctionCall();
      break;
    case RETURN_STMT:
      //fprintf(stderr, "return stmt\n");
      checkReturnStmt();
      break;
    default:
      printf("ERROR:processStmtNode()\n");
      setError();
      break;
    }
  }
}
void AST_NODE::processAssignOrExpr(){
  if(nodeType == STMT_NODE){//which can be looked as value
    if(semantic_value.stmtSemanticValue.kind == ASSIGN_STMT)
      checkAssignmentStmt();
    else if(semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
      checkFunctionCall();
  } else {
    processNodeWithValue();
  }
}
void AST_NODE::processVariableLValue(){//I think it's the same, if don't consider typedef array
  processIDExpr();
}
void AST_NODE::processIDExpr(){
  SymbolTableEntry *symbolTableEntry = retrieveSymbol(semantic_value.identifierSemanticValue.identifierName);
  semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
  if(!symbolTableEntry){
    printErrorMsg(SYMBOL_UNDECLARED);
    setError();
    return;
  }

  TypeDescriptor *typeDescriptor = semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
  if(semantic_value.identifierSemanticValue.kind == NORMAL_ID){
    if(typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR){
      printErrorMsg(INCOMPATIBLE_ARRAY_DIMENSION);
      setError();
    } else {
      dataType = typeDescriptor->properties.dataType;
    }
  } else if(semantic_value.identifierSemanticValue.kind == ARRAY_ID){
    dataType = typeDescriptor->properties.arrayProperties.elementType;
    int dimension = 0;
    AST_NODE *nowc = child;
    while(nowc != NULL){
      nowc->processNodeWithValue();
      if(nowc->dataType == FLOAT_TYPE){
	printErrorMsg(ARRAY_SUBSCRIPT_NOT_INT);
	setError();
      }
      nowc = nowc->rightSibling;
      dimension++;
    }
    if(dimension != typeDescriptor->properties.arrayProperties.dimension){
      printErrorMsg(INCOMPATIBLE_ARRAY_DIMENSION);
      setError();
    }
  }
}
void AST_NODE::processConstExpr(){     //cexpr
  switch(semantic_value.const1->const_type){
  case INTEGERC:
    dataType = INT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.iValue = semantic_value.const1->const_u.intval;
    break;
  case FLOATC:
    dataType = FLOAT_TYPE;
    semantic_value.exprSemanticValue.constEvalValue.fValue = semantic_value.const1->const_u.fval;
    break;
  case STRINGC:
    dataType = CONST_STRING_TYPE;
    break;
  default:
    fprintf(stderr, "ERROR: processConstExpr()\n");
    break;
  }
}

void AST_NODE::checkAssignmentStmt(){
  AST_NODE* leftOp = child;
  AST_NODE* rightOp = leftOp->rightSibling;
  leftOp->processVariableLValue();
  rightOp->processNodeWithValue();

  if(leftOp->dataType != ERROR_TYPE && rightOp->dataType != ERROR_TYPE)
    dataType = getBiggerType(leftOp->dataType, rightOp->dataType);
  if(rightOp->dataType == INT_PTR_TYPE || rightOp->dataType == FLOAT_PTR_TYPE){
    rightOp->printErrorMsg(INCOMPATIBLE_ARRAY_DIMENSION);
    setError();
  }
}
void AST_NODE::checkFunctionCall(){
  //FORMAT:  a(b, c, d)
  SymbolTableEntry* symbolTableEntry = retrieveSymbol(child->semantic_value.identifierSemanticValue.identifierName);
  child->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
  if(symbolTableEntry == NULL){
    child->printErrorMsg(SYMBOL_UNDECLARED);
    child->setError();
    return;
  } else if(symbolTableEntry->attribute->attributeKind != FUNCTION_SIGNATURE){
    child->printErrorMsg(NOT_FUNCTION_NAME);
    child->setError();
    return;
  }
  AST_NODE* paraList = child->rightSibling;//relop_expr_list
  paraList->processChildren(&AST_NODE::processNodeWithValue);
  dataType = symbolTableEntry->attribute->attr.functionSignature->returnType;

  AST_NODE* firstInput = paraList->child;
  FunctionSignature* functionDefinition = symbolTableEntry->attribute->attr.functionSignature;
  if(firstInput == NULL && functionDefinition->parametersCount != 0){
    child->printErrorMsg(TOO_FEW_ARGUMENTS);
    setError();
  } else if(!firstInput->checkParameters(functionDefinition)){
    setError();
  }
}
bool AST_NODE::checkParameters(FunctionSignature* functionDefinition){//ok
  AST_NODE* nowInput = this;
  int inputCount = 0;
  while(nowInput != NULL){
    nowInput = nowInput->rightSibling;
    inputCount++;
  }
  //fprintf(stderr, "function def parameter count = %d, real input count = %d\n", functionDefinition->parametersCount, inputCount);
  if(functionDefinition->parametersCount > inputCount){
    parent->parent->child->printErrorMsg(TOO_FEW_ARGUMENTS);
    setError();
    return false;
  } else if(functionDefinition->parametersCount < inputCount){
    parent->parent->child->printErrorMsg(TOO_MANY_ARGUMENTS);
    setError();
    return false;
  }

  nowInput = this;
  Parameter* nowParameter = functionDefinition->parameterList;
  bool err = false;
  while(nowInput != NULL){
    if(nowInput->dataType == ERROR_TYPE){
      err = true;
    } else if(!nowInput->checkParameter(nowParameter))
      err = true;
    nowInput = nowInput->rightSibling;
    nowParameter = nowParameter->next;
  }
  return !err;
}
bool AST_NODE::checkParameter(Parameter* nowParameter){//ERROR TYPE 3
  if(nowParameter == NULL){
    setError();
    return false;
  }
  TypeDescriptorKind defineTD = nowParameter->type->kind;
  char* paraName = nowParameter->parameterName;
  if(defineTD == SCALAR_TYPE_DESCRIPTOR && isArray()){
    printErrorMsg(PASS_ARRAY_TO_SCALAR, paraName);
    setError();
    return false;
  } else if(defineTD == ARRAY_TYPE_DESCRIPTOR && !isArray()){
    printErrorMsg(PASS_SCALAR_TO_ARRAY, paraName);
    setError();
    return false;
  }
  return true;
}
inline bool AST_NODE::isArray(){
  return (dataType == INT_PTR_TYPE) || (dataType == FLOAT_PTR_TYPE);
}

void AST_NODE::checkWhileStmt(){//only process block
  child->processAssignOrExpr();//test
  child->rightSibling->processStmtNode();//stmt
}
void AST_NODE::checkForStmt(){//only process block
  node* nowc = child;
  nowc->processBlock();//assign_expr_list
  nowc = nowc->rightSibling;
  nowc->processBlock();  //relop_expr_list
  nowc = nowc->rightSibling;
  nowc->processBlock();  //assign_expr_list
  nowc = nowc->rightSibling;
  nowc->processStmtNode();  //stmt
}
void AST_NODE::checkIfStmt(){//only process block
  node* nowc = child;
  nowc->processAssignOrExpr();//test
  nowc = nowc->rightSibling;
  nowc->processStmtNode();  //stmt
  nowc = nowc->rightSibling;
  nowc->processStmtNode();  //stmt
}

void AST_NODE::setError(){
  node* nowNode = this;
  while(nowNode){
    nowNode->dataType = ERROR_TYPE;
    nowNode = nowNode->parent;
  }
}
void AST_NODE::printErrorMsg(ErrorMsgKind errorMsgKind, char* para){
  g_anyErrorOccur = 1;
  printf("Error found in line %d\n", linenumber);
  char* idName = semantic_value.identifierSemanticValue.identifierName;
  switch(errorMsgKind){
    /* error type 1 */
  case SYMBOL_UNDECLARED:
    printf("ID <%s> undeclared.\n", idName);
    break;
  case SYMBOL_REDECLARE:
    printf("ID <%s> redeclared.\n", idName);
    break;    
    /* error type 2 */
  case RETURN_TYPE_UNMATCH:
    printf("Warning: Incompatible return type.\n");
    break;
  case TOO_FEW_ARGUMENTS:
    printf("Too few arguments to function <%s>.\n", idName);
    break;
  case TOO_MANY_ARGUMENTS:
    printf("Too many arguments to function <%s>.\n", idName);
    break;
    /* error type 3 */
  case INCOMPATIBLE_ARRAY_DIMENSION:
    printf("Incompatible array dimensions.\n");
    break;    
  case ARRAY_SUBSCRIPT_NOT_INT://for expression
    /*
      (1) In programming, a symbol or number used to identify an element in an array. Usually, the subscript is placed in brackets following the array name. For example, AR[5] identifies element number 5 in an array called AR.
      If the array is multidimensional, you must specify a subscript for each dimension. For example, MD[5][3][9] identifies an element in a three-dimensional array called MD.
    */
    printf("Array subscript is not an integer.\n");
    break;
  case ARRAY_SIZE_NOT_INT://for declaration
    printf("Array size is not an integer.\n");
    break;
  case PASS_ARRAY_TO_SCALAR:
    printf("Array <%s> passed to scalar parameter <%s>.\n", idName, para);
    break;
  case PASS_SCALAR_TO_ARRAY:
    printf("Scalar <%s> passed to array parameter <%s>.\n", idName, para);
    break;
 /* addtion semantic error */
  case EXCESSIVE_ARRAY_DIM_DECLARATION:
    printf("dimension of %s excess %d.\n", idName, MAX_ARRAY_DIMENSION);
    break;
  case ARRAY_SIZE_NEGATIVE:
    printf("array %s size not positive.\n", idName);
    break;
  case ASSIGN_FLOAT_TO_INT:
    printf("assign float to integer ID %s\n", idName);
    break;
  case STRING_OPERATION:
    printf("string operation of %s\n", idName);
    break;
  case VOID_ASSIGNMENT:
    printf("assign void to %s\n", idName);
    break;
  case VOID_VARIABLE:
    printf("declare void variable %s\n", idName);
    break;
  case NOT_FUNCTION_NAME:
    printf("%s is not function name.\n", idName);
    break;
  case DECLARED_AS_FUNCTION:
    printf("declare variable with function type\n");
    break;
  default:
    printf("Unknown Error id %d.\n", errorMsgKind);
    break;
  }
}
const char* nodeTypeStr[] = {
  "PROGRAM_NODE",
  "DECLARATION_NODE",
  "IDENTIFIER_NODE",
  "PARAM_LIST_NODE",
  "NUL_NODE",
  "BLOCK_NODE",
  "VARIABLE_DECL_LIST_NODE",
  "STMT_LIST_NODE",
  "STMT_NODE",
  "EXPR_NODE",
  "CONST_VALUE_NODE", 
  "NONEMPTY_ASSIGN_EXPR_LIST_NODE",
  "NONEMPTY_RELOP_EXPR_LIST_NODE"
};
void AST_NODE::printNodeType(const char s[]){
  fprintf(stderr, "%s's nodetype = %s\n", s, nodeTypeStr[nodeType]);
}
DATA_TYPE toPointer(DATA_TYPE dt){
  if(dt == INT_TYPE){
    return INT_PTR_TYPE;
  } else if(dt == FLOAT_TYPE){
    return FLOAT_PTR_TYPE;
  } else {
    return ERROR_TYPE;
  }
}
DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2){
  if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
    return FLOAT_TYPE;
  } else {
    return INT_TYPE;
  }
}
