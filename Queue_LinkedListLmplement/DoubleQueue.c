#include "doubleQueue.h"

struct doubleQueue
{
	doubleQueueNode* head;
	doubleQueueNode* tail;
	int size;
};

struct doubleQueueNode
{
	doubleQueue_Item data;
	doubleQueueNode* next;
};

doubleQueueNode* doubleQueueNode_Create(doubleQueue_Item data, doubleQueueNode* next)
{
	doubleQueueNode* node = (doubleQueueNode*)malloc(sizeof(doubleQueueNode));
	node->data = data;
	node->next = next;
	return node;
}

doubleQueue* doubleQueue_Create()
{
	doubleQueue* queue = (doubleQueue*)malloc(sizeof(doubleQueue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void doubleQueue_Destroy(doubleQueue* queue)
{
	if (queue == NULL) return;

	doubleQueueNode* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void doubleQueue_EnQueue(doubleQueue* queue, doubleQueue_Item data)
{
	doubleQueueNode* oldTail = queue->tail;
	queue->tail = doubleQueueNode_Create(data, NULL);
	if (doubleQueue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

doubleQueue_Item doubleQueue_DeQueue(doubleQueue* queue)
{
	if (doubleQueue_IsEmpty(queue))
		return 0;

	doubleQueue_Item data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (doubleQueue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int doubleQueue_Size(const doubleQueue* queue)
{
	return queue->size;
}

bool doubleQueue_IsEmpty(const doubleQueue* queue)
{
	return queue->size == 0;
}

void doubleQueue_Traverse(const doubleQueue* queue, void(*fun)(doubleQueue_Item data))
{
	doubleQueueNode* node = queue->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}