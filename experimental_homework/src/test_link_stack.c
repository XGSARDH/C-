#include <stdio.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

int test1();
int test2();

int main() {
    int test_output = 0;
    // test_output = test1();
    test_output = test2();
    return test_output;
}

int test1() {
    LinkStack myStack;
    LStack_ElemTypePtr elem1, elem2;
    int length;
    
    // 初始化栈
    if (initLStack(&myStack) == TRUE) {
        printf("栈初始化成功！\n");
    } else {
        printf("栈初始化失败！\n");
        return -1;
    }

    // 创建元素并入栈
    initLStack_ElemTypePtr(&elem1, 10, NULL);
    if (pushLStack(&myStack, elem1) == TRUE) {
        printf("元素 %d 入栈成功！\n", elem1->tag);
    } else {
        printf("元素入栈失败！\n");
        return -1;
    }

    // 获取栈顶元素
    if (getTopLStack(&myStack, &elem2) == TRUE) {
        printf("栈顶元素为：%d\n", elem2->tag);
    } else {
        printf("获取栈顶元素失败！\n");
    }

    // 检查栈是否为空
    if (isEmptyLStack(&myStack) == TRUE) {
        printf("栈为空。\n");
    } else {
        printf("栈不为空。\n");
    }

    // 获取栈长度
    if (LStackLength(&myStack, &length) == TRUE) {
        printf("栈的长度为：%d\n", length);
    } else {
        printf("获取栈长度失败！\n");
    }

    // 出栈
    if (popLStack(&myStack, &elem2) == TRUE) {
        printf("元素 %d 出栈成功！\n", elem2->tag);
        printLStack_ElemTypePtr(elem2);
        destroyLStack_ElemTypePtr(&elem2); // 摧毁弹出的元素
    } else {
        printf("出栈失败！\n");
    }

    // 销毁栈
    if (destroyLStack(&myStack) == TRUE) {
        printf("栈销毁成功！\n");
    } else {
        printf("栈销毁失败！\n");
    }
}

int test2() {
    // 创建一个栈
    LinkStack stack;
    initLStack(&stack);

    LStack_ElemTypePtr LStack_ElemTypePtr1 = NULL, LStack_ElemTypePtr2 = NULL;

    // avlBiTree + tag 等价于 LStack_ElemTypePtr
    avlBiTree avlPtr1 = NULL, avlPtr2 = NULL;
    LStack_ElemTypePtr curr = NULL;

    initAVL(&avlPtr1, 1);
    initLStack_ElemTypePtr(&LStack_ElemTypePtr1, 0, &avlPtr1);
    pushLStack(&stack, LStack_ElemTypePtr1);

    initAVL(&avlPtr2, 2);
    initLStack_ElemTypePtr(&LStack_ElemTypePtr2, 0, &avlPtr2);
    pushLStack(&stack, LStack_ElemTypePtr2);
    
    getTopLStack(&stack, &curr);
    printLStack_ElemTypePtr(curr);

    // 销毁栈和二叉树
    // 销毁栈时不会影响二叉树的原本结构
    destroyLStack(&stack);
    // printAVL(avlPtr1);
    destoryAVL(&avlPtr1);
    destoryAVL(&avlPtr2);
}