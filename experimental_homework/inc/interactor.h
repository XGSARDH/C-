#ifndef INTERACTOR_H
#define INTERACTOR_H

#include "status.h"

#define TOP_MENU_COUNT 4
#define TREE_MENU_COUNT 3
#define CONTROL_TREE_MENU_COUNT 7
#define MORE_MENU_COUNT 3
#define MAX_INPUT 100

typedef struct Menu Menu;
typedef struct LinkedList LinkedList;
typedef struct MenuOption MenuOption;

// 定义携带信息结构体
typedef struct HandlerContext {
    Menu *now_menu;
    Menu *top_menu;
    Menu *tree_menu;
    Menu *control_tree_menu;
    Menu *more_menu;
    LinkedList *avl_list;
    int *now_avl;
} HandlerContext;

// 清屏
void ClearScreen();
// 初始化顶级菜单
Status Top_Menu_Init(Menu *top_menu, MenuOption *top_menu_option);
// 初始化控制单棵树菜单
Status Control_Tree_Menu_Init(Menu *control_tree_menu, MenuOption *control_tree_menu_option);
// 初始化选择二叉树菜单
Status Tree_Menu_Init(Menu *tree_menu, MenuOption *tree_menu_option);
// 测试菜单显示
void Test_MenuDisplay(Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu);
// 初始化绑定context
Status HandlerContext_Init(HandlerContext *handler_context, Menu *now_menu, Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu, LinkedList *avl_list, int *now_avl);


#endif