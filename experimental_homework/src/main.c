#include <stdio.h>
#include <stdlib.h>
#include "status_enum.h"
#include "avl_binary_tree.h"
#include "link_stack.h"

void testAVL();
void testStack();

int main()
{
	testAVL();
	// testStack();
	return 0;
}

void testAVL() {
	printf("Test avl;\n");
	avlBiTree curr = NULL;
	printf("初始化是否成功:%d\n", initAVL(&curr, 10));
	printf("打印初始化节点的值:") && visitAVL(curr) && printf("\n");
	printf("删除是否成功:%d\n", destoryAVL(&curr));
	// InOrderTraverseAVL(curr, visitAVL);
}