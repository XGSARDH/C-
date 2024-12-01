#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "status_enum.h"

typedef struct AvlBiTNode AvlBiTNode, *AvlBiTree;

typedef enum LStack_ElemType_tag
{
    ERROR = -1,
    INITIAL_VALUE = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3
} LStack_ElemType_tag;

typedef struct
{
    AvlBiTree avlPtr;
    LStack_ElemType_tag tag;
} LStack_ElemType, *LStack_ElemTypePtr;

typedef struct StackNode
{
    LStack_ElemTypePtr data;
    struct StackNode *next;
} StackNode, *StackNodePtr;

// 头插法(有头结点)
typedef struct LinkStack
{
    StackNodePtr top;
    int count;
} LinkStack, LStack;

/*
与栈相关的基本操作
*/

// 初始化一个栈
Status initLStack(LinkStack *s);

// 创建一个栈节点
Status initLStackPtr(StackNodePtr *p, LStack_ElemTypePtr e);

// 判断栈是否为空
Status isEmptyLStack(LinkStack *s);

// 取得栈顶元素
Status getTopLStack(LinkStack *s, LStack_ElemTypePtr *e);

// 销毁栈
Status destroyLStack(LinkStack *s);

// 取得栈长度
Status LStackLength(LinkStack *s, int *length);

// 入栈
Status pushLStack(LinkStack *s, LStack_ElemTypePtr data);

// 出栈
Status popLStack(LinkStack *s, LStack_ElemTypePtr *data);

/*
与栈基本数据元素相关的基本操作
*/

// 创建一个LStack_ElemTypePtr, 放入LStack_ElemTypePtr的组成元素
Status initLStack_ElemTypePtr(LStack_ElemTypePtr *e, LStack_ElemType_tag tag, AvlBiTree *avlPtr);

// 创建一个LStack_ElemTypePtr, 放入默认的LStack_ElemTypePtr的组成元素
Status initLStack_ElemTypePtr_default(LStack_ElemTypePtr *e);

// 摧毁LStack_ElemTypePtr
Status destroyLStack_ElemTypePtr(LStack_ElemTypePtr *e);

// 使两个LStack_ElemTypePtr相等
Status makeEqualLStack_ElemTypePtr(LStack_ElemTypePtr *origin, LStack_ElemTypePtr *result);

// 判断两个LStack_ElemTypePtr是否相等
Status isEqualLStack_ElemTypePtr(LStack_ElemTypePtr origin, LStack_ElemTypePtr result);

// 打印tLStack_ElemTypePtr
Status printLStack_ElemTypePtr(LStack_ElemTypePtr origin);

#endif // STACK_H_INCLUDED