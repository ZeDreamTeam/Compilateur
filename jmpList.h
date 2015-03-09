#ifndef jmpList
#define jmpList
typedef struct IfJmpList {
  int statementLine;
  int jumpingLine;
  struct IfJmpList* next;
} IfJmpList;


void addStatementJL(int statementLine);

void updateJumpingJL(int jumpingLine);

void clearLast();

void displayJL();
//IfJmpList* jumpingList=NULL;

#endif
