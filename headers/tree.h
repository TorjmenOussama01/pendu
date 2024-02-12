#include "struct.h"

tree *arbreConsVide();
tree *arbreCons(char letter, tree *leftSubTree, tree *rightSubTree);
tree *arbreFilsDroit(tree *root);
tree *arbreFilsGauche(tree *root);
int arbreEstVide(tree *root);
char arbreRacineLetter(tree *root);
void arbreSuppr(tree *root);