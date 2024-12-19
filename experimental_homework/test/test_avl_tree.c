#include "avl_tree.h"
#include <stdio.h>

void Test_InsertAndDelete();

int main() {
    Test_InsertAndDelete();
    return 0;
}

void Test_InsertAndDelete() {
    AvlTree tree;
    Avl_Init(&tree);

    Avl_Insert(&tree, 1);
    Avl_Insert(&tree, 2);
    Avl_Insert(&tree, 3);
    Avl_Insert(&tree, 4);
    Avl_Insert(&tree, 5);
    Avl_Insert(&tree, 6);
    Avl_Insert(&tree, 7);
    Avl_Insert(&tree, 8);
    Avl_Insert(&tree, 9);

    printf("Avl_InOrderTraverse: \n");
    Avl_InOrderTraverse(tree);
    printf("\n\n");

    Avl_PrintTree(tree);

    Avl_Delete(&tree, 1);
    Avl_Delete(&tree, 3);
    Avl_Delete(&tree, 5);
    Avl_Delete(&tree, 4);
    Avl_Delete(&tree, 7);
    Avl_Delete(&tree, 8);
    Avl_Delete(&tree, 2);
    printf("after delete , Avl_InOrderTraverse: \n");
    Avl_InOrderTraverse(tree);
    printf("\n\n");
    Avl_PrintTree(tree);

    Avl_Destroy(&tree);
}