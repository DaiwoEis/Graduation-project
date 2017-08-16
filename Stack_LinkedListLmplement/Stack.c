#include "Stack.h"

struct Stack
{
	StackNode* head;
	int size;
};

struct StackNode
{
	Stack_Item data;
	StackNode* next;
};

StackNode* StackNode_Create(Stack_Item data, StackNode* next)
{
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->data = data;
	node->next = next;
	return node;
}

Stack* Stack_Create()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void Stack_Destroy(Stack* stack)
{
	if (stack == NULL) return;

	StackNode* head = stack->head;
	while (head != NULL)
	{
		StackNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void Stack_Push(Stack* stack, Stack_Item data)
{
	stack->head = StackNode_Create(data, stack->head);
	stack->size++;
}

Stack_Item Stack_Pop(Stack* stack)
{
	if (Stack_IsEmpty(stack)) return 0;

	StackNode* head = stack->head;
	Stack_Item data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

Stack_Item Stack_Peek(Stack* stack)
{
	if (Stack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool Stack_IsEmpty(const Stack* stack)
{
	return stack->size == 0;
}

int Stack_Size(const Stack* stack)
{
	return stack->size;
}

void Stack_Traverse(const Stack* stack, void(*fun)(Stack_Item data))
{
	StackNode* node = stack->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}
