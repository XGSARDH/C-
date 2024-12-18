#include"avl_stack.h"
#include"stack.h"
#include"avl_tree.h"
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
