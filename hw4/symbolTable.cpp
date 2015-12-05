#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"

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
void removeFromHashTrain(int hashIndex, SymbolTableEntry* entry){//do not delete
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

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry){
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashIndex];
  if(hashentry != NULL){
     hashentry->prevInHashChain = entry;
     entry->nextInHashChain = hashentry;
  }     
  symbolTable.hashTable[hashIndex] = entry;
}

void initReservedID();
void enterEntry(char* name, DATA_TYPE type, int level);
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
#define GLOBAL_SCOPE_LEVEL 0
void initReservedID(){//if no this, void, int, double... is undeclared
  //void int float //TODO: if else return while for main 
  enterEntry("int", INT_TYPE, GLOBAL_SCOPE_LEVEL);
  enterEntry("void", VOID_TYPE, GLOBAL_SCOPE_LEVEL);
  enterEntry("float", FLOAT_TYPE, GLOBAL_SCOPE_LEVEL);
}
void enterEntry(char* name, DATA_TYPE type, int level){
  SymbolTableEntry* entry = newSymbolTableEntry(level);
  entry->name = name;
  entry->attribute = new SymbolAttribute;
  entry->attribute->attributeKind = TYPE_ATTRIBUTE;

  TypeDescriptor* td = new TypeDescriptor;
  td->kind = SCALAR_TYPE_DESCRIPTOR;//non-array...
  td->properties.dataType = type;
  entry->attribute->attr.typeDescriptor = td;
  
  enterSymbol(entry->name, entry->attribute);
}

void symbolTableEnd(){
  symbolTable.scopeDisplay.clear();
  for(int i = 0; i < HASH_TABLE_SIZE; i++){
    SymbolTableEntry* hashentry = symbolTable.hashTable[i];
    while(hashentry != NULL){
      SymbolTableEntry* todelete = hashentry;
      hashentry = hashentry->nextInHashChain;
      delete todelete;
    }
  }
}

SymbolTableEntry* retrieveSymbol(char* symbolName){
  fprintf(stderr, "try to retrieve %s\n", symbolName);
  for(int i = symbolTable.currentLevel; i >= 0; i--){//from the most closest scope, search the name
    SymbolTableEntry* hashentry = symbolTable.scopeDisplay[i];
    while(hashentry != NULL){
      if(strcmp(symbolName, hashentry->name) == 0)//don't check level because it can use previous level variable
	return hashentry;
      hashentry = hashentry->nextInSameLevel;
    }
  }
  //TODO:undeclared
  return NULL;
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute){
  fprintf(stderr, "enter symbol %s in level %d\n", symbolName, symbolTable.currentLevel);
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];

  while(hashentry != NULL){
    if(strcmp(hashentry->name, symbolName) == 0)
      if(symbolTable.currentLevel == hashentry->currentLevel){
	fprintf(stderr, "ERROR:redeclare error\n");
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
void removeSymbol(char* symbolName){//only works in currentLevel
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];
  bool isFound = false;

  //remove in hashtable
  while(hashentry != NULL){
    if((strcmp(symbolName, hashentry->name) == 0) && symbolTable.currentLevel == hashentry->currentLevel){
      removeFromHashTrain(hashValue, hashentry);
      isFound = true;
      break;
    }
    hashentry = hashentry->nextInHashChain;
  }
  if(!isFound)
    fprintf(stderr, "ERROR: try to remove inexist symbol\n");

  //remove in scope
  SymbolTableEntry* scopeEntry = symbolTable.scopeDisplay[symbolTable.currentLevel];
  isFound = false;
  SymbolTableEntry* prevScopeEntry = NULL;
  SymbolTableEntry* toRemove = NULL;
  while(scopeEntry != NULL){
    if(strcmp(symbolName, scopeEntry->name) == 0){
      if(prevScopeEntry == NULL){//head
	symbolTable.scopeDisplay[symbolTable.currentLevel] = scopeEntry->nextInSameLevel;
      } else {
	prevScopeEntry->nextInSameLevel = scopeEntry->nextInSameLevel;
      }
      toRemove = scopeEntry;
      isFound = true;
      break;
    }
    prevScopeEntry = scopeEntry;
    scopeEntry = scopeEntry->nextInSameLevel;
  }
  if(!isFound)
    fprintf(stderr, "ERROR: try to remove inexist symbol\n");

  delete toRemove;//TODO: need to remove pointer in substructure?
}

bool declaredLocally(char* symbolName){//is declared in current scope or not
  int hashValue = HASH(symbolName);
  SymbolTableEntry* hashentry = symbolTable.hashTable[hashValue];
  while(hashentry != NULL){
    if((strcmp(hashentry->name, symbolName) == 0) && hashentry->currentLevel == symbolTable.currentLevel)
      return true;
    hashentry = hashentry->nextInHashChain;
  }
  return false;
}

void openScope(){
  symbolTable.currentLevel++;
  int originalLevelNum = symbolTable.scopeDisplay.size();
  if(symbolTable.currentLevel > originalLevelNum){
    symbolTable.scopeDisplay.resize(symbolTable.currentLevel+1);
    for(int i = originalLevelNum; i < symbolTable.currentLevel+1; i++)
      symbolTable.scopeDisplay[i] = NULL;
  } else {
    symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;//new empty scope instead
  }
}

void closeScope(){//revert to previous scope
  SymbolTableEntry* hashentry = symbolTable.scopeDisplay[symbolTable.currentLevel];
  symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
  while(hashentry != NULL){
    removeFromHashTrain(HASH(hashentry->name), hashentry);//remove from current symboltable
    hashentry = hashentry->nextInSameLevel;
  }
  symbolTable.currentLevel--;
}
