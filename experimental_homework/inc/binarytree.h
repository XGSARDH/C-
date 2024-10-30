#ifndef BINTARYTREE_H
#define BINTARYTREE_H

typedef int BiTElemType;
typedef enum Status {
	FALSE = 0,
	TRUE = 1
} Status;

typedef struct BiTNode {
	BiTElemType data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree; 

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

#endif // BINTARYTREE_H
