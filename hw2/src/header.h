struct symtab{
	char lexeme[256];
	struct symtab *front;
	struct symtab *back;
	int line;
	int counter;
};

typedef struct Comment{//insertComment
  char* s;
  struct Comment *next;
}Comment;

typedef struct symtab symtab;
symtab * lookup(char *name);
void insert(char *name);
