#ifndef AVL_BINARY_TREE_H
#define AVL_BINATY_TREE_H

#include "status_enum.h"

typedef int Avl_ElemType;

typedef struct AvlBiTNode {
    Avl_ElemType data;
    int balance_factor;
    struct AvlBiTNode *lchild, *rchild;
} AvlBiTNode, *AvlBiTree;

// 创建一棵Avl空树
Status initAvl(AvlBiTree *root);

// 默认初始化一个Avl节点
Status initAvlBiTNode_default(AvlBiTree *p);

// 初始化一个Avl节点
Status initAvlBiTNode(AvlBiTree *p, Avl_ElemType avl_ElemType);

// 销毁一个Avl树
Status destoryAvl(AvlBiTree *p);

// 对当前指针指向节点进行右旋操作
Status rRotate(AvlBiTree *p);

// 对当前指针指向节点进行做左旋操作
Status lRotate(AvlBiTree *p);

// 对以p节点为根的Avl树插入值为e的Avl树节点
Status insertAvl(AvlBiTree *p, Avl_ElemType e);

// 对以p节点为根的Avl树删除值为e的Avl树节点
Status deleteAvl(AvlBiTree *p, Avl_ElemType e);

// 输出p节点的值
Status visitAvl(AvlBiTree p);

// 中序遍历以p为节点的Avl树
// Status InOrderTraverseAvl(AvlBiTree p, Status *visit(AvlBiTree t));
Status inOrderTraverseAvl(AvlBiTree p);

// 以图形方式打印整个Avl树
Status printAvl(AvlBiTree p);

// 使两个Avl_ElemType相等
Status makeEqualAvl_ElemType(Avl_ElemType *purpose, Avl_ElemType *origin);

// 是否两个Avl_ElemType相等
int isEqualBiTElemType(Avl_ElemType a, Avl_ElemType b);

#endif // AVL_BINATY_TREE_H