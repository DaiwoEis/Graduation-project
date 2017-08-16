#include "boolStack.h"

struct boolStack
{
	boolStackNode* head;
	int size;
};

struct boolStackNode
{
	boolStack_Item data;
	boolStackNode* next;
};

boolStackNode* boolStackNode_Create(boolStack_Item data, boolStackNode* next)
{
	boolStackNode* node = (boolStackNode*)malloc(sizeof(boolStackNode));
	node->data = data;
	node->next = next;
	return node;
}

boolStack* boolStack_Create()
{
	boolStack* stack = (boolStack*)malloc(sizeof(boolStack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void boolStack_Destroy(boolStack* stack)
{
	if (stack == NULL) return;

	boolStackNode* head = stack->head;
	while (head != NULL)
	{
		boolStackNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void boolStack_Push(boolStack* stack, boolStack_Item data)
{
	stack->head = boolStackNode_Create(data, stack->head);
	stack->size++;
}

boolStack_Item boolStack_Pop(boolStack* stack)
{
	if (boolStack_IsEmpty(stack)) return 0;

	boolStackNode* head = stack->head;
	boolStack_Item data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

boolStack_Item boolStack_Peek(boolStack* stack)
{
	if (boolStack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool boolStack_IsEmpty(const boolStack* stack)
{
	return stack->size == 0;
}

int boolStack_Size(const boolStack* stack)
{
	return stack->size;
}

void boolStack_Traverse(const boolStack* stack, void(*fun)(boolStack_Item data))
{
	boolStackNode* node = stack->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}
