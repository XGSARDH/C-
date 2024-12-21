#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* ======================== AVL ����غ��� ======================== */

/* ��ʼ�� AVL �� */
Status Avl_Init(AvlTree *root)
{
    if (!root)
        return STATUS_FALSE;
    *root = NULL;
    return STATUS_TRUE;
}

/* Ĭ�ϳ�ʼ�� AVL ���ڵ� */
Status AvlNode_InitDefault(AvlTree *node)
{
    if (!node)
        return STATUS_FALSE;
    *node = (AvlNode *)malloc(sizeof(AvlNode));
    if (!(*node))
        return STATUS_OVERFLOW;
    AvlElement_Init(&(*node)->data, 0);
    (*node)->balanceFactor = 0;
    (*node)->leftChild = NULL;
    (*node)->rightChild = NULL;
    return STATUS_TRUE;
}

/* ��ʼ�� AVL ���ڵ� */
Status AvlNode_Init(AvlTree *node, AvlElementType element)
{
    if (!node)
        return STATUS_FALSE;
    *node = (AvlNode *)malloc(sizeof(AvlNode));
    if (!(*node))
        return STATUS_OVERFLOW;
    AvlElement_Init(&(*node)->data, element);
    (*node)->balanceFactor = 0;
    (*node)->leftChild = NULL;
    (*node)->rightChild = NULL;
    return STATUS_TRUE;
}

/* ���� AVL �� */
Status Avl_Destroy(AvlTree *root)
{
    if (!root || !(*root))
        return STATUS_FALSE;
    Avl_Destroy(&((*root)->leftChild));
    Avl_Destroy(&((*root)->rightChild));
    free(*root);
    *root = NULL;
    return STATUS_TRUE;
}

/* �������� */
Status Avl_RotateRight(AvlTree *root)
{
    if (!root || !(*root))
        return STATUS_FALSE;
    AvlTree leftChild = (*root)->leftChild;
    if (!leftChild)
        return STATUS_FALSE;
    (*root)->leftChild = leftChild->rightChild;
    leftChild->rightChild = *root;
    *root = leftChild;
    return STATUS_TRUE;
}

/* �������� */
Status Avl_RotateLeft(AvlTree *root)
{
    if (!root || !(*root))
        return STATUS_FALSE;
    AvlTree rightChild = (*root)->rightChild;
    if (!rightChild)
        return STATUS_FALSE;
    (*root)->rightChild = rightChild->leftChild;
    rightChild->leftChild = *root;
    *root = rightChild;
    return STATUS_TRUE;
}

// �������ĸ߶�
int Avl_GetHeight(AvlTree tree)
{
    if (tree == NULL)
    {
        return 0; // �����߶�Ϊ0
    }
    int leftHeight = Avl_GetHeight(tree->leftChild);
    int rightHeight = Avl_GetHeight(tree->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ����ƽ�����ӣ��ݹ������������
Status Avl_UpdateBalanceFactor(AvlTree root)
{
    if (root == NULL)
    {
        return STATUS_TRUE;
    }
    // ��������������ƽ������
    Avl_UpdateBalanceFactor(root->leftChild);
    Avl_UpdateBalanceFactor(root->rightChild);

    // ���㵱ǰ�ڵ��ƽ������
    int leftHeight = Avl_GetHeight(root->leftChild);
    int rightHeight = Avl_GetHeight(root->rightChild);
    root->balanceFactor = leftHeight - rightHeight;
    return STATUS_TRUE;
}

/* ����ڵ� */
Status Avl_Insert(AvlTree *root, AvlElementType element)
{
    if (!root)
    {
        return STATUS_FALSE;
    }
    if (!(*root))
    {
        return AvlNode_Init(root, element);
    }
    if (AvlElement_IsEqual(element, (*root)->data) == AVLELEMENT_LESS)
    {
        if (!Avl_Insert(&((*root)->leftChild), element))
            return STATUS_FALSE;
    }
    else if (AvlElement_IsEqual(element, (*root)->data) == AVLELEMENT_GREATER)
    {
        if (!Avl_Insert(&((*root)->rightChild), element))
            return STATUS_FALSE;
    }
    else
    {
        return STATUS_FALSE; // ����������ظ�ֵ
    }

    Avl_UpdateBalanceFactor(*root);
    ;
    // ��ת����ƽ��
    if ((*root)->balanceFactor > 1)
    {
        if (AvlElement_IsEqual(element, (*root)->leftChild->data) == AVLELEMENT_GREATER)
        {
            Avl_RotateLeft(&((*root)->leftChild));
            Avl_RotateRight(root);
        }
        else
        {
            Avl_RotateRight(root);
        }
    }
    else if ((*root)->balanceFactor < -1)
    {
        if (AvlElement_IsEqual(element, (*root)->rightChild->data) == AVLELEMENT_LESS)
        {
            Avl_RotateRight(&((*root)->rightChild));
            Avl_RotateLeft(root);
        }
        else
        {
            Avl_RotateLeft(root);
        }
    }

    return STATUS_TRUE;
}

/* ɾ���ڵ� */
Status Avl_Delete(AvlTree *root, AvlElementType element)
{
    if (!root || !(*root))
        return STATUS_FALSE;

    // �ݹ��ҵ�Ŀ��ڵ㲢ɾ��
    if (AvlElement_IsEqual(element, (*root)->data) == AVLELEMENT_LESS)
    {
        if (!Avl_Delete(&((*root)->leftChild), element))
            return STATUS_FALSE;
    }
    else if (AvlElement_IsEqual(element, (*root)->data) == AVLELEMENT_GREATER)
    {
        if (!Avl_Delete(&((*root)->rightChild), element))
            return STATUS_FALSE;
    }
    else
    {
        // �ҵ�Ҫɾ���Ľڵ�
        AvlTree temp = *root;

        // �ڵ��� 0 ���� 1 ���ӽڵ�
        if (!(*root)->leftChild)
        {
            *root = (*root)->rightChild;
        }
        else if (!(*root)->rightChild)
        {
            *root = (*root)->leftChild;
        }
        else
        {
            // �ڵ��������ӽڵ㣬�ҵ�����������Сֵ����̣�
            AvlTree successor = (*root)->rightChild;
            while (successor->leftChild)
            {
                successor = successor->leftChild;
            }
            // �ú�̽ڵ��ֵ�滻��ǰ�ڵ��ֵ
            (*root)->data = successor->data;
            // ɾ����̽ڵ�
            Avl_Delete(&((*root)->rightChild), successor->data);
            temp = NULL; // �������ͷ�
        }

        if (temp)
            free(temp); // �ͷ�ɾ���Ľڵ�
    }

    // �����Ϊ�գ��򷵻�
    if (!(*root))
        return STATUS_TRUE;

    // ���µ�ǰ�ڵ��ƽ������
    Avl_UpdateBalanceFactor(*root);

    // ƽ�����
    if ((*root)->balanceFactor > 1)
    { // ����������
        if ((*root)->leftChild->balanceFactor >= 0)
        {
            Avl_RotateRight(root); // LL ��
        }
        else
        {
            Avl_RotateLeft(&((*root)->leftChild)); // LR ��
            Avl_RotateRight(root);
        }
    }
    else if ((*root)->balanceFactor < -1)
    { // ����������
        if ((*root)->rightChild->balanceFactor <= 0)
        {
            Avl_RotateLeft(root); // RR ��
        }
        else
        {
            Avl_RotateRight(&((*root)->rightChild)); // RL ��
            Avl_RotateLeft(root);
        }
    }

    return STATUS_TRUE;
}

/* ���ҽڵ� */
Status Avl_Search(AvlTree *root, AvlElementType element)
{
    if (!root || !(*root))
        return STATUS_FALSE;
    AvlTree avl_tree = *root;
    if (AvlElement_IsEqual(avl_tree->data, element) == AVLELEMENT_EQUAL)
    {
        return STATUS_TRUE;
    }
    if (Avl_Search(&avl_tree->leftChild, element) == STATUS_TRUE)
    {
        return STATUS_TRUE;
    }
    if (Avl_Search(&avl_tree->rightChild, element) == STATUS_TRUE)
    {
        return STATUS_TRUE;
    }
    return STATUS_OVERFLOW;
}

/* ���ʽڵ�ֵ */
Status Avl_VisitNode(AvlTree node)
{
    if (!node)
    {
        return STATUS_FALSE;
    }
    AvlElement_Print(node->data);
    printf("(BF: %d)", node->balanceFactor);
    return STATUS_TRUE;
}

/* ������� */
Status Avl_InOrderTraverse(AvlTree root)
{
    if (!root)
        return STATUS_TRUE;
    Avl_InOrderTraverse(root->leftChild);
    AvlElement_Print(root->data);
    printf(" ");
    Avl_InOrderTraverse(root->rightChild);
    return STATUS_TRUE;
}

/**
 * ��ӡ AVL ���ĵݹ鸨������
 * @param root ��ǰ�ڵ�ָ��
 * @param depth ��ǰ�ڵ����ȣ����ڼ���������
 */
void printAvlRecursive(AvlTree root, int depth)
{
    if (!root)
        return;

    // ��ӡ������
    printAvlRecursive(root->rightChild, depth + 1);

    // ��ӡ��ǰ�ڵ�
    for (int i = 0; i < depth; i++)
    {
        printf("       "); // ÿ������
    }
    Avl_VisitNode(root);
    printf("\n");

    // ��ӡ������
    printAvlRecursive(root->leftChild, depth + 1);
}

/**
 * ��ӡ AVL ��
 * @param root ���ĸ��ڵ�
 * @return Status �ɹ����� STATUS_TRUE
 */
Status Avl_PrintTree(AvlTree root)
{
    if (!root)
        return STATUS_TRUE;     // ����ֱ�ӷ���
    printAvlRecursive(root, 0); // �Ӹ��ڵ㿪ʼ�ݹ��ӡ
    return STATUS_TRUE;
}

/* �ָ�AVL�� */
Status Avl_Split(AvlTree *root, AvlElementType element, AvlTree *smaller_tree, AvlTree *bigger_tree)
{
    if (!root || !*root)
    {
        // ԭĿ���ǿ���
        return STATUS_OVERFLOW;
    }
    if (AvlElement_IsEqual((*root)->data, element) == AVLELEMENT_LESS)
    {
        Avl_Insert(smaller_tree, (*root)->data);
    }
    if (AvlElement_IsEqual((*root)->data, element) == AVLELEMENT_GREATER)
    {
        Avl_Insert(bigger_tree, (*root)->data);
    }
    Status output_status = STATUS_TRUE;
    output_status = Avl_Split(&(*root)->leftChild, element, smaller_tree, bigger_tree);
    output_status = Avl_Split(&(*root)->rightChild, element, smaller_tree, bigger_tree);
    return output_status;
}

/* ����AVL�� */
Status Avl_Copy(AvlTree *origin_tree, AvlTree *purpose_tree)
{
    if (!origin_tree || !*origin_tree)
        return STATUS_TRUE;
    Avl_Copy(&(*origin_tree)->leftChild, purpose_tree);
    Avl_Insert(purpose_tree, (*origin_tree)->data);
    Avl_Copy(&(*origin_tree)->rightChild, purpose_tree);
    return STATUS_TRUE;
}

/* �ϲ�AVL���������� */
Status Avl_MergeHelper(AvlTree *origin_tree, AvlTree *purpose_tree)
{
    if (!origin_tree || !*origin_tree)
        return STATUS_TRUE;
    Avl_MergeHelper(&(*origin_tree)->leftChild, purpose_tree);
    Avl_Insert(purpose_tree, (*origin_tree)->data);
    Avl_MergeHelper(&(*origin_tree)->rightChild, purpose_tree);
    return STATUS_TRUE;
}

/* �ϲ�AVL�� */
Status Avl_Merge(AvlTree *origin_tree1, AvlTree *origin_tree2, AvlTree *purpose_tree)
{
    Avl_Copy(origin_tree1, purpose_tree);
    return Avl_MergeHelper(origin_tree2, purpose_tree);
}

/* ======================== AvlElementType ��غ��� ======================== */

/* Ԫ�ظ�ֵ */
Status AvlElement_Assign(AvlElementType *destination, const AvlElementType *source)
{
    if (!destination || !source)
    {
        return STATUS_FALSE;
    }
    *destination = *source;
    return STATUS_TRUE;
}

/* �Ƚ�����Ԫ���Ƿ���� */
AvlElementCompareResult AvlElement_IsEqual(AvlElementType a, AvlElementType b)
{
    if (a > b)
    {
        return AVLELEMENT_GREATER;
    }
    else if (a == b)
    {
        return AVLELEMENT_EQUAL;
    }
    else
    {
        return AVLELEMENT_LESS;
    }
}

/* ��ʼ��Ԫ�� */
Status AvlElement_Init(AvlElementType *element, AvlElementType value)
{
    if (!element)
    {
        return STATUS_FALSE;
    }
    *element = value;
    return STATUS_TRUE;
}

/* ��ӡԪ�� */
Status AvlElement_Print(AvlElementType element)
{
    printf("%d", element);
    return STATUS_TRUE;
}

/* �ͷ�Ԫ���ڴ棨������ã� */
Status AvlElement_Destroy(AvlElementType *element)
{
    return STATUS_TRUE;
}

/* �ж�Ԫ���Ƿ�Ϊ��ָ�� */
Status AvlElement_IsNull(AvlElementType *element)
{
    return STATUS_TRUE;
}
