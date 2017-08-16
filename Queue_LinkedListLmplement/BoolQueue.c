#include "boolQueue.h"

struct boolQueue
{
	boolQueueNode* head;
	boolQueueNode* tail;
	int size;
};

struct boolQueueNode
{
	boolQueue_Item data;
	boolQueueNode* next;
};

boolQueueNode* boolQueueNode_Create(boolQueue_Item data, boolQueueNode* next)
{
	boolQueueNode* node = (boolQueueNode*)malloc(sizeof(boolQueueNode));
	node->data = data;
	node->next = next;
	return node;
}

boolQueue* boolQueue_Create()
{
	boolQueue* queue = (boolQueue*)malloc(sizeof(boolQueue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void boolQueue_Destroy(boolQueue* queue)
{
	if (queue == NULL) return;

	boolQueueNode* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void boolQueue_EnQueue(boolQueue* queue, boolQueue_Item data)
{
	boolQueueNode* oldTail = queue->tail;
	queue->tail = boolQueueNode_Create(data, NULL);
	if (boolQueue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

boolQueue_Item boolQueue_DeQueue(boolQueue* queue)
{
	if (boolQueue_IsEmpty(queue))
		return 0;

	boolQueue_Item data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (boolQueue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int boolQueue_Size(const boolQueue* queue)
{
	return queue->size;
}

bool boolQueue_IsEmpty(const boolQueue* queue)
{
	return queue->size == 0;
}

void boolQueue_Traverse(const boolQueue* queue, void(*fun)(boolQueue_Item data))
{
	boolQueueNode* node = queue->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}