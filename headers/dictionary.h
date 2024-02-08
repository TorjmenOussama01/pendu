#include "struct.h"

tree *append(char letter);
tree *markEndOfWord();
tree *dicoInsererMot(char word[50], tree *root, int wordIndex);
tree* deleteWord(tree* root, char word[], int wordIndex);
void printArray(char letters[], int len);
void dicoAfficher(tree *node, char word[], int wordLen);
void removeWordFromTreeAndFile(tree **root);
int dicoNbOcc(char *word, int wordIndex, tree *root);
int dicoNbMotsDifferents(tree *root);
int dicoNbMotsTotal(tree *root);
char* choisirMot(char *filename, int level);