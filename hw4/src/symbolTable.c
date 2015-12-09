#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// This file is for reference only, you are not required to follow the implementation. //

int HASH(char * str) {
	int idx=0;
	while (*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}
	return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTableEntry* newSymbolTableEntry(int nestingLevel)
{
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->sameNameInOuterLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->nestingLevel = nestingLevel;
    return symbolTableEntry;
}

void removeFromHashTrain(int hashIndex, SymbolTableEntry* entry)
{
	
	if(!entry->nextInHashChain && !entry->prevInHashChain)
		symbolTable.hashTable[hashIndex] = NULL;
	else if(!entry->nextInHashChain && entry->prevInHashChain)
		entry->prevInHashChain->nextInHashChain = NULL;
	else if(entry->nextInHashChain && !entry->prevInHashChain)
	{
		entry->nextInHashChain->prevInHashChain = NULL;
		symbolTable.hashTable[hashIndex] = entry->nextInHashChain;
	}
	else if(entry->nextInHashChain && entry->prevInHashChain)
	{
		entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
		entry->nextInHashChain->prevInHashChain = entry->prevInHashChain;
	}
	entry->prevInHashChain = NULL;
	entry->nextInHashChain = NULL;
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry)
{
	if(symbolTable.hashTable[hashIndex])
	{
		symbolTable.hashTable[hashIndex]->prevInHashChain = entry;
		entry->nextInHashChain = symbolTable.hashTable[hashIndex];
	}
	symbolTable.hashTable[hashIndex] = entry;
}
void initReserveWord(char* name, DATA_TYPE type)
{
	SymbolTableEntry* entry = newSymbolTableEntry(0);
	entry->name = name;
	entry->attribute = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
	entry->attribute->attr.typeDescriptor = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
	
	entry->attribute->attributeKind = TYPE_ATTRIBUTE;
	entry->attribute->attr.typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
	entry->attribute->attr.typeDescriptor->properties.dataType = type;
	int hashIndex = HASH(name);
	enterIntoHashTrain(hashIndex, entry);
	entry->nextInSameLevel = symbolTable.scopeDisplay[0];
	symbolTable.scopeDisplay[0] = entry->nextInSameLevel;
}

void initializeSymbolTable()
{
	int i;
	symbolTable.currentLevel = 0;
	symbolTable.scopeDisplayElementCount = 5;
	for(i=0; i < HASH_TABLE_SIZE; i++)
		symbolTable.hashTable[i] = NULL;
	symbolTable.scopeDisplay = (SymbolTableEntry**)malloc(sizeof(SymbolTableEntry*)*symbolTable.scopeDisplayElementCount);
	for(i=0; i<symbolTable.scopeDisplayElementCount; i++)
		symbolTable.scopeDisplay[i] = NULL;

	initReserveWord("void", VOID_TYPE);
	initReserveWord("int", INT_TYPE);
	initReserveWord("float", FLOAT_TYPE);

}

void symbolTableEnd()
{
	int i;
	for(i=0; i<HASH_TABLE_SIZE; i++)
	{
		SymbolTableEntry* entry = symbolTable.hashTable[i];
		while(entry)
		{
			SymbolTableEntry* tmp = entry;
			entry = entry->nextInHashChain;
			free(tmp);
		}
	}
	for(i=0; i<symbolTable.scopeDisplayElementCount; i++)
		symbolTable.scopeDisplay[i] = NULL;
}

SymbolTableEntry* retrieveSymbol(char* symbolName)
{
	int curr_lv = symbolTable.currentLevel;
	SymbolTableEntry* entry = symbolTable.scopeDisplay[curr_lv];
	while(entry)
	{
		if(!strcmp(entry->name, symbolName))
			return entry;
		entry = entry->nextInSameLevel;
	}
	return NULL;
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute)
{
	int hashIndex = HASH(symbolName);
/*	SymbolTableEntry* entry = symbolTable.hashTable[hashIndex];
	while(entry)
	{
		if(!strcmp(entry->name, symbolName) && entry->nestingLevel == symbolTable.currentLevel)
		{
			printf("ID %s redeclared\n", symbolName);
			return NULL;
		}
		entry = entry->nextInHashChain;
	}*/

	//construct the entry
	SymbolTableEntry *entry = newSymbolTableEntry(symbolTable.currentLevel);
	entry->name = symbolName;
	entry->attribute = attribute;
	entry->nestingLevel = symbolTable.currentLevel;

	//add hash chain
	enterIntoHashTrain(hashIndex, entry);

	//add to scopeDisplay chain
	entry->nextInSameLevel = symbolTable.scopeDisplay[symbolTable.currentLevel];
	symbolTable.scopeDisplay[symbolTable.currentLevel] = entry;

	return entry;
}

//remove the symbol from the current scope
void removeSymbol(char* symbolName)
{
	int curr_lv = symbolTable.currentLevel;
	SymbolTableEntry* entry = symbolTable.scopeDisplay[curr_lv];
	if(!strcmp(entry->name, symbolName))
	{
		symbolTable.scopeDisplay[curr_lv] = entry->nextInSameLevel;
		return;
	}
	while(entry->nextInSameLevel)
	{
		if(!strcmp(entry->nextInSameLevel->name, symbolName))
		{
			int hashIndex = HASH(symbolName);
			removeFromHashTrain(hashIndex, entry->nextInSameLevel);
			entry->nextInSameLevel = entry->nextInSameLevel->nextInSameLevel;
			free(entry);
			return;
		}
		entry = entry->nextInSameLevel;
	}
}

int declaredLocally(char* symbolName)
{
	int hashIndex = HASH(symbolName);
	SymbolTableEntry* entry = symbolTable.hashTable[hashIndex];
	while(entry)
	{
		if(!strcmp(entry->name, symbolName) && entry->nestingLevel == symbolTable.currentLevel)
			return 1;
		entry = entry->nextInHashChain;
	}
	return 0;
}

void openScope()
{
	symbolTable.currentLevel++;
	if(symbolTable.currentLevel + 1 > symbolTable.scopeDisplayElementCount)
	{
		int i;
		symbolTable.scopeDisplayElementCount += 5;
		SymbolTableEntry** newDisplay = (SymbolTableEntry**)malloc(sizeof(SymbolTableEntry*)*symbolTable.scopeDisplayElementCount);
		memcpy(newDisplay, symbolTable.scopeDisplay, symbolTable.scopeDisplayElementCount-5);
		for(i=symbolTable.scopeDisplayElementCount-5; i<symbolTable.scopeDisplayElementCount; i++)
			newDisplay[i] = NULL;
		free(symbolTable.scopeDisplay);
		symbolTable.scopeDisplay = newDisplay;
	}
}

void closeScope()
{
	int curr_lv = symbolTable.currentLevel;
	SymbolTableEntry* entry = symbolTable.scopeDisplay[curr_lv];
	while(entry)
	{
		int hashIndex = HASH(entry->name);
		removeFromHashTrain(hashIndex, entry);
		entry = entry->nextInSameLevel;
	}
	symbolTable.scopeDisplay[curr_lv] = NULL;
	symbolTable.currentLevel--;
}

void showScope()
{
	int lv = 0;
	SymbolTableEntry* entryListHead = symbolTable.scopeDisplay[lv];

	while(entryListHead)
	{
		printf("\nlv = %d\n", lv);
		SymbolTableEntry* entry = entryListHead;
		while(entry)
		{
			printf("------ name = %s -----\n", entry->name);
			printf("nesting level = %d\n", entry->nestingLevel);
			SymbolAttribute* attr = entry->attribute;
			if(attr->attributeKind == VARIABLE_ATTRIBUTE)
			{
				printf("it's a var.\n");
				if(attr->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
					printf("it's not an array.\nData Type NO. = %d\n", attr->attr.typeDescriptor->properties.dataType);
				else if(attr->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
				{
					printf("it's an array.\n");
					printf("dimension = %d\n", attr->attr.typeDescriptor->properties.arrayProperties.dimension);
					int i;
					for(i=0; i<attr->attr.typeDescriptor->properties.arrayProperties.dimension; i++)
						printf("[%d]", attr->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[i]);
					printf("\nData Type No. = %d\n",  attr->attr.typeDescriptor->properties.arrayProperties.elementType);
				}
			}
			else if(attr->attributeKind == TYPE_ATTRIBUTE)
			{
				printf("it's a typedef\n");
				printf("ori type No. = %d\n", attr->attr.typeDescriptor->properties.dataType);
			}
			else if(attr->attributeKind == FUNCTION_SIGNATURE)
			{
				printf("it's a function signature\n");
				printf("return type data type No. = %d\n", attr->attr.functionSignature->returnType);
				printf("parameter count = %d\n", attr->attr.functionSignature->parametersCount);
				Parameter* param = attr->attr.functionSignature->parameterList;
				while(param)
				{
					printf("\nparameter name = %s\n", param->parameterName);
					if(param->type->kind == SCALAR_TYPE_DESCRIPTOR)
						printf("it's not an array.\nData Type NO. = %d\n", param->type->properties.dataType);
					else if(param->type->kind == ARRAY_TYPE_DESCRIPTOR)
					{
						printf("it's an array type.\n");
						printf("dimension = %d\n", param->type->properties.arrayProperties.dimension);
						int i;
						for(i=0; i<param->type->properties.arrayProperties.dimension; i++)
							printf("[%d]", param->type->properties.arrayProperties.sizeInEachDimension[i]);
						printf("\nData Type No. = %d\n",  param->type->properties.arrayProperties.elementType);
					}
					param = param->next;
				}
			}
			entry = entry->nextInSameLevel;
		}
		lv++;
		entryListHead = symbolTable.scopeDisplay[lv];
	}
}

