#ifndef nestedDeclarations
#define nestedDeclarations

typedef struct DeclDescr{
  struct DeclDescr* prev;
  int depth;
  int aCurBody;
  struct DeclDescr* next;
}DeclarationsDescriptorND;

void oneStepDeeperND();
DeclarationsDescriptorND* getcurDeclsDescrND();
void unDeepND();
#endif
