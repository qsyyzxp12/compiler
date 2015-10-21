#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"header.h"

#define TABLE_SIZE	256
#define min(a,b) (((a)<(b))?(a):(b))

symtab * hash_table[TABLE_SIZE];
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

void addNode(symtab* head, symtab* symptr)
{
	symptr->lchild = NULL;
	symptr->rchild = NULL;
	int symptr_len = strlen(symptr->lexeme);
	int head_len = strlen(head->lexeme);
	int j = 0;
	while( j < min( head_len, symptr_len) && head->lexeme[j] == symptr->lexeme[j])
		j++;
	if(j == min( head_len, symptr_len))
	{
		if(head_len > symptr_len)
		{
			if(head->lchild)
				addNode(head->lchild, symptr);
			else
				head->lchild = symptr;
		}
		else if(head_len < symptr_len)
		{
			if(head->rchild)
				addNode(head->rchild, symptr);
			else
				head->rchild = symptr;
		}
	}
	else if(head->lexeme[j] > symptr->lexeme[j])
	{
		if(head->lchild)
			addNode(head->lchild, symptr);
		else
			head->lchild = symptr;
	}
	else
	{
		if(head->rchild)
			addNode(head->rchild, symptr);
		else
			head->rchild = symptr;
	}
}

void sort()
{
	int i;
	head = NULL;
	for(i=0; i<TABLE_SIZE; i++)
	{
		symtab* symptr;
		symptr = hash_table[i];
		while(symptr)
		{
			if(!head)
			{
				head = symptr;
				head->rchild = NULL;
				head->lchild = NULL;
			}
			else
				addNode(head, symptr);
			symptr = symptr->front;
		}
	}

}

void printFreqOfSymb(symtab* head)
{
	if(head->lchild)
		printFreqOfSymb(head->lchild);
	if(strlen(head->lexeme) > 7)
		printf("%s\t%d\n", head->lexeme, head->counter);
	else
		printf("%s\t\t%d\n", head->lexeme, head->counter);
	if(head->rchild)
		printFreqOfSymb(head->rchild);
}
