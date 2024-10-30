#include <stdio.h>
#include <stdlib.h>
#include"link_queue.h"

void InitLQueue(LQueue *Q){
	Q->front = NULL;
	InitList_Node(&(Q->front));
	Q->rear = Q->front;
	Q->length = 0;
	return;
}

void DestoryLQueue(LQueue *Q){
	ClearLQueue(Q);
	free(Q->front);
	return;
}

Status IsEmptyLQueue(const LQueue *Q){
	if (Q->front == NULL || Q->rear == NULL)return TRUE;
	if (Q->front == Q->rear)return TRUE;
	Node* move = Q->front;
	while (move != NULL) {
		if (move == Q->rear)return FALSE;
		move = move->next;
	}
	return TRUE;
}

Status GetHeadLQueue(LQueue *Q, void **e){
	if (IsEmptyLQueue(Q) == TRUE)return FALSE;
	*e = Q->front->next->data;
	return TRUE;
}

int LengthLQueue(LQueue *Q){
	if (Q->front == NULL)return 0;
	int length = 0;
	Node* move = Q->front;
	while (move->next != NULL) {
		move = move->next;
		length++;
	}
	return length;
}

Status EnLQueue(LQueue *Q, void *data){
	if (Q->front == NULL)return FALSE;
	if (Q->rear == NULL)Q->rear = Q->front;
	Node* curr = NULL;
	InitList_Node(&curr);
	curr->next = NULL;
	curr->data = data;
	Q->rear->next = curr;
	Q->rear = Q->rear->next;
	Q->length = Q->length + 1;
	return TRUE;
}

Status DeLQueue(LQueue *Q){
	if (Q->front == NULL)return FALSE;
	if (Q->front->next == NULL)return FALSE;
	Node* curr = Q->front->next->next;
	free(Q->front->next);
	Q->front->next = curr;
	Q->length--;
	return TRUE;
}

void ClearLQueue(LQueue *Q){
	if (Q->front == NULL)return;
	Node* move = Q->front->next;
	if (move == NULL)return;
	while (move->next != NULL) {
		Node* curr = move->next;
		free(move);
		move = curr;
	}
	free(move);
	Q->length = 0;
	return;
}

Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){
	if (IsEmptyLQueue(Q) == TRUE) {
		printf("The queue is empty now!\n");
		return FALSE;
	}
	Node* move = Q->front;
	for (int i = 0; i < Q->length; i++) {
		move = move->next;
		foo(move->data);
		if (i != Q->length - 1)printf("->");
	}
	return TRUE;
}

void LPrint(void *q){
	size_t sizeLength = _msize(q);
	if (sizeLength == 1)printf("%c ", (*(char*)q));
	if (sizeLength == 4)printf("%d ", (*(int*)q));
	if (sizeLength == 8)printf("%f ", (*(double*)q));
	return;
}

Status InitList_Node(Node** L) {
	*L = (Node*)malloc(sizeof(Node));

	if (*L == NULL)return FALSE;

	void* initData = NULL;
	(*L)->next = NULL;

	return TRUE;
}