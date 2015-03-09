#ifndef toolsPLZ
#define toolsPLZ

#define DECLMAX 256

int tempTable[DECLMAX];
enum eType {
  CONST_INT,
  INT
};
int addSymboleTT(char* name, int isConst, int isInit);
void yyerror(char const *err); 
void addToTableTT(int id);
void assignTypeInSymboleTableTT(enum eType);
void flushTableTT();

#endif
