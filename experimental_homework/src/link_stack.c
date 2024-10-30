#include <stdio.h>
#include <stdlib.h>
#include "link_stack.h"
#include "avl_binary_tree.h"

Status initStackElemType(StackElemType *s){
	if (*s) return TRUE;
	*s = (StackElemType*)malloc(sizeof(StackElemTypeBasic));
	initAVL(&((*s)->avlBiTree));
	(*s)->tag = 0;
}

Status makeStackElemType(StackElemType *s, struct avlBiTNode *p, int tag){
	if (!(*s)) {
		initStackElemType(s);
	}
	(*s)->avlBiTree = p;
	(*s)->tag = tag;
	return TRUE;
}

Status destroyStackElemType(StackElemType *s){
	if (!(*s)) return TRUE;
	if (destoryAVL(&((*s)->avlBiTree)) == FALSE) {
		return FALSE;
	}
	free(*s);
	return TRUE;
}

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
		destroyStackElemType(move->data);
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
	free(s->top->next);
	s->top->next = curr;
	(s->count)--;
	return TRUE;
}

void PrintStackElemType(StackElemType e)
{
	visitAVL(e->avlBiTree);
	return;
}

Status ScanfStackElemType(StackElemType* e)
{
	int input = 0;
	if (e == NULL)return FALSE;
	do {
		printf("Plaese input a number:");
		input = scanf("%d", e);
		while (getchar() != '\n');
	} while (input == 0);
	return TRUE;
}

Status MakeEqualData(StackElemType* origin, StackElemType* result)
{
	if (!(*origin) || !(*result)) return FALSE;
	(*origin)->avlBiTree = (*result)->avlBiTree;
	(*origin)->tag = (*result)->tag;
	return TRUE;
}

Status IsMakeEqualData(StackElemType* origin, StackElemType* result)
{
	if (origin == NULL || result == NULL)return FALSE;
	if (*origin == *result)return TRUE;
	else return FALSE;
}

Status InitList_StackNode(StackNode** L) {
	*L = (StackNode*)malloc(sizeof(StackNode));

	if (*L == NULL)return FALSE;

	void* initData = NULL;
	(*L)->next = NULL;

	return TRUE;
}
