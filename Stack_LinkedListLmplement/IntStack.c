#include "intStack.h"

struct intStack
{
	intStackNode* head;
	int size;
};

struct intStackNode
{
	intStack_Item data;
	intStackNode* next;
};

intStackNode* intStackNode_Create(intStack_Item data, intStackNode* next)
{
	intStackNode* node = (intStackNode*)malloc(sizeof(intStackNode));
	node->data = data;
	node->next = next;
	return node;
}

intStack* intStack_Create()
{
	intStack* stack = (intStack*)malloc(sizeof(intStack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void intStack_Destroy(intStack* stack)
{
	if (stack == NULL) return;

	intStackNode* head = stack->head;
	while (head != NULL)
	{
		intStackNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void intStack_Push(intStack* stack, intStack_Item data)
{
	stack->head = intStackNode_Create(data, stack->head);
	stack->size++;
}

intStack_Item intStack_Pop(intStack* stack)
{
	if (intStack_IsEmpty(stack)) return 0;

	intStackNode* head = stack->head;
	intStack_Item data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

intStack_Item intStack_Peek(intStack* stack)
{
	if (intStack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool intStack_IsEmpty(const intStack* stack)
{
	return stack->size == 0;
}

int intStack_Size(const intStack* stack)
{
	return stack->size;
}

void intStack_Traverse(const intStack* stack, void(*fun)(intStack_Item data))
{
	intStackNode* node = stack->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}
