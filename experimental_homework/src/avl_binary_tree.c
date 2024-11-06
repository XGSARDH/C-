#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

Status makeEqualavlBiTElemType(avlBiTElemType *purpose, avlBiTElemType *origin) {
    if (purpose && origin) {
        *purpose = *origin;
        return TRUE;
    }
    return FALSE;
}

int IsEqualBiTElemType(avlBiTElemType a, avlBiTElemType b) {
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

Status initAVL(avlBiTree *p, avlBiTElemType avlBiTElemType) {
    if (*p) {
        return TRUE;
    }
    *p = (avlBiTree)malloc(sizeof(avlBiTNode));
    makeEqualavlBiTElemType(&((*p)->data), &avlBiTElemType);
    (*p)->lchild = NULL;
    (*p)->rchild = NULL;
    (*p)->balance_factor = 0;
    return *p ? TRUE : FALSE;
}

Status destoryAVL(avlBiTree *p) {
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

Status insertAVL(avlBiTree *p, avlBiTElemType e) {

}

Status deleteAVL(avlBiTree *p, avlBiTElemType e);

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
    printf("avlBiTree->data == %d; ", p->data);
    printf("avlBiTree->balance_factor == %d", p->balance_factor);
    return TRUE;
}