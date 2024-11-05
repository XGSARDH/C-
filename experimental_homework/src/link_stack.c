#include <stdio.h>
#include <stdlib.h>
#include "link_stack.h"
#include "avl_binary_tree.h"

Status initLStack(LinkStack *s){
	StackNode* head = NULL;
	if (InitList_StackNode(&head) == FALSE)return FALSE;
	s->top = head;
	s->count = 0;
	return TRUE;
}

Status isEmptyLStack(LinkStack *s){
	if (s->top == NULL)return TRUE;
	if (s->top->next == NULL)return TRUE;
	return FALSE;
}

Status getTopLStack(LinkStack *s,StackElemType *e){
	if (isEmptyLStack(s) == TRUE) {
		printf("This is an empty stack\n");
		return FALSE;
	}
	MakeEqualData(e, &(s->top->next->data));
	return TRUE;
}

Status clearLStack(LinkStack *s){
	if (isEmptyLStack(s) == TRUE) {
		return TRUE;
	}
	StackNode* move = s->top->next;
	while (move->next != NULL) {
		StackNode* curr = move->next;
		free(move);
		move = curr;
	}
	s->count = 0;
}

Status destroyLStack(LinkStack *s){
	clearLStack(s);
	free(s->top);
	s->top = NULL;
	return TRUE;
}

Status LStackLength(LinkStack *s,int *length){
	if (isEmptyLStack(s) == TRUE) {
		*length = 0;
	}
	*length = 0;
	StackNode* move = s->top;
	while (move->next != NULL) {
		move = move->next;
		(*length)++;
	}
	return TRUE;
}

Status pushLStack(LinkStack *s,StackElemType data){
	StackNode* curr = NULL;
	if (InitList_StackNode(&curr) == FALSE)return FALSE;
	MakeEqualData(&(curr->data), &data);
	if (isEmptyLStack(s) == TRUE) {
		s->top->next = curr;
		(s->count)++;
		return TRUE;
	}
	curr->next = s->top->next;
	s->top->next = curr;
	(s->count)++;
	return TRUE;
}

Status popLStack(LinkStack *s,StackElemType *data){
	if (isEmptyLStack(s) == TRUE) {
		printf("This is an empty stack\n");
		return FALSE;
	}
	StackNode* curr = s->top->next->next;
	getTopLStack(s, data);
	free(s->top->next);
	s->top->next = curr;
	(s->count)--;
	return TRUE;
}

void PrintStackElemType(StackElemType e)
{
	// printf("%d", e);
	printAVL(e);
	return;
}

Status MakeEqualData(StackElemType* origin, StackElemType* result)
{
	if (origin == NULL || result == NULL) {
		if (origin == result) {
			return TRUE;
		}
		return FALSE;
	}
	if ((*origin) == NULL || (*result) == NULL) {
		if ((*origin) == (*result)) {
			return TRUE;
		}
		return FALSE;
	}
	(*origin)->data = (*result)->data;
	(*origin)->lchild = (*result)->lchild;
	(*origin)->rchild = (*result)->rchild;
	return TRUE;
}

Status IsMakeEqualData(StackElemType* origin, StackElemType* result)
{
	if (origin == NULL || result == NULL) {
		if (origin == result) {
			return TRUE;
		}
		return FALSE;
	}
	if ((*origin) == NULL || (*result) == NULL) {
		if ((*origin) == (*result)) {
			return TRUE;
		}
		return FALSE;
	}
	if ((*origin)->data == (*result)->data && (*origin)->lchild == (*result)->lchild && (*origin)->rchild == (*result)->rchild) {
		return TRUE;
	}
	return FALSE;
}

Status InitList_StackNode(StackNode** L) {
	*L = (StackNode*)malloc(sizeof(StackNode));

	if (*L == NULL)return FALSE;

	(*L)->next = NULL;
	return InitStackElemType(&((*L)->data));
}

Status InitStackElemType(StackElemType* e) {
	return initAVL(e);
}