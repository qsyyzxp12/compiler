#include <cstdio>
#include <cstdlib>

#define writeV8(s, b...)\
{\
 fprintf(outputFile, s, ##b);\
}
struct ARMV8AssemblyWriter{
  FILE* outputFile;
  int ifCount;
  int whileCount;
  int constCount;//TODO: need to merge
  //label number should be maintained on a stack.

  //TODO: move out(to semanticAnalysis )

  ARMV8AssemblyWriter(){
    ifCount = 0;
    whileCount = 0;
    constCount = 0;
  }
  
  void writeString(char* strName, char* strValue){
    //data part
    writeV8(".data\n");
    writeV8("%s: .ascii \"%s\\000\"\n", strName, strValue);
    //TODO: constant_0 -> constant_n
    int alignNum = 4-(strlen(strValue)%4);
    if(alignNum == 4)
      alignNum = 0;
    writeV8(".align %d\n", );//align is 4 times
    
    //test part
    writeV8(".text\n");
    writeV8("ldr x0, =%s\n", strName);//"_CONSTANT_0" or what?
    //mov x0, x9 //TODO: wtf is this?
    writeV8("bl _write_str\n");
  }

  void writeInt(char* reg){
    writeV8("ldr w9, [x29, #-4]\n");
    writeV8("mov %s, w9\n", reg);//#w0 is used to pass the value you would like to write.
    writeV8("bl _write_int\n");
  }

  void writeFloat(char* reg){
    writeV8("ldr s16, [x29, #-8]\n");
    writeV8("fmov %s, s16\n", reg);//#s0 is used to pass the value you would like to write out
    writeV8("bl _write_float\n");
  }

  void readInt(char* reg){
    writeV8("bl _read_int\n");
    writeV8("mov w9, %s\n", reg);
    writeV8("str w9, [x29, #-4]\n");
  }

  void readFloat(char* reg){
    writeV8("bl _read_float");
    writeV8("fmov s16, %s\n", reg);
    writeV8("str s16, [x29, #-8]\n");
  }

  void doWhile(){//while(xxx) yyy
    whileCount++;
    char testName[15];
    sprintf(testName, "WhileTest%d", whileCount);
    char exitName[15];
    sprintf(exitName, "WhileExit%d", whileCount);

    writeV8("%s:", testName);
    //TODO: generate xxx
    
    //I wish to get result register 
    writeV8("cmp %s, 0\n", resultReg);
    writeV8("beq %s\n", exitName);
    //TODO: generate yyy
    
    writeV8("b %s\n", testName);
    writeV8("%s:", exitName);
  }

  void doIf(){//if(xxx) yyy
    ifCount++;
    char exitName[10];
    sprintf(exitName, "IfExit%d", ifCount);
    //if xxx eq false or 0 , jump to exit
    //TODO: code of xxx(with final compare jump to exit)

    //I wish to get result register 
    writeV8("cmp %s, 0\n", resultReg);
    writeV8("beq %s\n", exitName); 
    //TODO: code of block(yyy)
    
    writeV8("%s:\n", exitName);
  }

  //Don't know whether to write else if or not
  void doIfElse(){//if(xxx) yyy else zzz
    ifCount++;
    char elseName[10];
    sprintf(elseName, "IfElse%d", ifCount);
    char exitName[10];
    sprintf(exitName, "IfExit%d", ifCount);

    //TODO: code of xxx(with final compare jump to else)

    //I wish to get result register 
    writeV8("cmp %s, 0\n", resultReg);
    writeV8("beq %s\n", elseName);
    //TODO: code of if block(yyy)(with final jump to exit)

    writeV8("b %s\n", exitName);
    //TODO: code of else block(zzz)
    writeV8("%s:\n", elseName);

    writeV8("%s:\n", exitName);
  }


};

