#ifndef omg
#define omg

typedef struct {
    int address;
    char* name;
    int isConst;
    int isInit;
} Symbale;

void symbolePush(char* name, int isConst, int isInit);

void symbolePop();


#endif
