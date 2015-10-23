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
extern int IDcount;

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
  Comment* newc = (Comment*)malloc(strlen(comment)+1);
  int len = strlen(comment);
  newc->s = (char*)malloc(len+1);
  strncpy(newc->s, comment, len+1);
  newc->next = NULL;
  if(comment_root == NULL){
    comment_root = newc;
  } else {
    previusComment->next = newc;
  }
  previusComment = newc;
}

char reservedWordList[][12] = {"return", "typedef", "if", "else", "int", "float", "for", "void", "while"};
const int reservedWordNum = 9;
int checkReservedWords(char *name){
  int i;
  for(i = 0; i < reservedWordNum; i++){
    if(strcmp(reservedWordList[i], name) == 0){
      return 1;
    }
  }
  return 0;
}

void insertID(char *name){
  if(checkReservedWords(name) == 1){
    return;
  }
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
  int nowcount = 0; symtab* nowp;
  //printf("count = %d\n", IDcount);
  symtab** newhashtable = (symtab**)malloc(sizeof(symtab*)*IDcount);
  for (i=0; i<TABLE_SIZE; i++){
    nowp = hash_table[i];
    if (nowp != NULL){
      while(nowp != NULL){
	newhashtable[nowcount++] = nowp;
	nowp = nowp->front;
      }
    }
  }
  qsort(newhashtable, nowcount, sizeof(symtab*), compstr);
  for (i=0; i<nowcount; i++){
    symtab* symptr = newhashtable[i];
    printf("%s\t%d\n",symptr->lexeme, symptr->counter);
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
