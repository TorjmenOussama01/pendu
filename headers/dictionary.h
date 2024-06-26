#include "struct.h"

tree *append(char letter);
tree *markEndOfWord();
tree *dicoInsererMot(char word[50], tree *root, int wordIndex);
tree* deleteWord(tree* root, char word[], int wordIndex);
void printArray(char letters[], int len);
void dicoAfficher(tree *node, char word[], int wordLen);
void removeWordFromTreeAndFile(tree **root);
int searchWord(char *word, int wordIndex, tree *root);
char* choisirMot(char *filename, int level);
tree *createTreeByLevel(tree *dico,int level);
char* chooseRandomWord(tree *node);