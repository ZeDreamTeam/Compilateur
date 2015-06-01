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
int symboleAddST(char* name, int isConst, int isInit, int relAddrToBP) {
  if(isAlreadyDeclaredST(name) == 0) {
    char err[50] = "Var ";
    strcat(err,name);
    strcat(err," already declared");
    yyerror(err);
  }

  Symbale s = {relAddrToBP, name, isConst, isInit};
  symboles[++address] = s;
  return relAddrToBP;

}


void symbolePopST() {
  address--;
}
void setIfSymboleIsConstST(int index, int isConst){
  if(index <= address){
    symboles[index].isConst = isConst;
  }
  else{
    char* str = malloc(100*sizeof(char));
    sprintf(str, "SetIfSymbIsConst: symbtable contains too few elements. Asked for %d/%d", index, address);
    yyerror(str);
  }
}

void printTableSymboleST(){
  int k;
  Symbale currentSymbole;
  printf("Total vars: %d; addressRelatives: %d, nbTmp: %d\n", address, addressRelative,nbTmp);
  printf("\n---------------------------------------------------------\n");
  for(k=0;k<=address;k++){
     currentSymbole = symboles[k];
     printf("Entry %d : addr : %4d, %10s, isConst : %d, isInit : %d \n",k, currentSymbole.address,currentSymbole.name,currentSymbole.isConst,currentSymbole.isInit);
  }
  printf("\n---------------------------------------------------------\n");
}
void setIsInitST(int index){
  if(index <= address){
    symboles[index].isInit = 1;
  }else {
    yyerror("SetIsInitST: Symbol table contains too few arguments");
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
  int i, ret, found = 0;
  //int min = addressRelative != -1 ? addressRelative : 0;  
  int min = 0;//getCurDeclsDescrND()->aCurBody;  
  for(i=address; i>=min && found ==0; i--){
    if(strcmp(name, symboles[i].name) == 0){
      ret = symboles[i].address;
      found = 1;
      break;
    }
  }
  if (found==0) {
      char* err = malloc(sizeof(char)*100);
      strcat(err, "Error var not declared: ");
      strcat(err, name);
      yyerror(err);

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
    resetRelative();
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
