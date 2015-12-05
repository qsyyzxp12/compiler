TARGET = parser
OBJECT = parser.tab.cc parser.tab.o lex.yy.c alloc.o functions.o semanticAnalysis.o symbolTable.o
OUTPUT = parser.output parser.tab.h
CC = g++ -g 
LEX = flex
YACC = bison -v
YACCFLAG = -d
LIBS = -lfl 

parser: parser.tab.o alloc.o functions.o symbolTable.o semanticAnalysis.o 
	$(CC) -o $(TARGET) parser.tab.o alloc.o functions.o symbolTable.o semanticAnalysis.o $(LIBS)

parser.tab.o: parser.tab.cc lex.yy.c alloc.o functions.c symbolTable.o semanticAnalysis.o
	$(CC) -c parser.tab.cc

semanticAnalysis.o: semanticAnalysis.cpp symbolTable.o
	$(CC) -c semanticAnalysis.cpp

symbolTable.o: symbolTable.cpp
	$(CC) -c symbolTable.cpp

lex.yy.c: lexer3.ll
	$(LEX) lexer3.ll

parser.tab.cc: parser.yy 
	$(YACC) $(YACCFLAG) parser.yy

alloc.o: alloc.c
	$(CC) -c alloc.c

functions.o: functions.c
	$(CC) -c functions.c

clean:
	rm -f $(TARGET) $(OBJECT) $(OUTPUT)


