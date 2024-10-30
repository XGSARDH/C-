#ifndef LINK_STACK_H
#define LINK_STACK_H

#include "status_enum.h"
// #include "avl_binary_tree.h"

typedef struct StackElemTypeBasic{
	struct avlBiTNode *avlBiTree;
	int tag;
}StackElemTypeBasic, *StackElemType;

typedef struct StackNode
{
	StackElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;

Status initStackElemType(StackElemType *s);

Status initLStack(LinkStack *s);

Status isEmptyLStack(LinkStack *s);

Status getTopLStack(LinkStack *s,StackElemType *e);

Status clearLStack(LinkStack *s);

Status destroyLStack(LinkStack *s);

Status LStackLength(LinkStack *s,int *length);

Status pushLStack(LinkStack *s,StackElemType data);//ÈëÕ»

Status popLStack(LinkStack *s,StackElemType *data);

void PrintStackElemType(StackElemType e);

Status ScanfStackElemType(StackElemType* e);

Status MakeEqualData(StackElemType* origin, StackElemType* result);

Status IsMakeEqualData(StackElemType* origin, StackElemType* result);

Status InitList_StackNode(StackNode** L);

#endif // LINK_STACK_H