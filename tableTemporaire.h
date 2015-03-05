#ifndef toolsPLZ
#define toolsPLZ

#define DECLMAX 256

int tempTable[DECLMAX];
enum eType {
  CONST_INT,
  INT
};
int addSymbole(char* name, int isConst, int isInit);
void yyerror(char const *err); 
void addToTable(int id);
void assignTypeInSymboleTable(enum eType);
void flushTable();

#endif
