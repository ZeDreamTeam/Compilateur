#include <stdio.h>
#include <stdlib.h>
#include "tableTemporaire.h"
#include "symbaleToble.h"
#include "nestedDeclarations.h"

int cursor = 0;

int tempTable[DECLMAX];


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
  printf("WE ARE AT %d", cursor);
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
    printf("%d ok\n", i);
    currentIndex = tempTable[i];
    setIfSymboleIsConstST(currentIndex,type); 
  }
  flushTableTT();
}
