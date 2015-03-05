#include <stdio.h>
#include <stdlib.h>
#include "nestedDeclarations.h"

DeclarationsDescriptor mainDeclarations={NULL,0,0,NULL};

void oneStepDeeper(){
  int depth;
  DeclarationsDescriptor * next = malloc(sizeof(DeclarationsDescriptor));
  DeclarationsDescriptor * currentDeclaration = getCurrentDeclarationsDescriptor();
  depth = currentDeclaration->depth;
  depth++;
  next->depth = depth;
  next->currentBodyNumberOfDeclarations=0;
  currentDeclaration->next = next;
  next->prev = currentDeclaration;
}

DeclarationsDescriptor* getCurrentDeclarationsDescriptor(){
  DeclarationsDescriptor* currentDeclarationsDescriptor = &mainDeclarations;
  while(currentDeclarationsDescriptor->next != NULL){
    currentDeclarationsDescriptor = currentDeclarationsDescriptor->next;
  }
  return currentDeclarationsDescriptor;
}

void unDeep(){
  DeclarationsDescriptor currentDeclarationsDescriptor = *getCurrentDeclarationsDescriptor();
  popDeclarationsInSymboleTable(currentDeclarationsDescriptor.currentBodyNumberOfDeclarations);
  currentDeclarationsDescriptor = *currentDeclarationsDescriptor.prev;
  free(currentDeclarationsDescriptor.next);
  currentDeclarationsDescriptor.next = NULL;
}
void addDecl(){
  getCurrentDeclarationsDescriptor()->currentBodyNumberOfDeclarations++;
}
void popDeclarationsInSymboleTable(int number){
  //popSymboles(number);
}
