#include "charStack.h"

struct charStack
{
	charStackNode* head;
	int size;
};

struct charStackNode
{
	charStack_Item data;
	charStackNode* next;
};

charStackNode* charStackNode_Create(charStack_Item data, charStackNode* next)
{
	charStackNode* node = (charStackNode*)malloc(sizeof(charStackNode));
	node->data = data;
	node->next = next;
	return node;
}

charStack* charStack_Create()
{
	charStack* stack = (charStack*)malloc(sizeof(charStack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void charStack_Destroy(charStack* stack)
{
	if (stack == NULL) return;

	charStackNode* head = stack->head;
	while (head != NULL)
	{
		charStackNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void charStack_Push(charStack* stack, charStack_Item data)
{
	stack->head = charStackNode_Create(data, stack->head);
	stack->size++;
}

charStack_Item charStack_Pop(charStack* stack)
{
	if (charStack_IsEmpty(stack)) return 0;

	charStackNode* head = stack->head;
	charStack_Item data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

charStack_Item charStack_Peek(charStack* stack)
{
	if (charStack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool charStack_IsEmpty(const charStack* stack)
{
	return stack->size == 0;
}

int charStack_Size(const charStack* stack)
{
	return stack->size;
}

void charStack_Traverse(const charStack* stack, void(*fun)(charStack_Item data))
{
	charStackNode* node = stack->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}
