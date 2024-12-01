#include "avl_binary_tree.h"
#include "link_stack.h"
#include "status_enum.h"
#include <stdio.h>
#include <stdlib.h>

void testAvl();
void testStack();

int main()
{
    testAvl();
    // testStack();
    return 0;
}

void testAvl()
{
    printf("Test Avl;\n");
    AvlBiTree curr = NULL;
    printf("初始化是否成功:%d\n", initAvlBiTNode(&curr, 10));
    printf("打印初始化节点的值:") && visitAvl(curr) && printf("\n");
    printf("删除是否成功:%d\n", destoryAvl(&curr));
    // InOrderTraverseAvl(curr, visitAvl);
}