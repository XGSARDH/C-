#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "status_enum.h"

typedef struct avlBiTNode *StackElemType;

typedef  struct StackNode
{
	StackElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;

Status initLStack(LinkStack *s);

Status isEmptyLStack(LinkStack *s);

Status getTopLStack(LinkStack *s,StackElemType *e);

Status clearLStack(LinkStack *s);

Status destroyLStack(LinkStack *s);

Status LStackLength(LinkStack *s,int *length);

Status pushLStack(LinkStack *s,StackElemType data);//��ջ

Status popLStack(LinkStack *s,StackElemType *data);

void PrintStackElemType(StackElemType e);

Status MakeEqualData(StackElemType* origin, StackElemType* result);

Status IsMakeEqualData(StackElemType* origin, StackElemType* result);

Status InitList_StackNode(StackNode** L);

Status InitStackElemType (StackElemType* e);

#endif 