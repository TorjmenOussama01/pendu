#include <stdio.h>
#include <stdlib.h>
#include "../../headers/struct.h"

// * Retourner un pointeur null
tree *arbreConsVide()
{
    return NULL;
}

//  * Construire un arbre
tree *arbreCons(char letter, tree *leftSubTree, tree *rightSubTree)
{
    tree *root;
    root = (tree *)malloc(sizeof(tree));

    root->letter = letter;
    root->left = leftSubTree;
    root->right = rightSubTree;

    return root;
}

// * Vider l'arbre donné
void arbreSuppr(tree *root)
{
    if (root == NULL)
        return;

    arbreSuppr(root->left);
    arbreSuppr(root->right);
    free(root);
}

