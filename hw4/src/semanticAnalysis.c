#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //

#define isVarAttr(a) 	(a->attribute->attributeKind == VARIABLE_ATTRIBUTE) 
#define isTypeAttr(a) 	(a->attribute->attributeKind == TYPE_ATTRIBUTE) 
#define isFuncAttr(a) 	(a->attribute->attributeKind == FUNCTION_SIGNATURE) 
#define isScalarVar(a) 	(a->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
#define isArrayVar(a) 	(a->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)

#define IDNodeName(a) 	(a->semantic_value.identifierSemanticValue.identifierName)
#define ArrayElemType(a)(a->attribute->attr.typeDescriptor->properties.arrayProperties.elementType)
#define ArrayDimen(a)	(a->attribute->attr.typeDescriptor->properties.arrayProperties.dimension)
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
void checkOneSideOfAssignOrExpr(AST_NODE* OHS);


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
    g_anyErrorOccur++;
    printf("Error found in line %d\n", node1->linenumber);
    
    switch(errorMsgKind)
    {
    	default:
        	printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        	break;
    }
    
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur++;
    printf("Error found in line %d\n", node->linenumber);
    
	char* ID = node->semantic_value.identifierSemanticValue.identifierName;
    switch(errorMsgKind)
    {
		case SYMBOL_IS_NOT_TYPE:
			break;
   		case SYMBOL_REDECLARE:
			printf("ID `%s` redeclared.\n", ID);
			break;
		case SYMBOL_UNDECLARED:
			printf("ID `%s` undeclared.\n", ID);
			break;
		case NOT_FUNCTION_NAME:
			printf("ID `%s` is not a functino name.\n", ID);
			break;
    	case TRY_TO_INIT_ARRAY:
			break;
		case EXCESSIVE_ARRAY_DIM_DECLARATION:
			break;
    	case RETURN_ARRAY:
			break;
    	case VOID_VARIABLE:
			break;
    	case TYPEDEF_VOID_ARRAY:
			break;
    	case PARAMETER_TYPE_UNMATCH:
			printf("argument `%s` type wrong.\n", ID);
			break;
    	case TOO_FEW_ARGUMENTS:
			printf("too few arguments to function `%s`.\n", ID);
			break;
    	case TOO_MANY_ARGUMENTS:
			printf("too many arguments to function `%s`.\n", ID);
			break;
    	case RETURN_TYPE_UNMATCH:
			break;
    	case INCOMPATIBLE_ARRAY_DIMENSION:
			printf("argument `%s` dimension wrong.\n", ID);
			break;
		case NOT_ASSIGNABLE:
			printf("ID `%s` is not assignable.\n", ID);
			break;
    	case NOT_ARRAY:
			break;
		case IS_TYPE_NOT_VARIABLE:
			printf("ID `%s` is a type not a variable\n", ID);
			break;
    	case IS_FUNCTION_NOT_VARIABLE:
			printf("ID `%s` is a function not a variable\n", ID);
			break;
		case STRING_OPERATION:
			printf("invalid operand %s\n", ID);
			break;
		case ARRAY_SIZE_NOT_INT:
			break;
    	case ARRAY_SIZE_NEGATIVE:
			break;
    	case ARRAY_SUBSCRIPT_NOT_INT:
			break;
    	case PASS_ARRAY_TO_SCALAR:
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
	if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE)
        return FLOAT_TYPE;
	else
		return INT_TYPE;
}


void processProgramNode(AST_NODE *programNode)
{
	AST_NODE* func_decl_node = programNode->child;
	while(func_decl_node)
	{
		declareFunction(func_decl_node);
		func_decl_node = func_decl_node->rightSibling;
	}
}

void processDeclarationNode(AST_NODE* declarationNode)
{
	AST_NODE* type_node = declarationNode->child;
	char* typeName = type_node->semantic_value.identifierSemanticValue.identifierName;
	
	DATA_TYPE typeNo = getDataType(typeName);
	if(typeNo == ERROR_TYPE)
	{
		printErrorMsg(type_node, SYMBOL_UNDECLARED);
		return;
	}

	AST_NODE* ID_node = type_node->rightSibling;
	while(ID_node)
	{
		char* varName = ID_node->semantic_value.identifierSemanticValue.identifierName;
		SymbolAttribute* attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
		attr->attributeKind = VARIABLE_ATTRIBUTE;
		attr->attr.typeDescriptor = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
		if(ID_node->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
		{
			attr->attr.typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
			attr->attr.typeDescriptor->properties.arrayProperties.elementType = typeNo;
			
			AST_NODE* dimension_node = ID_node->child;
			int dimension = 0;
			while(dimension_node)
			{
				if(dimension_node->nodeType == NUL_NODE)
					attr->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = 0;
				else
				{
					int value = dimension_node->semantic_value.const1->const_u.intval; 
					attr->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = value;
				}
				dimension++;
				dimension_node = dimension_node->rightSibling;
			}
			attr->attr.typeDescriptor->properties.arrayProperties.dimension = dimension;
		}
		else
		{
			attr->attr.typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
			attr->attr.typeDescriptor->properties.dataType = typeNo;
		}

		enterSymbol(varName, attr);
		ID_node = ID_node->rightSibling;
	}
}

void processTypeNode(AST_NODE* idNodeAsType)
{
	AST_NODE* oriTypeNode = idNodeAsType->child;
	AST_NODE* newTypeNode = oriTypeNode->rightSibling;
	char* oriTypeName = oriTypeNode->semantic_value.identifierSemanticValue.identifierName;
	char* newTypeName = newTypeNode->semantic_value.identifierSemanticValue.identifierName;
	
	SymbolAttribute* attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
	attr->attributeKind = TYPE_ATTRIBUTE;
	attr->attr.typeDescriptor = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
	attr->attr.typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
	DATA_TYPE typeNo = getDataType(oriTypeName);
	if(typeNo != ERROR_TYPE)
		attr->attr.typeDescriptor->properties.dataType = typeNo;
	else
	{
		printErrorMsg(oriTypeNode, SYMBOL_UNDECLARED);
		return;
	}

	enterSymbol(newTypeName, attr);
}

void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
	AST_NODE* LHS = assignOrExprRelatedNode->child;
	AST_NODE* RHS = LHS->rightSibling;

	checkOneSideOfAssignOrExpr(LHS);
	checkOneSideOfAssignOrExpr(RHS);		
}

void checkOneSideOfAssignOrExpr(AST_NODE* OHS)
{
	if(OHS->nodeType == EXPR_NODE)
		checkAssignOrExpr(OHS);
	else if(OHS->nodeType == IDENTIFIER_NODE)
	{	
		SymbolTableEntry* entry = retrieveSymbol(OHS->semantic_value.identifierSemanticValue.identifierName);
		if(!entry)
			printErrorMsg(OHS, SYMBOL_UNDECLARED);
		else if(!isVarAttr(entry))
			printErrorMsg(OHS, NOT_ASSIGNABLE);
	}
	else if(OHS->nodeType == CONST_VALUE_NODE)
	{
		if(OHS->semantic_value.const1->const_type == STRINGC)
			printErrorMsg(OHS, STRING_OPERATION);
	}
	else if(OHS->nodeType == STMT_NODE && OHS->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
		checkFunctionCall(OHS);
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
	AST_NODE* funcNameNode = functionCallNode->child;
	AST_NODE* paramNode = funcNameNode->rightSibling;

	SymbolTableEntry* funcEntry = retrieveSymbol(funcNameNode->semantic_value.identifierSemanticValue.identifierName);
	if(!funcEntry)
	{
		printErrorMsg(funcNameNode, SYMBOL_UNDECLARED);
		return;
	}

	if(!isFuncAttr(funcEntry))
	{
		printErrorMsg(funcNameNode, NOT_FUNCTION_NAME);
		return;
	}
	int paramCount = funcEntry->attribute->attr.functionSignature->parametersCount;
	Parameter* param = funcEntry->attribute->attr.functionSignature->parameterList;
	DATA_TYPE returnTypeNo = funcEntry->attribute->attr.functionSignature->returnType;
	
	if(paramCount == 0)
	{
		if(paramNode->nodeType != NUL_NODE)
		    printErrorMsg(funcNameNode, TOO_MANY_ARGUMENTS);
		return;	
	}
	paramNode = paramNode->child;
	while(paramNode)
	{
		if(paramNode->nodeType == IDENTIFIER_NODE)
		{
			SymbolTableEntry* paramEntry = retrieveSymbol(IDNodeName(paramNode));
			if(isTypeAttr(paramEntry))
			{
				printErrorMsg(paramNode, IS_TYPE_NOT_VARIABLE);
				return;
			}
			else if(isFuncAttr(paramEntry))
			{
				printErrorMsg(paramNode, IS_FUNCTION_NOT_VARIABLE);
				return;
			}
			if(isScalarVar(paramEntry))
			{
				if(param->type->kind == ARRAY_TYPE_DESCRIPTOR)
				{
					printErrorMsg(paramNode, PASS_SCALAR_TO_ARRAY);
					return;
				}
				DATA_TYPE paramType = paramEntry->attribute->attr.typeDescriptor->properties.dataType;
				DATA_TYPE typeShouldBe = param->type->properties.dataType;
				if(paramType != typeShouldBe)
				{
					printErrorMsg(paramNode, PARAMETER_TYPE_UNMATCH);
					return;
				}
			}
			else
			{
				if(param->type->kind == SCALAR_TYPE_DESCRIPTOR)
				{
					printErrorMsg(paramNode, PASS_ARRAY_TO_SCALAR);
					return;
				}
				DATA_TYPE paramType = paramEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
				DATA_TYPE typeShouldBe = param->type->properties.arrayProperties.elementType;
				if(paramType != typeShouldBe)
				{
					printErrorMsg(paramNode, PARAMETER_TYPE_UNMATCH);
					return;
				}
				int dimenShouldBe = param->type->properties.arrayProperties.dimension;
				if(ArrayDimen(paramEntry) != dimenShouldBe)
				{
					printErrorMsg(paramNode, INCOMPATIBLE_ARRAY_DIMENSION);
					return;
				}
			}
		}
		param = param->next;
		paramNode = paramNode->rightSibling;
		if(!param && paramNode)
		{
			printErrorMsg(funcNameNode, TOO_MANY_ARGUMENTS);
			return;
		}
	}
	if(param)
		printErrorMsg(funcNameNode, TOO_FEW_ARGUMENTS);
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
	AST_NODE* childNode = blockNode->child;
	if(childNode->nodeType == VARIABLE_DECL_LIST_NODE)
	{
		AST_NODE* decl_node = childNode->child;
		while(decl_node)
		{
			if(decl_node->semantic_value.declSemanticValue.kind == VARIABLE_DECL)
				processDeclarationNode(decl_node);
			else if(decl_node->semantic_value.declSemanticValue.kind == TYPE_DECL)
				processTypeNode(decl_node);
			else
				printf("syntax result error\n");
			decl_node = decl_node->rightSibling;
		}
		childNode = childNode->rightSibling;
	}

	if(childNode)
	{
		AST_NODE* stmt_node = childNode->child;
		while(stmt_node)
		{
			processStmtNode(stmt_node);
			stmt_node = stmt_node->rightSibling;
		}
	}
//	closeScope();
}


void processStmtNode(AST_NODE* stmtNode)
{
	STMT_KIND stmt_kind = stmtNode->semantic_value.stmtSemanticValue.kind;
	switch(stmt_kind)
	{
		case WHILE_STMT:
			break;
		case FOR_STMT:
			break;
		case ASSIGN_STMT:
			checkAssignOrExpr(stmtNode);
			break;
		case IF_STMT:
			break;
		case FUNCTION_CALL_STMT:
			break;
		case RETURN_STMT:
			break;
		default:
			break;
	}
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
	DATA_TYPE typeNo = getDataType(returnTypeName);
	if(typeNo == ERROR_TYPE)
	{
		printErrorMsg(returnType, SYMBOL_UNDECLARED);
		return;
	}
	
	SymbolTableEntry* entry;
	char* funcName = funcID->semantic_value.identifierSemanticValue.identifierName;
	if(entry = retrieveSymbol(funcName))
		if(entry->attribute->attributeKind == FUNCTION_SIGNATURE)
		{
			printErrorMsg(returnType, SYMBOL_REDECLARE);
			return;
		}


	SymbolAttribute* attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
	attr->attributeKind = FUNCTION_SIGNATURE;

	attr->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));
	attr->attr.functionSignature->returnType = typeNo;
	
	attr->attr.functionSignature->parameterList = NULL;
	attr->attr.functionSignature->parametersCount = 0;

	AST_NODE* param_decl_node = param->child;
	Parameter* paramListTail = NULL;
	if(block->child)
		symbolTable.currentLevel++;
	while(param_decl_node)
	{
		if(block->child)
			processDeclarationNode(param_decl_node);
		attr->attr.functionSignature->parametersCount++;

		Parameter* param = (Parameter*)malloc(sizeof(Parameter));
		param->type = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
		param->parameterName = param_decl_node->child->rightSibling->semantic_value.identifierSemanticValue.identifierName;
		AST_NODE* type_node = param_decl_node->child;
		AST_NODE* ID_node = type_node->rightSibling;


		char* typeName = type_node->semantic_value.identifierSemanticValue.identifierName;
		DATA_TYPE typeNo = getDataType(typeName);
		if(typeNo == ERROR_TYPE)
		{
			printErrorMsg(type_node, SYMBOL_UNDECLARED);
			return;
		}

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
			param->type->properties.arrayProperties.elementType = typeNo;
		}
		else if(kind == NORMAL_ID)
		{
			param->type->kind = SCALAR_TYPE_DESCRIPTOR;
			param->type->properties.dataType = typeNo;
		}
		else
			printf("Unknown ID type in ID_Node\n");
		
		param->next = NULL;
		if(!attr->attr.functionSignature->parameterList)
		{
			attr->attr.functionSignature->parameterList = param;
			paramListTail = param;
		}
		else
			paramListTail->next = param;

		param_decl_node = param_decl_node->rightSibling;
	}
	if(block->child)
		symbolTable.currentLevel--;
	enterSymbol(funcName, attr);
	if(block->child)
	{
		openScope();
		processBlockNode(block);
	}
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
	
	//typeName is a typedef type or error
	SymbolTableEntry* typeEntry = retrieveSymbol(typeName);
	if(typeEntry && isTypeAttr(typeEntry) && 
	   typeEntry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
	{
		return typeEntry->attribute->attr.typeDescriptor->properties.dataType;
	}
	return ERROR_TYPE;
		
}
