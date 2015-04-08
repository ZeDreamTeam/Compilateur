#ifndef omg
#define omg
/*
 * Fichier utilisé pour la gestion de la table des symboles.
 */


typedef struct {
    int address;
    char* name;
    int isConst;
    int isInit;
} Symbale;

/*
 * Affichage de la table des symboles
 */
void printTableSymboleST();

/*
 * Defini si un symbole à l'addresse index est constant ou pas.
 */
void setIfSymboleIsConstST(int index, int isConst);
/*
 * Ajoute un symbole dans la table
 */
int symbolePushST(char* name, int isConst, int isInit);
/*
 * Enleve le dernier symboel ajoutée à notre table.
 */
void symbolePopST();

/*
 * Défini qu'un symbole est initialisé.
 */
void setIsInitST(int index);

/*
 * Défini qu'un symbole est initialisé depuis le nom de ce symbole.
 */
void symbolInitST(char* name);

/*
 * Enleve les derniers symbole dans la table jusqu'à atteindre l'addresse adress.
 */ 
void popTilST(int adress);

/*
 * Recupere l'index d'une variable depuis son nom
 */
int getIndexWithVarNameST(char* name);

/*
 * Ajout d'une variable temporaire (nom nommée)
 */
int tempAddST();

/*
 * Libere l'adresse de la derniere variable temporaire
 */
int tempPopST();

/* retourne une erreur yacc.*/
void yyerror(char const *err);

/*
 * Remet à 0 l'adresse relative
 */
void resetRelative();

#endif
