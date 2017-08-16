#include "IntQueue.h"

typedef struct Node Node;

struct IntQueue
{
	Node* head;
	Node* tail;
	int size;
};

struct Node
{
	int data;
	Node* next;
};

Node* IntQueueNode_Create(int data, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = next;
	return node;
}

IntQueue* IntQueue_Create()
{
	IntQueue* queue = (IntQueue*)malloc(sizeof(IntQueue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void IntQueue_Delete(IntQueue* queue)
{
	if (queue == NULL) return;

	Node* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void IntQueue_EnQueue(IntQueue* queue, int data)
{
	Node* oldTail = queue->tail;
	queue->tail = IntQueueNode_Create(data, NULL);
	if (IntQueue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

int IntQueue_DeQueue(IntQueue* queue)
{
	if (IntQueue_IsEmpty(queue))
		return 0;

	int data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (IntQueue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int IntQueue_Size(const IntQueue* queue)
{
	return queue->size;
}

bool IntQueue_IsEmpty(const IntQueue* queue)
{
	return queue->size == 0;
}

void IntQueue_Traverse(const IntQueue* queue, void(*pfun)(int data))
{
	Node* node = queue->head;
	while (node != NULL)
	{
		pfun(node->data);
		node = node->next;
	}
}

Array(int)* IntQueue_ToArray(const IntQueue* queue)
{
	Array(int)* arr = Array_Create(int)(queue->size);
	int count = 0;
	for (Node* node = queue->head; node != NULL; node = node->next)
	{
		Array_Set(int)(arr, count++, node->data);
	}
	return arr;
}
