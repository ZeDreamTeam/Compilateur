#include <stdio.h>
#include <stdlib.h>
#include "nestedDeclarations.h"

DeclarationsDescriptorND mainDeclarations={NULL,0,0,NULL};

void oneStepDeeperND(){
  int depth;
  DeclarationsDescriptorND * next = malloc(sizeof(DeclarationsDescriptorND));
  DeclarationsDescriptorND * currentDeclaration = getcurDeclsDescrND();
  depth = currentDeclaration->depth;
  depth++;
  next->depth = depth;
  next->aCurBody=getCurrentAddrST();
  currentDeclaration->next = next;
  next->prev = currentDeclaration;
  next->next = NULL;
}

DeclarationsDescriptorND* getcurDeclsDescrND(){
  DeclarationsDescriptorND* curDeclsDescr = &mainDeclarations;
  while(curDeclsDescr->next != NULL){
    curDeclsDescr = curDeclsDescr->next;
  }
  return curDeclsDescr;
}

void unDeepND(){
  DeclarationsDescriptorND *curDeclsDescr = getcurDeclsDescrND();
  popTilST(curDeclsDescr->aCurBody);
  curDeclsDescr = curDeclsDescr->prev;
  free(curDeclsDescr->next);
  curDeclsDescr->next = NULL;
}
