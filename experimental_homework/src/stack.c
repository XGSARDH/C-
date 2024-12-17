#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* 初始化链栈 */
Status Stack_Init(LinkedStack* stack) {
    if (!stack) return STATUS_FALSE;
    stack->top = NULL;
    stack->size = 0;
    return STATUS_TRUE;
}

/* 销毁链栈 */
Status Stack_Destroy(LinkedStack* stack) {
    if (!stack) return STATUS_FALSE;

    StackNode* current = stack->top;
    while (current) {
        StackNode* temp = current;
        current = current->next;
        free(temp);
    }

    stack->top = NULL;
    stack->size = 0;
    return STATUS_TRUE;
}

/* 入栈 */
Status Stack_Push(LinkedStack* stack, StackElementType element) {
    if (!stack) return STATUS_FALSE;

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return STATUS_OVERFLOW;

    newNode->data = element;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;

    return STATUS_TRUE;
}

/* 出栈 */
Status Stack_Pop(LinkedStack* stack, StackElementType* element) {
    if (!stack || !element || Stack_IsEmpty(stack)) return STATUS_FALSE;

    StackNode* temp = stack->top;
    *element = temp->data;

    stack->top = temp->next;
    free(temp);
    stack->size--;

    return STATUS_TRUE;
}

/* 获取栈顶元素 */
Status Stack_Top(LinkedStack* stack, StackElementType* element) {
    if (!stack || !element || Stack_IsEmpty(stack)) return STATUS_FALSE;

    *element = stack->top->data;
    return STATUS_TRUE;
}

/* 判断栈是否为空 */
Status Stack_IsEmpty(LinkedStack* stack) {
    if (!stack) return STATUS_FALSE;
    return stack->top == NULL ? STATUS_TRUE : STATUS_FALSE;
}

/* 获取栈中元素数量 */
int Stack_Size(LinkedStack* stack) {
    return (stack) ? stack->size : -1;
}

/* 打印栈 */
Status Stack_Print(LinkedStack* stack, void (*printFunc)(StackElementType)) {
    if (!stack || Stack_IsEmpty(stack)) {
        printf("栈为空\n");
        return STATUS_FALSE;
    }

    printf("栈内容（从栈顶到栈底）:\n");
    StackNode* current = stack->top;
    while (current) {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");
    return STATUS_TRUE;
}
