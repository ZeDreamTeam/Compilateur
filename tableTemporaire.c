#include <stdio.h>
#include <stdlib.h>
#include "tableTemporaire.h"
#include "symbaleToble.h"
#include "nestedDeclarations.h"

int cursor = 0;

int addSymboleTT(char* name, int isConst, int isInit){
  int index = symbolePushST(name, isConst, isInit);
  addToTableTT(index);
  return index;
}

void addToTableTT(int id){
  if(cursor < DECLMAX){
    tempTable[cursor] = id;
    cursor++;
  }else{
    yyerror("Too many declarations");
  }
}

void flushTableTT(){
  cursor = 0 ;
}
void assignTypeInSymboleTableTT(enum eType enumType) {
  int currentIndex, i, type;
  switch(enumType){
    case CONST_INT:
      type = 1;
      break;
    case INT:
      type = 0;
      break; 
  }
  for(i=0;i<cursor;i++){
    currentIndex = tempTable[i]-1;
    setIfSymboleIsConstST(currentIndex,type); 
  }
  flushTableTT();
}
