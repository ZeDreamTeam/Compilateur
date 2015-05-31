#ifndef toolsPLZ
#define toolsPLZ

#define DECLMAX 256

/*
 * Ce fichier sert à utiliser une table temporaire de variable.
 * Elle est utile lorsque nous déclarons une liste de variable tel que int a,b,c=0,d;
 * de façon à pouvoir retrouver le type de chacune de ses variable.
 */


enum eType {
  CONST_INT,
  INT
};

/*
 * Ajoute un symbole (nom) à notre table temporaire.
 * Cela va aussi affecter notre variable dans notre table temporaire
 */
int addSymboleTT(char* name, int isConst, int isInit);

void yyerror(char const *err); 

/*
 * Privée. Ajoute tout simplement une variable a ntore tempTable.
 */
void addToTableTT(int id);

/*
 * Une fois toute les variable ajoutées, il nous faut toute leurs affecté leurs type.
 */
void assignTypeInSymboleTableTT(enum eType);

/*
 * On flush notre table temporaire.
 */
void flushTableTT();

#endif
