#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
#include "semanticAnalysis.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //

#define isVarAttr(a) 		(a->attribute->attributeKind == VARIABLE_ATTRIBUTE) 
#define isTypeAttr(a) 		(a->attribute->attributeKind == TYPE_ATTRIBUTE) 
#define isFuncAttr(a) 		(a->attribute->attributeKind == FUNCTION_SIGNATURE) 
#define isScalarVar(a) 		(a->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
#define isArrayVar(a) 		(a->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
#define ArrayElemType(a)	(a->attribute->attr.typeDescriptor->properties.arrayProperties.elementType)
#define ArrayDimen(a)		(a->attribute->attr.typeDescriptor->properties.arrayProperties.dimension)

#define IDNodeName(a) 		(a->semantic_value.identifierSemanticValue.identifierName)
#define isIDNode(a)			(a->nodeType == IDENTIFIER_NODE)
#define isExprNode(a)		(a->nodeType == EXPR_NODE)
#define isConstNode(a)		(a->nodeType == CONST_VALUE_NODE)
#define isIntConstNode(a)	(a->semantic_value.const1->const_type == INTEGERC)
#define isFloatConstNode(a) (a->semantic_value.const1->const_type == FLOATC)
#define isStringConstNode(a)(a->semantic_value.const1->const_type == STRINGC)
#define ConstNodeInt(a)		(a->semantic_value.const1->const_u.intval)
#define ConstNodeFloat(a)	(a->semantic_value.const1->const_u.fval)
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
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcNameNode);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
ExprValue* evaluateExprValue(AST_NODE* exprNode);
DATA_TYPE getDataType(char* typeName);
void checkOneSideOfAssignOrExpr(AST_NODE* OHS);
int cmpArraySubscript(AST_NODE* arrayIDNode, int dimenShouldBe);


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
    
	char* ID = IDNodeName(node);
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
			printf("array `%s` excessive array dimension declaration\n", ID);
			break;
    	case RETURN_ARRAY:
			break;
    	case VOID_VARIABLE:
			break;
    	case TYPEDEF_VOID_ARRAY:
			break;
    	case PARAMETER_TYPE_UNMATCH:
			printf("Arguments of function `%s` have wrong type.\n", ID);
			break;
    	case TOO_FEW_ARGUMENTS:
			printf("Too few arguments to function `%s`.\n", ID);
			break;
    	case TOO_MANY_ARGUMENTS:
			printf("Too many arguments to function `%s`.\n", ID);
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
			printf("size of array `%s` has non-integer type\n", ID);
			break;
    	case ARRAY_SIZE_NEGATIVE:
			printf("size of array `%s` is negative\n", ID);
			break;
    	case ARRAY_SUBSCRIPT_NOT_INT:
			printf("array `%s` subscriptor is not an integer\n", ID);
			break;
    	case PASS_ARRAY_TO_SCALAR:
			printf("try to pass array `%s` to scalar.\n", ID);
			break;
    	case PASS_SCALAR_TO_ARRAY:
			printf("try to pass scalar `%s` to array.\n", ID);
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
	char* typeName = IDNodeName(type_node);
	
	DATA_TYPE typeNo = getDataType(typeName);
	if(typeNo == ERROR_TYPE)
	{
		printErrorMsg(type_node, SYMBOL_UNDECLARED);
		return;
	}

	AST_NODE* ID_node = type_node->rightSibling;
	while(ID_node)
	{
		char* varName = IDNodeName(ID_node);
		if(declaredLocally(varName))
		{
			printErrorMsg(ID_node, SYMBOL_REDECLARE);
			ID_node = ID_node->rightSibling;
			continue;
		}
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
					ExprValue* value = evaluateExprValue(dimension_node);
					if(!value->hasFloat && !value->hasID)
					{
						if(value->val >= 0)
							attr->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = value->val;
						else
						{
							printErrorMsg(ID_node, ARRAY_SIZE_NEGATIVE);
							return;
						}
					}
					else
					{
						printErrorMsg(ID_node, ARRAY_SIZE_NOT_INT);
						return;
					}
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
	char* oriTypeName = IDNodeName(oriTypeNode);
	char* newTypeName = IDNodeName(newTypeNode);
	
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
	if(isExprNode(OHS))
		checkAssignOrExpr(OHS);
	else if(isIDNode(OHS))
	{	
		SymbolTableEntry* entry = retrieveSymbol(IDNodeName(OHS));
		if(!entry)
			printErrorMsg(OHS, SYMBOL_UNDECLARED);
		else if(!isVarAttr(entry))
			printErrorMsg(OHS, NOT_ASSIGNABLE);
		else if(isArrayVar(entry))
		{
			int ret = cmpArraySubscript(OHS, ArrayDimen(entry));
			if(ret)
				printErrorMsg(OHS, INCOMPATIBLE_ARRAY_DIMENSION);
		}
			
	}
	else if(isConstNode(OHS))
	{
		if(isStringConstNode(OHS))
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

	SymbolTableEntry* funcEntry = retrieveSymbol(IDNodeName(funcNameNode));
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
	
	checkParameterPassing(param, paramNode, funcNameNode);
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcNameNode)
{
	while(actualParameter)
	{
		if(isIDNode(actualParameter))
		{
			SymbolTableEntry* paramEntry = retrieveSymbol(IDNodeName(actualParameter));
			if(!paramEntry)
			{
				printErrorMsg(actualParameter, SYMBOL_UNDECLARED);
				return;
			}
			if(isTypeAttr(paramEntry))
			{
				printErrorMsg(actualParameter, IS_TYPE_NOT_VARIABLE);
				return;
			}
			else if(isFuncAttr(paramEntry))
			{
				printErrorMsg(actualParameter, IS_FUNCTION_NOT_VARIABLE);
				return;
			}
			printf("hello\n");
			//isVarAttr
			if(isScalarVar(paramEntry))
			{
				if(formalParameter->type->kind == ARRAY_TYPE_DESCRIPTOR)
				{
					printErrorMsg(actualParameter, PASS_SCALAR_TO_ARRAY);
					return;
				}
				DATA_TYPE paramType = paramEntry->attribute->attr.typeDescriptor->properties.dataType;
				DATA_TYPE typeShouldBe = formalParameter->type->properties.dataType;
				if(paramType != typeShouldBe)
				{
					printErrorMsg(funcNameNode, PARAMETER_TYPE_UNMATCH);
					return;
				}
			}
			else //if(isArrayVar(paramEntry))
			{
				if(formalParameter->type->kind == SCALAR_TYPE_DESCRIPTOR)
				{
					int typeShoudBe = formalParameter->type->properties.dataType;
					int ret = cmpArraySubscript(actualParameter, ArrayDimen(paramEntry));
					if(ret == -1)
					{
						printErrorMsg(actualParameter, PASS_ARRAY_TO_SCALAR);
						return;
					}
					else if(ret == 1)
					{
						printErrorMsg(actualParameter, EXCESSIVE_ARRAY_DIM_DECLARATION);
						return;
					}
				}
				else //if(param->type->kind == ARRAY_TYPE_DESCRIPTOR)
				{
					DATA_TYPE paramType = paramEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
					DATA_TYPE typeShouldBe = formalParameter->type->properties.arrayProperties.elementType;
					if(paramType != typeShouldBe)
					{
						printErrorMsg(funcNameNode, PARAMETER_TYPE_UNMATCH);
						return;
					}
					int dimenShouldBe = formalParameter->type->properties.arrayProperties.dimension;
					if(ArrayDimen(paramEntry) != dimenShouldBe)
					{
						printErrorMsg(actualParameter, INCOMPATIBLE_ARRAY_DIMENSION);
						return;
					}
				}
			}
		}
		else if(isConstNode(actualParameter))
		{
			if(formalParameter->type->kind == ARRAY_TYPE_DESCRIPTOR || isStringConstNode(actualParameter))
			{
				printErrorMsg(funcNameNode, PARAMETER_TYPE_UNMATCH);
				return;
			}
			else if(formalParameter->type->properties.dataType != actualParameter->semantic_value.const1->const_type)
			{
				printErrorMsg(funcNameNode, PARAMETER_TYPE_UNMATCH);
				return;
			}
		}	
		
		formalParameter = formalParameter->next;
		actualParameter = actualParameter->rightSibling;
		if(!formalParameter && actualParameter)
		{
			printErrorMsg(funcNameNode, TOO_MANY_ARGUMENTS);
			return;
		}
	}
	if(formalParameter)
		printErrorMsg(funcNameNode, TOO_FEW_ARGUMENTS);
}

int cmpArraySubscript(AST_NODE* arrayIDNode, int dimenShouldBe)
{
	int dimenCount = 0;
	AST_NODE* dimension = arrayIDNode->child;
	while(dimension)
	{
		ExprValue* ret = evaluateExprValue(dimension);
		if(ret->hasFloat)
			printErrorMsg(arrayIDNode, ARRAY_SUBSCRIPT_NOT_INT);
		dimension = dimension -> rightSibling;
		dimenCount++;
	}
	if(dimenCount > dimenShouldBe)
		return 1;
	if(dimenCount < dimenShouldBe)
		return -1;
	else
		return 0;
}

void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
}

ExprValue* evaluateExprValue(AST_NODE* exprNode)
{
	ExprValue* ret;
	if(isConstNode(exprNode))
	{
		ret = (ExprValue*)malloc(sizeof(ExprValue));
		memset(ret, 0, sizeof(ExprValue));
		if(isIntConstNode(exprNode))
		{
			ret->val = ConstNodeInt(exprNode);
			return ret;
		}
		else if(isFloatConstNode(exprNode))
		{
			ret->hasFloat = 1;
			return ret;
		}
	}
	else if(isIDNode(exprNode))
	{
		SymbolTableEntry* entry = retrieveSymbol(IDNodeName(exprNode));
		if(!entry)
			printErrorMsg(exprNode, SYMBOL_UNDECLARED);
		ret = (ExprValue*)malloc(sizeof(ExprValue));
		memset(ret, 0, sizeof(ExprValue));
		ret->hasID = 1;
		return ret;
	}
		

	EXPRSemanticValue* exprAttr = &(exprNode->semantic_value.exprSemanticValue);
	if(exprAttr->kind == UNARY_OPERATION)
	{	
		AST_NODE* childNode = exprNode->child;
		int unary = 1;
		if(exprAttr->op.unaryOp == UNARY_OP_NEGATIVE)
			unary = -1;

		ret = evaluateExprValue(childNode);
		if(!ret->hasFloat && !ret->hasID)
			ret->val = unary * ret->val;
		return ret;
	}
	else
	{
		AST_NODE* LHSNode = exprNode->child;
		AST_NODE* RHSNode = LHSNode->rightSibling;
		ExprValue* LHSValue = evaluateExprValue(LHSNode);
		ExprValue* RHSValue = evaluateExprValue(RHSNode);
		if(LHSValue->hasFloat)
			return LHSValue;
		if(RHSValue->hasFloat)
			return RHSValue;
		if(LHSValue->hasID)
			return LHSValue;
		if(RHSValue->hasID)
			return RHSValue;
		switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp)
		{
			case BINARY_OP_ADD:
				LHSValue->val = LHSValue->val + RHSValue->val;
				break;
			case BINARY_OP_SUB:
				LHSValue->val = LHSValue->val - RHSValue->val;
				break;
			case BINARY_OP_MUL:
				LHSValue->val = LHSValue->val * RHSValue->val;
				break;
			case BINARY_OP_DIV:
				LHSValue->val = LHSValue->val / RHSValue->val;
				break;
		}
		free(RHSValue);
		return LHSValue;
	}
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
			checkFunctionCall(stmtNode);	
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

	char* returnTypeName = IDNodeName(returnType);
	DATA_TYPE typeNo = getDataType(returnTypeName);
	if(typeNo == ERROR_TYPE)
	{
		printErrorMsg(returnType, SYMBOL_UNDECLARED);
		return;
	}
	
	SymbolTableEntry* entry;
	char* funcName = IDNodeName(funcID);
	if(declaredLocally(funcName))
	{
		printErrorMsg(funcID, SYMBOL_REDECLARE);
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
		param->parameterName = IDNodeName(param_decl_node->child->rightSibling);
		AST_NODE* type_node = param_decl_node->child;
		AST_NODE* ID_node = type_node->rightSibling;


		char* typeName = IDNodeName(type_node);
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
					param->type->properties.arrayProperties.sizeInEachDimension[dimension] = ConstNodeInt(dimension_node);
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
