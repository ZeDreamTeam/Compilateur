#include "jmpList.h"
#include <stdlib.h> 
#include <stdio.h>
IfJmpList* jumpingList=NULL;


void addStatementJL(int statementLine) {
  IfJmpList* cell = jumpingList;
  
  if(jumpingList==NULL) {
    jumpingList=malloc(sizeof(IfJmpList));
    cell = jumpingList;
  } else {
    while(cell->next != NULL) {
      cell = cell->next;
    }
    cell->next = malloc(sizeof(IfJmpList));
    cell = cell->next;
  }
  cell->statementLine = statementLine;
  cell->jumpingLine = -1;
  cell->next=NULL;

}

void updateJumpingJL(int jumpingLine) {
  IfJmpList* cell = jumpingList;
  if(jumpingList->next== NULL) {
    jumpingList->jumpingLine == jumpingLine;
  } else {
    while(cell->next != NULL && cell->jumpingLine != -1) {
      cell = cell->next;
    }
    cell->jumpingLine = jumpingLine;
  }
}
void clearLast() {
  IfJmpList* cell = jumpingList;
  if(cell!=NULL && cell->next != NULL) {
    while(cell->next->next != NULL) {
      cell = cell->next;
    }
  }
  cell->next=NULL;

}
void displayJL() {
  printf("\n----------------------------------\n");
  IfJmpList* cell = jumpingList;
  int i=0;
  while(cell!=NULL) {
    printf("%d: statement: %d ; jumping %d\n",i, cell->statementLine, cell->jumpingLine);
    cell = cell->next;
    i++;
  }
  
}

