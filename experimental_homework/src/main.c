#include <stdio.h>
#include <stdlib.h>
#include "status_enum.h"
#include "avl_binary_tree.h"
#include "link_stack.h"

void testAVL();
void testStack();

int main()
{
	// testAVL();
	// testStack();
	return 0;
}

void testAVL() {
	printf("Test avl;\n");
	avlBiTree curr = NULL;
	printf("%d\n", initAVL(&curr));
	visitAVL(curr);
	printf("\n");
	printf("%d\n", destoryAVL(&curr));
}

void testStack() {
	printf("Test avlstack;\n");
	LinkStack stack;
	initLStack(&stack);
	StackElemType temp = NULL;
	initStackElemType(&temp);
	PrintStackElemType(temp);
	printf("\n");
	pushLStack(&stack, temp);
	popLStack(&stack, &temp);
	PrintStackElemType(temp);
	printf("\n");
	destroyLStack(&stack);
}