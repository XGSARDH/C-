#include <stdio.h>
#include "linked_list.h"

// ��ӡ�������ݵĻص�����
void PrintInt(ListElementType element) {
    printf("%d -> ", *(int*)element);
}

int main() {
    LinkedList list;
    List_Init(&list);

    int a = 10, b = 20, c = 30, d = 40;
    List_Append(&list, &a);
    List_Append(&list, &b);
    List_Insert(&list, 1, &c); // ������ 1 ���� c
    List_Append(&list, &d);

    printf("��������: ");
    List_Print(&list, PrintInt);

    printf("�����С: %d\n", List_Size(&list));

    int* removedElement;
    List_RemoveAt(&list, 1, (ListElementType*)&removedElement);
    printf("ɾ��Ԫ��: %d\n", *removedElement);

    printf("ɾ������������: ");
    List_Print(&list, PrintInt);

    List_Destroy(&list);
    printf("����������ɡ�\n");

    return 0;
}
