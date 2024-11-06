#ifndef AVL_BINARY_TREE_H
#define AVL_BINATY_TREE_H

#include "status_enum.h"

typedef int avl_ElemType;

typedef struct avlBiTNode {
    avl_ElemType data;
    int balance_factor;
    struct avlBiTNode *lchild, *rchild;
} avlBiTNode, *avlBiTree;

// 使两个avl_ElemType相等
Status makeEqualavl_ElemType(avl_ElemType *purpose, avl_ElemType *origin);

// 是否两个avl_ElemType相等
int IsEqualBiTElemType(avl_ElemType a, avl_ElemType b);

// 默认初始化一个avl节点
Status initAVL_default(avlBiTree *p);

// 初始化一个avl节点
Status initAVL(avlBiTree *p, avl_ElemType avl_ElemType);

// 销毁一个avl树
Status destoryAVL(avlBiTree *p);

// 对当前指针指向节点进行右旋操作
Status rRotate(avlBiTree *p);

// 对当前指针指向节点进行做左旋操作
Status lRotate(avlBiTree *p);

// 对以p节点为根的avl树插入值为e的avl树节点
Status insertAVL(avlBiTree *p, avl_ElemType e);

// 对以p节点为根的avl树删除值为e的avl树节点
Status deleteAVL(avlBiTree *p, avl_ElemType e);

// 输出p节点的值
Status visitAVL(avlBiTree p);

// 中序遍历以p为节点的avl树
Status InOrderTraverseAVL(avlBiTree p, Status *visit(avlBiTree t));

// 以图形方式打印整个avl树
Status printAVL(avlBiTree p);


#endif // AVL_BINATY_TREE_H