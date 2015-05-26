#include <stdio.h>
#include <stdlib.h>
#include "funcTable.h"

struct FuncTable {
  char* name;
  int nbArgs;
  int asmLine;
  struct FuncTable* next;
};

struct FuncTable* table=NULL;
void ftable_add(char* name, int nbArgs, int line) {
  struct FuncTable* current = table;
  if(current==NULL) {
    current = malloc(sizeof(struct FuncTable));
    current->name = name;
    current->nbArgs = nbArgs;
    current->asmLine= line;
    current->next = NULL;
  }
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = malloc(sizeof(struct FuncTable));
  current->next->name = name;
  current->next->nbArgs = nbArgs;
  current->next->asmLine = line;
  current->next->next = NULL;
  printf("%s(%d args) : line %d", name, nbArgs, line);
}

int ftable_exists(char * name, int nbArgs) {
  struct FuncTable* current = table;
  int found=-1;
  while(current != NULL && found == -1) {
    if(current->name == name && current->nbArgs == nbArgs) {
      found == current->asmLine;
    }
  }
  return found;
}

