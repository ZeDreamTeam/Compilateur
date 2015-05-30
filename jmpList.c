#include "jmpList.h"
#include <stdlib.h> 
#include <stdio.h>
IfJmpList* jumpingList=NULL;
IfJmpList* lastCell=NULL;

void addJumpJL(int from, int to) {
  IfJmpList* cell = jumpingList;
  IfJmpList* pred = NULL;
  if(jumpingList==NULL) {
    jumpingList = malloc(sizeof(IfJmpList));
    cell = jumpingList;
  } else {
    while(cell->next != NULL) {
      cell = cell->next;
    }
    cell->next = malloc(sizeof(IfJmpList));
    pred=cell;
    cell = cell->next;
  }
  cell->statementLine = from;
  cell->jumpingLine = to;
  cell->next = NULL;
  cell->pred = pred;
  lastCell = cell;
}

void addStatementJL(int statementLine) {
  IfJmpList* cell = jumpingList;
  IfJmpList* pred = NULL;  
  if(jumpingList==NULL) {
    jumpingList=malloc(sizeof(IfJmpList));
    cell = jumpingList;
  } else {
    while(cell->next != NULL) {
      cell = cell->next;
    }
    cell->next = malloc(sizeof(IfJmpList));
    pred = cell;
    cell = cell->next;
  }
  cell->statementLine = statementLine;
  cell->jumpingLine = -1;
  cell->next=NULL;
  cell->pred =pred;
  lastCell = cell;
}

void addJumpingJL(int jumpingLine) {
  IfJmpList* cell = jumpingList;
  IfJmpList* pred = NULL;
  if(jumpingList==NULL) {
    jumpingList=malloc(sizeof(IfJmpList));
    cell = jumpingList;
  } else {
    while(cell->next != NULL) {
      cell = cell->next;
    }
    cell->next = malloc(sizeof(IfJmpList));
    pred = cell;
    cell = cell->next;
  }
  cell->statementLine=-1;
  cell->jumpingLine = jumpingLine;
  cell->next = NULL;
  cell->pred = pred;
  lastCell = cell;
}

void updateStatementLine(int statementLine) {
  IfJmpList* cell = jumpingList;
  if(jumpingList->next == NULL) {
    jumpingList->statementLine == statementLine;
  } else {
    while(cell->next != NULL && cell->statementLine != -1) {
      cell = cell->next;
    }
    cell->statementLine = statementLine;
  }
}

void updateStatementLineFromBottom(int statementLine) {
  IfJmpList* cell = lastCell;
  if(cell->pred == NULL) {
    cell->statementLine == statementLine;
  } else {
    while(cell->pred != NULL && cell->statementLine != -1) {
      cell = cell->pred;
    }

    cell->statementLine = statementLine;
  }
}

void updateJumpingJLFromBottom(int jumpingLine) {
  IfJmpList* cell =lastCell;
  if(cell->pred == NULL) {
    cell->jumpingLine == jumpingLine;
  } else {
    while(cell->pred != NULL && cell->jumpingLine != -1) {
      cell = cell->pred;
    }
    cell->jumpingLine = jumpingLine;
  }
}

void updateJumpingJL(int jumpingLine) {
  IfJmpList* cell = jumpingList;
  if(jumpingList->next== NULL) {
    jumpingList->jumpingLine == jumpingLine;
  } else {
    while(cell->next != NULL && cell->jumpingLine != -1) {
      cell = cell->next;
    }
//    while(cell->next != NULL && cell->next->jumpingLine == -1) {
//      cell = cell->next;
//    }
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


IfJmpList* getJmpList() {

  return jumpingList;
}

/*
 * Should we jump on line line ?
 * Returns the line to jump to if so, -1 otherwise.
 */
int isThereAJump(int line) {
  IfJmpList* head = jumpingList;
  IfJmpList* cur = head;
  int res;
  while(cur != NULL && cur->statementLine!= line) {
    cur = cur->next;
  }

  if(cur != NULL)
    res = cur->jumpingLine;
  else
    res = -1;
  return res;

}

