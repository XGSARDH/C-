#ifndef MENU_H
#define MENU_H

#include "status.h"

typedef struct MenuOption
{
    int key;
    char *description;
    Status (*handler)(void *context);
} MenuOption;

typedef struct Menu
{
    char *title;
    MenuOption *option;
    int option_count;
    int display_count;
} Menu;

// ����menu�˵��е�ѡ�������
Status Menu_UpdateOption(Menu *menu, MenuOption *option, int option_count);

// ����menu�˵�
Status Menu_Create(Menu *menu, char **title, MenuOption *option, int option_count, int display_count);

// �˵���ֵ
Status Menu_UpdateByMenu(Menu *menu_changed, Menu *menu_purpose);

// ��ӡ�˵�
Status Menu_Display(Menu *menu);

// ���²˵�Ҫ��ʾ��ѡ����
Status Menu_UpdateDisplayCount(Menu *menu, int display_count);

// ����˵�����
Status Menu_HandlerInput(Menu menu, char *input_option, void *context);

// �����˵�ѡ��
Status MenuOption_create(MenuOption *menuOption, int key, char *description, Status (*handler)(void *context));

#endif // MENU_H