#include "avl_tree.h"
#include "interactor.h"
#include "linked_list.h"
#include "menu.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP_MENU_COUNT 4
#define TREE_MENU_COUNT 3
#define CONTROL_TREE_MENU_COUNT 7
#define MORE_MENU_COUNT 4
#define MAX_INPUT 100

int main()
{
    // 定义变量
    Menu top_menu, tree_menu, control_tree_menu, more_menu;
    MenuOption top_menu_option[TOP_MENU_COUNT];
    MenuOption tree_menu_option[TREE_MENU_COUNT];
    MenuOption control_tree_menu_option[CONTROL_TREE_MENU_COUNT];
    MenuOption more_menu_option[MORE_MENU_COUNT];
    LinkedList avl_list;
    int now_avl_position = -1;
    Menu now_menu;
    HandlerContext context;

    // 初始化变量
    List_Init(&avl_list);
    Top_Menu_Init(&top_menu, top_menu_option);
    Tree_Menu_Init(&tree_menu, tree_menu_option);
    Control_Tree_Menu_Init(&control_tree_menu, control_tree_menu_option);
    More_Menu_Init(&more_menu, more_menu_option);
    HandlerContext_Init(&context, &now_menu, &top_menu, &tree_menu, &control_tree_menu, &more_menu, &avl_list,
                        &now_avl_position);
    now_menu = top_menu;

    // 开始程序
    Status main_status = STATUS_TRUE;
    char input_choose[MAX_INPUT] = {};
    while (main_status != STATUS_FALSE)
    {
        Menu_Display(context.now_menu);
        printf("\n请输入选择: ");
        if (fgets(input_choose, sizeof(input_choose), stdin) != NULL)
        {
            // 去掉换行符
            input_choose[strcspn(input_choose, "\n")] = '\0';
        }
        main_status = Menu_HandlerInput(*context.now_menu, input_choose, &context);
        // if(main_status == STATUS_OVERFLOW) {
        //     printf("您的输入不合法, 请输入指定选项的数字\n");
        // }
        printf("按回车以继续\n");
        getchar();
        ClearScreen();
    }
    printf("程序发生错误, 即将终止");
    getchar();
    return 0;
}
