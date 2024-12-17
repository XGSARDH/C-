#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "status_enum.h"

typedef struct AvlBiTNode AvlBiTNode, *AvlBiTree;

typedef enum LStackElemType_tag
{
    ERROR = -1,
    INITIAL_VALUE = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3
} LStackElemType_tag;

typedef struct
{
    AvlBiTree avlPtr;
    LStackElemType_tag tag;
} LStackElemType, *LStackElemTypePtr;

typedef struct StackNode
{
    LStackElemTypePtr data;
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
Status initLStackPtr(StackNodePtr *p, LStackElemTypePtr e);

// 判断栈是否为空
Status isEmptyLStack(LinkStack *s);

// 取得栈顶元素
Status getTopLStack(LinkStack *s, LStackElemTypePtr *e);

// 销毁栈
Status destroyLStack(LinkStack *s);

// 取得栈长度
Status LStackLength(LinkStack *s, int *length);

// 入栈
Status pushLStack(LinkStack *s, LStackElemTypePtr data);

// 出栈
Status popLStack(LinkStack *s, LStackElemTypePtr *data);

/*
与栈基本数据元素相关的基本操作
*/

// 创建一个LStackElemTypePtr, 放入LStackElemTypePtr的组成元素
Status initLStackElemTypePtr(LStackElemTypePtr *e, LStackElemType_tag tag, AvlBiTree *avlPtr);

// 创建一个LStackElemTypePtr, 放入默认的LStackElemTypePtr的组成元素
Status initLStackElemTypePtr_default(LStackElemTypePtr *e);

// 摧毁LStackElemTypePtr
Status destroyLStackElemTypePtr(LStackElemTypePtr *e);

// 使两个LStackElemTypePtr相等
Status makeEqualLStackElemTypePtr(LStackElemTypePtr *origin, LStackElemTypePtr *result);

// 判断两个LStackElemTypePtr是否相等
Status isEqualLStackElemTypePtr(LStackElemTypePtr origin, LStackElemTypePtr result);

// 打印tLStackElemTypePtr
Status printLStackElemTypePtr(LStackElemTypePtr origin);

#endif // STACK_H_INCLUDED