#include <stdio.h>
#include <stdlib.h>
#include "nestedDeclarations.h"

DeclarationsDescriptor mainDeclarations={NULL,0,0,NULL};

void oneStepDeeper(){
  int depth;
  DeclarationsDescriptor * next = malloc(sizeof(DeclarationsDescriptor));
  DeclarationsDescriptor * currentDeclaration = getcurDeclsDescr();
  depth = currentDeclaration->depth;
  depth++;
  next->depth = depth;
  next->curBodyNmbDecls=0;
  currentDeclaration->next = next;
  next->prev = currentDeclaration;
  next->next = NULL;
}

DeclarationsDescriptor* getcurDeclsDescr(){
  DeclarationsDescriptor* curDeclsDescr = &mainDeclarations;
  while(curDeclsDescr->next != NULL){
    curDeclsDescr = curDeclsDescr->next;
  }
  return curDeclsDescr;
}

void unDeep(){
  DeclarationsDescriptor *curDeclsDescr = getcurDeclsDescr();
  popDeclInSymbTable(curDeclsDescr->curBodyNmbDecls);
  curDeclsDescr = curDeclsDescr->prev;
  free(curDeclsDescr->next);
  curDeclsDescr->next = NULL;
}
void addDecl(){
  getcurDeclsDescr()->curBodyNmbDecls++;
}
void popDeclInSymbTable(int number){
  popSymboles(number);
}
