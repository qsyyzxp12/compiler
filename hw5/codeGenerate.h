void gen_prologue(char* name);
void gen_epilogue(char* name);
void gen_frameSizeLabel(char* name, int size);
void writeString(char* strName, char* strValue);
void writeInt(char* reg);
void writeFloat(char* reg);
void readInt(char* reg);
void doVarDeclLst(AST_NODE* varDeclNode, int lv);
void doFuncCallStmt(AST_NODE* funcCallStmtNode);

