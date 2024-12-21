#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "status.h"

typedef int AvlElementType;

// AVL ���ڵ㶨��
typedef struct AvlNode
{
    AvlElementType data;
    int balanceFactor;
    struct AvlNode *leftChild, *rightChild;
} AvlNode, *AvlTree;

typedef enum AvlElementCompareResult
{
    // ��ʾ���Ԫ��С���Ҳ�Ԫ��
    AVLELEMENT_LESS = -1,
    // ��ʾ����Ԫ�����
    AVLELEMENT_EQUAL = 0,
    // ��ʾ���Ԫ�ش����Ҳ�Ԫ��
    AVLELEMENT_GREATER = 1
} AvlElementCompareResult;

/* ======================== AVL ����غ��� ======================== */

/* ��ʼ�� AVL �� */
Status Avl_Init(AvlTree *root);

/* Ĭ�ϳ�ʼ�� AVL ���ڵ� */
Status AvlNode_InitDefault(AvlTree *node);

/* ��ʼ�� AVL ���ڵ� */
Status AvlNode_Init(AvlTree *node, AvlElementType element);

/* ���� AVL �� */
Status Avl_Destroy(AvlTree *root);

/* �������� */
Status Avl_RotateRight(AvlTree *root);

/* �������� */
Status Avl_RotateLeft(AvlTree *root);

/* ����ڵ� */
Status Avl_Insert(AvlTree *root, AvlElementType element);

/* ɾ���ڵ� */
Status Avl_Delete(AvlTree *root, AvlElementType element);

/* ���ҽڵ� */
Status Avl_Search(AvlTree *root, AvlElementType element);

/* ����ƽ������ */
Status Avl_UpdateBalanceFactor(AvlTree root);

/* ���ʽڵ�ֵ */
Status Avl_VisitNode(AvlTree node);

/* ������� */
Status Avl_InOrderTraverse(AvlTree root);

/* ͼ�λ���ӡ AVL �� */
Status Avl_PrintTree(AvlTree root);

/* �ָ�AVL�� */
Status Avl_Split(AvlTree *root, AvlElementType element, AvlTree *smaller_tree, AvlTree *bigger_tree);

/* ����AVL�� */
Status Avl_Copy(AvlTree *origin_tree, AvlTree *purpose_tree);

/* �ϲ�AVL�� */
Status Avl_Merge(AvlTree *origin_tree1, AvlTree *origin_tree2, AvlTree *purpose_tree);

/* ======================== AvlElementType ��غ��� ======================== */

/* Ԫ�ظ�ֵ */
Status AvlElement_Assign(AvlElementType *destination, const AvlElementType *source);

/* �Ƚ�����Ԫ���Ƿ���� */
AvlElementCompareResult AvlElement_IsEqual(AvlElementType a, AvlElementType b);

/* ��ʼ��Ԫ�� */
Status AvlElement_Init(AvlElementType *element, AvlElementType value);

/* ��ӡԪ�� */
Status AvlElement_Print(AvlElementType element);

/* �ͷ�Ԫ���ڴ� */
Status AvlElement_Destroy(AvlElementType *element);

/* �ж�Ԫ���Ƿ�Ϊ�� */
Status AvlElement_IsNull(AvlElementType *element);

#endif // AVL_TREE_H
