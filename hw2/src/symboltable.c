#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"header.h"

#define TABLE_SIZE	256

symtab * hash_table[TABLE_SIZE];
Comment* comment_root, *previusComment;
extern int linenumber;

int HASH(char * str){
  int idx=0;
  while(*str){
    idx = idx << 1;
    idx+=*str;
    str++;
  }	
  return (idx & (TABLE_SIZE-1));
}

/*returns the symbol table entry if found else NULL*/

symtab * lookup(char *name){
  int hash_key;
  symtab* symptr;
  if(!name)
    return NULL;
  hash_key=HASH(name);
  symptr=hash_table[hash_key];

  while(symptr){
    if(!(strcmp(name,symptr->lexeme)))
      return symptr;
    symptr=symptr->front;
  }
  return NULL;
}

void insertComment(char* comment){
  Comment* newc = (Comment*)malloc(sizeof(Comment));
  int len = strlen(comment);
  newc->s = (char*)malloc(sizeof(char)*len);
  strncpy(newc->s, comment, len);
  newc->next = NULL;
  if(comment_root == NULL){
    comment_root = newc;
  } else {
    previusComment->next = newc;
  }
  previusComment = newc;
}

void insertID(char *name){
  int hash_key;
  symtab* ptr;
  symtab* symptr=(symtab*)malloc(sizeof(symtab));	
	
  hash_key=HASH(name);
  ptr=hash_table[hash_key];
	
  if(ptr==NULL){
    /*first entry for this hash_key*/
    hash_table[hash_key]=symptr;
    symptr->front=NULL;
    symptr->back=symptr;
  }
  else{
    symptr->front=ptr;
    ptr->back=symptr;
    symptr->back=symptr;
    hash_table[hash_key]=symptr;	
  }
	
  strcpy(symptr->lexeme,name);
  symptr->line=linenumber;
  symptr->counter=1;
}

void printSym(symtab* ptr) 
{
  printf(" Name = %s \n", ptr->lexeme);
  printf(" References = %d \n", ptr->counter);
}

void printComment(){
  Comment* nowc = comment_root;
  while(nowc != NULL){
    printf("%s\n", nowc->s);
    nowc = nowc->next;
  }
}

int compstr(const void* ai, const void* bi){
  symtab* a = *(symtab**)ai;//not a good thing...
  symtab* b = *(symtab**)bi;
  //printf("compare %s %s\n", a->lexeme, b->lexeme);
  return strcmp(a->lexeme, b->lexeme);
}

void printIDFrequency(){
  int i;
  symtab* hashList = NULL, *nowp = NULL;
  int count = 0;
  for (i=0; i<TABLE_SIZE; i++){
    symtab* symptr = hash_table[i];
    if (symptr != NULL){
      if(hashList == NULL){
	hashList = symptr;
	nowp = symptr;
	count++;
      } else {
	symptr->back = nowp;
	nowp->front = symptr;
      }
      while(nowp != NULL && nowp->front != NULL){
	nowp = nowp->front;
	count++;
      }
    }
  }
  printf("new count = %d\n", count);
  symtab** newhashtable = (symtab**)malloc(sizeof(symtab*)*count);
  for (i=0; i<count; i++){
    newhashtable[i] = hashList;
    //printf("prei = %d: %s %d\n", i, hashList->lexeme, hashList->counter);
    hashList = hashList->front;
  }
  qsort(newhashtable, count, sizeof(symtab*), compstr);
  for (i=0; i<count; i++){
    symtab* symptr = newhashtable[i];
    printf("i = %d: %s %d\n", i, symptr->lexeme, symptr->counter);
  }  
}

void printSymTab()
{
  int i;
  printf("----- Symbol Table ---------\n");
  for (i=0; i<TABLE_SIZE; i++)
    {
      symtab* symptr;
      symptr = hash_table[i];
      while (symptr != NULL)
	{
	  printf("====>  index = %d \n", i);
	  printSym(symptr);
	  symptr=symptr->front;
	}
    }
}
