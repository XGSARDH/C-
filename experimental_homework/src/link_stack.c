#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

/*
与栈相关的基本操作
*/

// 初始化一个栈
Status initLStack(LinkStack *s) {
    if (!s) return FALSE;
    s->top = (LinkStackPtr)malloc(sizeof(StackNode));
    if (!s->top) return FALSE;
    s->top->next = NULL;
    s->count = 0;
    return TRUE;
}

// 创建一个栈节点
Status initLStackPtr(LinkStackPtr *p, LStack_ElemTypePtr e) {
    if (!p || !e) return FALSE;
    *p = (LinkStackPtr)malloc(sizeof(StackNode));
    if (!*p) return FALSE;
    (*p)->data = e;
    (*p)->next = NULL;
    return TRUE;
}

// 判断栈是否为空
Status isEmptyLStack(LinkStack *s) {
    if (!s) return FALSE;
    return s->count == 0 ? TRUE : FALSE;
}

// 取得栈顶元素
Status getTopLStack(LinkStack *s, LStack_ElemTypePtr *e) {
    if (!s || !e || isEmptyLStack(s)) return FALSE;
    *e = s->top->data;
    return TRUE;
}

// 销毁栈
Status destroyLStack(LinkStack *s) {
    if (!s) return FALSE;
    LinkStackPtr p;
    while (s->top) {
        p = s->top;
        s->top = s->top->next;
        free(p->data);
        free(p);
    }
    s->count = 0;
    return TRUE;
}

// 取得栈长度
Status LStackLength(LinkStack *s, int *length) {
    if (!s || !length) return FALSE;
    *length = s->count;
    return TRUE;
}

// 入栈
Status pushLStack(LinkStack *s, LStack_ElemTypePtr data) {
    if (!s || !data) return FALSE;
    LinkStackPtr newNode;
    if (!initLStackPtr(&newNode, data)) return FALSE;
    newNode->next = s->top;
    s->top = newNode;
    s->count++;
    return TRUE;
}

// 出栈
Status popLStack(LinkStack *s, LStack_ElemTypePtr *data) {
    if (!s || !data || isEmptyLStack(s)) return FALSE;
    LinkStackPtr temp = s->top;
    *data = temp->data;
    s->top = temp->next;
    free(temp);
    s->count--;
    return TRUE;
}

/*
与栈基本数据元素相关的基本操作
*/

// 创建一个LStack_ElemTypePtr, 放入LStack_ElemTypePtr的组成元素
Status initLStack_ElemTypePtr(LStack_ElemTypePtr *e, int tag) {
    if (!e) return FALSE;
    *e = (LStack_ElemTypePtr)malloc(sizeof(LStack_ElemType));
    if (!*e) return FALSE;
    (*e)->tag = tag;
    return TRUE;
}

// 创建一个LStack_ElemTypePtr, 放入默认的LStack_ElemTypePtr的组成元素
Status initLStack_ElemTypePtr_default(LStack_ElemTypePtr *e, int tag) {
    return initLStack_ElemTypePtr(e, tag);
}

// 摧毁LStack_ElemTypePtr
Status destroyLStack_ElemTypePtr(LStack_ElemTypePtr **e) {
    if (!e || !*e) return FALSE;
    free(*e);
    *e = NULL;
    return TRUE;
}

// 使两个LStack_ElemTypePtr相等
Status makeEqualLStack_ElemTypePtr(LStack_ElemTypePtr *origin, LStack_ElemTypePtr *result) {
    if (!origin || !result || !*origin || !*result) return FALSE;
    (*result)->tag = (*origin)->tag;
    return TRUE;
}

// 判断两个LStack_ElemTypePtr是否相等
Status isEqualLStack_ElemTypePtr(LStack_ElemTypePtr origin, LStack_ElemTypePtr result) {
    if (!origin || !result) return FALSE;
    return origin->tag == result->tag ? TRUE : FALSE;
}
