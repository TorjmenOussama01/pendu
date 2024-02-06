#include <stdio.h>
#include <stdlib.h>
#include "../../headers/struct.h"

// * Retourner un pointeur null
tree *arbreConsVide()
{
    return NULL;
}

// * Vérifier si l'arbre est vide ou non
int arbreEstVide(tree *root)
{
    if (root == NULL)
        return 1;

    return 0;
}

//  * Construire un arbre
tree *arbreCons(char letter, int occurrences, tree *leftSubTree, tree *rightSubTree)
{
    tree *root;
    root = (tree *)malloc(sizeof(tree));

    root->letter = letter;
    root->occurrences = occurrences;
    root->left = leftSubTree;
    root->right = rightSubTree;

    return root;
}

// * Retouner la lettre d'un noeud donné
char arbreRacineLetter(tree *node)
{
    return node->letter;
}

// * Retouner le nombre d'occurence d'un noeud donné
int arbreRacineNbOcc(tree *node)
{
    return node->occurrences;
}

// * Retourner le sous arbre gauche d'un arbre donné
tree *arbreFilsGauche(tree *root)
{
    return root->left;
}

// * Retourner le sous arbre droite d'un arbre donné
tree *arbreFilsDroit(tree *root)
{
    return root->right;
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