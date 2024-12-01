#include "avl_binary_tree.h"
#include "link_stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Status initAvl(AvlBiTree *root)
{
    if (!root)
    {
        return FALSE;
    }
    if (!*root)
    {
        destoryAvl(root);
    }
    *root = NULL;
}

Status makeEqualAvl_ElemType(Avl_ElemType *purpose, Avl_ElemType *origin)
{
    if (purpose && origin)
    {
        *purpose = *origin;
        return TRUE;
    }
    return FALSE;
}

int isEqualBiTElemType(Avl_ElemType a, Avl_ElemType b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    else
        return 0;
}

Status initAvlBiTNode_default(AvlBiTree *p)
{
    initAvlBiTNode(p, 0);
}

// initAvl应该是指创建一颗空树, 而不是创建一个包含默认值的只有一个节点的树
Status initAvlBiTNode(AvlBiTree *p, Avl_ElemType avl_ElemType)
{
    if (*p)
    {
        return TRUE;
    }
    *p = (AvlBiTree)malloc(sizeof(AvlBiTNode));
    makeEqualAvl_ElemType(&((*p)->data), &avl_ElemType);
    (*p)->lchild = NULL;
    (*p)->rchild = NULL;
    (*p)->balance_factor = 0;
    return *p ? TRUE : FALSE;
}

Status destoryAvl(AvlBiTree *p)
{
    if (!p)
    {
        return TRUE;
    }
    if (*p)
    {
        destoryAvl(&((*p)->lchild));
        destoryAvl(&((*p)->rchild));
        free(*p);
        *p = NULL;
    }
    return TRUE;
}

Status rRotate(AvlBiTree *p)
{
    if (!p)
    {
        return FALSE;
    }
    if (!*p)
    {
        return TRUE;
    }
    AvlBiTree root = *p;
    AvlBiTree rootLchild = root->lchild;
    if (!rootLchild)
    {
        return FALSE;
    }
    AvlBiTree rootLchildRchild = rootLchild->rchild;
    rootLchild->rchild = root;
    root->lchild = rootLchildRchild;
    *p = rootLchild;
    return TRUE;
}

Status lRotate(AvlBiTree *p)
{
    if (!p)
    {
        return FALSE;
    }
    if (!*p)
    {
        return TRUE;
    }
    AvlBiTree root = *p;
    AvlBiTree rootRchild = root->rchild;
    if (!rootRchild)
    {
        return FALSE;
    }
    AvlBiTree rootRchildLchild = rootRchild->lchild;
    rootRchild->lchild = root;
    root->rchild = rootRchildLchild;
    *p = rootRchild;
    return TRUE;
}

Status rotate(AvlBiTree *p)
{
    if (abs((*p)->balance_factor) < 2)
        return TRUE;
    if ((*p)->balance_factor == 2)
    {
        // if(!(*p)->rchild) {
        //     return rRotate(p);
        // }
        if (abs((*p)->lchild->balance_factor) >= 2)
        {
            return FALSE;
        }
        if ((*p)->lchild->balance_factor >= 0)
        {
            return rRotate(p);
        }
        else
        {
            if (!lRotate(&((*p)->lchild)))
                return FALSE;
            return rRotate(p);
        }
    }
    if ((*p)->balance_factor == -2)
    {
        // if(!(*p)->lchild) {
        //     return lRotate(p);
        // }
        if (abs((*p)->rchild->balance_factor) >= 2)
        {
            return FALSE;
        }
        if ((*p)->rchild->balance_factor <= 0)
        {
            return lRotate(p);
        }
        else
        {
            if (!rRotate(&((*p)->rchild)))
                return FALSE;
            return lRotate(p);
        }
    }
}

Status insertAvl_helper1(AvlBiTree *p, Avl_ElemType e, LStack *stack)
{
    if (!p)
    {
        return FALSE;
    }
    if (!*p)
    {
        return initAvlBiTNode(p, e);
    }
    // 定义move来确定要插入的位置
    AvlBiTree *move = p;
    // 利用栈来记录查找经过的位置
    while ((*move))
    {
        int isBigger = isEqualBiTElemType(e, (*move)->data);
        // isBigger == 0, means equal. isBigger == 1, means right. isBigger == -1, means left.
        // but when left, tag == 1; when right, tag == 2.
        LStack_ElemTypePtr curr = NULL;

        if (isBigger == 0)
        {
            // destroyLStack(stack);
            return TRUE;
        }
        else if (isBigger == 1)
        {
            initLStack_ElemTypePtr(&curr, RIGHT, move);
            move = &((*move)->rchild);
        }
        else
        {
            initLStack_ElemTypePtr(&curr, LEFT, move);
            move = &((*move)->lchild);
        }
        pushLStack(stack, curr);
    }
    if (!initAvlBiTNode(move, e))
    {
        destroyLStack(stack);
        return FALSE;
    }
    // 可忽略下列该行
    // (*move)->data = e;
}

Status balanceAvlByStack(AvlBiTree *p, LStack *stack)
{
    LStack_ElemTypePtr move = NULL;
    while (!isEmptyLStack(stack))
    {
        popLStack(stack, &move);
        if (!updateBalanceFactor(move->avlPtr))
            return FALSE;
        if (abs(move->avlPtr->balance_factor) == 2)
        {
            // if (!rotate(&(move->avlPtr))) return FALSE;
            // return TRUE;
            break;
        }
        destroyLStack_ElemTypePtr(&move);
    }
    if (move && abs(move->avlPtr->balance_factor) == 2)
    {
        destroyLStack_ElemTypePtr(&move);
        if (isEmptyLStack(stack))
        {
            return rotate(p);
        }
        else
        {
            getTopLStack(stack, &move);
            if (move->tag == LEFT)
            {
                return rotate(&move->avlPtr->lchild);
            }
            if (move->tag == RIGHT)
            {
                return rotate(&move->avlPtr->rchild);
            }
        }
    }
    return TRUE;
}

Status insertAvl(AvlBiTree *p, Avl_ElemType e)
{
    // 初始化一个栈
    LStack stack;
    initLStack(&stack);
    if (insertAvl_helper1(p, e, &stack) == FALSE)
        return FALSE;
    // 应该在此处增加平衡因子调整相关代码
    if (balanceAvlByStack(p, &stack) == FALSE)
        return FALSE;
    destroyLStack(&stack);
    return TRUE;
}

Status deleteAvl_helper3(AvlBiTree *p, Avl_ElemType e, LStack *stack)
{
    LStack_ElemTypePtr curr = NULL;
    if (!getTopLStack(stack, &curr))
        return FALSE;
    LStack_ElemTypePtr root = curr;
    if (curr->avlPtr->balance_factor >= 0)
    {
        // left tree is higher, to make left max to be root
        AvlBiTree move = curr->avlPtr->lchild;
        // log the way
        initLStack_ElemTypePtr(&curr, LEFT, &move);
        pushLStack(stack, curr);
        move = move->rchild;
        while (move)
        {
            initLStack_ElemTypePtr(&curr, RIGHT, &move);
            pushLStack(stack, curr);
            move = move->rchild;
        }
        // sure the position
        popLStack(stack, &curr);
        // change the root
        makeEqualAvl_ElemType(&root->avlPtr->data, &curr->avlPtr->data);
        // delete before
        AvlBiTree deleteAvlLchild = curr->avlPtr->lchild;
        // delete
        destroyLStack_ElemTypePtr(&curr);
        // delete after
        getTopLStack(stack, &curr);
        if (curr->avlPtr != root->avlPtr)
            curr->avlPtr->rchild = deleteAvlLchild;
        else
            curr->avlPtr->lchild = deleteAvlLchild;
        return balanceAvlByStack(p, stack);
    }
    else if (curr->avlPtr->balance_factor == -1)
    {
        // right tree is higher, to make right min to be root
        AvlBiTree move = curr->avlPtr->rchild;
        // log the way
        initLStack_ElemTypePtr(&curr, RIGHT, &move);
        pushLStack(stack, curr);
        move = move->lchild;
        while (move)
        {
            initLStack_ElemTypePtr(&curr, LEFT, &move);
            pushLStack(stack, curr);
            move = move->lchild;
        }
        // sure the position
        popLStack(stack, &curr);
        // change the root
        makeEqualAvl_ElemType(&root->avlPtr->data, &curr->avlPtr->data);
        // delete before
        AvlBiTree deleteAvlRchild = curr->avlPtr->rchild;
        // delete
        destroyLStack_ElemTypePtr(&curr);
        // delete after
        getTopLStack(stack, &curr);
        if (curr->avlPtr != root->avlPtr)
            curr->avlPtr->lchild = deleteAvlRchild;
        else
            curr->avlPtr->rchild = deleteAvlRchild;
        return balanceAvlByStack(p, stack);
    }
}

Status deleteAvl_helper2(AvlBiTree *p, Avl_ElemType e, LStack *stack)
{
    if (!p || !*p)
    {
        return FALSE;
    }
    // 校验是否是要删除的元素
    LStack_ElemTypePtr move = NULL;
    if (!getTopLStack(stack, &move))
        return FALSE;
    if (isEqualBiTElemType(move->avlPtr->data, e) != 0)
        return FALSE;
    int flag = 0;
    if (move->avlPtr->lchild)
        flag += 1;
    if (move->avlPtr->rchild)
        flag += 2;

    if (flag == 0)
    {
        if (!popLStack(stack, &move))
            return FALSE;
        if (!destroyLStack_ElemTypePtr(&move))
            return FALSE;
        if (!popLStack(stack, &move))
            return FALSE;
        if (move->tag == LEFT)
        {
            move->avlPtr->lchild = NULL;
        }
        else if (move->tag == RIGHT)
        {
            move->avlPtr->rchild = NULL;
        }
        if (!destroyLStack_ElemTypePtr(&move))
            return FALSE;
    }
    else if (flag == 1)
    {
        if (!popLStack(stack, &move))
            return FALSE;
        AvlBiTree curr = move->avlPtr->lchild;
        if (!destroyLStack_ElemTypePtr(&move))
            return FALSE;
        if (!getTopLStack(stack, &move))
            return FALSE;
        if (move->tag == LEFT)
        {
            move->avlPtr->lchild = curr;
        }
        else if (move->tag == RIGHT)
        {
            move->avlPtr->rchild = curr;
        }
    }
    else if (flag == 2)
    {
        if (!popLStack(stack, &move))
            return FALSE;
        AvlBiTree curr = move->avlPtr->rchild;
        if (!destroyLStack_ElemTypePtr(&move))
            return FALSE;
        if (!getTopLStack(stack, &move))
            return FALSE;
        if (move->tag == LEFT)
        {
            move->avlPtr->lchild = curr;
        }
        else if (move->tag == RIGHT)
        {
            move->avlPtr->rchild = curr;
        }
    }
    else if (flag == 3)
    {
        return deleteAvl_helper3(p, e, stack);
    }
    else
    {
        return FALSE;
    }
    return balanceAvlByStack(p, stack);
}

Status deleteAvl_helper1(AvlBiTree *p, Avl_ElemType e, LStack *stack)
{
    if (!p)
    {
        return FALSE;
    }
    if (!*p)
    {
        // OVERFLOW代表找不到
        return OVERFLOW;
    }
    // 定义move来确定要删除的位置
    AvlBiTree *move = p;
    // 利用栈来记录查找经过的位置
    while ((*move))
    {
        int isBigger = isEqualBiTElemType(e, (*move)->data);
        // isBigger == 0, means equal. isBigger == 1, means right. isBigger == -1, means left.
        // but when left, tag == 1; when right, tag == 2.
        LStack_ElemTypePtr curr = NULL;
        if (isBigger == 0)
        {
            initLStack_ElemTypePtr(&curr, RIGHT, move);
            pushLStack(stack, curr);
            return TRUE;
        }
        else if (isBigger == 1)
        {
            initLStack_ElemTypePtr(&curr, RIGHT, move);
            move = &((*move)->rchild);
        }
        else
        {
            initLStack_ElemTypePtr(&curr, LEFT, move);
            move = &((*move)->lchild);
        }
        pushLStack(stack, curr);
    }
    return OVERFLOW;
}

Status deleteAvl(AvlBiTree *p, Avl_ElemType e)
{
    LStack stack;
    Status status = TRUE;
    initLStack(&stack);
    status = deleteAvl_helper1(p, e, &stack);
    if (status != TRUE)
        return status;
    status = deleteAvl_helper2(p, e, &stack);
    if (status != TRUE)
        return status;
    destroyLStack(&stack);
    return status;
}

Status updateBalanceFactor_helper(AvlBiTree p, int *depth)
{
    if (!p)
    {
        *depth = 0;
        return TRUE;
    }
    int leftDepth = 0, rightDepth = 0;
    updateBalanceFactor_helper(p->lchild, &leftDepth);
    updateBalanceFactor_helper(p->rchild, &rightDepth);
    p->balance_factor = leftDepth - rightDepth;
    *depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

Status updateBalanceFactor(AvlBiTree p)
{
    if (!p)
    {
        return TRUE;
    }
    int depth = 0;
    if (!updateBalanceFactor_helper(p, &depth))
    {
        return FALSE;
    }
    if (depth <= 0)
    {
        return FALSE;
    }
    return TRUE;
}

Status visitAvl(AvlBiTree p)
{
    if (p)
    {
        printf("%d", p->data);
        return TRUE;
    }
    return FALSE;
}

// Status InOrderTraverseAvl(AvlBiTree p, Status *visit(AvlBiTree t)) {
Status inOrderTraverseAvl(AvlBiTree p)
{
    if (!p)
        return TRUE;
    inOrderTraverseAvl(p->lchild);
    visitAvl(p);
    printf(" ");
    inOrderTraverseAvl(p->rchild);
    return TRUE;
}

Status printAvl(AvlBiTree p)
{
    if (!p)
        return TRUE;
    LinkStack stack;
    initLStack(&stack);
    LStack_ElemTypePtr topLStack_ElemTypePtr = NULL;
    LStack_ElemType_tag tag = INITIAL_VALUE;
    initLStack_ElemTypePtr(&topLStack_ElemTypePtr, RIGHT, &p);
    pushLStack(&stack, topLStack_ElemTypePtr);
    while (!isEmptyLStack(&stack))
    {
        popLStack(&stack, &topLStack_ElemTypePtr);
        LStack_ElemTypePtr curr = NULL;
        tag = topLStack_ElemTypePtr->tag;
        if (tag == ERROR)
            return FALSE;
        else if (tag == RIGHT)
        {
            initLStack_ElemTypePtr(&curr, INITIAL_VALUE, &topLStack_ElemTypePtr->avlPtr);
            pushLStack(&stack, curr);
            if (topLStack_ElemTypePtr->avlPtr->rchild)
            {
                initLStack_ElemTypePtr(&curr, RIGHT, &topLStack_ElemTypePtr->avlPtr->rchild);
                pushLStack(&stack, curr);
            }
        }
        else if (tag == LEFT)
        {
            initLStack_ElemTypePtr(&curr, UP, &topLStack_ElemTypePtr->avlPtr);
            pushLStack(&stack, curr);
            if (topLStack_ElemTypePtr->avlPtr->lchild)
            {
                initLStack_ElemTypePtr(&curr, RIGHT, &topLStack_ElemTypePtr->avlPtr->lchild);
                pushLStack(&stack, curr);
            }
        }
        else if (tag == INITIAL_VALUE)
        {
            int length = 0;
            LStackLength(&stack, &length);
            for (int i = 0; i < length; i++)
            {
                printf("       |");
            }
            visitAvl(topLStack_ElemTypePtr->avlPtr);
            printf("\n");
            initLStack_ElemTypePtr(&curr, LEFT, &topLStack_ElemTypePtr->avlPtr);
            pushLStack(&stack, curr);
        }
        else if (tag == UP)
        {
        }
        else
        {
            destroyLStack_ElemTypePtr(&topLStack_ElemTypePtr);
            destroyLStack(&stack);
            return FALSE;
        }
        destroyLStack_ElemTypePtr(&topLStack_ElemTypePtr);
    }
    destroyLStack(&stack);
}
