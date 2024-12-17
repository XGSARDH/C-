#ifndef STACK_H
#define STACK_H

#include "status.h"

// 链栈元素类型
typedef void* StackElementType;

// 栈节点定义
typedef struct StackNode {
    // 数据
    StackElementType data;
    // 指向下一个节点
    struct StackNode* next;
} StackNode;

// 链栈定义
typedef struct LinkedStack {
    // 指向栈顶节点
    StackNode* top;
    // 栈中元素个数
    int size;
} LinkedStack;

/* ======================== 链栈相关函数 ======================== */

/* 初始化链栈 */
Status Stack_Init(LinkedStack* stack);

/* 销毁链栈 */
Status Stack_Destroy(LinkedStack* stack);

/* 入栈 */
Status Stack_Push(LinkedStack* stack, StackElementType element);

/* 出栈 */
Status Stack_Pop(LinkedStack* stack, StackElementType* element);

/* 获取栈顶元素 */
Status Stack_Top(LinkedStack* stack, StackElementType* element);

/* 判断栈是否为空 */
Status Stack_IsEmpty(LinkedStack* stack);

/* 获取栈中元素数量 */
int Stack_Size(LinkedStack* stack);

/* 打印栈 */
Status Stack_Print(LinkedStack* stack, void (*printFunc)(StackElementType));

#endif // STACK_H
