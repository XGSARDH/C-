#include "status.h"
#include "menu.h"
#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 创建menu菜单
Status Menu_Create(Menu *menu, char **title, MenuOption *option, int option_count, int display_count) {
    if(!menu) {
        return STATUS_FALSE;
    }
    menu->title = *title;
    menu->option = option;
    menu->option_count = option_count;
    menu->display_count = display_count;
    return STATUS_TRUE;
}

// 菜单赋值
Status Menu_UpdateByMenu(Menu *menu_changed, Menu *menu_purpose) {
    if(!menu_purpose || !menu_changed) {
        return STATUS_FALSE;
    }
    *menu_changed = *menu_purpose;
    return STATUS_TRUE;
}

// 打印菜单
Status Menu_Display(Menu *menu) {
    printf("%s\n", menu->title); // 打印标题
    for (int i = 0; i < menu->display_count && i < menu->option_count; i++) {
        printf("%d. %s\n", menu->option[i].key, menu->option[i].description);
    }

    return STATUS_TRUE;
}

// 更新menu菜单中的选项和项数
Status Menu_UpdateOption(Menu *menu, MenuOption *option, int option_count) {
    if(!menu) {
        return STATUS_FALSE;
    }
    menu->option = option;
    menu->option_count = option_count;
    return STATUS_TRUE;
}

// 更新菜单要显示的选项数
Status Menu_UpdateDisplayCount(Menu *menu, int display_count) {
    if(!menu) {
        return STATUS_FALSE;
    }
    menu->display_count = display_count;
    return STATUS_TRUE;
}

// 创建菜单选项
Status MenuOption_create(MenuOption *menuOption, int key, char *description, Status (*handler)()) {
    if(!menuOption) {
        return STATUS_FALSE;
    }
    menuOption->key = key;
    menuOption->description = description;
    menuOption->handler = handler;
    return STATUS_TRUE;
}

// 判断字符串是否为数字
Status is_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return STATUS_FALSE; // 空字符串或 NULL 非法
    }
    while (*str) {
        if (!isdigit(*str)) {
            return STATUS_FALSE; // 非数字字符
        }
        str++;
    }
    return STATUS_TRUE;
}

// 处理菜单输入
Status Menu_HandlerInput(Menu menu, char *input_option, void *context) {
    // 检查输入是否为空
    if (input_option == NULL || strlen(input_option) == 0) {
        return STATUS_OVERFLOW; // 输入为空，返回失败
    }
    // 检查输入是否为纯数字
    if (is_number(input_option) == STATUS_FALSE) {
        return STATUS_OVERFLOW; // 输入中有非数字字符
    }
    if (strlen(input_option) > 5) {
        return STATUS_OVERFLOW; // 输入超过范围
    }
    // 将输入字符串转换为数字
    int option = strtol(input_option, NULL, 10);
    if (option < 0 || option >= menu.option_count) {
        return STATUS_OVERFLOW; // 输入不合法
    }
    return menu.option[option].handler(context);
}