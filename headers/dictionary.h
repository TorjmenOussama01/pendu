#include "struct.h"

tree *append(char letter);
tree *markEndOfWord();
tree *dicoInsererMot(char word[50], tree *root, int wordIndex);
void printArray(char letters[], int len);
void dicoAfficher(tree *node, char word[], int wordLen);
int dicoNbOcc(char *word, int wordIndex, tree *root);
int dicoNbMotsDifferents(tree *root);
int dicoNbMotsTotal(tree *root);
int choisirMot(char *motChoisi,int niveau, char *filename);