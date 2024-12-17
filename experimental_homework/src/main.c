#include "avl_binary_tree.h"
#include "link_stack.h"
#include <stdio.h>

void testAvl();

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
    printf("Is initialization successful:%d\n", initAvlBiTNode(&curr, 10));
    printf("Print the value of the initialization node:") && visitAvl(curr) && printf("\n");
    printf("Was the deletion successful:%d\n", destoryAvl(&curr));
    // InOrderTraverseAvl(curr, visitAvl);
}