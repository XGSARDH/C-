#include <stdio.h>
#include <stdlib.h>
#include "avl_binary_tree.h"
#include "link_stack.h"

int test1();
AvlBiTree allBinaryTree();
int testRotate();
int testRRotate(AvlBiTree *p);
int testLRotate(AvlBiTree *p);

int main()
{
    int main_output = 0;
    // main_output = test1();
    main_output = testRotate();
    return main_output;
}

int test1() {
    AvlBiTree root = NULL;
    if (!initAvl(&root)) {
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

AvlBiTree allBinaryTree() {
    AvlBiTree root = NULL;
    if (!initAvl(&root)) {
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

int testRotate() {
    int output = 0;

    AvlBiTree root = allBinaryTree();
    printf("旋转前\n") && printAvl(root) && printf("\n");

    output = testLRotate(&root);
    // output = testRRotate(&root);

    printf("旋转后\n") && printAvl(root) && printf("\n");

    destoryAvl(&root);
    return output;
}

int testRRotate(AvlBiTree *p) {
    rRotate(p);
}

int testLRotate(AvlBiTree *p) {
    lRotate(p);
}