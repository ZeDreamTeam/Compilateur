#ifndef nestedDeclarations
#define nestedDeclarations
/*
 * Ce fichier permet la gestion de l'imbrication de différents contexte. Le principe étant d'avoir une base dans la table des symboles permettant de savoir jusqu'à quel contexte on à accès a quel moment
 * Ainsi pour savoir si un symbole et dans le contexte, il faut nous limiter à l'adresse aCurBody contenu dans le dernier DeclarationsDescriptor (retourné par getCurDeclsDescrND()). 
 */


typedef struct DeclDescr{
  struct DeclDescr* prev;
  int depth;
  int aCurBody;
  struct DeclDescr* next;
}DeclarationsDescriptorND;


/*
 * Déclare l'entrée dans un contexte
 */
void oneStepDeeperND();

/*
 * Permet de récupérer l'accès à la base du contexte.
 */ 
DeclarationsDescriptorND* getCurDeclsDescrND();

/*
 * Déclare la sortie d'un contexte
 */
void unDeepND();
#endif
