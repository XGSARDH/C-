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

// 更新menu菜单中的选项和项数
Status Menu_UpdateOption(Menu *menu, MenuOption *option, int option_count);

// 创建menu菜单
Status Menu_Create(Menu *menu, char **title, MenuOption *option, int option_count, int display_count);

// 菜单赋值
Status Menu_UpdateByMenu(Menu *menu_changed, Menu *menu_purpose);

// 打印菜单
Status Menu_Display(Menu *menu);

// 更新菜单要显示的选项数
Status Menu_UpdateDisplayCount(Menu *menu, int display_count);

// 处理菜单输入
Status Menu_HandlerInput(Menu menu, char *input_option, void *context);

// 创建菜单选项
Status MenuOption_create(MenuOption *menuOption, int key, char *description, Status (*handler)(void *context));

#endif // MENU_H