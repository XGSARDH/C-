#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"
#include "menu.h"
#include "linked_list.h"

#define TOP_MENU_COUNT 4
#define TREE_MENU_COUNT 3
#define CONTROL_TREE_MENU_COUNT 7
#define MORE_MENU_COUNT 3
#define MAX_INPUT 100

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

int main() {
    // 定义变量
    Menu top_menu, tree_menu, control_tree_menu, more_menu;
    MenuOption top_menu_option[TOP_MENU_COUNT];
    MenuOption tree_menu_option[TREE_MENU_COUNT];
    MenuOption control_tree_menu_option[CONTROL_TREE_MENU_COUNT];
    // MenuOption more_menu_option[MORE_MENU_COUNT];
    LinkedList avl_list;
    int now_avl_position = 0;
    Menu now_menu;
    HandlerContext context;

    // 初始化变量
    List_Init(&avl_list);
    Top_Menu_Init(&top_menu, top_menu_option);
    Tree_Menu_Init(&tree_menu, tree_menu_option);
    Control_Tree_Menu_Init(&control_tree_menu, control_tree_menu_option);
    HandlerContext_Init(&context, &now_menu, &top_menu, &tree_menu, &control_tree_menu, &more_menu, &avl_list, &now_avl_position);
    now_menu = top_menu;

    // 开始程序
    Status main_status = STATUS_TRUE;
    char input_choose[MAX_INPUT] = {};
    while(main_status != STATUS_FALSE) {
        Menu_Display(context.now_menu);
        printf("\n请输入选择: ");
        if (fgets(input_choose, sizeof(input_choose), stdin) != NULL) {
            // 去掉换行符
            input_choose[strcspn(input_choose, "\n")] = '\0';
        }
        main_status = Menu_HandlerInput(*context.now_menu, input_choose, &context);
        if(main_status == STATUS_OVERFLOW) {
            printf("您的输入不合法, 请输入指定选项的数字\n");
        }
    }
    return 0;
}

Status HandlerContext_Init(HandlerContext *handler_context, Menu *now_menu, Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu, LinkedList *avl_list, int *now_avl) {
    if(!handler_context || !top_menu || !avl_list || !now_avl || !tree_menu || !control_tree_menu || !more_menu) {
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

void Test_MenuDisplay(Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu) {
    Menu_Display(top_menu);
    Menu_Display(tree_menu);
    Menu_Display(control_tree_menu);
}

Status top_menu_handler0(void *context) {
    exit(0);
}

Status top_menu_handler1(void *context) {
    HandlerContext *handlerContext = (HandlerContext*)context;
    AvlTree new_avl = NULL;
    Avl_Init(&new_avl);
    Status output_status = List_Append(handlerContext->avl_list, &new_avl);
    if(output_status == STATUS_TRUE) {
        printf("创建成功\n");
        return output_status;
    }
    else {
        printf("创建失败\n");
        return output_status;
    }
}

Status top_menu_handler2(void *context) {
    HandlerContext *handlerContext = (HandlerContext*)context;
    handlerContext->now_menu = handlerContext->tree_menu;
    return STATUS_TRUE;
}

Status top_menu_handler3(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler0(void *now_menu) {
//    *((Menu*)now_menu) = top_menu;
//    return STATUS_TRUE;
}

Status control_tree_menu_handler1(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler2(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler3(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler4(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler5(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler6(void *context) {

    return STATUS_TRUE;
}

Status tree_menu_handler0(void *context) {

    return STATUS_TRUE;
}

Status tree_menu_handler1(void *context) {

    return STATUS_TRUE;
}

Status tree_menu_handler2(void *context) {

    return STATUS_TRUE;
}

Status Top_Menu_Init(Menu *top_menu, MenuOption *top_menu_option) {
    MenuOption_create(&top_menu_option[0], 0, "退出程序", top_menu_handler0);
    MenuOption_create(&top_menu_option[1], 1, "创建一棵新平衡二叉树", top_menu_handler1);
    MenuOption_create(&top_menu_option[2], 2, "选择二叉树进行调整", top_menu_handler2);
    MenuOption_create(&top_menu_option[3], 3, "更多功能", top_menu_handler3);
    char *top_menu_title = "顶级菜单展示";
    Menu_Create(top_menu, &top_menu_title, top_menu_option, TOP_MENU_COUNT, TOP_MENU_COUNT);
}

Status Control_Tree_Menu_Init(Menu *control_tree_menu, MenuOption *control_tree_menu_option) {
    MenuOption_create(&control_tree_menu_option[0], 0, "返回顶级目录", control_tree_menu_handler0);
    MenuOption_create(&control_tree_menu_option[1], 1, "插入数值", control_tree_menu_handler1);
    MenuOption_create(&control_tree_menu_option[2], 2, "删除数值", control_tree_menu_handler2);
    MenuOption_create(&control_tree_menu_option[3], 3, "查找数值", control_tree_menu_handler3);
    MenuOption_create(&control_tree_menu_option[4], 4, "打印二叉树", control_tree_menu_handler4);
    MenuOption_create(&control_tree_menu_option[5], 5, "中序遍历", control_tree_menu_handler5);
    MenuOption_create(&control_tree_menu_option[6], 6, "以某值为界限拆分二叉树", control_tree_menu_handler6);
    char *control_tree_menu_title = "单棵平衡二叉树调整菜单";
    Menu_Create(control_tree_menu, &control_tree_menu_title, control_tree_menu_option, CONTROL_TREE_MENU_COUNT, CONTROL_TREE_MENU_COUNT);
}

Status Tree_Menu_Init(Menu *tree_menu, MenuOption *tree_menu_option) {
    MenuOption_create(&tree_menu_option[0], 0, "返回顶级目录", tree_menu_handler0);
    MenuOption_create(&tree_menu_option[1], 1, "查看当前二叉树数量", tree_menu_handler1);
    MenuOption_create(&tree_menu_option[2], 2, "跳转到指定序号平衡二叉树调整菜单", tree_menu_handler2);
    char *tree_menu_title = "选择二叉树进行调整菜单";
    Menu_Create(tree_menu, &tree_menu_title, tree_menu_option, TREE_MENU_COUNT, TREE_MENU_COUNT);
};