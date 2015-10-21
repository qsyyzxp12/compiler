struct symtab{
	char lexeme[256];
	struct symtab *front;
	struct symtab *back;
	int line;
	int counter;
	struct symtab* rchild;
	struct symtab* lchild;
};
struct symtab* head;
typedef struct symtab symtab;
symtab * lookup(char *name);
void insert(char *name);
void addNode(symtab* head, symtab* symptr);
void sort();
void printFreqOfSymb(symtab* head);
