/*
- Short-circuit boolean expressions
- For loops
7) Variable initializations
8) Procedure and function calls with parameters
11) Implicit type conversions
10) Multiple dimensional arrays
*/

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "codeGenerate.h"
FILE* outputFile;
int ifCount;
int whileCount;
int constCount;
int AROffset;
int regStat[15] = {0};

//label number should be maintained on a stack.

#define writeV8(s, b...)			\
  {						\
    fprintf(outputFile, s, ##b);		\
  }

void gen_prologue(char* name)
{
  writeV8("\t.text\n");
  writeV8("_start_%s:\n", name);
  writeV8("\tstr x30, [sp, #0]\n");
  writeV8("\tstr x29, [sp, #-8]\n");
  writeV8("\tadd x29, sp, #-8\n");
  writeV8("\tadd sp, sp, #-16\n");
  writeV8("\tldr x30, =_frameSize_%s\n", name);
  writeV8("\tldr x30, [x30, #0]\n");
  writeV8("\tsub sp, sp, w30\n");
  writeV8("\tstr x9, [sp, #8]\n");
  writeV8("\tstr x10, [sp, #16]\n");
  writeV8("\tstr x11, [sp, #24]\n");
  writeV8("\tstr x12, [sp, #32]\n");
  writeV8("\tstr x13, [sp, #40]\n");
  writeV8("\tstr x14, [sp, #48]\n");
  writeV8("\tstr x15, [sp, #56]\n");
  writeV8("\tstr x16, [sp, #64]\n");
  writeV8("\tstr x17, [sp, #68]\n");
  writeV8("\tstr x18, [sp, #72]\n");
  writeV8("\tstr x19, [sp, #76]\n");
  writeV8("\tstr x20, [sp, #80]\n");
  writeV8("\tstr x21, [sp, #84]\n");
  writeV8("\tstr x22, [sp, #88]\n");
  writeV8("\tstr x23, [sp, #92]\n\n");
}

void gen_epilogue(char* name)
{
  writeV8("\n_end_%s:\n", name);
  writeV8("\tldr x9, [sp, #8]\n");
  writeV8("\tldr x10, [sp, #16]\n");
  writeV8("\tldr x11, [sp, #24]\n");
  writeV8("\tldr x12, [sp, #32]\n");
  writeV8("\tldr x13, [sp, #40]\n");
  writeV8("\tldr x14, [sp, #48]\n");
  writeV8("\tldr x15, [sp, #56]\n");
  writeV8("\tldr x16, [sp, #64]\n");
  writeV8("\tldr x17, [sp, #68]\n");
  writeV8("\tldr x18, [sp, #72]\n");
  writeV8("\tldr x19, [sp, #76]\n");
  writeV8("\tldr x20, [sp, #80]\n");
  writeV8("\tldr x21, [sp, #84]\n");
  writeV8("\tldr x22, [sp, #88]\n");
  writeV8("\tldr x23, [sp, #92]\n");
  writeV8("\tldr x30, [x29, #8]\n");
  writeV8("\tmov sp, x29\n");
  writeV8("\tadd sp, sp, #8\n");
  writeV8("\tldr x29, [x29, #0]\n");
  writeV8("\tRET x30\n");
  writeV8("\t.data\n");
}

void gen_frameSizeLabel(char* name, int size)
{
  writeV8("_frameSize_%s:\n", name);
  writeV8("\t.word %d\n", size);
}

Reg doMath(AST_NODE* node)
{
  Reg reg;
  if(node->nodeType == CONST_VALUE_NODE)
    {
      int regNo;
      switch(node->semantic_value.const1->const_type)
	{
	case INTEGERC:
	  writeV8("\t.data\n");
	  writeV8("_CONSTANT_%d:\n", constCount);
	  writeV8("\t.word %d\n", node->semantic_value.const1->const_u.intval);
	  writeV8("\t.align 3\n");
	  writeV8("\t.text\n");
	  regNo = getFreeReg(INT_TYPE);
	  writeV8("\tldr w%d, _CONSTANT_%d\n", regNo, constCount);
	  constCount++;
	  reg.c = 'w';
	  break;
	case FLOATC:
	  writeV8("\t.data\n");
	  writeV8("_CONSTANT_%d:\n", constCount);
	  writeV8("\t.float %f\n", node->semantic_value.const1->const_u.fval);
	  writeV8("\t.align 3\n");
	  writeV8("\t.text\n");
	  regNo = getFreeReg(FLOAT_TYPE);
	  writeV8("\tldr s%d, _CONSTANT_%d\n", regNo, constCount);
	  constCount++;
	  reg.c = 's';
	  break;
	}
      reg.no = regNo;
      return reg;
    }
  else if(node->nodeType == IDENTIFIER_NODE)
    {
      int regNo;
      int index = 0;
      char* name = node->semantic_value.identifierSemanticValue.identifierName;
      DATA_TYPE type;

      SymbolTableEntry* entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
      if(node->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	{
	  type = entry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
	  AST_NODE* indexNode = node->child;
	  index = indexNode->semantic_value.const1->const_u.intval;
	}
      else if(node->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	{
	  type = entry->attribute->attr.typeDescriptor->properties.dataType;
	}

      if(entry->nestingLevel == 0)
	{
	  char* label = entry->address.label;
	  int labelReg = getFreeReg(INT_TYPE);
	  writeV8("\tldr x%d, =%s\n", labelReg, label)
	    if(type == INT_TYPE)
	      {
		regNo = getFreeReg(INT_TYPE);
		writeV8("\tldr w%d, [x%d, #%d]\n", regNo, labelReg, 4*index);
		reg.c = 'w';
	      }
	    else if(type == FLOAT_TYPE)
	      {
		regNo = getFreeReg(FLOAT_TYPE);
		writeV8("\tldr s%d, [x%d, #%d]\n", regNo, labelReg, 4*index);
		reg.c = 's';
	      }
	  freeReg(labelReg);
	}
      else
	{
	  int FpOffset = entry->address.FpOffset;
	  //			printf("id %s FpOffset = %d\n", name, FpOffset);
	  if(type == INT_TYPE)
	    {
	      regNo = getFreeReg(INT_TYPE);
	      writeV8("\tldr w%d, [x29, #%d]\n", regNo, FpOffset-4*index);
	      reg.c = 'w';
	    }
	  else if(type == FLOAT_TYPE)
	    {
	      regNo = getFreeReg(FLOAT_TYPE);
	      writeV8("\tldr s%d, [x29, #%d]\n", regNo, FpOffset-4*index);
	      reg.c = 's';
	    }
	}
      reg.no = regNo;
      return reg;
    }
  else if(node->nodeType == EXPR_NODE)
    {
      if(node->semantic_value.exprSemanticValue.kind == BINARY_OPERATION)
	{
	  Reg LHSReg = doMath(node->child);
	  Reg RHSReg = doMath(node->child->rightSibling);
	  switch(node->semantic_value.exprSemanticValue.op.binaryOp)
	    {
	    case BINARY_OP_ADD:
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{	
		  writeV8("\tfadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      break;
	    case BINARY_OP_SUB:
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{
		  writeV8("\tfsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      break;
	    case BINARY_OP_MUL:
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{
		  writeV8("\tfmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      break;
	    case BINARY_OP_DIV:
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tsdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{
		  writeV8("\tfdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      break;
	    case BINARY_OP_EQ:	// ==	
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, eq\n", LHSReg.c, LHSReg.no);
		  //						writeV8("\tcsel %c%d, %c%d, %c%d, eq\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, eq\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_GE:	// >=
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, ge\n", LHSReg.c, LHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, ge\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_LE:	// <=
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, le\n", LHSReg.c, LHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, le\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_NE:	// !=
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, ne\n", LHSReg.c, LHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, ne\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_GT:	// >
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, gt\n", LHSReg.c, LHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, gt\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_LT:	// <
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  writeV8("\tcset %c%d, lt\n", LHSReg.c, LHSReg.no);
		}
	      else
		{
		  writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		  freeReg(LHSReg.no);
		  LHSReg.no = getFreeReg(INT_TYPE);
		  LHSReg.c = 'w';
		  writeV8("\tcset w%d, lt\n", LHSReg.no);
		}
	      break;
	    case BINARY_OP_AND: // &&
	      if(LHSReg.c == 'w')
		{
		  writeV8("\tand %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{	
		  Reg isLHSZeroReg, isRHSZeroReg;
		  isLHSZeroReg.no = getFreeReg(INT_TYPE);
		  isRHSZeroReg.no = getFreeReg(INT_TYPE);
		  isLHSZeroReg.c = 'w';
						
		  writeV8("\tfcmp %c%d, #0.0\n", LHSReg.c, LHSReg.no);
		  writeV8("\tcset w%d, eq\n", isLHSZeroReg.no);
		  writeV8("\tfcmp %c%d, #0.0\n", RHSReg.c, RHSReg.no);
		  writeV8("\tcset w%d, eq\n", isRHSZeroReg.no);

		  writeV8("\tand w%d, w%d, w%d\n", isLHSZeroReg.no, isLHSZeroReg.no, isRHSZeroReg.no);
		  freeReg(LHSReg.no, RHSReg.no, isRHSZeroReg.no);
		  return isLHSZeroReg;
		}
	      break;
	    case BINARY_OP_OR:	// ||
	      if(LHSReg.c == 'w')
		{
		  writeV8("\torr %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
		}
	      else
		{
		  Reg isLHSZeroReg, isRHSZeroReg;
		  isLHSZeroReg.no = getFreeReg(INT_TYPE);
		  isRHSZeroReg.no = getFreeReg(INT_TYPE);
		  isLHSZeroReg.c = 'w';
						
		  writeV8("\tfcmp %c%d, #0.0\n", LHSReg.c, LHSReg.no);
		  writeV8("\tcset w%d, eq\n", isLHSZeroReg.no);
		  writeV8("\tfcmp %c%d, #0.0\n", RHSReg.c, RHSReg.no);
		  writeV8("\tcset w%d, eq\n", isRHSZeroReg.no);

		  writeV8("\torr w%d, w%d, w%d\n", isLHSZeroReg.no, isLHSZeroReg.no, isRHSZeroReg.no);
		  freeReg(LHSReg.no, RHSReg.no, isRHSZeroReg.no);
		  return isLHSZeroReg;
		}
	      break;
	    }
	  freeReg(RHSReg.no);
	  return LHSReg;
	}
      else if(node->semantic_value.exprSemanticValue.kind == UNARY_OPERATION)
	{
	  if(node->semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_NEGATIVE)
	    {
	      AST_NODE* valueNode = node->child;
	      //				DATA_TYPE type = valueNode->semantic_value.const1->const_type;
	      reg = doMath(valueNode);
	      if(reg.c == 'w')
		{
		  writeV8("\tneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
		}
	      else
		{
		  writeV8("\tfneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
		}
	      return reg;
	    }
	}
    }
  else if(node->nodeType == STMT_NODE && node->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
    {
      doFuncCallStmt(node);
      AST_NODE* funcNameNode = node->child;
      SymbolTableEntry* entry = funcNameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
      DATA_TYPE type = entry->attribute->attr.functionSignature->returnType;
      int retReg;
      if(type == INT_TYPE)
	{
	  retReg = getFreeReg(INT_TYPE);
	  writeV8("\tmov w%d, w0\n", retReg);
	  reg.c = 'w';
	}
      else if(type == FLOAT_TYPE)
	{
	  retReg = getFreeReg(FLOAT_TYPE);
	  writeV8("\tfmov s%d, s0\n", retReg);
	  reg.c = 's';
	}
      reg.no = retReg;
      return reg;
    }
}

int getFreeReg(DATA_TYPE type)
{
  int i;
  if(type == INT_TYPE)
    {
      i = 0;
      while(regStat[i] && i<7)
	i++;
      if(i == 7)
	return -1;
    }
  else
    {
      i = 7;
      while(regStat[i] && i<15)
	i++;
      if(i == 15)
	return -1;
    }
  regStat[i] = 1;
  return i+9;
}

void freeReg(int no, ...)
{
  regStat[no-9] = 0;
	
  va_list ap;
  int arg;
	
  va_start(ap, no);
  while(!(arg = va_arg(ap, int)))
    {
      printf("arg = %d\n", arg);
      regStat[arg-9] = 0;
    }
  va_end(ap);
}

void doAssignStmt(AST_NODE* assignStatNode)
{
  AST_NODE* LHS = assignStatNode->child;
  AST_NODE* RHS = LHS->rightSibling;
  Reg RHSReg = doMath(RHS);
  int offset = 0;
	
  SymbolTableEntry* LHSEntry = LHS->semantic_value.identifierSemanticValue.symbolTableEntry;
  DATA_TYPE type;
  if(LHS->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
    {
      type = LHSEntry->attribute->attr.typeDescriptor->properties.dataType;
    }
  if(LHS->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
    {
      type = LHSEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
      AST_NODE* indexNode = LHS->child;
      offset = indexNode->semantic_value.const1->const_u.intval;
    }

  if(LHSEntry->nestingLevel == 0)
    {
      char* label = LHSEntry->address.label;
      int labelReg = getFreeReg(INT_TYPE);
      writeV8("\tldr x%d, =%s\n", labelReg, label);
      if(type == INT_TYPE)
	{
	  writeV8("\tstr %c%d, [x%d, #%d]\n", RHSReg.c, RHSReg.no, labelReg, offset*4);
	}
      else if(type == FLOAT_TYPE)
	{
	  writeV8("\tstr %c%d, [x%d, #%d]\n", RHSReg.c, RHSReg.no, labelReg, offset*4);
	}
      regStat[labelReg-9] = 0;
    }
  else
    {
      if(type == INT_TYPE)
	{
	  writeV8("\tstr %c%d, [x29, #%d]\n", RHSReg.c, RHSReg.no, LHSEntry->address.FpOffset - 4*offset);		
	}
      else if(type == FLOAT_TYPE)
	{
	  writeV8("\tstr %c%d, [x29, #%d]\n", RHSReg.c, RHSReg.no, LHSEntry->address.FpOffset);
	}
      constCount++;
    }
  freeReg(RHSReg.no);
}

void writeString(char* strName, char* strValue)
{
  //data part
  writeV8("\t.data\n");

  char* newStrValue = (char*)malloc(sizeof(strValue)*2);
  int count = 0;
  int newcount = 0;
  int length = 0;
  while(strValue[count] != '\0')
    {
      /*if(strValue[count] == '\n'){
	newStrValue[newcount++] = '\\';
	newStrValue[newcount++] = 'n';
	} else if(strValue[count] == '\t'){
	newStrValue[newcount++] = '\\';
	newStrValue[newcount++] = 't';
	} else if(strValue[count] == '\\'){
	newStrValue[newcount++] = '\\';
	newStrValue[newcount++] = '\\';
	} else if(strValue[count] == '\r'){
	newStrValue[newcount++] = '\\';
	newStrValue[newcount++] = 'r';
	} else if(strValue[count] == '\0'){
	newStrValue[newcount++] = '\\';
	newStrValue[newcount++] = '0';
	} else {*/
      newStrValue[newcount++] = strValue[count];
      count++;
    }
  newStrValue[newcount] = '\0';
  fprintf(stderr, "original strvalue = [%s], after = [%s]\n", strValue, newStrValue);

  writeV8("%s: .ascii %s\n", strName, newStrValue);

  int alignNum = 4-((strlen(newStrValue)+2)%4);
  if(alignNum == 4)
    alignNum = 0;
  writeV8("\t.align %d\n", alignNum);//align is 4 times
    
  //test part
  writeV8("\t.text\n");
  writeV8("\tldr x0, =%s\n", strName);//"_CONSTANT_0" or what?
  //mov x0, x9 //TODO: check is needed or not
  writeV8("\tbl _write_str\n");
}

void writeInt(Reg reg)//reg will read the value from local stack and write
{
  //if directly give a reg to write, it's value will be deleted(?) after called write()
  writeV8("\tmov w0, %c%d\n", reg.c, reg.no);
  writeV8("\tbl _write_int\n");
}

void writeFloat(Reg reg)
{
  writeV8("\tfmov s0, %c%d\n", reg.c, reg.no);
  writeV8("\tbl _write_float\n");
}

void readInt()//will read value into reg and write into local stack
{
  int i = getFreeReg(INT_TYPE);
  writeV8("\tbl _read_int\n");
  writeV8("\tmov w%d, w0\n", i);
  //writeV8("str w%d, [x29, #-4]\n", i);
}

void readFloat()
{
  int i = getFreeReg(FLOAT_TYPE);
  writeV8("\tbl _read_float\n");
  writeV8("\tfmov s%d, s0\n", i);
  //writeV8("str s%d, [x29, #-8]\n", i);
}

void doFuncCallStmt(AST_NODE* funcCallStmtNode)
{
  AST_NODE* funcNameNode = funcCallStmtNode->child;
  char* funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;
  AST_NODE* parameterListNode = funcNameNode->rightSibling;
  AST_NODE* firstParameter = parameterListNode->child;
  if(strcmp(funcName, "fread") == 0)
    {//TODO: 1. how to assign(he use w0 as return val) 2. send parameter
      readFloat();
    } 
  else if(strcmp(funcName, "read") == 0)
    {
      readInt();
    } 
  else if(strcmp(funcName, "write") == 0)
    {
      Reg reg;
      char strName[20];
      switch(firstParameter->dataType)
	{
	case INT_TYPE:
	  reg = doMath(firstParameter);
	  writeInt(reg);
	  freeReg(reg.no);
	  break;
	case FLOAT_TYPE:
	  reg = doMath(firstParameter);
	  writeFloat(reg);
	  freeReg(reg.no);
	  break;
	case CONST_STRING_TYPE:
	  sprintf(strName, "_CONSTANT_%d", constCount++);//TODO: check data declare twice
	  writeString(strName, firstParameter->semantic_value.const1->const_u.sc);
	  break;
	}
    } 
  else
    {
      writeV8("\tbl _start_%s\n", funcName);
    }
}

void doRetStmt(AST_NODE* stmtNode, char* funcName)
{
  AST_NODE* retValNode = stmtNode->child;
  Reg retReg = doMath(retValNode);
  writeV8("\tmov %c0, %c%d\n", retReg.c, retReg.c, retReg.no);
  writeV8("\tb _end_%s\n", funcName);
  freeReg(retReg.no);
}

void doStmtLst(AST_NODE* stmtLstNode, char* funcName)
{
  AST_NODE* stmtNode = stmtLstNode->child;
  while(stmtNode)
    {
      switch(stmtNode->semantic_value.stmtSemanticValue.kind)
	{
	case ASSIGN_STMT:
	  doAssignStmt(stmtNode);
	  break;
	case FUNCTION_CALL_STMT:
	  doFuncCallStmt(stmtNode);
	  break;
	case RETURN_STMT:
	  doRetStmt(stmtNode, funcName);
	  break;
	case WHILE_STMT:
	  doWhileStmt(stmtNode, funcName);
	  break;
	case IF_STMT:
	  doIfStmt(stmtNode, funcName);
	  break;
	}
      stmtNode = stmtNode->rightSibling;
    }
}

void doWhileStmt(AST_NODE* stmtNode, char* funcName)
{
  whileCount++;
  char testName[15];
  sprintf(testName, "WhileTest%d", whileCount);
  char exitName[15];
  sprintf(exitName, "WhileExit%d", whileCount);

  writeV8("%s:\n", testName);
  Reg reg = doMath(stmtNode->child);  //generate xxx
  //I wish to get result register 
  if(reg.c == 'w')
    {
      writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
    }
  else
    {
      writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
    }
  freeReg(reg.no);

  writeV8("\tbeq %s\n", exitName);
  doBlock(stmtNode->child->rightSibling, funcName);  //generate yyy
  writeV8("\tb %s\n", testName);
  writeV8("%s:\n", exitName);
}

void doIfStmt(AST_NODE* stmtNode, char* funcName)
{
  AST_NODE* elsePartNode = stmtNode->child->rightSibling->rightSibling;
  if(elsePartNode->nodeType == NUL_NODE)
    {
      ifCount++;
      char exitName[10];
      sprintf(exitName, "IfExit%d", ifCount);
      //if xxx eq false or 0 , jump to exit
      Reg reg = doMath(stmtNode->child);    //code of xxx(with final compare jump to exit)
      if(reg.c == 'w')
	{
	  writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
	} 
      else 
	{
	  writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
	}
      freeReg(reg.no);
      writeV8("\tbeq %s\n", exitName); 
      doBlock(stmtNode->child->rightSibling, funcName);    //TODO: code of block(yyy)
      writeV8("%s:\n", exitName);  
    } 
  else 
    {
      ///if else
      ifCount++;
      char elseName[10];
      sprintf(elseName, "IfElse%d", ifCount);
      char exitName[10];
      sprintf(exitName, "IfExit%d", ifCount);

      Reg reg = doMath(stmtNode->child);    //TODO: code of xxx(with final compare jump to else)
      if(reg.c == 'w')
	{
	  writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
	} 
      else 
	{
	  writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
	}
      freeReg(reg.no);
      writeV8("\tbeq %s\n", elseName);
      doBlock(stmtNode->child->rightSibling, funcName);    //TODO: code of if block(yyy)(with final jump to exit)
      writeV8("\tb %s\n", exitName);
      writeV8("%s:\n", elseName);
      doBlock(elsePartNode, funcName);    //TODO: code of else block(zzz)
      writeV8("%s:\n", exitName);
    }
}

void doBlock(AST_NODE* blockNode, char* funcName)
{
  AST_NODE* content = blockNode->child;
  while(content)
    {
      switch(content->nodeType)
	{
	case STMT_LIST_NODE:
	  doStmtLst(content, funcName);
	  break;
	case VARIABLE_DECL_LIST_NODE:
	  doVarDeclLst(content, 1);
	  break;
	}
      content = content->rightSibling;
    }
}

void doDeclFunc(AST_NODE* declNode)
{
  AST_NODE* blockNode = declNode->child->rightSibling->rightSibling->rightSibling;
  AST_NODE* content = blockNode->child;
	

  int frameSize = 92;
  AROffset = 0;
  char* funcName = declNode->child->rightSibling->semantic_value.identifierSemanticValue.identifierName;
  gen_prologue(funcName);

  while(content)
    {
      switch(content->nodeType)
	{
	case STMT_LIST_NODE:
	  doStmtLst(content, funcName);
	  break;
	case VARIABLE_DECL_LIST_NODE:
	  doVarDeclLst(content, 1);
	  break;
	}
      content = content->rightSibling;
    }

  gen_epilogue(funcName);
  gen_frameSizeLabel(funcName, frameSize-AROffset);
  AROffset = 0;
}

void doVarDeclLst(AST_NODE* varDeclNode, int lv)
{
  varDeclNode = varDeclNode->child;
  while(varDeclNode)
    {
      AST_NODE* typeNode = varDeclNode->child;
      AST_NODE* nameNode = typeNode->rightSibling;
      while(nameNode)
	{
	  char* name = nameNode->semantic_value.identifierSemanticValue.identifierName;
	  //			printf("Decl id %s\n", name);
	  SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
	  if(nameNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	    {
	      if(lv == 0) //global var decl
		{
		  char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
		  sprintf(label, "_g_%s", name);
		  label[strlen(name)+3] = '\0';
	
		  writeV8("\t.data\n");
		  writeV8("%s:\n", label);
		  if(typeNode->dataType == INT_TYPE)
		    {
		      writeV8("\t.word 0\n");
		    }
		  else if(typeNode->dataType == FLOAT_TYPE)
		    {
		      writeV8("\t.float 0\n");
		    }
		  writeV8("\t.align 3\n");
		  writeV8("\t.text\n");
		  entry->address.label = label;
		}
	      else
		{
		  AROffset -= 4;
		  entry->address.FpOffset = AROffset;
		}
	    }
	  else if(nameNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	    {
	      AST_NODE* arraySizeNode = nameNode->child;
	      int arraySize = arraySizeNode->semantic_value.const1->const_u.intval;
	      SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
	      if(lv == 0)
		{
		  char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
		  sprintf(label, "_g_%s", name);
		  label[strlen(name)+3] = '\0';
	
		  writeV8("\t.data\n");
		  writeV8("%s:\n", label);
		  writeV8("\t.place %d\n", arraySize);
		  writeV8("\t.text\n");
		  entry->address.label = label;
		}
	      else
		{
		  entry->address.FpOffset = AROffset-4;
		  AROffset -= 4*arraySize;
		}
	    }
	  //			printf("AROffset = %d, entry->address.FpOffset = %d\n", AROffset, entry->address.FpOffset);
	  nameNode = nameNode->rightSibling;
	}
      varDeclNode = varDeclNode->rightSibling;
    }
}

void doDeclLst(AST_NODE* declNode)
{
  switch(declNode->semantic_value.declSemanticValue.kind)
    {
    case FUNCTION_DECL:
      doDeclFunc(declNode);
      break;
    }
}

void printCode(AST_NODE *root)
{
  //frame information: temporarily added
  outputFile = fopen("output.s", "w");
  ifCount = 0;
  whileCount = 0;
  constCount = 0;

  AST_NODE* child = root->child;
  while(child)
    {
      if(child->nodeType == VARIABLE_DECL_LIST_NODE)
	{
	  doVarDeclLst(child, 0);
	}
      else if(child->nodeType == DECLARATION_NODE);
      {
	doDeclLst(child);
      }
      child = child->rightSibling;
    }
}
