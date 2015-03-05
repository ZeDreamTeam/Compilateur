#ifndef nestedDeclarations
#define nestedDeclarations

typedef struct DeclDescr{
  struct DeclDescr* prev;
  int depth;
  int currentBodyNumberOfDeclarations;
  struct DeclDescr* next;
}DeclarationsDescriptor;

void oneStepDeeper();
DeclarationsDescriptor* getCurrentDeclarationsDescriptor();
void unDeep();
void addDecl();
void popDeclarationsInSymboleTable(int number);
#endif
