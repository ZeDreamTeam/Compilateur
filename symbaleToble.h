#ifndef omg
#define omg

typedef struct {
    int address;
    char* name;
    int isConst;
    int isInit;
} Symbale;
void printTableSymboleST();
void yyerror(char const *err);
void setIfSymboleIsConstST(int index, int isConst);
int symbolePushST(char* name, int isConst, int isInit);
void symbolePopST();
void setIsInitST(int index);
void symbolInitST(char* name);
void popTilST(int adress);
int getIndexWithVarNameST(char* name);
int tempAddST();
int tempPopST();
#endif
