#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbaleToble.h"
#include "nestedDeclarations.h"

#define MAX_VAR 256


Symbale symboles[MAX_VAR];
int address=-1;//Nombre de variable total.
int nbTmp = MAX_VAR;
int base=0;
int addressRelative=-1;//Addresse relative

int symbolePushST(char* name, int isConst, int isInit) {
  if(isAlreadyDeclaredST(name) == 0){
    char err[50] = "Var ";
    strcat(err,name);
    strcat(err," already declared");
    yyerror(err);
  }
  Symbale s = {++addressRelative, name, isConst, isInit};
  symboles[++address] = s;
  return addressRelative;
}
void symbolePopST() {
  address--;
}
void setIfSymboleIsConstST(int index, int isConst){
  if(index <= address){
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
  for(k=0;k<=address;k++){
     currentSymbole = symboles[k];
     printf("Entry %4d : %10s, isConst : %d, isInit : %d \n",currentSymbole.address,currentSymbole.name,currentSymbole.isConst,currentSymbole.isInit);
  }
  printf("\n---------------------------------------------------------\n");
}
void setIsInitST(int index){
  if(index <= address){
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
  for(i=address; i>=address-addressRelative; i--){
    if(strcmp(name, symboles[i].name) == 0){
      ret = symboles[i].address;
      break;
    }
  }
  return ret;
}
int isAlreadyDeclaredST(char* name){
  int ret = -1, i;
  int currBodyAddr = getCurDeclsDescrND()->aCurBody;
  for(i=address; i>currBodyAddr; i--){
    if(strcmp(name, symboles[i].name) == 0){
      ret = 0;
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
  if(addrToReturn<=address){
    address = addrToReturn;
  }
  else{
    yyerror("You can't pop that much");
  }
}
int getCurrentAddrST(){
  return address;
}
void resetRelative() {
  addressRelative = -1;
}
