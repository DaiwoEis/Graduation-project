#include "doubleStack.h"

struct doubleStack
{
	doubleStackNode* head;
	int size;
};

struct doubleStackNode
{
	doubleStack_Item data;
	doubleStackNode* next;
};

doubleStackNode* doubleStackNode_Create(doubleStack_Item data, doubleStackNode* next)
{
	doubleStackNode* node = (doubleStackNode*)malloc(sizeof(doubleStackNode));
	node->data = data;
	node->next = next;
	return node;
}

doubleStack* doubleStack_Create()
{
	doubleStack* stack = (doubleStack*)malloc(sizeof(doubleStack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void doubleStack_Destroy(doubleStack* stack)
{
	if (stack == NULL) return;

	doubleStackNode* head = stack->head;
	while (head != NULL)
	{
		doubleStackNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void doubleStack_Push(doubleStack* stack, doubleStack_Item data)
{
	stack->head = doubleStackNode_Create(data, stack->head);
	stack->size++;
}

doubleStack_Item doubleStack_Pop(doubleStack* stack)
{
	if (doubleStack_IsEmpty(stack)) return 0;

	doubleStackNode* head = stack->head;
	doubleStack_Item data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

doubleStack_Item doubleStack_Peek(doubleStack* stack)
{
	if (doubleStack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool doubleStack_IsEmpty(const doubleStack* stack)
{
	return stack->size == 0;
}

int doubleStack_Size(const doubleStack* stack)
{
	return stack->size;
}

void doubleStack_Traverse(const doubleStack* stack, void(*fun)(doubleStack_Item data))
{
	doubleStackNode* node = stack->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}
