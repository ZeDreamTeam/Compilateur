#ifndef FUNC_TABLE
#define FUNC_TABLE
/*
 * Gestion de la table des fonctions
 */


/*
 * Ajoute un element a la table des fonctions
 */
void ftable_add(char* name, int nbArgs, int line);

/*
 * Verifie si une fonction de ce nom existe ou pas
 */
int ftable_exists(char * name, int nbArgs);

/*
 * Affiche la table des symboles.
 */
void ftable_print();

#endif
