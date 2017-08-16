#include "Queue.h"

struct Queue
{
	QueueNode* head;
	QueueNode* tail;
	int size;
};

struct QueueNode
{
	Queue_Item data;
	QueueNode* next;
};

QueueNode* QueueNode_Create(char data, QueueNode* next)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
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

	QueueNode* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void Queue_EnQueue(Queue* queue, Queue_Item data)
{
	QueueNode* oldTail = queue->tail;
	queue->tail = QueueNode_Create(data, NULL);
	if (Queue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

Queue_Item Queue_DeQueue(Queue* queue)
{
	if (Queue_IsEmpty(queue))
		return 0;

	char data = queue->head->data;
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

void Queue_Traverse(const Queue* queue, void(*fun)(Queue_Item data))
{
	QueueNode* node = queue->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}