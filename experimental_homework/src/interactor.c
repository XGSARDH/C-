#include "interactor.h"
#include "avl_tree.h"
#include "linked_list.h"
#include "menu.h"
#include "status.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ClearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows ƽ̨
#else
    system("clear"); // Linux/Unix ƽ̨
#endif
}

// �ж��ַ����Ƿ�Ϊ����
Status Interactor_IsNumber(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return STATUS_FALSE; // ���ַ����� NULL �Ƿ�
    }
    while (*str)
    {
        if (!isdigit(*str))
        {
            return STATUS_FALSE; // �������ַ�
        }
        str++;
    }
    return STATUS_TRUE;
}

Status Helper_CharInputAndOutputInt(int *output)
{
    char input_num[MAX_INPUT];
    if (fgets(input_num, sizeof(input_num), stdin) != NULL)
    {
        // ȥ�����з�
        input_num[strcspn(input_num, "\n")] = '\0';
    }
    // ��������Ƿ�Ϊ������
    if (Interactor_IsNumber(input_num) == STATUS_FALSE)
    {
        return STATUS_OVERFLOW; // �������з������ַ�
    }
    if (strlen(input_num) > 5)
    {
        return STATUS_TRUE; // ���볬����Χ
    }
    // �������ַ���ת��Ϊ����
    int number = strtol(input_num, NULL, 10);
    *output = number;
    return STATUS_TRUE;
}

Status HandlerContext_Init(HandlerContext *handler_context, Menu *now_menu, Menu *top_menu, Menu *tree_menu,
                           Menu *control_tree_menu, Menu *more_menu, LinkedList *avl_list, int *now_avl)
{
    if (!handler_context || !top_menu || !avl_list || !now_avl || !tree_menu || !control_tree_menu || !more_menu)
    {
        return STATUS_FALSE;
    }
    handler_context->top_menu = top_menu;
    handler_context->now_menu = now_menu;
    handler_context->tree_menu = tree_menu;
    handler_context->control_tree_menu = control_tree_menu;
    handler_context->more_menu = more_menu;
    handler_context->avl_list = avl_list;
    handler_context->now_avl = now_avl;
    return STATUS_TRUE;
}

/* �����˵� - �˳����� */
Status top_menu_handler0(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;

    while (List_Size(handler_context->avl_list) > 0)
    {
        ListElementType get_avl_tree_origin;
        if (STATUS_FALSE == List_RemoveAt(handler_context->avl_list, 0, &get_avl_tree_origin))
        {
            *handler_context->now_avl = -1;
            continue;
        }
        AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
        if (get_avl_tree_origin == NULL)
        {
            continue;
        }
        Status status = Avl_Destroy(&avl_tree);
    }
    exit(0);
}

/* �����˵� - ����һ����ƽ������� */
Status top_menu_handler1(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    Status output_status = List_Append(handler_context->avl_list, NULL);
    if (output_status == STATUS_TRUE)
    {
        printf("�����ɹ�\n");
        return output_status;
    }
    else
    {
        printf("����ʧ��\n");
        return output_status;
    }
}

/* �����˵� - �Զ��������е��� */
Status top_menu_handler2(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    handler_context->now_menu = handler_context->tree_menu;
    return STATUS_TRUE;
}

/* �����˵� - ���๦�� */
Status top_menu_handler3(void *context)
{
    if (!context)
    {
        return STATUS_FALSE;
    }
    HandlerContext *handler_context = (HandlerContext *)context;
    handler_context->now_menu = handler_context->more_menu;
    return STATUS_TRUE;
}

/* �����˵� - �Զ�����һ�ð������д���ʼֵ������ֵ�������߽�ֵ����ƽ������� */
Status top_menu_handler4(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("������ʼֵ: ");
    int number1 = -1;
    if (Helper_CharInputAndOutputInt(&number1) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    printf("�������ֵ: ");
    int number2 = -1;
    if (Helper_CharInputAndOutputInt(&number2) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (number1 > number2)
    {
        printf("��ʼֵӦ���ڵ��ڽ���ֵ");
        return STATUS_OVERFLOW; // ���벻�Ϸ�
    }
    AvlTree avl_tree = NULL;
    Avl_Init(&avl_tree);
    Status output_status = STATUS_TRUE;
    for (int insert_number = number1; insert_number <= number2; insert_number++)
    {
        output_status = Avl_Insert(&avl_tree, insert_number);
    }
    if (output_status == STATUS_TRUE)
    {
        printf("���ɳɹ�\n");
    }
    else
    {
        printf("����ʧ��\n");
    }
    printf("\n���ɽ��: \n");
    Avl_PrintTree(avl_tree);

    ListElementType curr = NULL;
    curr = (ListElementType *)avl_tree;
    List_Append(handler_context->avl_list, curr);
    return output_status;
}

/* ���ƶ������˵� - ����ѡ��������˵� */
Status control_tree_menu_handler0(void *context)
{
    if (!context)
    {
        return STATUS_FALSE;
    }
    HandlerContext *handler_context = (HandlerContext *)context;
    handler_context->now_menu = handler_context->tree_menu;
    return STATUS_TRUE;
}

/* ���ƶ������˵� - ������ֵ */
Status control_tree_menu_handler1(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    int insert_value = 0;
    printf("����Ҫ��ӵ�����: ");
    if (Helper_CharInputAndOutputInt(&insert_value) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (abs(insert_value) > 65533)
    {
        printf("�������־���ֵ����\n");
        return STATUS_OVERFLOW;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        AvlTree purpose = NULL;
        Avl_Init(&purpose);
        avl_tree = purpose;
    }
    Avl_Insert(&avl_tree, insert_value);
    ListElementType curr = (ListElementType *)avl_tree;
    List_Change(handler_context->avl_list, *handler_context->now_avl, &curr);
    return STATUS_TRUE;
}

/*���ƶ������˵� - ɾ����ֵ  */
Status control_tree_menu_handler2(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    int insert_value = 0;
    printf("����Ҫɾ��������: ");
    if (Helper_CharInputAndOutputInt(&insert_value) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (abs(insert_value) > 65533)
    {
        printf("�������־���ֵ����\n");
        return STATUS_OVERFLOW;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        printf("��������Ϊ����, �޷�ִ�иò���.\n");
        return STATUS_OVERFLOW;
    }
    Status delete_status = Avl_Delete(&avl_tree, insert_value);
    if (delete_status == STATUS_FALSE)
    {
        printf("���������ڸ�ֵ, �޷�ִ�иò���.\n");
        return STATUS_OVERFLOW;
    }
    ListElementType curr = (ListElementType *)avl_tree;
    List_Change(handler_context->avl_list, *handler_context->now_avl, &curr);
    return STATUS_TRUE;
}

/* ���ƶ������˵� - ������ֵ */
Status control_tree_menu_handler3(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    int insert_value = 0;
    printf("����Ҫɾ��������: ");
    if (Helper_CharInputAndOutputInt(&insert_value) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (abs(insert_value) > 65533)
    {
        printf("�������־���ֵ����\n");
        return STATUS_OVERFLOW;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        printf("��������Ϊ����, �޷�ִ�иò���.\n");
        return STATUS_OVERFLOW;
    }
    Status delete_status = Avl_Search(&avl_tree, insert_value);
    if (delete_status == STATUS_OVERFLOW)
    {
        printf("���������ڸ�ֵ\n");
        return STATUS_OVERFLOW;
    }
    else
    {
        printf("�������ڸ�ֵ %d \n", insert_value);
    }
    return STATUS_TRUE;
}

/* ���ƶ������˵� - ��ӡ������ */
Status control_tree_menu_handler4(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        printf("��������Ϊ����.\n");
        return STATUS_TRUE;
    }
    Status status = Avl_PrintTree(avl_tree);
    return STATUS_TRUE;
}

/* ���ƶ������˵� - ������� */
Status control_tree_menu_handler5(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        printf("��������Ϊ����.\n");
        return STATUS_TRUE;
    }
    Status status = Avl_InOrderTraverse(avl_tree);
    printf("\n");
    return STATUS_TRUE;
}

/* ���ƶ������˵� - ��ĳֵΪ���޲�ֶ����� */
Status control_tree_menu_handler6(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    int insert_value = 0;
    printf("����Ҫ��Ϊ�ָ�����ƽ�������������: ");
    if (Helper_CharInputAndOutputInt(&insert_value) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (abs(insert_value) > 65533)
    {
        printf("�������־���ֵ����\n");
        return STATUS_OVERFLOW;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        AvlTree purpose = NULL;
        Avl_Init(&purpose);
        avl_tree = purpose;
    }
    AvlTree spilt_tree1 = NULL;
    AvlTree spilt_tree2 = NULL;
    Avl_Split(&avl_tree, insert_value, &spilt_tree1, &spilt_tree2);
    // ListElementType curr = (ListElementType*)avl_tree;
    printf("�ָ�ɹ�\n");
    printf("�ָ�ĵ�1����:\n");
    Avl_PrintTree(spilt_tree1);
    printf("�ָ�ĵ�2����:\n");
    Avl_PrintTree(spilt_tree2);

    ListElementType curr = NULL;
    curr = (ListElementType *)spilt_tree1;
    List_Append(handler_context->avl_list, curr);
    curr = (ListElementType *)spilt_tree2;
    List_Append(handler_context->avl_list, curr);

    return STATUS_TRUE;
}

/* ���ƶ������˵� - ɾ������ */
Status control_tree_menu_handler7(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    ListElementType get_avl_tree_origin;
    handler_context->now_menu = handler_context->tree_menu;
    if (STATUS_FALSE == List_RemoveAt(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin))
    {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL)
    {
        return STATUS_TRUE;
    }
    Status status = Avl_Destroy(&avl_tree);
    return STATUS_TRUE;
}

/* ѡ��������˵� - ���ض���Ŀ¼ */
Status tree_menu_handler0(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    handler_context->now_menu = handler_context->top_menu;
    return STATUS_TRUE;
}

/* ѡ��������˵� - ��ת��ָ�����ƽ������������˵� */
Status tree_menu_handler1(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("������Ҫ�鿴�Ķ�������Ӧ�����: ");
    int number = -1;
    if (Helper_CharInputAndOutputInt(&number) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (number < 1 || number > List_Size(handler_context->avl_list))
    {
        printf("���������Χ");
        return STATUS_OVERFLOW; // ���벻�Ϸ�
    }
    *handler_context->now_avl = number - 1;
    handler_context->now_menu = handler_context->control_tree_menu;
    return STATUS_TRUE;
}

/* ѡ��������˵� - �鿴��ǰ���������� */
Status tree_menu_handler2(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("��ǰ���ж���������Ϊ %d \n", List_Size(handler_context->avl_list));
    return STATUS_TRUE;
}

/* ���๦�ܲ˵� - ���ض���Ŀ¼ */
Status more_menu_handler0(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    handler_context->now_menu = handler_context->top_menu;
    return STATUS_TRUE;
}

/* ���๦�ܲ˵� - ��ӡָ����ŵĶ����� */
Status more_menu_handler1(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("������Ҫ�鿴�Ķ�������Ӧ�����: ");
    int number = -1;
    if (Helper_CharInputAndOutputInt(&number) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (number < 1 || number > List_Size(handler_context->avl_list))
    {
        printf("���������Χ");
        return STATUS_OVERFLOW; // ���벻�Ϸ�
    }
    *handler_context->now_avl = number - 1;
    return control_tree_menu_handler4(context);
}

/* ���๦�ܲ˵� - �ϲ�ָ��������ŵĶ����� */
Status more_menu_handler2(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("������Ҫ�ϲ��ĵ�1�ö�������Ӧ�����: ");
    int number1 = -1;
    if (Helper_CharInputAndOutputInt(&number1) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (number1 < 1 || number1 > List_Size(handler_context->avl_list))
    {
        printf("���������Χ");
        return STATUS_OVERFLOW; // ���벻�Ϸ�
    }
    printf("������Ҫ�ϲ��ĵ�2�ö�������Ӧ�����: ");
    int number2 = -1;
    if (Helper_CharInputAndOutputInt(&number2) != STATUS_TRUE)
    {
        printf("���벻�Ǵ�����\n");
        return STATUS_OVERFLOW;
    }
    if (number2 < 1 || number2 > List_Size(handler_context->avl_list))
    {
        printf("���������Χ");
        return STATUS_OVERFLOW; // ���벻�Ϸ�
    }
    ListElementType get_avl_tree_origin_1;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, number1 - 1, &get_avl_tree_origin_1))
    {
        control_tree_menu_handler0(context);
        return STATUS_FALSE;
    }
    ListElementType get_avl_tree_origin_2;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, number2 - 1, &get_avl_tree_origin_2))
    {
        control_tree_menu_handler0(context);
        return STATUS_FALSE;
    }
    AvlTree avl_tree_1 = (AvlTree)get_avl_tree_origin_1;
    AvlTree avl_tree_2 = (AvlTree)get_avl_tree_origin_2;
    AvlTree purpose_tree = NULL;

    Status output_status = Avl_Merge(&avl_tree_1, &avl_tree_2, &purpose_tree);
    if (output_status == STATUS_TRUE)
    {
        printf("�ϲ��ɹ�\n");
    }
    else
    {
        printf("�ϲ�ʧ��\n");
    }

    printf("\n����ϲ��ĵ�1����: \n");
    Avl_PrintTree(avl_tree_1);
    printf("\n����ϲ��ĵ�2����: \n");
    Avl_PrintTree(avl_tree_2);
    printf("\n�ϲ����: \n");
    Avl_PrintTree(purpose_tree);

    ListElementType curr = NULL;
    curr = (ListElementType *)purpose_tree;
    List_Append(handler_context->avl_list, curr);

    return output_status;
}

/* ���๦�ܲ˵� - �鿴��ǰ������������ */
Status more_menu_handler3(void *context)
{
    HandlerContext *handler_context = (HandlerContext *)context;
    printf("��ǰ���ж���������Ϊ %d \n", List_Size(handler_context->avl_list));
    return STATUS_TRUE;
}

/* �����˵���ѡ���ʼ�� */
Status Top_Menu_Init(Menu *top_menu, MenuOption *top_menu_option)
{
    MenuOption_create(&top_menu_option[0], 0, "�˳�����", top_menu_handler0);
    MenuOption_create(&top_menu_option[1], 1, "����һ����ƽ�������", top_menu_handler1);
    MenuOption_create(&top_menu_option[2], 2, "ѡ����������е���", top_menu_handler2);
    MenuOption_create(&top_menu_option[3], 3, "���๦��", top_menu_handler3);
    MenuOption_create(&top_menu_option[4], 4, "�Զ�����һ�ð������д���ʼֵ������ֵ�������߽�ֵ����ƽ�������",
                      top_menu_handler4);
    char *top_menu_title = "�����˵�";
    Menu_Create(top_menu, &top_menu_title, top_menu_option, TOP_MENU_COUNT, TOP_MENU_COUNT);
    return STATUS_TRUE;
}

/* ���ƶ������˵���ѡ���ʼ�� */
Status Control_Tree_Menu_Init(Menu *control_tree_menu, MenuOption *control_tree_menu_option)
{
    MenuOption_create(&control_tree_menu_option[0], 0, "����ѡ��������˵�", control_tree_menu_handler0);
    MenuOption_create(&control_tree_menu_option[1], 1, "������ֵ", control_tree_menu_handler1);
    MenuOption_create(&control_tree_menu_option[2], 2, "ɾ����ֵ", control_tree_menu_handler2);
    MenuOption_create(&control_tree_menu_option[3], 3, "������ֵ", control_tree_menu_handler3);
    MenuOption_create(&control_tree_menu_option[4], 4, "��ӡ������", control_tree_menu_handler4);
    MenuOption_create(&control_tree_menu_option[5], 5, "�������", control_tree_menu_handler5);
    MenuOption_create(&control_tree_menu_option[6], 6, "��ĳֵΪ���޲�ֶ�����", control_tree_menu_handler6);
    MenuOption_create(&control_tree_menu_option[7], 7, "ɾ������", control_tree_menu_handler7);
    char *control_tree_menu_title = "����ƽ������������˵�";
    Menu_Create(control_tree_menu, &control_tree_menu_title, control_tree_menu_option, CONTROL_TREE_MENU_COUNT,
                CONTROL_TREE_MENU_COUNT);
    return STATUS_TRUE;
}

/* ѡ��������˵���ѡ���ʼ�� */
Status Tree_Menu_Init(Menu *tree_menu, MenuOption *tree_menu_option)
{
    MenuOption_create(&tree_menu_option[0], 0, "���ض���Ŀ¼", tree_menu_handler0);
    MenuOption_create(&tree_menu_option[1], 1, "��ת��ָ�����ƽ������������˵�", tree_menu_handler1);
    MenuOption_create(&tree_menu_option[2], 2, "�鿴��ǰ����������", tree_menu_handler2);
    char *tree_menu_title = "ѡ��������˵�";
    Menu_Create(tree_menu, &tree_menu_title, tree_menu_option, TREE_MENU_COUNT, TREE_MENU_COUNT);
    return STATUS_TRUE;
};

/* ���๦�ܲ˵���ѡ���ʼ�� */
Status More_Menu_Init(Menu *more_menu, MenuOption *more_menu_option)
{
    MenuOption_create(&more_menu_option[0], 0, "���ض���Ŀ¼", more_menu_handler0);
    MenuOption_create(&more_menu_option[1], 1, "��ӡָ����ŵĶ�����", more_menu_handler1);
    MenuOption_create(&more_menu_option[2], 2, "�ϲ�ָ��������ŵĶ�����", more_menu_handler2);
    MenuOption_create(&more_menu_option[3], 3, "�鿴��ǰ������������", more_menu_handler3);
    char *more_menu_title = "���๦�ܲ˵�";
    Menu_Create(more_menu, &more_menu_title, more_menu_option, MORE_MENU_COUNT, MORE_MENU_COUNT);
    return STATUS_TRUE;
};