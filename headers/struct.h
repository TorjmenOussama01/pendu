#ifndef TREE_H
#define TREE_H

typedef struct treeType
{
    int occurrences;
    char letter;
    struct treeType *left;
    struct treeType *right;
} tree;

#endif
