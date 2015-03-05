#ifndef nestedDeclarations
#define nestedDeclarations

typedef struct DeclDescr{
  struct DeclDescr* prev;
  int depth;
  int curBodyNmbDecls;
  struct DeclDescr* next;
}DeclarationsDescriptor;

void oneStepDeeper();
DeclarationsDescriptor* getcurDeclsDescr();
void unDeep();
void addDecl();
void popDeclInSymbTable(int number);
#endif
