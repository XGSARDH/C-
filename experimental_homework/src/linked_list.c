#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/* ��ʼ������ */
Status List_Init(LinkedList *list)
{
    if (list == NULL)
        return STATUS_FALSE;
    list->head = NULL;
    list->size = 0;
    return STATUS_TRUE;
}

/* �������� */
Status List_Destroy(LinkedList *list)
{
    if (list == NULL)
        return STATUS_FALSE;

    ListNode *current = list->head;
    while (current != NULL)
    {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
    list->size = 0;
    return STATUS_TRUE;
}

/* ������β�����Ԫ�� */
Status List_Append(LinkedList *list, ListElementType element)
{
    if (list == NULL)
        return STATUS_FALSE;

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
        return STATUS_OVERFLOW;

    newNode->data = element;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        // ����Ϊ��ʱ��ֱ�������½ڵ�Ϊͷ�ڵ�
        list->head = newNode;
    }
    else
    {
        // ����������β������ӽڵ�
        ListNode *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
    return STATUS_TRUE;
}

/* ������ָ��λ�ò���Ԫ�� */
Status List_Insert(LinkedList *list, int index, ListElementType element)
{
    if (list == NULL || index < 0 || index > list->size)
        return STATUS_FALSE;

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
        return STATUS_OVERFLOW;

    newNode->data = element;

    if (index == 0)
    {
        // ��ͷ������
        newNode->next = list->head;
        list->head = newNode;
    }
    else
    {
        // ������ָ��λ��ǰһ���ڵ�
        ListNode *current = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
    return STATUS_TRUE;
}

/* ɾ������ָ��λ�õ�Ԫ�� */
Status List_RemoveAt(LinkedList *list, int index, ListElementType *element)
{
    if (list == NULL || index < 0 || index >= list->size)
        return STATUS_FALSE;

    ListNode *toDelete;
    if (index == 0)
    {
        // ɾ��ͷ�ڵ�
        toDelete = list->head;
        list->head = toDelete->next;
    }
    else
    {
        // ������ָ��λ��ǰһ���ڵ�
        ListNode *current = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }

    if (element != NULL)
    {
        *element = toDelete->data;
    }

    free(toDelete);
    list->size--;
    return STATUS_TRUE;
}

/* ��ȡ����ָ��λ�õ�Ԫ�� */
Status List_Get(LinkedList *list, int index, ListElementType *element)
{
    if (list == NULL || index < 0 || index >= list->size)
        return STATUS_FALSE;

    ListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // if (element != NULL) {
    //     *element = current->data;
    // }
    *element = current->data;
    return STATUS_TRUE;
}

Status List_Change(LinkedList *list, int index, ListElementType *element)
{
    if (list == NULL || index < 0 || index >= list->size)
        return STATUS_FALSE;
    ListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    current->data = *element;
    return STATUS_TRUE;
}

/* ��ȡ�����С */
int List_Size(LinkedList *list)
{
    if (list == NULL)
        return 0;
    return list->size;
}

/* �ж������Ƿ�Ϊ�� */
Status List_IsEmpty(LinkedList *list)
{
    if (list == NULL)
        return STATUS_TRUE;
    return (list->size == 0) ? STATUS_TRUE : STATUS_FALSE;
}

/* ��ӡ���� */
Status List_Print(LinkedList *list, void (*printFunc)(ListElementType))
{
    if (list == NULL || printFunc == NULL)
        return STATUS_FALSE;

    ListNode *current = list->head;
    while (current != NULL)
    {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");

    return STATUS_TRUE;
}
