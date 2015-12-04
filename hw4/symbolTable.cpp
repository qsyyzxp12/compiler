#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
  12/4:
  1. doesn't implement sameNameInOuterLevel
  2. scopeDisplay is a vector
 */

int HASH(char * str) {
	int idx=0;
	while (*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}
	return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTable symbolTable;

SymbolTableEntry* newSymbolTableEntry(int currentLevel)
{
    SymbolTableEntry* symbolTableEntry = new SymbolTableEntry;
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->currentLevel = currentLevel;
    return symbolTableEntry;
}

#define isHead(a) (a->prevInHashChain == NULL)
#define isEnd(a) (a->nextInHashChain == NULL)
void removeFromHashTrain(int hashIndex, SymbolTableEntry* entry){
  if(isHead(entry) && isEnd(entry)){
    symbolTable.hashTable[hashIndex] = NULL;
  } else if(isHead(entry)){
    entry->nextInHashChain->prevInHashChain = NULL;
    symbolTable.hashTable[hashIndex] = entry->nextInHashChain;
  } else if(isEnd(entry)) {
    entry->prevInHashChain->nextInHashChain = NULL;
  } else {
    entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
    entry->nextInHashChain->prevInHashChain = entry->prevInHashChain;
  }
  entry->prevInHashChain = entry->nextInHashChain = NULL;
  return;
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry){//???
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashIndex];
  symbolTable.hashTable[hashIndex] = entry;
  if(hashentry != NULL){
    hashentry->prevInHashChain = entry;
    entry->nextInHashChain = hashentry;
  }
}

void initReservedID();
#define INITIAL_SCOPE_NUM 5
void initializeSymbolTable(){
  symbolTable.currentLevel = 0;//set global = 0
  for(int i = 0; i < HASH_TABLE_SIZE; i++)//256
    symbolTable.hashTable[i] = NULL;
  symbolTable.scopeDisplay.resize(INITIAL_SCOPE_NUM);
  for(int i = 0; i < INITIAL_SCOPE_NUM; i++)
    symbolTable.scopeDisplay[i] = NULL;

  initReservedID();
}
void makeEntry(char* name, DATA_TYPE type){
  SymbolTableEntry* entry = newSymbolTableEntry(0);//TODO: needs to be the global level
  entry->name = name;
  entry->attribute = new SymbolAttribute;
  entry->attribute->attributeKind = TYPE_ATTRIBUTE;
  TypeDescriptor* td = new TypeDescriptor;
  td->kind = SCALAR_TYPE_DESCRIPTOR;//i think it's non-array...
  td->properties.dataType = type;
  entry->attribute->attr.typeDescriptor = td;
  enterIntoHashTrain(HASH(entry->name), entry);
}
void initReservedID(){//if no this, void, int, double... is undeclared
  //void int float 
  makeEntry("int", INT_TYPE);
  makeEntry("void", VOID_TYPE);
  makeEntry("float", FLOAT_TYPE);
  }

void symbolTableEnd(){
  symbolTable.scopeDisplay.clear();
  for(int i = 0; i < HASH_TABLE_SIZE; i++){
    if(symbolTable.hashTable[i] != NULL){
      SymbolTableEntry* hashentry = symbolTable.hashTable[i];
      while(hashentry != NULL){
	SymbolTableEntry* todelete = hashentry;
	hashentry = hashentry->nextInHashChain;
	delete todelete;
      }
    }
  }
}

SymbolTableEntry* retrieveSymbol(char* symbolName){
  SymbolTableEntry* hashentry = symbolTable.hashTable[HASH(symbolName)];
  while(hashentry != NULL){
    if(strcmp(symbolName, hashentry->name) == 0)
      return hashentry;
    hashentry = hashentry->nextInHashChain;
  }
  fprintf(stderr, "redeclare error\n");//ERROR:
  return NULL;
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute){
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];
  
  while(hashentry != NULL){
    if(strcmp(hashentry->name, symbolName) == 0)
      if(symbolTable.currentLevel == hashentry->currentLevel){	// ERROR: redeclare error
	fprintf(stderr, "redeclare error\n");
	return NULL;
      }
    hashentry = hashentry->nextInHashChain;
  }

  SymbolTableEntry* newentry = newSymbolTableEntry(symbolTable.currentLevel);
  newentry->attribute = attribute;
  newentry->name = symbolName;
  enterIntoHashTrain(hashValue, newentry);

  newentry->nextInSameLevel = symbolTable.scopeDisplay[symbolTable.currentLevel];
  symbolTable.scopeDisplay[symbolTable.currentLevel] = newentry;

  return newentry;
}

//TODO: use c++ class to rewrite
void removeSymbol(char* symbolName){
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];
  while(hashentry != NULL){
    if((strcmp(symbolName, hashentry->name) == 0) && symbolTable.currentLevel == hashentry->currentLevel){
      removeFromHashTrain(hashValue, hashentry);
      return;
    }
    hashentry = hashentry->nextInHashChain;
  }
  fprintf(stderr, "remove symbol not found error\n");//ERROR:
}

int declaredLocally(char* symbolName){//is declared in current scope or not
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];
  while(hashentry != NULL)
    if((strcmp(hashentry->name, symbolName) == 0) && hashentry->currentLevel == symbolTable.currentLevel)
      return 1;
  return 0;
}

void openScope(){
  symbolTable.currentLevel++;
  int originalLevelNum = symbolTable.scopeDisplay.size();
  if(symbolTable.currentLevel >= originalLevelNum){
    symbolTable.scopeDisplay.resize(symbolTable.currentLevel+1);
    for(int i = originalLevelNum+1; i < symbolTable.currentLevel+1; i++){
      symbolTable.scopeDisplay[i] = NULL;
    }
  } else 
    symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;//new scope instead//TODO: null??
}

void closeScope(){//revert to previous scope
  SymbolTableEntry* hashentry = symbolTable.scopeDisplay[symbolTable.currentLevel];
  symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
  while(hashentry != NULL){
    removeFromHashTrain(HASH(hashentry->name), hashentry);
    hashentry = hashentry->nextInSameLevel;//!!
  }
  symbolTable.currentLevel--;
}
