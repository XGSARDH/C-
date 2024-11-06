#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

Status makeEqualAvl_ElemType(Avl_ElemType *purpose, Avl_ElemType *origin) {
    if (purpose && origin) {
        *purpose = *origin;
        return TRUE;
    }
    return FALSE;
}

int isEqualBiTElemType(Avl_ElemType a, Avl_ElemType b) {
    if (a < b) {
        return -1;
    }
    else if (b < a) {
        return 1;
    }
    return 0;
}

Status initAvl_default(AvlBiTree *p) {
    initAvl(p, 0);
}

Status initAvl(AvlBiTree *p, Avl_ElemType avl_ElemType) {
    if (*p) {
        return TRUE;
    }
    *p = (AvlBiTree)malloc(sizeof(AvlBiTNode));
    makeEqualAvl_ElemType(&((*p)->data), &avl_ElemType);
    (*p)->lchild = NULL;
    (*p)->rchild = NULL;
    (*p)->balance_factor = 0;
    return *p ? TRUE : FALSE;
}

Status destoryAvl(AvlBiTree *p) {
    if (!p) {
        return TRUE;
    }
    if (*p) {
        destoryAvl(&((*p)->lchild));
        destoryAvl(&((*p)->rchild));
        free(*p);
        *p = NULL;
    }
    return TRUE;
}

Status rRotate(AvlBiTree *p) {

}

Status lRotate(AvlBiTree *p) {

}

Status insertAvl(AvlBiTree *p, Avl_ElemType e) {
    if (!p || !*p) {
        initAvl(p, e);
        return (!p || !*p)? FALSE: TRUE;
    }
    // 定义move来确定要插入的位置
    AvlBiTree *move = p;
    // 初始化一个栈
    LStack stack;
    initLStack(&stack);
    // 利用栈来记录查找经过的位置
    while ((*move)) {
        int isBigger = isEqualBiTElemType(e, (*move)->data);
        // isBigger == 0, means equal. isBigger == 1, means right. isBigger == -1, means left.
        // but when left, tag == 1; when right, tag == 2.
        LStack_ElemTypePtr curr = NULL;

        if (isBigger == 0) {
            destroyLStack(&stack);
            return TRUE;
        }
        else if(isBigger == 1) {
            initLStack_ElemTypePtr(&curr, RIGHT, move);
            move = &((*move)->rchild);
        }
        else {
            initLStack_ElemTypePtr(&curr, LEFT, move);
            move = &((*move)->lchild);
        }
        pushLStack(&stack, curr);
        destroyLStack_ElemTypePtr(&curr);
    }
    if (!initAvl(move, e)) {
        destroyLStack(&stack);
        return FALSE;
    }
    (*move)->data = e;
    destroyLStack(&stack);
    return TRUE;
}

Status deleteAvl(AvlBiTree *p, Avl_ElemType e);

Status visitAvl(AvlBiTree p) {
    if(p) {
        printf("%d", p->data);
        return TRUE;
    }
    return FALSE;
}

// Status InOrderTraverseAvl(AvlBiTree p, Status *visit(AvlBiTree t)) {
Status inOrderTraverseAvl(AvlBiTree p) {
    if (!p) return TRUE;
    inOrderTraverseAvl(p->lchild);
    visitAvl(p);
    printf(" ");
    inOrderTraverseAvl(p->rchild);
    return TRUE;
}

Status printAvl(AvlBiTree p) {
}