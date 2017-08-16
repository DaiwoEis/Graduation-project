#include "IntVector.h"
#include "IntegerArray.c"

typedef struct Node Node;

struct IntVector
{
	Node* head;
	int size;
};

struct Node
{
	int data;
	Node* next;
};

Node* IntVectorNode_Create(int data, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = next;
	return node;
}

IntVector* IntVector_Create()
{
	IntVector* vector = (IntVector*)malloc(sizeof(IntVector));
	vector->size = 0;
	vector->head = NULL;
	return vector;
}

void IntVector_Delete(IntVector* vector)
{
	if (vector == NULL) return;

	Node* head = vector->head;
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		free(temp);
	}
	free(vector);
}

void IntVector_Add(IntVector* vector, int data)
{
	vector->head = IntVectorNode_Create(data, vector->head);
	vector->size++;
}


bool IntVector_IsEmpty(const IntVector* vector)
{
	return vector->size == 0;
}

int IntVector_Size(const IntVector* vector)
{
	return vector->size;
}

void IntVector_Traverse(const IntVector* vector, void(*pfun)(int data))
{
	Node* node = vector->head;
	while (node != NULL)
	{
		pfun(node->data);
		node = node->next;
	}
}

Array(int)* IntVector_ToArray(const IntVector* vector)
{
	Array(int)* arr = Array_Create(int)(IntVector_Size(vector));
	int i = 0;
	for (Node* node = vector->head; node != NULL; node = node->next)
	{
		Array_Set(int)(arr, i++, node->data);
	}
	return arr;
}