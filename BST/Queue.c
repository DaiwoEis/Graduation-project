#include "Queue.h"

typedef struct Node Node;

struct Queue
{
	Node* head;
	Node* tail;
	int size;
};

struct Node
{
	Key data;
	Node* next;
};

Node* QueueNode_Create(Key data, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = next;
	return node;
}

Queue* Queue_Create()
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void Queue_Destroy(Queue* queue)
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

void Queue_EnQueue(Queue* queue, Key data)
{
	Node* oldTail = queue->tail;
	queue->tail = QueueNode_Create(data, NULL);
	if (Queue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

Key Queue_DeQueue(Queue* queue)
{
	if (Queue_IsEmpty(queue))
		return 0;

	Key data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (Queue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int Queue_Size(const Queue* queue)
{
	return queue->size;
}

bool Queue_IsEmpty(const Queue* queue)
{
	return queue->size == 0;
}

void Queue_Traverse(const Queue* queue, void(*pfun)(Key data))
{
	Node* node = queue->head;
	while (node != NULL)
	{
		pfun(node->data);
		node = node->next;
	}
}