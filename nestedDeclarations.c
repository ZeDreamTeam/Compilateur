#include <stdio.h>
#include <stdlib.h>
#include "nestedDeclarations.h"

DeclarationsDescriptorND mainDeclarations={NULL,0,-1,NULL};

void oneStepDeeperND(){
  int depth;
  DeclarationsDescriptorND * next = malloc(sizeof(DeclarationsDescriptorND));
  DeclarationsDescriptorND * currentDeclaration = getCurDeclsDescrND();
  depth = currentDeclaration->depth;
  depth++;
  next->depth = depth;
  next->aCurBody=getCurrentAddrST();
  currentDeclaration->next = next;
  next->prev = currentDeclaration;
  next->next = NULL;
  printTableSymboleST();
  printf("\ncurrent Body adress : %d\n",getCurDeclsDescrND()->aCurBody);
}

DeclarationsDescriptorND* getCurDeclsDescrND(){
  DeclarationsDescriptorND* curDeclsDescr = &mainDeclarations;
  while(curDeclsDescr->next != NULL){
    curDeclsDescr = curDeclsDescr->next;
  }
  return curDeclsDescr;
}

void unDeepND(){
  DeclarationsDescriptorND *curDeclsDescr = getCurDeclsDescrND();
  popTilST(curDeclsDescr->aCurBody);
  curDeclsDescr = curDeclsDescr->prev;
  free(curDeclsDescr->next);
  curDeclsDescr->next = NULL;
  printTableSymboleST();
  printf("\ncurrent adress : %d\n",getCurDeclsDescrND()->aCurBody);
}
