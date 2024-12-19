#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/* 初始化链表 */
Status List_Init(LinkedList* list) {
    if (list == NULL) return STATUS_FALSE;
    list->head = NULL;
    list->size = 0;
    return STATUS_TRUE;
}

/* 销毁链表 */
Status List_Destroy(LinkedList* list) {
    if (list == NULL) return STATUS_FALSE;

    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
    list->size = 0;
    return STATUS_TRUE;
}

/* 在链表尾部添加元素 */
Status List_Append(LinkedList* list, ListElementType element) {
    if (list == NULL) return STATUS_FALSE;

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) return STATUS_OVERFLOW;

    newNode->data = element;
    newNode->next = NULL;

    if (list->head == NULL) {
        // 链表为空时，直接设置新节点为头节点
        list->head = newNode;
    } else {
        // 遍历到链表尾部并添加节点
        ListNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
    return STATUS_TRUE;
}

/* 在链表指定位置插入元素 */
Status List_Insert(LinkedList* list, int index, ListElementType element) {
    if (list == NULL || index < 0 || index > list->size) return STATUS_FALSE;

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) return STATUS_OVERFLOW;

    newNode->data = element;

    if (index == 0) {
        // 在头部插入
        newNode->next = list->head;
        list->head = newNode;
    } else {
        // 遍历到指定位置前一个节点
        ListNode* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
    return STATUS_TRUE;
}

/* 删除链表指定位置的元素 */
Status List_RemoveAt(LinkedList* list, int index, ListElementType* element) {
    if (list == NULL || index < 0 || index >= list->size) return STATUS_FALSE;

    ListNode* toDelete;
    if (index == 0) {
        // 删除头节点
        toDelete = list->head;
        list->head = toDelete->next;
    } else {
        // 遍历到指定位置前一个节点
        ListNode* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }

    if (element != NULL) {
        *element = toDelete->data;
    }

    free(toDelete);
    list->size--;
    return STATUS_TRUE;
}

/* 获取链表指定位置的元素 */
Status List_Get(LinkedList* list, int index, ListElementType* element) {
    if (list == NULL || index < 0 || index >= list->size) return STATUS_FALSE;

    ListNode* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    if (element != NULL) {
        *element = current->data;
    }

    return STATUS_TRUE;
}

/* 获取链表大小 */
int List_Size(LinkedList* list) {
    if (list == NULL) return 0;
    return list->size;
}

/* 判断链表是否为空 */
Status List_IsEmpty(LinkedList* list) {
    if (list == NULL) return STATUS_TRUE;
    return (list->size == 0) ? STATUS_TRUE : STATUS_FALSE;
}

/* 打印链表 */
Status List_Print(LinkedList* list, void (*printFunc)(ListElementType)) {
    if (list == NULL || printFunc == NULL) return STATUS_FALSE;

    ListNode* current = list->head;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");

    return STATUS_TRUE;
}
