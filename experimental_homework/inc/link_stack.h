#ifndef LINK_STACK_H
#define LINK_STACK_H

#include "status_enum.h"

typedef int StackElemType;

typedef struct StackNode
{
	StackElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;

/**
 *  @name        : Status initLStack(LinkStack *s)
 *	@description : Initialize stack
 *	@param		 : LinkStack *s
 *	@return		 : Status
 *  @notice      : None
 */
Status initLStack(LinkStack *s);

/**
 *  @name        : Status isEmptyLStack(LinkStack *s)
 *	@description : Is the stack break empty
 *	@param		 : LinkStack *s
 *	@return		 : Status
 *  @notice      : SUCCESS is empty, ERROR is non empty
 */
Status isEmptyLStack(LinkStack *s);

/**
 *  @name        : Status getTopLStack(LinkStack *s,StackElemType *e)
 *	@description : Get the top element of the stack
 *	@param		 : LinkStack *s,StackElemType *e
 *	@return		 : Status
 *  @notice      : None
 */
Status getTopLStack(LinkStack *s,StackElemType *e);

/**
 *  @name        : Status clearLStack(LinkStack *s)
 *	@description : Clear stack
 *	@param		 : LinkStack *s
 *	@return		 : Status
 *  @notice      : None
 */
Status clearLStack(LinkStack *s);

/**
 *  @name        : Status destroyLStack(LinkStack *s
 *	@description : Destroy stack
 *	@param		 : LinkStack *s
 *	@return		 : Status
 *  @notice      : None
 */
Status destroyLStack(LinkStack *s);

/**
 *  @name        : Status LStackLength(LinkStack *s,int *length)
 *	@description : Detect stack length
 *	@param		 : LinkStack *s,StackElemType data
 *	@return		 : Status
 *  @notice      : None
 */
Status LStackLength(LinkStack *s,int *length);

/**
 *  @name        : Status pushLStack(LinkStack *s,StackElemType data)
 *	@description : push
 *	@param		 : LinkStack *s,StackElemType data
 *	@return		 : Status
 *  @notice      : None
 */
Status pushLStack(LinkStack *s,StackElemType data);//ÈëÕ»

/**
 *  @name        : Status popLStack(LinkStack *s,StackElemType *data)
 *	@description : pop
 *	@param		 : LinkStack *s,StackElemType *data
 *	@return		 : Status
 *  @notice      : None
 */
Status popLStack(LinkStack *s,StackElemType *data);

/**
 *  @name        : void PrintStackElemType(StackElemType e)
 *	@description : print the StackElemType
 *	@param		 : StackElemType e
 *	@return		 : None
 *  @notice      : Self written
 */
void PrintStackElemType(StackElemType e);

/**
 *  @name        : void ScanfStackElemType(StackElemType *e)
 *	@description : scanf the StackElemType
 *	@param		 : StackElemType *e
 *	@return		 : Status
 *  @notice      : Self written
 */
Status ScanfStackElemType(StackElemType* e);

/**
 *  @name        : Status MakeEqualData(StackElemType* origin, StackElemType* Result);
 *	@description : Make the value of ElemData equal to the value of another ElemDatas
 *	@param		 : StackElemType* origin, StackElemType* result
 *	@return		 : Status
 *  @notice      : Self written
 */
Status MakeEqualData(StackElemType* origin, StackElemType* result);

/**
 *  @name        : Status MakeEqualData(StackElemType* origin, StackElemType* Result);
 *	@description : Check if two StackElemTypes are equal
 *	@param		 : StackElemType* origin, StackElemType* result
 *	@return		 : Status
 *  @notice      : Self written, SUCCESS is equal.ERROR is not equal.
 */
Status IsMakeEqualData(StackElemType* origin, StackElemType* result);

/**
 *  @name        : Status InitList_Node(Node** L)
 *    @description : ³õÊ¼»¯Á´±í½Úµã
 *    @param         Node** L
 *  @notice      : None
 */
Status InitList_StackNode(StackNode** L);

#endif // LINK_STACK_H