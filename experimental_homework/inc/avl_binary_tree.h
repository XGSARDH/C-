#ifndef AVL_BINARY_TREE_H
#define AVL_BINATY_TREE_H

typedef int avlBiTElemType;

typedef enum Status {
    FALSE = 0,
    TRUE = 1
} Status;

typedef struct avlBiTNode {
    avlBiTElemType data;
    int bf;
    struct avlBiTNode *lchild, *rchild;
    
}

#ifndef // AVL_BINATY_TREE_H