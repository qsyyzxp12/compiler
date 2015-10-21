struct symtab{
	char lexeme[256];
	struct symtab *front;
	struct symtab *back;
	int line;
	int counter;
	struct symtab* next;
};

typedef struct symtab symtab;
symtab * lookup(char *name);
void insert(char *name);
void printFreqOfSymb();
