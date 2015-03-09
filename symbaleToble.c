#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbaleToble.h"
#include "nestedDeclarations.h"

#define MAX_VAR 256


Symbale symboles[MAX_VAR];
int adress=-1;
int nbTmp = MAX_VAR;

int symbolePushST(char* name, int isConst, int isInit) {
  if(getIndexWithVarNameST(name)!=-1){
    char err[50] = "Var ";
    strcat(err,name);
    strcat(err," already declared");
    yyerror(err);
  }
  //addDecl();
  Symbale s = {adress++, name, isConst, isInit};
  symboles[adress] = s;
  return adress;
}
void symbolePopST() {
  adress--;
}
void setIfSymboleIsConstST(int index, int isConst){
  if(index <= adress){
    symboles[index].isConst = isConst;
  }
  else{
    yyerror("Symbol table contains too few arguments");
  }
}

void printTableSymboleST(){
  int k;
  Symbale currentSymbole;
  printf("\n---------------------------------------------------------\n");
  for(k=0;k<=adress;k++){
     currentSymbole = symboles[k];
     printf("Entry %4d : %10s, isConst : %d, isInit : %d \n",currentSymbole.address,currentSymbole.name,currentSymbole.isConst,currentSymbole.isInit);
  }
  printf("\n---------------------------------------------------------\n");
}
void setIsInitST(int index){
  if(index <= adress){
    symboles[index].isInit = 1;
  }else {
    yyerror("Symbol table contains too few arguments");
  }
}
void symbolInitST(char* name){
  int index;
  if((index = getIndexWithVarNameST(name))!=-1){
    setIsInitST(index);
  }
  else{
    yyerror("var not declared");
  }
}
int getIndexWithVarNameST(char* name){
  int i, ret=-1;  
  for(i=0; i<=adress; i++){
    if(strcmp(name, symboles[i].name) == 0){
      ret = i;
      break;
    }
  }
  return ret;
}


int tempAddST() {
 nbTmp--;
 return nbTmp; 
}

int tempPopST() {
  nbTmp++;
  return nbTmp;
}
void popTilST(int addrToReturn){
  if(addrToReturn<=adress){
    adress = addrToReturn;
  }
  else{
    yyerror("You can't pop that much");
  }
}
int getCurrentAddrST(){
  return adress;
}