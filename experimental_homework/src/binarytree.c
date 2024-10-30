#include<stdio.h>
#include<stdlib.h>
#include"binarytree.h"

Status InitBiTree(BiTree *T) {
	printf("init\n");
	if(*T == NULL) {
		return TRUE;
	}
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	(*T)->data = 0;
	if(*T == NULL) {
		return TRUE;
	}
	return FALSE;
}

Status InitBiTree(BiTree *T);
Status DestoryBiTree(BiTree *T);
Status EmptyBiTree(BiTree T);
int DepthBiTree(BiTree T);
BiTNode* ParentBiTree(BiTree *T);
BiTNode* LeftSiblingBiTree(BiTree T);
BiTNode* RightSiblingBiTree(BiTree T);
Status VisitBiTree(BiTree T);
Status PreOrderTraverseBiTree(BiTree T);
Status InOrderTraverseBiTree(BiTree T);
Status PostOrderTraverseBiTree(BiTree T);
Status LevelOrderTraverseBiTree(BiTree T);