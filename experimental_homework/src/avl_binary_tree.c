#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

Status makeEqualavl_ElemType(avl_ElemType *purpose, avl_ElemType *origin) {
    if (purpose && origin) {
        *purpose = *origin;
        return TRUE;
    }
    return FALSE;
}

int IsEqualBiTElemType(avl_ElemType a, avl_ElemType b) {
    if (a < b) {
        return -1;
    }
    else if (b < a) {
        return 1;
    }
    return 0;
}

Status initAVL_default(avlBiTree *p) {
    initAVL(p, 0);
}

Status initAVL(avlBiTree *p, avl_ElemType avl_ElemType) {
    if (*p) {
        return TRUE;
    }
    *p = (avlBiTree)malloc(sizeof(avlBiTNode));
    makeEqualavl_ElemType(&((*p)->data), &avl_ElemType);
    (*p)->lchild = NULL;
    (*p)->rchild = NULL;
    (*p)->balance_factor = 0;
    return *p ? TRUE : FALSE;
}

Status destoryAVL(avlBiTree *p) {
    if (!p) {
        return TRUE;
    }
    if (*p) {
        destoryAVL(&((*p)->lchild));
        destoryAVL(&((*p)->rchild));
        free(*p);
        *p = NULL;
    }
    return TRUE;
}

Status rRotate(avlBiTree *p) {

}

Status lRotate(avlBiTree *p) {

}

Status insertAVL(avlBiTree *p, avl_ElemType e) {

}

Status deleteAVL(avlBiTree *p, avl_ElemType e);

Status visitAVL(avlBiTree p) {
    if(p) {
        printf("%d", p->data);
        return TRUE;
    }
    return FALSE;
}

Status InOrderTraverseAVL(avlBiTree p, Status *visit(avlBiTree t)) {
    return TRUE;
}

Status printAVL(avlBiTree p) {
    if (!p) {
        printf("avlBiTree == NULL");
        return FALSE;
    }
    printf("avlBiTree != NULL\n");

    printf("avlBiTree->data == %d; ", p->data);
    printf("avlBiTree->balance_factor == %d", p->balance_factor);
    return TRUE;
}