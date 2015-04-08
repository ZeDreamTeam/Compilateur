#include <stdio.h>
#include <stdlib.h>
#include "funcTable.h"

struct FuncTable {
  char* name;
  struct FuncTable* next;

};

struct FuncTable* table=NULL;
void ftable_add(char* name) {
  struct FuncTable* current = table;
  if(current==NULL) {
    current = malloc(sizeof(struct FuncTable));
    current->name = name;
    current->next = NULL;
  }
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = malloc(sizeof(struct FuncTable));
  current->next->name = name;
  current->next->next = NULL;

}

int ftable_exists(char * name) {
  struct FuncTable* current = table;
  int found=0;
  while(current != NULL && found != 1) {
    if(current->name == name) {
      found == 1;   
    }
  }
  return found;
}

