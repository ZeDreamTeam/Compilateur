#ifndef jmpList
#define jmpList
typedef struct IfJmpList {
  int statementLine;
  int jumpingLine;
  struct IfJmpList* next;
  struct IfJmpList* pred;
} IfJmpList;

void addJumpJL(int from, int to);

/*
if
*/
void addStatementJL(int statementLine);

void updateJumpingJL(int jumpingLine);

/*
  while
*/
void addJumpingJL(int jumpingLine);
void updateStatementLine(int statementLine);

void clearLast();

void displayJL();
//IfJmpList* jumpingList=NULL;


IfJmpList* getJmpList();
int isThereAJump(int line);
#endif
