#include "avl_binary_tree.h"
#include "link_stack.h"
#include <stdio.h>
#include <stdlib.h>

int test1();
AvlBiTree allBinaryTree();
int testRotate();
int testRRotate(AvlBiTree *p);
int testLRotate(AvlBiTree *p);

int main()
{
    int main_output = 0;
    main_output = test1();
    // main_output = testRotate();
    return main_output;
}

int test1()
{
    AvlBiTree root = NULL;
    if (!initAvl(&root))
    {
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
    insertAvl(&root, 13);
    insertAvl(&root, 12);
    insertAvl(&root, 100);
    insertAvl(&root, 87);
    insertAvl(&root, 90);
    // deleteAvl(&root, 11);
    // deleteAvl(&root, 13);
    // deleteAvl(&root, 90);
    printf("beforeprintAvl:\n") && printAvl(root) && printf("\n");
    deleteAvl(&root, 87);
    // printf("inOrderTraverseAvl:\n") && inOrderTraverseAvl(root) && printf("\n");
    printf("afterprintAvl:\n") && printAvl(root) && printf("\n");
    deleteAvl(&root, -1);
    deleteAvl(&root, 2);
    deleteAvl(&root, 4);
    deleteAvl(&root, 7);
    deleteAvl(&root, 9);
    printf("afterprintAvl:\n") && printAvl(root) && printf("\n");
    return 0;
}

AvlBiTree allBinaryTree()
{
    AvlBiTree root = NULL;
    if (!initAvl(&root))
    {
        printf("initAvl error\n");
        return 0;
    }
    insertAvl(&root, 4);

    insertAvl(&root, 2);
    insertAvl(&root, 6);

    insertAvl(&root, 1);
    insertAvl(&root, 3);
    insertAvl(&root, 5);
    insertAvl(&root, 7);
    return root;
}

int testRotate()
{
    int output = 0;

    AvlBiTree root = allBinaryTree();
    printf("起始state\n") && printAvl(root) && printf("\n");
    insertAvl(&root, 8);
    insertAvl(&root, 9);
    // updateBalanceFactor(root);
    // output = testLRotate(&root);
    // printf("1state\n") && printAvl(root) && printf("\n");
    // updateBalanceFactor(root);
    // output = testRRotate(&root);
    // printf("2state\n") && printAvl(root) && printf("\n");
    // updateBalanceFactor(root);

    // printf("end state\n") && printAvl(root) && printf("\n");
    printf("End State\n") && printAvl(root) && printf("\n");
    destoryAvl(&root);
    return output;
}

int testRRotate(AvlBiTree *p)
{
    rRotate(p);
}

int testLRotate(AvlBiTree *p)
{
    lRotate(p);
}