#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbaleToble.h"

#define MAX_VAR 256


Symbale symboles[MAX_VAR];
int nbVar=-1;
int nbTmp = MAX_VAR;

int symbolePush(char* name, int isConst, int isInit) {
  if(getIndexWithVarName(name)!=-1){
    char err[50] = "Var ";
    strcat(err,name);
    strcat(err," already declared");
    yyerror(err);
  }
  Symbale s = {nbVar++, name, isConst, isInit};
  symboles[nbVar] = s;
  return nbVar;
}
void symbolePop() {
  nbVar--;
}
void setIfSymboleIsConst(int index, int isConst){
  if(index <= nbVar){
    symboles[index].isConst = isConst;
  }
  else{
    yyerror("Symbol table contains too few arguments");
  }
}

void printTableSymbole(){
  int k;
  Symbale currentSymbole;
  printf("\n---------------------------------------------------------\n");
  for(k=0;k<=nbVar;k++){
     currentSymbole = symboles[k];
     printf("Entry %4d : %10s, isConst : %d, isInit : %d \n",currentSymbole.address,currentSymbole.name,currentSymbole.isConst,currentSymbole.isInit);
  }
  printf("\n---------------------------------------------------------\n");
}
void setIsInit(int index){
  if(index <= nbVar){
    symboles[index].isInit = 1;
  }else {
    yyerror("Symbol table contains too few arguments");
  }
}
void symbolInit(char* name){
  int index;
  if((index = getIndexWithVarName(name))!=-1){
    setIsInit(index);
  }
  else{
    yyerror("var not declared");
  }
}
int getIndexWithVarName(char* name){
  int i, ret=-1;  
  for(i=0; i<=nbVar; i++){
    if(strcmp(name, symboles[i].name) == 0){
      ret = i;
      break;
    }
  }
  return ret;
}


int tempAdd() {
 nbTmp--;
 return nbTmp; 
}

int tempPop() {
  nbTmp++;
  return nbTmp;
}
