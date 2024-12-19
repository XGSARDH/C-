#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"
#include "menu.h"
#include "linked_list.h"

#define top_menu_count 4
#define control_tree_menu_count 7
#define more_menu_count 3

Menu top_menu, tree_menu, control_tree_menu, more_menu, now_menu;
MenuOption
        *top_menu_option = NULL,
        *tree_menu_option = NULL,
        *control_tree_menu_option = NULL,
        *more_menu_option = NULL;
LinkedList avl_list;
int now_avl = 0;

Status Menu_AllInit();
Status List_AllInit();

int main() {
    List_AllInit();
    Menu_AllInit();
    now_menu = control_tree_menu;
    Menu_Display(&now_menu);
    return 0;
}

Status List_AllInit() {
    List_Init(&avl_list);
    return STATUS_TRUE;
}

Status top_menu_handler0() {
    exit(0);
    return STATUS_TRUE;
}

Status top_menu_handler1() {
    AvlTree new_avl = NULL;
    Avl_Init(&new_avl);
    Status output_status = List_Append(&avl_list, &new_avl);
    if(output_status == STATUS_TRUE) {
        printf("�����ɹ�\n");
        return output_status;
    }
    else {
        printf("����ʧ��\n");
        return output_status;
    }
}

Status top_menu_handler2() {
    return STATUS_TRUE;
}

Status top_menu_handler3() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler0() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler1() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler2() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler3() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler4() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler5() {

    return STATUS_TRUE;
}

Status control_tree_menu_handler6() {

    return STATUS_TRUE;
}

Status Menu_AllInit() {
    top_menu_option = (MenuOption*) malloc(sizeof(MenuOption) * top_menu_count);
    control_tree_menu_option = (MenuOption*) malloc(sizeof(MenuOption) * control_tree_menu_count);
    more_menu_option = (MenuOption*) malloc(sizeof(MenuOption) * more_menu_count);

    // �����˵���ʼ��
    char *top_menu_title = "�����˵�չʾ";
    char *top_menu_option_description[top_menu_count];
    top_menu_option_description[0] = "�˳�����";
    MenuOption_create(&top_menu_option[0], 0, &top_menu_option_description[0], top_menu_handler0);
    top_menu_option_description[1] = "����һ����ƽ�������";
    MenuOption_create(&top_menu_option[1], 1, &top_menu_option_description[1], top_menu_handler1);
    top_menu_option_description[2] = "ѡ����������е���";
    MenuOption_create(&top_menu_option[2], 2, &top_menu_option_description[2], top_menu_handler2);
    top_menu_option_description[3] = "���๦��";
    MenuOption_create(&top_menu_option[3], 3, &top_menu_option_description[3], top_menu_handler3);
    Menu_Create(&top_menu, &top_menu_title, top_menu_option, top_menu_count, top_menu_count);

    // ���������˵���ʼ��
    char *control_tree_menu_title = "����ƽ������������˵�";
    char *control_tree_menu_option_description[control_tree_menu_count];
    control_tree_menu_option_description[0] = "���ض���Ŀ¼";
    MenuOption_create(&control_tree_menu_option[0], 0, &control_tree_menu_option_description[0], control_tree_menu_handler0);
    control_tree_menu_option_description[1] = "������ֵ";
    MenuOption_create(&control_tree_menu_option[1], 1, &control_tree_menu_option_description[1], control_tree_menu_handler1);
    control_tree_menu_option_description[2] = "ɾ����ֵ";
    MenuOption_create(&control_tree_menu_option[2], 2, &control_tree_menu_option_description[2], control_tree_menu_handler2);
    control_tree_menu_option_description[3] = "������ֵ";
    MenuOption_create(&control_tree_menu_option[3], 3, &control_tree_menu_option_description[3], control_tree_menu_handler3);
    control_tree_menu_option_description[4] = "��ӡ������";
    MenuOption_create(&control_tree_menu_option[4], 4, &control_tree_menu_option_description[4], control_tree_menu_handler4);
    control_tree_menu_option_description[5] = "�������";
    MenuOption_create(&control_tree_menu_option[5], 5, &control_tree_menu_option_description[5], control_tree_menu_handler5);
    control_tree_menu_option_description[6] = "��ĳֵΪ���޲�ֶ�����";
    MenuOption_create(&control_tree_menu_option[6], 6, &control_tree_menu_option_description[6], control_tree_menu_handler6);
    Menu_Create(&control_tree_menu, &control_tree_menu_title, control_tree_menu_option, control_tree_menu_count, control_tree_menu_count);

    return STATUS_TRUE;
}