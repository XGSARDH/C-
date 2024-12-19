#include <stdio.h>
#include "linked_list.h"

// 打印整型数据的回调函数
void PrintInt(ListElementType element) {
    printf("%d -> ", *(int*)element);
}

int main() {
    LinkedList list;
    List_Init(&list);

    int a = 10, b = 20, c = 30, d = 40;
    List_Append(&list, &a);
    List_Append(&list, &b);
    List_Insert(&list, 1, &c); // 在索引 1 插入 c
    List_Append(&list, &d);

    printf("链表内容: ");
    List_Print(&list, PrintInt);

    printf("链表大小: %d\n", List_Size(&list));

    int* removedElement;
    List_RemoveAt(&list, 1, (ListElementType*)&removedElement);
    printf("删除元素: %d\n", *removedElement);

    printf("删除后链表内容: ");
    List_Print(&list, PrintInt);

    List_Destroy(&list);
    printf("链表销毁完成。\n");

    return 0;
}
