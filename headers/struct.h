#ifndef TREE_H
#define TREE_H

typedef struct treeType
{
    char letter;
    struct treeType *left;
    struct treeType *right;
} tree;

#endif
