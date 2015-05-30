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
    table = malloc(sizeof(struct FuncTable));
    current=table;
  } else {
    while(current->next != NULL) {
      current = current->next;
    }
    current->next = malloc(sizeof(struct FuncTable));
    current = current->next;
  }
  current->name = name;
  current->nbArgs = nbArgs;
  current->asmLine = line;
  current->next = NULL;
  printf("%s(%d args) : line %d", name, nbArgs, line);
}

void ftable_print() {
  struct FuncTable* elem = table;
  int i=0;
  printf("\n---------------------------------------------------------\n");
  while(elem!=NULL) {
    printf("Entry %d : %s: %d args\t line %d \n",i, elem->name,elem->nbArgs,elem->asmLine);
    elem = elem->next;
    i++;
  }
  printf("\n---------------------------------------------------------\n");

}

int ftable_exists(char * name, int nbArgs) {
  struct FuncTable* current = table;
  int found=-1;
  while( current != NULL && found == -1) {
    if(strcmp(current->name,name)==0 && current->nbArgs == nbArgs) {
      printf("Found the function %s\n", name);
      found = current->asmLine;
    }
    current = current->next;
  }
  return found;
}

