#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

int test1();

int main()
{
    int main_output = 0;
    main_output = test1();
    return 0;
}

int test1() {
    AvlBiTree root = NULL;
    if (!initAvl(&root, 1)) {
        printf("initAvl error\n");
        return 0;
    }
    insertAvl(&root, 3);
    insertAvl(&root, 2);
    insertAvl(&root, 4);
    insertAvl(&root, 0);
    insertAvl(&root, -1);
    insertAvl(&root, 10);
    insertAvl(&root, 11);
    insertAvl(&root, 5);
    insertAvl(&root, 6);
    insertAvl(&root, 7);
    insertAvl(&root, 9);
    insertAvl(&root, 8);
    printf("inOrderTraverseAvl:\n") && inOrderTraverseAvl(root) && printf("\n");
    printf("printAvl:\n") && printAvl(root) && printf("\n");
    return 0;
}