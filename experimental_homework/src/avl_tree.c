#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* ======================== AVL 树相关函数 ======================== */

/* 初始化 AVL 树 */
Status Avl_Init(AvlTree *root)
{
    if (!root)
        return STATUS_FALSE;
    *root = NULL;
    return STATUS_TRUE;
}

/* 默认初始化 AVL 树节点 */
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

/* 初始化 AVL 树节点 */
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

/* 销毁 AVL 树 */
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

/* 右旋操作 */
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

/* 左旋操作 */
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

// 计算树的高度
int Avl_GetHeight(AvlTree tree)
{
    if (tree == NULL)
    {
        return 0; // 空树高度为0
    }
    int leftHeight = Avl_GetHeight(tree->leftChild);
    int rightHeight = Avl_GetHeight(tree->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// 更新平衡因子（递归更新整棵树）
Status Avl_UpdateBalanceFactor(AvlTree root)
{
    if (root == NULL)
    {
        return STATUS_TRUE;
    }
    // 更新左右子树的平衡因子
    Avl_UpdateBalanceFactor(root->leftChild);
    Avl_UpdateBalanceFactor(root->rightChild);

    // 计算当前节点的平衡因子
    int leftHeight = Avl_GetHeight(root->leftChild);
    int rightHeight = Avl_GetHeight(root->rightChild);
    root->balanceFactor = leftHeight - rightHeight;
    return STATUS_TRUE;
}

/* 插入节点 */
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
        return STATUS_FALSE; // 不允许插入重复值
    }

    Avl_UpdateBalanceFactor(*root);
    ;
    // 旋转保持平衡
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

/* 删除节点 */
Status Avl_Delete(AvlTree *root, AvlElementType element)
{
    if (!root || !(*root))
        return STATUS_FALSE;

    // 递归找到目标节点并删除
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
        // 找到要删除的节点
        AvlTree temp = *root;

        // 节点有 0 个或 1 个子节点
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
            // 节点有两个子节点，找到右子树的最小值（后继）
            AvlTree successor = (*root)->rightChild;
            while (successor->leftChild)
            {
                successor = successor->leftChild;
            }
            // 用后继节点的值替换当前节点的值
            (*root)->data = successor->data;
            // 删除后继节点
            Avl_Delete(&((*root)->rightChild), successor->data);
            temp = NULL; // 避免误释放
        }

        if (temp)
            free(temp); // 释放删除的节点
    }

    // 如果树为空，则返回
    if (!(*root))
        return STATUS_TRUE;

    // 更新当前节点的平衡因子
    Avl_UpdateBalanceFactor(*root);

    // 平衡调整
    if ((*root)->balanceFactor > 1)
    { // 左子树过高
        if ((*root)->leftChild->balanceFactor >= 0)
        {
            Avl_RotateRight(root); // LL 型
        }
        else
        {
            Avl_RotateLeft(&((*root)->leftChild)); // LR 型
            Avl_RotateRight(root);
        }
    }
    else if ((*root)->balanceFactor < -1)
    { // 右子树过高
        if ((*root)->rightChild->balanceFactor <= 0)
        {
            Avl_RotateLeft(root); // RR 型
        }
        else
        {
            Avl_RotateRight(&((*root)->rightChild)); // RL 型
            Avl_RotateLeft(root);
        }
    }

    return STATUS_TRUE;
}

/* 查找节点 */
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

/* 访问节点值 */
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

/* 中序遍历 */
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
 * 打印 AVL 树的递归辅助函数
 * @param root 当前节点指针
 * @param depth 当前节点的深度（用于计算缩进）
 */
void printAvlRecursive(AvlTree root, int depth)
{
    if (!root)
        return;

    // 打印右子树
    printAvlRecursive(root->rightChild, depth + 1);

    // 打印当前节点
    for (int i = 0; i < depth; i++)
    {
        printf("       |"); // 每层缩进
    }
    Avl_VisitNode(root);
    printf("\n");

    // 打印左子树
    printAvlRecursive(root->leftChild, depth + 1);
}

/**
 * 打印 AVL 树
 * @param root 树的根节点
 * @return Status 成功返回 STATUS_TRUE
 */
Status Avl_PrintTree(AvlTree root)
{
    if (!root)
        return STATUS_TRUE;     // 空树直接返回
    printAvlRecursive(root, 0); // 从根节点开始递归打印
    return STATUS_TRUE;
}

/* 分割AVL树 */
Status Avl_Split(AvlTree *root, AvlElementType element, AvlTree *smaller_tree, AvlTree *bigger_tree)
{
    if (!root || !*root)
    {
        // 原目标是空树
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

/* 复制AVL树 */
Status Avl_Copy(AvlTree *origin_tree, AvlTree *purpose_tree)
{
    if (!origin_tree || !*origin_tree)
        return STATUS_TRUE;
    Avl_Copy(&(*origin_tree)->leftChild, purpose_tree);
    Avl_Insert(purpose_tree, (*origin_tree)->data);
    Avl_Copy(&(*origin_tree)->rightChild, purpose_tree);
    return STATUS_TRUE;
}

/* 合并AVL树辅助函数 */
Status Avl_MergeHelper(AvlTree *origin_tree, AvlTree *purpose_tree)
{
    if (!origin_tree || !*origin_tree)
        return STATUS_TRUE;
    Avl_MergeHelper(&(*origin_tree)->leftChild, purpose_tree);
    Avl_Insert(purpose_tree, (*origin_tree)->data);
    Avl_MergeHelper(&(*origin_tree)->rightChild, purpose_tree);
    return STATUS_TRUE;
}

/* 合并AVL树 */
Status Avl_Merge(AvlTree *origin_tree1, AvlTree *origin_tree2, AvlTree *purpose_tree)
{
    Avl_Copy(origin_tree1, purpose_tree);
    return Avl_MergeHelper(origin_tree2, purpose_tree);
}

/* ======================== AvlElementType 相关函数 ======================== */

/* 元素赋值 */
Status AvlElement_Assign(AvlElementType *destination, const AvlElementType *source)
{
    if (!destination || !source)
    {
        return STATUS_FALSE;
    }
    *destination = *source;
    return STATUS_TRUE;
}

/* 比较两个元素是否相等 */
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

/* 初始化元素 */
Status AvlElement_Init(AvlElementType *element, AvlElementType value)
{
    if (!element)
    {
        return STATUS_FALSE;
    }
    *element = value;
    return STATUS_TRUE;
}

/* 打印元素 */
Status AvlElement_Print(AvlElementType element)
{
    printf("%d", element);
    return STATUS_TRUE;
}

/* 释放元素内存（如果适用） */
Status AvlElement_Destroy(AvlElementType *element)
{
    return STATUS_TRUE;
}

/* 判断元素是否为空指针 */
Status AvlElement_IsNull(AvlElementType *element)
{
    return STATUS_TRUE;
}
