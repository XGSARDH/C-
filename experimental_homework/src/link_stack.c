#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

/*
与栈相关的基本操作
*/

Status initLStack(LinkStack *s) {
    if (!s) return FALSE;
    s->top = (StackNodePtr)malloc(sizeof(StackNode));
    if (!s->top) return FALSE;
    s->top->next = NULL;
    s->count = 0;
    return TRUE;
}

Status initLStackPtr(StackNodePtr *p, LStack_ElemTypePtr e) {
    if (!p || !e) return FALSE;
    *p = (StackNodePtr)malloc(sizeof(StackNode));
    if (!*p) return FALSE;
    (*p)->data = e;
    (*p)->next = NULL;
    return TRUE;
}

Status isEmptyLStack(LinkStack *s) {
    if (!s) return FALSE;
    return s->count == 0 ? TRUE : FALSE;
}

Status getTopLStack(LinkStack *s, LStack_ElemTypePtr *e) {
    if (!s || !e || isEmptyLStack(s)) return FALSE;
    *e = s->top->data;
    return TRUE;
}

Status destroyLStack(LinkStack *s) {
    if (!s) return FALSE;
    StackNodePtr p;
    while (s->top) {
        p = s->top;
        s->top = s->top->next;
        if(!p->data) free(p->data);
        free(p);
    }
    s->count = 0;
    return TRUE;
}

Status LStackLength(LinkStack *s, int *length) {
    if (!s || !length) return FALSE;
    *length = s->count;
    return TRUE;
}

Status pushLStack(LinkStack *s, LStack_ElemTypePtr data) {
    if (!s || !data) return FALSE;
    StackNodePtr newNode;
    if (!initLStackPtr(&newNode, data)) return FALSE;
    newNode->next = s->top;
    s->top = newNode;
    s->count++;
    return TRUE;
}

Status popLStack(LinkStack *s, LStack_ElemTypePtr *data) {
    if (!s || !data || isEmptyLStack(s)) return FALSE;
    StackNodePtr temp = s->top;
    *data = temp->data;
    s->top = temp->next;
    free(temp);
    s->count--;
    return TRUE;
}

/*
与栈基本数据元素相关的基本操作
*/

Status initLStack_ElemTypePtr(LStack_ElemTypePtr *e, LStack_ElemType_tag tag, AvlBiTree *avlPtr) {
    if (!e) return FALSE;
    *e = (LStack_ElemTypePtr)malloc(sizeof(LStack_ElemType));
    if (!*e) return FALSE;
    (*e)->tag = tag;
	if (avlPtr == NULL) {
		(*e)->avlPtr = NULL;
	}
	else (*e)->avlPtr = *avlPtr;
    return TRUE;
}

Status initLStack_ElemTypePtr_default(LStack_ElemTypePtr *e) {
    return initLStack_ElemTypePtr(e, INITIAL_VALUE, NULL);
}

Status destroyLStack_ElemTypePtr(LStack_ElemTypePtr *e) {
    if (!e || !*e) return FALSE;
    free(*e);
    *e = NULL;
    return TRUE;
}

Status makeEqualLStack_ElemTypePtr(LStack_ElemTypePtr *origin, LStack_ElemTypePtr *result) {
    if (!origin || !result || !*origin || !*result) return FALSE;
    (*result)->tag = (*origin)->tag;
    (*result)->avlPtr = (*origin)->avlPtr;
    return TRUE;
}

Status isEqualLStack_ElemTypePtr(LStack_ElemTypePtr origin, LStack_ElemTypePtr result) {
    if (!origin || !result) return FALSE;
	Status status = TRUE;
    status = origin->tag == result->tag ? TRUE : FALSE;
	if (!status) return status;
    status = origin->avlPtr == result->avlPtr ? TRUE : FALSE;
	return status;
}

Status printLStack_ElemTypePtr(LStack_ElemTypePtr origin) {
    AvlBiTree p = origin->avlPtr;
    if (!p) {
        printf("AvlBiTree == NULL");
        return FALSE;
    }
    printf("AvlBiTree->data == %d; ", p->data);
    printf("AvlBiTree->balance_factor == %d", p->balance_factor);
    printf("\n");
	printf("origin->tag == %d \n", origin->tag);
	return TRUE;
}