#ifndef AVL_STACK_H
#define AVL_STACK_H

#include "status.h"

/* AVL栈元素类型 */
typedef struct AvlNode *AvlTree;
typedef AvlTree* AvlStackElementType;

/* AVL栈定义 */
typedef struct LinkedStack LinkedStack;
typedef LinkedStack AvlStack;

/* AVL栈操作接口 */
Status AvlStack_Init(AvlStack* stack);

Status AvlStack_Destroy(AvlStack* stack);

Status AvlStack_Push(AvlStack* stack, AvlStackElementType element);

Status AvlStack_Pop(AvlStack* stack, AvlStackElementType* element);

Status AvlStack_Top(AvlStack* stack, AvlStackElementType* element);

Status AvlStack_IsEmpty(AvlStack* stack);

int AvlStack_Size(AvlStack* stack);

Status AvlStack_Print(AvlStack* stack, void (*printFunc)(AvlStackElementType));

#endif // AVL_STACK_H