typedef struct
{
	int no;
	char c;
}Reg;

void gen_prologue(char* name, int paramCount);
void gen_epilogue(char* name, int paramCount);
void gen_frameSizeLabel(char* name, int size);
void writeString(char* strName, char* strValue);
void writeInt(Reg reg);
void writeFloat(Reg reg);
void readInt();
void readFloat();
void doWhile();
void doIf();
void doIfElse();
Reg doMath(AST_NODE* node);
int getFreeReg(DATA_TYPE type);
void freeReg(int no, ...);
void doAssignStmt(AST_NODE* assignStatNode);
void doFuncCallStmt(AST_NODE* funcCallStmtNode);
void doRetStmt(AST_NODE* stmtNode, char* funcName);
void doStmtLst(AST_NODE* stmtLstNode, char* funcName);
void doDeclFunc(AST_NODE* declNode);
void doDeclLst(AST_NODE* declNode);
void doVarDeclLst(AST_NODE* varDeclNode, int lv);
void printCode(AST_NODE *root);
void doWhileStmt(AST_NODE* stmtNode, char* funcName);
void doIfStmt(AST_NODE* stmtNode, char* funcName);
void doBlock(AST_NODE* blockNode, char* funcName);
int ldrArrayElem(AST_NODE* arrayIDNode);
