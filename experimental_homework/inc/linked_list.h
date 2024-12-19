#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "status.h"

// 通用链表元素类型
typedef void* ListElementType;

// 链表节点定义
typedef struct ListNode {
    // 数据
    ListElementType data;
    // 指向下一个节点
    struct ListNode* next;
} ListNode;

// 链表定义
typedef struct LinkedList {
    // 指向链表头节点
    ListNode* head;
    // 链表中元素个数
    int size;
} LinkedList;

/* ======================== 通用链表相关函数 ======================== */

/* 初始化链表 */
Status List_Init(LinkedList* list);

/* 销毁链表 */
Status List_Destroy(LinkedList* list);

/* 在链表尾部添加元素 */
Status List_Append(LinkedList* list, ListElementType element);

/* 在链表指定位置插入元素 */
Status List_Insert(LinkedList* list, int index, ListElementType element);

/* 删除链表指定位置的元素 */
Status List_RemoveAt(LinkedList* list, int index, ListElementType* element);

/* 获取链表指定位置的元素 */
Status List_Get(LinkedList* list, int index, ListElementType* element);

/* 替代链表指定位置的元素 */
Status List_Change(LinkedList* list, int index, ListElementType* element);

/* 获取链表大小 */
int List_Size(LinkedList* list);

/* 判断链表是否为空 */
Status List_IsEmpty(LinkedList* list);

/* 打印链表 */
Status List_Print(LinkedList* list, void (*printFunc)(ListElementType));

#endif // LINKED_LIST_H
