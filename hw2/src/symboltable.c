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

void printFreqOfSymb()
{
	symtab* head = NULL;
	symtab* curr = NULL;
	symtab* prev = NULL;
	printf("Frequency of identifiers:\n");
	int i;
	for(i=0; i<TABLE_SIZE; i++)
	{
		symtab* symptr;
		symptr = hash_table[i];
		while(symptr)
		{
			if(!head)
			{
				head = symptr;
				head->next = NULL;
			}
			else
			{
				prev = head;
				curr = head;
				int symptr_len = strlen(symptr->lexeme);
				while(curr)
				{
					int curr_len = strlen(curr->lexeme);
					int j = 0;
					while( j < min( curr_len, symptr_len) && curr->lexeme[j] == symptr->lexeme[j])
						j++;
					if(j == min( curr_len, symptr_len))
					{
						if(curr_len > symptr_len)
						{
							prev->next = symptr;
							symptr->next = curr;
						}
						else if(curr_len < symptr_len)
						{
							prev = curr;
							curr = curr->next;
							continue;
						}
						else
						{
							printf("WRONG\n");
							printf("curr = %s\nsymptr = %s\n", curr->lexeme, symptr->lexeme);
							printf("curr_len = %d, symptr_len = %d\n", curr_len, symptr_len);
						}
						break;
					}
					if(curr->lexeme[j] > symptr->lexeme[j])
					{
						if(!strcmp(curr->lexeme, head->lexeme))
						{
							head = symptr;
							symptr->next = curr;
						}
						else
						{
							prev->next = symptr;
							symptr->next = curr;
						}
						break;
					}
					prev = curr;
					curr = curr->next;
				}
				if(!curr)
				{
					prev->next = symptr;
					symptr->next = NULL;
				}
			}
			symptr = symptr->front;
		}
	}
	curr = head;
	while(curr)
	{
		if(strlen(curr->lexeme) > 6)
			printf("%s\t%d\n", curr->lexeme, curr->counter);
		else
			printf("%s\t\t%d\n", curr->lexeme, curr->counter);
		curr = curr->next;
	}
}
