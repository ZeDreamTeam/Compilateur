#ifndef omg
#define omg

typedef struct {
    int address;
    char* name;
    int isConst;
    int isInit;
} Symbale;
void printTableSymbole();
void yyerror(char const *err);
void setIfSymboleIsConst(int index, int isConst);
int symbolePush(char* name, int isConst, int isInit);
void symbolePop();
void setIsInit(int index);
void symbolInit(char* name);
int getIndexWithVarName(char* name);
int tempAdd();
int tempPop();
#endif
