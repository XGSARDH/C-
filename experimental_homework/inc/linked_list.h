#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "status.h"

// ͨ������Ԫ������
typedef void *ListElementType;

// ����ڵ㶨��
typedef struct ListNode
{
    // ����
    ListElementType data;
    // ָ����һ���ڵ�
    struct ListNode *next;
} ListNode;

// ������
typedef struct LinkedList
{
    // ָ������ͷ�ڵ�
    ListNode *head;
    // ������Ԫ�ظ���
    int size;
} LinkedList;

/* ======================== ͨ��������غ��� ======================== */

/* ��ʼ������ */
Status List_Init(LinkedList *list);

/* �������� */
Status List_Destroy(LinkedList *list);

/* ������β�����Ԫ�� */
Status List_Append(LinkedList *list, ListElementType element);

/* ������ָ��λ�ò���Ԫ�� */
Status List_Insert(LinkedList *list, int index, ListElementType element);

/* ɾ������ָ��λ�õ�Ԫ�� */
Status List_RemoveAt(LinkedList *list, int index, ListElementType *element);

/* ��ȡ����ָ��λ�õ�Ԫ�� */
Status List_Get(LinkedList *list, int index, ListElementType *element);

/* �������ָ��λ�õ�Ԫ�� */
Status List_Change(LinkedList *list, int index, ListElementType *element);

/* ��ȡ�����С */
int List_Size(LinkedList *list);

/* �ж������Ƿ�Ϊ�� */
Status List_IsEmpty(LinkedList *list);

/* ��ӡ���� */
Status List_Print(LinkedList *list, void (*printFunc)(ListElementType));

#endif // LINKED_LIST_H
