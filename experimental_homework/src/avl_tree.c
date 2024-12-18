#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* ======================== AVL 树相关函数 ======================== */

/* 初始化 AVL 树 */
Status Avl_Init(AvlTree *root) {
    if (!root) {
        return STATUS_FALSE;
    }
    *root = NULL;
    return STATUS_TRUE;
}

/* 默认初始化 AVL 树节点 */
Status AvlNode_InitDefault(AvlTree *node) { return STATUS_TRUE; }

/* 初始化 AVL 树节点 */
Status AvlNode_Init(AvlTree *node, AvlElementType element) {
    if(!node) {
        return STATUS_FALSE;
    }
    if(!*node) {
        *node = (AvlTree) malloc(sizeof(AvlNode));
    }
    AvlTree curr = *node;
    AvlElement_Assign(&curr->data, &element);
    curr->leftChild = NULL;
    curr->rightChild = NULL;
    curr->depth = 0;
    return STATUS_TRUE;
}

/* 销毁 AVL 树 */
Status Avl_Destroy(AvlTree *root) {

}

/* 右旋操作 */
Status Avl_RotateRight(AvlTree *root) { return 0; }

/* 左旋操作 */
Status Avl_RotateLeft(AvlTree *root) { return 0; }

/* 插入节点 */
Status Avl_Insert(AvlTree *root, AvlElementType element) { return 0; }

/* 删除节点 */
Status Avl_Delete(AvlTree *root, AvlElementType element) { return 0; }

/* 更新平衡因子 */
Status Avl_UpdateBalanceFactor(AvlTree root) { return 0; }

/* 访问节点值 */
Status Avl_VisitNode(AvlTree node) { return 0; }

/* 中序遍历 */
Status Avl_InOrderTraverse(AvlTree root) { return 0; }

/* 图形化打印 AVL 树 */
Status Avl_PrintTree(AvlTree root) { return 0; }

/* ======================== AvlElementType 相关函数 ======================== */

/* 元素赋值 */
Status AvlElement_Assign(AvlElementType *destination, const AvlElementType *source) {
    if(!destination || !source) {
        return STATUS_FALSE;
    }
    *destination = *source;
    return STATUS_TRUE;
}

/* 比较两个元素是否相等 */
AvlElementCompareResult AvlElement_IsEqual(AvlElementType a, AvlElementType b) {
    if(a > b) {
        return AVLELEMENT_GREATER;
    }
    else if(a == b) {
        return AVLELEMENT_EQUAL;
    }
    else {
        return AVLELEMENT_LESS;
    }
}

/* 初始化元素 */
Status AvlElement_Init(AvlElementType *element, AvlElementType value) {
    if(!element) {
        return STATUS_FALSE;
    }
    *element = value;
    return STATUS_TRUE;
}

/* 打印元素 */
Status AvlElement_Print(AvlElementType element) {
    printf("%d", element);
    return STATUS_TRUE;
}

/* 释放元素内存（如果适用） */
Status AvlElement_Destroy(AvlElementType *element) { return STATUS_TRUE; }

/* 判断元素是否为空指针 */
Status AvlElement_IsNull(AvlElementType *element) { return STATUS_TRUE; }

/* ======================== AvlStack 相关函数 ======================== */

/* 初始化AVL栈 */
Status AvlStack_Init(AvlStack* stack) {
    return Stack_Init(stack);
}

/* 销毁AVL栈 */
Status AvlStack_Destroy(AvlStack* stack) {
    return Stack_Destroy(stack);
}

/* 入栈 */
Status AvlStack_Push(AvlStack* stack, AvlStackElementType element) {
    return Stack_Push(stack, (StackElementType)element);
}

/* 出栈 */
Status AvlStack_Pop(AvlStack* stack, AvlStackElementType* element) {
    return Stack_Pop(stack, (StackElementType*)element);
}

/* 获取栈顶元素 */
Status AvlStack_Top(AvlStack* stack, AvlStackElementType* element) {
    return Stack_Top(stack, (StackElementType*)element);
}

/* 判断栈是否为空 */
Status AvlStack_IsEmpty(AvlStack* stack) {
    return Stack_IsEmpty(stack);
}

/* 获取栈大小 */
int AvlStack_Size(AvlStack* stack) {
    return Stack_Size(stack);
}

/* 打印栈 */
Status AvlStack_Print(AvlStack* stack, void (*printFunc)(AvlStackElementType)) {
    return Stack_Print(stack, (void (*)(StackElementType))printFunc);
}
