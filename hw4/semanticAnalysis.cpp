#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //

#pragma GCC diagnostic ignored "-Wwrite-strings"

int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* returnTypeNode);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void processExprNode(AST_NODE* exprNode);

//newly add function
DATA_TYPE toPointer(DATA_TYPE dt);

// /0, void array, call variable as function, overflow, int[string]
typedef enum ErrorMsgKind
  {
    SYMBOL_IS_NOT_TYPE,
    SYMBOL_REDECLARE,
    SYMBOL_UNDECLARED,
    NOT_FUNCTION_NAME,
    TRY_TO_INIT_ARRAY,
    EXCESSIVE_ARRAY_DIM_DECLARATION,
    RETURN_ARRAY,
    VOID_VARIABLE,
    TYPEDEF_VOID_ARRAY,
    PARAMETER_TYPE_UNMATCH,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    RETURN_TYPE_UNMATCH,
    INCOMPATIBLE_ARRAY_DIMENSION,
    NOT_ASSIGNABLE,
    NOT_ARRAY,
    IS_TYPE_NOT_VARIABLE,
    IS_FUNCTION_NOT_VARIABLE,
    STRING_OPERATION,
    ARRAY_SIZE_NOT_INT,
    ARRAY_SIZE_NEGATIVE,
    ARRAY_SUBSCRIPT_NOT_INT,
    PASS_ARRAY_TO_SCALAR,
    PASS_SCALAR_TO_ARRAY
  } ErrorMsgKind;

void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind, char* para = ""){
  g_anyErrorOccur = 1;//TODO:??
  printf("Error found in line %d\n", node->linenumber);
  char* idName = node->semantic_value.identifierSemanticValue.identifierName;
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
    /* others */
  case EXCESSIVE_ARRAY_DIM_DECLARATION:
    printf("dimension of %s excess %d\n", idName, MAX_ARRAY_DIMENSION);
    break;
  default:
    printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind), %d\n", errorMsgKind);
    break;
  }
}
DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2){
  if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
    return FLOAT_TYPE;
  } else {
    return INT_TYPE;
  }
}


void semanticAnalysis(AST_NODE *root){
  root->processProgramNode();
}
void AST_NODE::processProgramNode(){
  AST_NODE *nowc = child;
  while(nowc){//global_decl: decl_list func_decl | func_decl
    if(nowc->nodeType == VARIABLE_DECL_LIST_NODE){//decl_list: process all children
      nowc->processDeclarationNodes();
    } else{//func_decl
      nowc->processDeclarationNode();
    }
    if(nowc->dataType == ERROR_TYPE)
      dataType = ERROR_TYPE;
    nowc = nowc->rightSibling;
  }
}

void AST_NODE::processDeclarationNodes(){
  AST_NODE* nowc = child;
  while(nowc != NULL){
    nowc->processDeclarationNode();
    if(nowc->dataType == ERROR_TYPE)
      dataType = ERROR_TYPE;
    nowc = nowc->rightSibling;
  }
}
void AST_NODE::processDeclarationNode(){//ok
  //including func_decl, type_decl, var_decl // func_para
  node* typeNode = child;
  typeNode->processTypeNode();
  if(typeNode->dataType == ERROR_TYPE){
    dataType = ERROR_TYPE;
    return;
  }
  switch(semantic_value.declSemanticValue.kind){
  case VARIABLE_DECL:
    declareIdList(VARIABLE_ATTRIBUTE, false);
    break;
  case TYPE_DECL:
    declareIdList(TYPE_ATTRIBUTE, false);
    break;
  case FUNCTION_DECL:
    declareFunction();
    break;
  case FUNCTION_PARAMETER_DECL:
    declareIdList(VARIABLE_ATTRIBUTE, true);//ignore first dim of array
    break;
  }
}
void AST_NODE::declareIdList(int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize){//ok
  //id_list, init_id_list
  //1. get type
  AST_NODE* typeNode = child;
  TypeDescriptor* typeTypeDescriptor = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
  //2. process each declare ID
  node* nowc = typeNode->rightSibling;
  while(nowc != NULL){
    nowc->declareId(isVariableOrTypeAttribute, ignoreArrayFirstDimSize, typeTypeDescriptor);
    if(nowc->dataType == ERROR_TYPE)
      dataType = ERROR_TYPE;
    nowc = nowc->rightSibling;
  }
}
void AST_NODE::declareId(int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize, TypeDescriptor* typeTypeDescriptor){//ok
  //KNOWN: ast_node's attr(typenode's information), TOFILL: symbolentry's attr(SymbolAttribute)
  //FORMAT: var_decl: init_id: a(normal), a[10](array), a = 10(with_init_id)
  //FORMAT: type_decl: type a, type a[10], (type only has int, float, void)
  //FORMAT: param_list: the same as type_decl 
  //TODO: no type=ID?
  
  IdentifierSemanticValue& semVal = semantic_value.identifierSemanticValue;
  fprintf(stderr, "try to declare %s\n", semVal.identifierName);
  if(declaredLocally(semVal.identifierName)){
    printErrorMsg(this, SYMBOL_REDECLARE);
    return;
  }

  SymbolAttribute* idAttr = new SymbolAttribute;
  idAttr->attributeKind = SymbolAttributeKind(isVariableOrTypeAttribute);
  TypeDescriptor* idTypeDescriptor;
  //fill TypeDescriptor
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
  case WITH_INIT_ID: //relop_expr
    idAttr->attr.typeDescriptor = typeTypeDescriptor;
    child->processExprRelatedNode();
    if (child->dataType == ERROR_TYPE) {//do not early return because need to list all errors
      dataType = ERROR_TYPE;
    }
    if (child->dataType == INT_PTR_TYPE || child->dataType == FLOAT_PTR_TYPE) {//cannot be pointer(means it's not fully inited)
      printErrorMsg(child, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
    }
    break;
  default:
    fprintf(stderr, "error: declareIdList()\n");
    dataType = ERROR_TYPE;
    break;
  }
      
  if(dataType == ERROR_TYPE){
    delete idAttr;
  } else {
    semVal.symbolTableEntry = enterSymbol(semVal.identifierName, idAttr);
  }
}
void AST_NODE::processTypeNode(){//ok
  SymbolTableEntry* symbolTableEntry = retrieveSymbol(semantic_value.identifierSemanticValue.identifierName);
  if (symbolTableEntry == NULL){
    printErrorMsg(this, SYMBOL_UNDECLARED);//TODO: inclass
    dataType = ERROR_TYPE;
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
  }
}
void AST_NODE::processDeclDimList(TypeDescriptor* typeDescriptor, int ignoreFirstDimSize){//ok
  //dim_decl: cexpr
  AST_NODE* nowDim = child;
  int dimension = 0;
  int size;
  if(ignoreFirstDimSize){//maybe ignored
    if(nowDim->nodeType == NUL_NODE){
      typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = 0;// if [], set to 0
      nowDim = nowDim->rightSibling;
      dimension++;
    }
  }
  while(nowDim){
    if(dimension >= MAX_ARRAY_DIMENSION)//array full
      break;
    
    nowDim->processConstExpr();//TODO: check(different)
    switch(nowDim->dataType){
    case INT_TYPE:
      size = nowDim->semantic_value.exprSemanticValue.constEvalValue.iValue;
      if(size <= 0){
	printErrorMsg(this, ARRAY_SIZE_NEGATIVE);//TODO:
	dataType = ERROR_TYPE;
      } else {
	typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = size;
      }
      break;
    case ERROR_TYPE:
      dataType = ERROR_TYPE;//TODO: can use error propogation do reduce this
      break;
    default:
      printErrorMsg(nowDim->parent, ARRAY_SIZE_NOT_INT);
      dataType = ERROR_TYPE;
      break;
    }
    
    nowDim = nowDim->rightSibling;
    dimension++;
  }

  if(dimension >= MAX_ARRAY_DIMENSION){
    printErrorMsg(this, EXCESSIVE_ARRAY_DIM_DECLARATION);//TODO:
    dataType = ERROR_TYPE;
  } else {
    typeDescriptor->properties.arrayProperties.dimension = dimension;
  }
}
void AST_NODE::processExprRelatedNode(){//TODO: rename?
  //process nodes which generate expr
  switch(nodeType){
  case EXPR_NODE:
    this->processExprNode();
    break;
  case STMT_NODE:
    this->checkFunctionCall();
    break;
  case IDENTIFIER_NODE:
    this->processIDExpr();
    break;
  case CONST_VALUE_NODE:
    this->processConstExpr();
    break;
  default:
    fprintf(stderr, "ERROR: exprRelatedNode()\n");
    dataType = ERROR_TYPE;
    break;
  }
}
void AST_NODE::declareFunction(){//ok
  //FORMAT: int a(...){}
  //INCLUDE: return(type), functionname(ID), param_list(similar to declareidlist, but without with_init_id), block(block)

  //1. return type
  AST_NODE* returnNode = child;

  SymbolAttribute* funcAttr = new SymbolAttribute;
  funcAttr->attributeKind = FUNCTION_SIGNATURE;
  funcAttr->attr.functionSignature = new FunctionSignature;
  funcAttr->attr.functionSignature->returnType = returnNode->dataType;
  funcAttr->attr.functionSignature->parameterList = NULL;

  //2. function name
  AST_NODE* idNode = returnNode->rightSibling;
  char* functionName = idNode->semantic_value.identifierSemanticValue.identifierName;
  bool redeclareError = false;
  if(declaredLocally(functionName)){
    printErrorMsg(idNode, SYMBOL_REDECLARE);
    idNode->dataType = ERROR_TYPE;
    redeclareError = true;
  } else {
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry = enterSymbol(functionName, funcAttr);
  }

  //3. parameter
  openScope();
    
  AST_NODE *parameterListNode = idNode->rightSibling;
  AST_NODE *nowParameter = parameterListNode->child;
  int parametersCount = 0;
  bool parameterError = false;
  while(nowParameter){
    parametersCount++;
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
  funcAttr->attr.functionSignature->parametersCount = parametersCount;

  //4. block, share the same scope as parameters
  if(!parameterError){//cannot process because some parameter is not correct//TODO: ask
    AST_NODE *blockNode = parameterListNode->rightSibling;
    AST_NODE *inBlockNode = blockNode->child;
    while(inBlockNode){
      inBlockNode->processGeneralNode();
      inBlockNode = inBlockNode->rightSibling;
    }
  }
  closeScope();

  //end
  if(redeclareError || parameterError){
    dataType = ERROR_TYPE;
    if(parameterError){
      removeSymbol(functionName);
      
      Parameter* parameter = funcAttr->attr.functionSignature->parameterList;
      while(parameter){
	Parameter* todelete = parameter;
	parameter = parameter->next;
	delete todelete;
      }
      delete funcAttr->attr.functionSignature;
      delete funcAttr;
    }
  }
}
void AST_NODE::processExprNode(){//ok
  // +-*/ , relop_expr
  if(semantic_value.exprSemanticValue.kind == BINARY_OPERATION){//binary
    AST_NODE* leftExp = this->child;
    AST_NODE* rightExp = leftExp->rightSibling;
    leftExp->processExprRelatedNode();
    rightExp->processExprRelatedNode();
    switch(leftExp->dataType){
    case INT_PTR_TYPE:
    case FLOAT_PTR_TYPE:
      printErrorMsg(leftExp, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
      break;
    case ERROR_TYPE:
    case VOID_TYPE:
      dataType = ERROR_TYPE;//TODO: print what error message?
      break;
    }
    switch(rightExp->dataType){
    case INT_PTR_TYPE:
    case FLOAT_PTR_TYPE:
      printErrorMsg(rightExp, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
      break;
    case ERROR_TYPE:
    case VOID_TYPE:
      dataType = ERROR_TYPE;//TODO: print what error message?
      break;
    }

    if((dataType != ERROR_TYPE) && leftExp->isConst() && rightExp->isConst()){//if const, evaluate it's value
      evaluateExprValue();
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
	  dataType = INT_TYPE;//bool
	  break;
	default:
	  dataType = getBiggerType(leftExp->dataType, rightExp->dataType);
	  break;
	}
      }
    }
  } else {//unary
    child->processExprRelatedNode();
    switch(child->dataType){
    case INT_PTR_TYPE:
    case FLOAT_PTR_TYPE:
      printErrorMsg(child, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
      break;
    case ERROR_TYPE:
    case VOID_TYPE:
      dataType = ERROR_TYPE;//TODO: print what error message?
      break;
    default:
      if(semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_LOGICAL_NEGATION)
	dataType = INT_TYPE;
      else 
	dataType = child->dataType;
      break;
    }

    if((dataType != ERROR_TYPE) && child->isConst()){
      evaluateExprValue();
      semantic_value.exprSemanticValue.isConstEval = 1;
    }
  }
}
void AST_NODE::evaluateExprValue(){//ok
  if(semantic_value.exprSemanticValue.kind == BINARY_OPERATION){
    evaluateBinaryExprValue();
  } else {
    evaluateUnaryExprValue();
  }
}
void AST_NODE::evaluateBinaryExprValue(){//ok
  AST_NODE* leftOp = child;
  AST_NODE* rightOp = leftOp->rightSibling;
  int leftValue = 0;
  int rightValue = 0;
  float leftValueF = 0;
  float rightValueF = 0;
  leftOp->getExprOrConstValue(&leftValue, NULL);
  rightOp->getExprOrConstValue(&rightValue, NULL);
  leftOp->getExprOrConstValue(NULL, &leftValueF);
  rightOp->getExprOrConstValue(NULL, &rightValueF);

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
  default://handled below
    if(leftOp->dataType == INT_TYPE && rightOp->dataType == INT_TYPE){
      dataType = INT_TYPE;
      switch(semantic_value.exprSemanticValue.op.binaryOp){
      case BINARY_OP_ADD:
	semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue + rightValue;
	break;
      case BINARY_OP_SUB:
	semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue - rightValue;
	break;
      case BINARY_OP_MUL:
	semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue * rightValue;
	break;
      case BINARY_OP_DIV:
	semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue / rightValue;
	break;
      default:
	break;
      }
    } else {
      dataType = FLOAT_TYPE;
      switch(semantic_value.exprSemanticValue.op.binaryOp){
      case BINARY_OP_ADD:
	semantic_value.exprSemanticValue.constEvalValue.fValue = leftValueF + rightValueF;
	break;
      case BINARY_OP_SUB:
	semantic_value.exprSemanticValue.constEvalValue.fValue = leftValueF - rightValueF;
	break;
      case BINARY_OP_MUL:
	semantic_value.exprSemanticValue.constEvalValue.fValue = leftValueF * rightValueF;
	break;
      case BINARY_OP_DIV:
	semantic_value.exprSemanticValue.constEvalValue.fValue = leftValueF / rightValueF;
	break;
      default:
	break;
      }
    }
    break;
  }
}
void AST_NODE::evaluateUnaryExprValue(){//ok
  AST_NODE* operand = child;
  if(operand->dataType == INT_TYPE){
    int operandValue = 0;
    operand->getExprOrConstValue(&operandValue, NULL);
    dataType = INT_TYPE;
    switch(semantic_value.exprSemanticValue.op.unaryOp){
    case UNARY_OP_POSITIVE:
      semantic_value.exprSemanticValue.constEvalValue.iValue = operandValue;
      break;
    case UNARY_OP_NEGATIVE:
      semantic_value.exprSemanticValue.constEvalValue.iValue = -operandValue;
      break;
    case UNARY_OP_LOGICAL_NEGATION:
      semantic_value.exprSemanticValue.constEvalValue.iValue = !operandValue;
      break;
    default:
      break;
    }
  } else {
    float operandValue = 0;
    operand->getExprOrConstValue(NULL, &operandValue);
    dataType = FLOAT_TYPE;
    switch(semantic_value.exprSemanticValue.op.unaryOp){
    case UNARY_OP_POSITIVE:
      semantic_value.exprSemanticValue.constEvalValue.fValue = operandValue;
      break;
    case UNARY_OP_NEGATIVE:
      semantic_value.exprSemanticValue.constEvalValue.fValue = -operandValue;
      break;
    case UNARY_OP_LOGICAL_NEGATION:
      dataType = INT_TYPE;
      semantic_value.exprSemanticValue.constEvalValue.iValue = !operandValue;
      break;
    default:
      printf("Unhandled case in void evaluateExprValue(AST_NODE* exprNode)\n");
      break;
    }
  }
}
void AST_NODE::getExprOrConstValue(int* iValue, float* fValue){//ok
  if(nodeType == CONST_VALUE_NODE){
    if(dataType == INT_TYPE){
      if(fValue){
	*fValue = semantic_value.const1->const_u.intval;
      } else{
	*iValue = semantic_value.const1->const_u.intval;
      }
    } else {
      *fValue = semantic_value.const1->const_u.fval;
    }
  } else {//expr
    if(dataType == INT_TYPE){
      if(fValue){
	*fValue = semantic_value.exprSemanticValue.constEvalValue.iValue;
      } else {
	*iValue = semantic_value.exprSemanticValue.constEvalValue.iValue;
      }
    } else {
      *fValue = semantic_value.exprSemanticValue.constEvalValue.fValue;
    }
  } 
}
bool AST_NODE::isConst(){//ok
  return nodeType == CONST_VALUE_NODE || (nodeType == EXPR_NODE && semantic_value.exprSemanticValue.isConstEval);
}

void AST_NODE::checkReturnStmt(){//ok
  AST_NODE* parentNode = parent;
  while(parentNode){
    if(parentNode->nodeType == DECLARATION_NODE){
      if(parentNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL)
	dataType = parentNode->child->dataType;//get return datatype
      break;
    }
    parentNode = parentNode->parent;
  }

  if(child->nodeType == NUL_NODE){
    if(dataType != VOID_TYPE){//return; in non-void function
      printErrorMsg(this, RETURN_TYPE_UNMATCH);
      dataType = ERROR_TYPE;
    }
  } else {
    child->processExprRelatedNode();
    if((dataType != child->dataType) && !((dataType == FLOAT_TYPE) && (child->dataType == INT_TYPE))){
      printErrorMsg(this, RETURN_TYPE_UNMATCH);
      dataType = ERROR_TYPE;
    }
  }
}
void AST_NODE::processBlockNode(){//ok
  //generalnode with scope
  openScope();
  AST_NODE *nowc = child;
  while(nowc){
    nowc->processGeneralNode();
    nowc = nowc->rightSibling;
  }
  closeScope();
}
void AST_NODE::processStmtNode(){//ok
  if(child->nodeType == NUL_NODE){
    return;
  } else if(child->nodeType == BLOCK_NODE){//with scope
    fprintf(stderr, "block\n");
    processBlockNode();
  } else{
    switch(semantic_value.stmtSemanticValue.kind){
    case WHILE_STMT://no implement
      break;
    case FOR_STMT://no implement
      break;
    case ASSIGN_STMT:
      fprintf(stderr, "assign stmt\n");
      checkAssignmentStmt();
      break;
    case IF_STMT://no implement
      break;
    case FUNCTION_CALL_STMT:
      fprintf(stderr, "func call stmt\n");
      checkFunctionCall();
      break;
    case RETURN_STMT:
      fprintf(stderr, "return stmt\n");
      checkReturnStmt();
      break;
    default:
      printf("ERROR:processStmtNode()\n");
      dataType = ERROR_TYPE;
      break;
    }
  }
}

void AST_NODE::processGeneralNode(){
  //decl_list func_decl
  AST_NODE *nowc = child;
  switch(nodeType){//TODO: use class function to eliminate this things
  case VARIABLE_DECL_LIST_NODE:
    fprintf(stderr, "VARIABLE_DECL_LIST_NODE\n");
    processDeclarationNodes();
    break;
  case STMT_LIST_NODE:
    fprintf(stderr, "STMT_LIST_NODE\n");
    while(nowc != NULL){
      nowc->processStmtNode();
      if(nowc->dataType == ERROR_TYPE)
	dataType = ERROR_TYPE;
      nowc = nowc->rightSibling;
    }
    break;
  case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
    fprintf(stderr, "NONEMPTY_ASSIGN_EXPR_LIST_NODE\n");
    while(nowc != NULL){
      nowc->processAssignOrExpr();
      if(nowc->dataType == ERROR_TYPE)
	dataType = ERROR_TYPE;
      nowc = nowc->rightSibling;
    }
    break;
  case NONEMPTY_RELOP_EXPR_LIST_NODE:
    fprintf(stderr, "NONEMPTY_RELOP_EXPR_LIST_NODE\n");
    while(nowc != NULL){
      nowc->processExprRelatedNode();
      if(nowc->dataType == ERROR_TYPE)
	dataType = ERROR_TYPE;
      nowc = nowc->rightSibling;
    }
    break;
  case NUL_NODE:
    break;
  default:
    dataType = ERROR_TYPE;
    break;
  }  
}

void AST_NODE::processAssignOrExpr(){//ok
  if(nodeType == STMT_NODE){//which can be looked as value
    if(semantic_value.stmtSemanticValue.kind == ASSIGN_STMT)
      checkAssignmentStmt();
    else if(semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
      checkFunctionCall();
  } else {
    processExprRelatedNode();
  }
}
void AST_NODE::processVariableLValue(){//compared with idexpr
  SymbolTableEntry *symbolTableEntry = retrieveSymbol(semantic_value.identifierSemanticValue.identifierName);
  if(!symbolTableEntry){
    printErrorMsg(this, SYMBOL_UNDECLARED);
    dataType = ERROR_TYPE;
    return;
  }
  semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;

  TypeDescriptor *typeDescriptor = semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
  if(semantic_value.identifierSemanticValue.kind == NORMAL_ID){
    if(typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR){
      printErrorMsg(this, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
    } else{
      dataType = typeDescriptor->properties.dataType;
    }
  } else if(semantic_value.identifierSemanticValue.kind == ARRAY_ID){
    int dimension = 0;
    AST_NODE *nowc = child;
    while(nowc != NULL){
      nowc->processExprRelatedNode();
      if(nowc->dataType == ERROR_TYPE){
	dataType = ERROR_TYPE;
      } else if(nowc->dataType == FLOAT_TYPE){
	printErrorMsg(this, ARRAY_SUBSCRIPT_NOT_INT);
	dataType = ERROR_TYPE;
      }
      nowc = nowc->rightSibling;
      dimension++;
    }
    if(dimension == typeDescriptor->properties.arrayProperties.dimension){
      dataType = typeDescriptor->properties.arrayProperties.elementType;
    } else {
      printErrorMsg(this, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
    }
  }
}

void AST_NODE::checkAssignmentStmt(){//ok
  AST_NODE* leftOp = child;
  AST_NODE* rightOp = leftOp->rightSibling;
  leftOp->processVariableLValue();
  rightOp->processExprRelatedNode();

  if(rightOp->dataType == INT_PTR_TYPE || rightOp->dataType == FLOAT_PTR_TYPE){
    printErrorMsg(rightOp, INCOMPATIBLE_ARRAY_DIMENSION);
    dataType = ERROR_TYPE;
  } else if(leftOp->dataType == ERROR_TYPE || rightOp->dataType == ERROR_TYPE){
    dataType = ERROR_TYPE;
  } else{
    dataType = leftOp->dataType;
  }
}
void AST_NODE::checkFunctionCall(){//check why generalnode
  //FORMAT:  a(b, c, d)
  SymbolTableEntry* symbolTableEntry = retrieveSymbol(child->semantic_value.identifierSemanticValue.identifierName);
  child->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
  if(symbolTableEntry == NULL){
    printErrorMsg(child, SYMBOL_UNDECLARED);
    child->dataType = ERROR_TYPE;
    dataType = ERROR_TYPE;
    return;
  }
  AST_NODE* paraList = child->rightSibling;//relop_expr_list
  paraList->processGeneralNode();
  dataType = symbolTableEntry->attribute->attr.functionSignature->returnType;

  AST_NODE* firstInput = paraList->child;
  FunctionSignature* functionDefinition = symbolTableEntry->attribute->attr.functionSignature;
  if(firstInput == NULL && functionDefinition->parametersCount != 0){
    printErrorMsg(child, TOO_FEW_ARGUMENTS);
    dataType = ERROR_TYPE;
  } else if(!firstInput->checkParameters(functionDefinition)){
    dataType = ERROR_TYPE;
  }
}
bool AST_NODE::checkParameters(FunctionSignature* functionDefinition){//ok
  AST_NODE* nowInput = this;
  int inputCount = 0;
  while(nowInput != NULL){
    nowInput = nowInput->rightSibling;
    inputCount++;
  }
  fprintf(stderr, "function def parameter count = %d, real input count = %d\n", functionDefinition->parametersCount, inputCount);
  if(functionDefinition->parametersCount > inputCount){
    printErrorMsg(parent->parent->child, TOO_FEW_ARGUMENTS);
    dataType = ERROR_TYPE;
    return false;
  } else if(functionDefinition->parametersCount < inputCount){
    printErrorMsg(parent->parent->child, TOO_MANY_ARGUMENTS);
    dataType = ERROR_TYPE;
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
    dataType = ERROR_TYPE;
    return false;
  }
  TypeDescriptorKind defineTD = nowParameter->type->kind;
  char* paraName = nowParameter->parameterName;
  if(defineTD == SCALAR_TYPE_DESCRIPTOR && isArray()){
    printErrorMsg(this, PASS_ARRAY_TO_SCALAR, paraName);
    dataType = ERROR_TYPE;
    return false;
  } else if(defineTD == ARRAY_TYPE_DESCRIPTOR && !isArray()){
    printErrorMsg(this, PASS_SCALAR_TO_ARRAY, paraName);
    dataType = ERROR_TYPE;
    return false;
  }
  return true;
}
inline bool AST_NODE::isArray(){//ok
  return (dataType == INT_PTR_TYPE) || (dataType == FLOAT_PTR_TYPE);
}
void AST_NODE::processIDExpr(){//ok
  SymbolTableEntry *symbolTableEntry = retrieveSymbol(semantic_value.identifierSemanticValue.identifierName);
  semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
  if(!symbolTableEntry){
    printErrorMsg(this, SYMBOL_UNDECLARED);
    dataType = ERROR_TYPE;
    return;
  }
  
  TypeDescriptor *assignTd = semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
  if(semantic_value.identifierSemanticValue.kind == NORMAL_ID){
    if(assignTd->kind == ARRAY_TYPE_DESCRIPTOR)
      dataType = assignTd->properties.arrayProperties.elementType;
    else
      dataType = assignTd->properties.dataType;
  } else if(semantic_value.identifierSemanticValue.kind == ARRAY_ID){//get real value a = b[10][11];
    int dimension = 0;
    AST_NODE *nowc = child;
    while(nowc != NULL){
      nowc->processExprRelatedNode();
      if(nowc->dataType == ERROR_TYPE){
	dataType = ERROR_TYPE;
      } else if(nowc->dataType == FLOAT_TYPE){
	printErrorMsg(this, ARRAY_SUBSCRIPT_NOT_INT);
	dataType = ERROR_TYPE;
      }
      nowc = nowc->rightSibling;
      dimension++;
    }

    if(dimension > assignTd->properties.arrayProperties.dimension){
      printErrorMsg(this, INCOMPATIBLE_ARRAY_DIMENSION);
      dataType = ERROR_TYPE;
      return;
    } else if(dimension == assignTd->properties.arrayProperties.dimension){
      dataType = assignTd->properties.arrayProperties.elementType;
    } else{// < , still pointer
      dataType = toPointer(assignTd->properties.arrayProperties.elementType);
    } 
  }
}
void AST_NODE::processConstExpr(){//ok
     //cexpr
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

DATA_TYPE toPointer(DATA_TYPE dt){
  if(dt == INT_TYPE){
    return INT_PTR_TYPE;
  } else if(dt == FLOAT_TYPE){
    return FLOAT_PTR_TYPE;
  } else {
    return ERROR_TYPE;
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

void AST_NODE::checkWhileStmt(){//only process block
}
void AST_NODE::checkForStmt(){//only process block
}
void AST_NODE::checkIfStmt(){//only process block
}
void AST_NODE::checkWriteFunction(){//?
}



