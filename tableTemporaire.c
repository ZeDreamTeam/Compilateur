#include <stdio.h>
#include <stdlib.h>
#include "tableTemporaire.h"
#include "symbaleToble.h"

int cursor = 0;

void addSymbole(char* name, int isConst, int isInit){
  int index = symbolePush(name, isConst, isInit);
  addToTable(index);
}

void addToTable(int id){
  if(cursor < DECLMAX){
    tempTable[cursor] = id;
    cursor++;
  }else{
    yyerror("Too many declarations");
  }
}

void flushTable(){
  cursor = 0 ;
}
void assignTypeInSymboleTable(enum eType enumType) {
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
    setIfSymboleIsConst(currentIndex,type); 
  }
  flushTable();
}
