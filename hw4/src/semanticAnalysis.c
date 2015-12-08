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
DATA_TYPE getDataType(char* typeName);


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
    /*
    switch(errorMsgKind)
    {
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    /*
    switch(errorMsgKind)
    {
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void semanticAnalysis(AST_NODE *root)
{
	processProgramNode(root);
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
	if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE)
        return FLOAT_TYPE;
	else
		return INT_TYPE;
}


void processProgramNode(AST_NODE *programNode)
{
	declareFunction(programNode->child);
}

void processDeclarationNode(AST_NODE* declarationNode)
{
}


void processTypeNode(AST_NODE* idNodeAsType)
{
}


void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}

void checkWhileStmt(AST_NODE* whileNode)
{
}


void checkForStmt(AST_NODE* forNode)
{
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
}


void checkIfStmt(AST_NODE* ifNode)
{
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
}

void evaluateExprValue(AST_NODE* exprNode)
{
}


void processExprNode(AST_NODE* exprNode)
{
}


void processVariableLValue(AST_NODE* idNode)
{
}

void processVariableRValue(AST_NODE* idNode)
{
}


void processConstValueNode(AST_NODE* constValueNode)
{
}


void checkReturnStmt(AST_NODE* returnNode)
{
}


void processBlockNode(AST_NODE* blockNode)
{
}


void processStmtNode(AST_NODE* stmtNode)
{
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}


void declareFunction(AST_NODE* declarationNode)
{
	AST_NODE* returnType = declarationNode->child;
	AST_NODE* funcID = returnType->rightSibling;
	AST_NODE* param = funcID->rightSibling;
	AST_NODE* block = param->rightSibling;

	char* returnTypeName = returnType->semantic_value.identifierSemanticValue.identifierName;
	if(!declaredLocally(returnTypeName))
		printf("ID %s undeclared\n", returnTypeName);
	
	SymbolTableEntry* entry;
	char* funcName = funcID->semantic_value.identifierSemanticValue.identifierName;
	if(entry = retrieveSymbol(funcName))
		if(entry->attribute->attributeKind == FUNCTION_SIGNATURE)
		{
			printf("ID %s redeclared\n", funcName);
			return;
		}


	SymbolAttribute* attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
	attr->attributeKind = FUNCTION_SIGNATURE;

	attr->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));
	attr->attr.functionSignature->returnType = getDataType(returnTypeName);
	attr->attr.functionSignature->parameterList = NULL;
	attr->attr.functionSignature->parametersCount = 0;

	AST_NODE* param_decl_node = param->child;
	while(param_decl_node)
	{
		attr->attr.functionSignature->parametersCount++;

		Parameter* param = (Parameter*)malloc(sizeof(Parameter));
		param->type = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
		param->parameterName = param_decl_node->child->rightSibling->semantic_value.identifierSemanticValue.identifierName;
		AST_NODE* type_node = param_decl_node->child;
		AST_NODE* ID_node = type_node->rightSibling;

		IDENTIFIER_KIND kind = ID_node->semantic_value.identifierSemanticValue.kind;
		if(kind == ARRAY_ID)
		{
			param->type->kind = ARRAY_TYPE_DESCRIPTOR;
			AST_NODE* dimension_node = ID_node->child;
			int dimension = 0;
			while(dimension_node)
			{
				if(dimension_node->nodeType == NUL_NODE)
					param->type->properties.arrayProperties.sizeInEachDimension[dimension] = 0;
				else
					param->type->properties.arrayProperties.sizeInEachDimension[dimension] = dimension_node->semantic_value.const1->const_u.intval;
				dimension++;
				dimension_node = dimension_node->rightSibling;
			}
			param->type->properties.arrayProperties.dimension = dimension;
			param->type->properties.arrayProperties.elementType = getDataType(type_node->semantic_value.identifierSemanticValue.identifierName);
		}
		else if(kind == NORMAL_ID)
		{
			param->type->kind = SCALAR_TYPE_DESCRIPTOR;
			param->type->properties.dataType = type_node->dataType;
		}
		else
			printf("Unknown ID type in ID_Node\n");
		
		param->next = attr->attr.functionSignature->parameterList;
		attr->attr.functionSignature->parameterList = param;

		param_decl_node = param_decl_node->rightSibling;
	}
/*
	printf("attribute Kind No. = %d\n", attr->attributeKind);
	printf("paramenterCount = %d\n", attr->attr.functionSignature->parametersCount);
	printf("return type = %d\n", attr->attr.functionSignature->returnType);
	printf("parameter name = %s\n", attr->attr.functionSignature->parameterList->parameterName);
	printf("parameter type No. = %d\n", attr->attr.functionSignature->parameterList->type->properties.arrayProperties.elementType);
	printf("parameter is array? = %d\n", attr->attr.functionSignature->parameterList->type->kind);
	printf("dimension = %d\n", attr->attr.functionSignature->parameterList->type->properties.arrayProperties.dimension);
	printf("size = %d\n", attr->attr.functionSignature->parameterList->type->properties.arrayProperties.sizeInEachDimension[0]);
*/	enterSymbol(funcName, attr);
}

DATA_TYPE getDataType(char* typeName)
{
	if(!strcmp(typeName, "int"))
		return INT_TYPE;
	else if(!strcmp(typeName, "float"))
		return FLOAT_TYPE;
	else if(!strcmp(typeName, "void"))
		return VOID_TYPE;
	else if(!strcmp(typeName, "int*") || !strcmp(typeName, "int *"))
		return INT_PTR_TYPE;
	else if(!strcmp(typeName, "float*") || !strcmp(typeName, "float *"))
		return FLOAT_PTR_TYPE;
	else
		return ERROR_TYPE;
}
