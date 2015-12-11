#ifndef __HEADER_H__
#define __HEADER_H__

#define MAX_ARRAY_DIMENSION 10

typedef enum DATA_TYPE
{
    INT_TYPE,
    FLOAT_TYPE,
    VOID_TYPE,
    INT_PTR_TYPE,//for parameter passing
    FLOAT_PTR_TYPE,//for parameter passing
    CONST_STRING_TYPE,//for "const string"
    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
    ERROR_TYPE
} DATA_TYPE;

typedef enum IDENTIFIER_KIND
{
    NORMAL_ID, //function Name, uninitialized scalar variable
    ARRAY_ID, //ID_NODE->child = dim
    WITH_INIT_ID, //ID_NODE->child = initial value
} IDENTIFIER_KIND;

typedef enum BINARY_OPERATOR
{
    BINARY_OP_ADD,
    BINARY_OP_SUB,
    BINARY_OP_MUL,
    BINARY_OP_DIV,
    BINARY_OP_EQ,
    BINARY_OP_GE,
    BINARY_OP_LE,
    BINARY_OP_NE,
    BINARY_OP_GT,
    BINARY_OP_LT,
    BINARY_OP_AND,
    BINARY_OP_OR
} BINARY_OPERATOR;

typedef enum UNARY_OPERATOR
{
    UNARY_OP_POSITIVE,
    UNARY_OP_NEGATIVE,
    UNARY_OP_LOGICAL_NEGATION
} UNARY_OPERATOR;

//C_type= type of constant ex: 1, 3.3, "const string"
//do not modify, or lexer might break
typedef enum C_type {INTEGERC,FLOATC,STRINGC} C_type;

typedef enum STMT_KIND
{
    WHILE_STMT,
    FOR_STMT,
    ASSIGN_STMT, //TODO:for simpler implementation, assign_expr also uses this
    IF_STMT,
    FUNCTION_CALL_STMT,
    RETURN_STMT,
} STMT_KIND;

typedef enum EXPR_KIND
{
    BINARY_OPERATION,
    UNARY_OPERATION
} EXPR_KIND;

typedef enum DECL_KIND
{
    VARIABLE_DECL,
    TYPE_DECL,
    FUNCTION_DECL,
    FUNCTION_PARAMETER_DECL
} DECL_KIND;

typedef enum AST_TYPE
{
    PROGRAM_NODE,
    DECLARATION_NODE,
    IDENTIFIER_NODE,
    PARAM_LIST_NODE,
    NUL_NODE,
    BLOCK_NODE,
    VARIABLE_DECL_LIST_NODE,
    STMT_LIST_NODE,
    STMT_NODE,
    EXPR_NODE,
    CONST_VALUE_NODE, //ex:1, 2, "constant string"
    NONEMPTY_ASSIGN_EXPR_LIST_NODE,
    NONEMPTY_RELOP_EXPR_LIST_NODE
} AST_TYPE;

//*************************
// AST_NODE's semantic value
//*************************

typedef struct STMTSemanticValue
{
    STMT_KIND kind;
} STMTSemanticValue;

typedef struct EXPRSemanticValue
{
    EXPR_KIND kind;
    
    int isConstEval;

    union
    {
        int iValue;
        float fValue;
    } constEvalValue;//no string??????

    union
    {
        BINARY_OPERATOR binaryOp;
        UNARY_OPERATOR unaryOp;
    } op;
} EXPRSemanticValue;

typedef struct DECLSemanticValue
{
    DECL_KIND kind;
} DECLSemanticValue;

struct SymbolAttribute;

typedef struct IdentifierSemanticValue
{
    char *identifierName;
    struct SymbolTableEntry *symbolTableEntry;
    IDENTIFIER_KIND kind;
} IdentifierSemanticValue;

typedef struct TypeSpecSemanticValue
{
    char *typeName;
} TypeSpecSemanticValue;

//don't modify or lexer may break
typedef struct CON_Type{
        C_type  const_type;
	union {
		int     intval;
		double  fval;
		char    *sc; }
		const_u;
} CON_Type;

//Forward declaration
struct FunctionSignature;
struct Parameter;
struct TypeDescriptor;
struct IdentifierSemanticValue;
struct SymbolAttribute;
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
    PASS_SCALAR_TO_ARRAY,
    ASSIGN_FLOAT_TO_INT,
    VOID_ASSIGNMENT,
    DECLARED_AS_FUNCTION
  } ErrorMsgKind;


struct AST_NODE {
  struct AST_NODE *child;
  struct AST_NODE *parent;
  struct AST_NODE *rightSibling;
  struct AST_NODE *leftmostSibling;
  AST_TYPE nodeType;
  DATA_TYPE dataType;
  int linenumber;
  union {
    IdentifierSemanticValue identifierSemanticValue;
    STMTSemanticValue stmtSemanticValue;
    DECLSemanticValue declSemanticValue;
    EXPRSemanticValue exprSemanticValue;
    CON_Type *const1;
  } semantic_value;

  //TODO: change to bool to reduce recheck (datatype == null)
  void processProgramNode();
  void processDeclarationNodes();
  void processDeclarationNode();
  void declareIdList(TypeDescriptor* typeTypeDescriptor,int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize);//enum cannot be forward declared...
  void declareId(int isVariableOrTypeAttribute, bool ignoreArrayFirstDimSize, TypeDescriptor* typeTypeDescriptor);

  void processNodeWithValue();//main
  void processExprNode();//1
  void checkExprType();
  void evaluateExprValue();
  void evaluateBinaryExprValue();
  void evaluateNonRelationExpr(AST_NODE* leftOp, AST_NODE* rightOp, float lvalue, float rvalue);
  void evaluateUnaryExprValue();
  void checkFunctionCall();//2
  void processParameterList();
  bool checkParameters(FunctionSignature*);
  bool checkParameter(Parameter*);
  void processIDExpr();//3
  void processConstExpr();//4

  void declareFunction();
  void processAssignOrExpr();

  void processDeclDimList(TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
  void processTypeNode();

  void processBlock();
  void processStmtNode();
  void checkWhileStmt();
  void checkForStmt();
  void checkIfStmt();
  void checkWriteFunction();

  void checkAssignmentStmt();
  void checkReturnStmt();
  void processBlockNode();
  float getValue();
  void processVariableLValue();

  
  bool isArray();
  bool isConst();
  void setError();
  void printNodeType(const char*);
  void printErrorMsg(ErrorMsgKind errorMsgKind, char* para="");
  
  void processChildren(void(AST_NODE::*fn)());
};
typedef struct AST_NODE AST_NODE;
typedef struct AST_NODE node;

AST_NODE *Allocate(AST_TYPE type);
void semanticAnalysis(AST_NODE *root);

#endif
