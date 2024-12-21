#include "menu.h"
#include "status.h"
#include <stdio.h>

// �����õĲ˵�������
Status test_handler()
{
    printf("����ѡ��ɹ����ã�\n");
    return STATUS_TRUE;
}

void test_menu1()
{
    // ��ʼ���˵�ѡ��
    MenuOption options[3];
    char *description1 = "ѡ��1: ���Թ���1";
    char *description2 = "ѡ��2: ���Թ���2";
    char *description3 = "ѡ��3: ���Թ���3";

    // �����˵�ѡ��
    MenuOption_create(&options[0], 1, description1, test_handler);
    MenuOption_create(&options[1], 2, description2, test_handler);
    MenuOption_create(&options[2], 3, description3, test_handler);

    // �����˵�
    Menu menu;
    char *title = "���Բ˵�";
    Menu_Create(&menu, &title, options, 3, 3);

    // ��ʾ�˵�
    printf("----- ���Բ˵���ʾ -----\n");
    Menu_Display(&menu);

    // ���²˵�ѡ��
    printf("----- ���Ը��²˵�ѡ�� -----\n");
    char *new_description1 = "��ѡ��1: ����A";
    char *new_description2 = "��ѡ��2: ����B";
    MenuOption new_options[2];
    MenuOption_create(&new_options[0], 1, new_description1, test_handler);
    MenuOption_create(&new_options[1], 2, new_description2, test_handler);
    Menu_UpdateOption(&menu, new_options, 2);
    Menu_Display(&menu);

    // ���Դ�������
    printf("----- ���Բ˵����봦�� -----\n");
    char input1[] = "1";
    char input2[] = "3";   // ������Χ��ѡ��
    char input3[] = "abc"; // �Ƿ�����
    char input4[] = "";    // ������

    printf("����: %s\n", input1);
    if (Menu_HandlerInput(menu, input1, NULL) == STATUS_TRUE)
    {
        printf("ѡ��1����ɹ���\n");
    }
    else
    {
        printf("ѡ��1����ʧ�ܣ�\n");
    }

    printf("����: %s\n", input2);
    if (Menu_HandlerInput(menu, input2, NULL) == STATUS_TRUE)
    {
        printf("ѡ��3����ɹ���\n");
    }
    else
    {
        printf("ѡ��3����ʧ�ܣ�\n");
    }

    printf("����: %s\n", input3);
    if (Menu_HandlerInput(menu, input3, NULL) == STATUS_TRUE)
    {
        printf("�Ƿ����봦��ɹ���\n");
    }
    else
    {
        printf("�Ƿ����봦��ʧ�ܣ�\n");
    }

    printf("����: %s\n", input4);
    if (Menu_HandlerInput(menu, input4, NULL) == STATUS_TRUE)
    {
        printf("�����봦��ɹ���\n");
    }
    else
    {
        printf("�����봦��ʧ�ܣ�\n");
    }
}

int main()
{
    test_menu1();
    return 0;
}
