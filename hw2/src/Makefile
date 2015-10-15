TARGET = scanner
OBJECT = lex.yy.o symboltable.o 
CC = cc -g
LEX = flex
LIBS = -lfl 

scanner: lex.yy.o symboltable.o
	$(CC) -o scanner lex.yy.o symboltable.o

test1: scanner
	./scanner ../test/test.c

test2: scanner
	./scanner ../test/test-spec.c

test3: scanner
	./scanner ../test/test3-unrecognizedtoken.c

test4: scanner
	./scanner ../test/teststr.c

symboltable.o: symboltable.c 
	$(CC) -c symboltable.c 

lex.yy.o: lex.yy.c 
	$(CC) -c lex.yy.c 

lex.yy.c: lexer.l
	$(LEX) $(LIB) lexer.l

clean:
	rm -f $(TARGET) $(OBJECT) 

