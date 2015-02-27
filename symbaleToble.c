#include "symbaleToble.h"

#define MAX_VAR 256


Symbale symboles[MAX_VAR];
int nbVar=0;

void symbolePush(char* name, int isConst, int isInit) {
  Symbale s = {nbVar++, name, isConst, isInit};
  symboles[nbVar] = s;
}
void symbolePop() {
  nbVar--;
}
