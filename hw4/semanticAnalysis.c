#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //
int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void evaluateExprValue(AST_NODE* exprNode);


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

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind)
{
  g_anyErrorOccur = 1;
  printf("Error found in line %d\n", node1->linenumber);
  switch(errorMsgKind)
    {

      //TODO:
      //error type 3
    case PASS_ARRAY_TO_SCALAR:
      printf("Array <%s> passed to scalar parameter <%s>.\n", node1->semantic_value.identifierSemanticValue.identifierName, name2);
      break;      
    default:
      printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
      break;
    }
    
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
  g_anyErrorOccur = 1;
  printf("Error found in line %d\n", node->linenumber);
  switch(errorMsgKind)
    {
      //TODO:
      //error type 3
    case ARRAY_SUBSCRIPT_NOT_INT:
      printf("Array subscript is not an integer.\n");
      break;
    case INCOMPATIBLE_ARRAY_DIMENSION:
      printf("Incompatible array dimensions.\n");
      break;
      //error type 2
    case RETURN_TYPE_UNMATCH:
      printf("Warning: Incompatible return type.\n");
      break;
    case TOO_FEW_ARGUMENTS:
      printf("Too few arguments to function <%s>.\n", node->semantic_value.identifierSemanticValue.identifierName);
      break;
      //error type 1
    case SYMBOL_UNDECLARED:
      printf("ID <%s> undeclared.\n", node->semantic_value.identifierSemanticValue.identifierName);
      break;
    default:
      printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
      break;
    }
}


void semanticAnalysis(AST_NODE *root)
{
  processProgramNode(root);
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
  if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
    return FLOAT_TYPE;
  } else {
    return INT_TYPE;
  }
}


void processProgramNode(AST_NODE *programNode)
{
  //TODO:
}

void processDeclarationNode(AST_NODE* declarationNode)
{
  //TODO:
}


void processTypeNode(AST_NODE* idNodeAsType)
{
  //TODO:
}


void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
  //TODO:
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
  //TODO:
}

void checkWhileStmt(AST_NODE* whileNode)
{
  //TODO:
}


void checkForStmt(AST_NODE* forNode)
{
  //TODO:
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
  //TODO:
}


void checkIfStmt(AST_NODE* ifNode)
{
  //TODO:
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
  //TODO:
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
  //TODO:
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
  //TODO:
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
  //TODO:
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
  //TODO:
}

void evaluateExprValue(AST_NODE* exprNode)
{
  //TODO:
}


void processExprNode(AST_NODE* exprNode)
{
  //TODO:
}


void processVariableLValue(AST_NODE* idNode)
{
  //TODO:
}

void processVariableRValue(AST_NODE* idNode)
{
  //TODO:
}


void processConstValueNode(AST_NODE* constValueNode)
{
  //TODO:
}


void checkReturnStmt(AST_NODE* returnNode)
{
  //TODO:
}


void processBlockNode(AST_NODE* blockNode)
{
  //TODO:
}


void processStmtNode(AST_NODE* stmtNode)
{
  //TODO:
}


void processGeneralNode(AST_NODE *node)
{
  //TODO:
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
  //TODO:
}


void declareFunction(AST_NODE* declarationNode)
{
  //TODO:
}
