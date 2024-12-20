#include "avl_tree.h"
#include <stdio.h>

void Test_InsertAndDelete();
void Test_Split();
void Test_Copy();
void Test_Merge();

int main()
{
    // Test_InsertAndDelete();
    // Test_Split();
    // Test_Copy();
    Test_Merge();
    return 0;
}

void Test_InsertAndDelete()
{
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

    Status status;
    status = STATUS_TRUE;
    status = Avl_Search(&tree, 1);
    if (status == STATUS_TRUE)
    {
        printf("find 1\n");
    }
    else if (status == STATUS_OVERFLOW)
    {
        printf("not find 1\n");
    }
    else
    {
        printf("ERROR\n");
    }

    status = STATUS_TRUE;
    status = Avl_Search(&tree, 6);
    if (status == STATUS_TRUE)
    {
        printf("find 1\n");
    }
    else if (status == STATUS_OVERFLOW)
    {
        printf("not find 1\n");
    }
    else
    {
        printf("ERROR\n");
    }

    Avl_Destroy(&tree);
}

void Test_Split()
{
    AvlTree tree = NULL;
    AvlTree small_tree = NULL;
    AvlTree big_tree = NULL;
    Avl_Init(&tree);

    for (int i = 0; i <= 20; i++)
    {
        Avl_Insert(&tree, i);
    }

    Avl_Split(&tree, 10, &small_tree, &big_tree);

    printf("\norigin_tree\n");
    Avl_PrintTree(tree);
    printf("\nsmall_tree\n");
    Avl_PrintTree(small_tree);
    printf("\nbig_tree\n");
    Avl_PrintTree(big_tree);
}

void Test_Copy()
{
    AvlTree tree = NULL;
    AvlTree purpose_tree = NULL;
    Avl_Init(&tree);

    for (int i = 0; i <= 10; i++)
    {
        Avl_Insert(&tree, i);
    }

    Avl_Copy(&tree, &purpose_tree);

    printf("\ntree\n");
    Avl_PrintTree(tree);
    printf("\npurpose_tree\n");
    Avl_PrintTree(purpose_tree);
}

void Test_Merge()
{
    AvlTree tree1 = NULL;
    AvlTree tree2 = NULL;
    AvlTree purpose_tree = NULL;
    Avl_Init(&tree1);
    Avl_Init(&tree2);

    for (int i = 0; i < 10; i++)
    {
        Avl_Insert(&tree1, i);
    }
    for (int i = 10; i < 20; i++)
    {
        Avl_Insert(&tree2, i);
    }

    Avl_Merge(&tree1, &tree2, &purpose_tree);

    printf("\n tree1: \n");
    Avl_PrintTree(tree1);
    printf("\n tree2: \n");
    Avl_PrintTree(tree2);
    printf("\n purpose_tree: \n");
    Avl_PrintTree(purpose_tree);
}