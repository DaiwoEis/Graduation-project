#include "IntStack.h"

typedef struct Node Node;

struct IntStack
{
	Node* head;
	int size;
};

struct Node
{
	int data;
	Node* next;
};

Node* IntStackNode_Create(int data, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = next;
	return node;
}

IntStack* IntStack_Create()
{
	IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

void IntStack_Delete(IntStack* stack)
{
	if (stack == NULL) return;

	Node* head = stack->head;
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		free(temp);
	}
	free(stack);
}

void IntStack_Push(IntStack* stack, int data)
{
	stack->head = IntStackNode_Create(data, stack->head);
	stack->size++;
}

int IntStack_Pop(IntStack* stack)
{
	if (IntStack_IsEmpty(stack)) return 0;

	Node* head = stack->head;
	int data = head->data;
	stack->head = head->next;
	stack->size--;
	if (head != NULL)
		free(head);
	return data;
}

int IntStack_Peek(IntStack* stack)
{
	if (IntStack_IsEmpty(stack)) return 0;

	return stack->head->data;
}

bool IntStack_IsEmpty(const IntStack* stack)
{
	return stack->size == 0;
}

int IntStack_Size(const IntStack* stack)
{
	return stack->size;
}

void IntStack_Traverse(const IntStack* stack, void(*pfun)(int data))
{
	Node* node = stack->head;
	while (node != NULL)
	{
		pfun(node->data);
		node = node->next;
	}
}

Array(int)* IntStack_ToArray(const IntStack* stack)
{
	Array(int)* arr = Array_Create(int)(stack->size);
	int count = 0;
	for (Node* node = stack->head; node != NULL; node = node->next)
	{
		Array_Set(int)(arr, count++, node->data);
	}
	return arr;
}
