#include "charQueue.h"

struct charQueue
{
	charQueueNode* head;
	charQueueNode* tail;
	int size;
};

struct charQueueNode
{
	charQueue_Item data;
	charQueueNode* next;
};

charQueueNode* charQueueNode_Create(charQueue_Item data, charQueueNode* next)
{
	charQueueNode* node = (charQueueNode*)malloc(sizeof(charQueueNode));
	node->data = data;
	node->next = next;
	return node;
}

charQueue* charQueue_Create()
{
	charQueue* queue = (charQueue*)malloc(sizeof(charQueue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void charQueue_Destroy(charQueue* queue)
{
	if (queue == NULL) return;

	charQueueNode* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void charQueue_EnQueue(charQueue* queue, charQueue_Item data)
{
	charQueueNode* oldTail = queue->tail;
	queue->tail = charQueueNode_Create(data, NULL);
	if (charQueue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

charQueue_Item charQueue_DeQueue(charQueue* queue)
{
	if (charQueue_IsEmpty(queue))
		return 0;

	charQueue_Item data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (charQueue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int charQueue_Size(const charQueue* queue)
{
	return queue->size;
}

bool charQueue_IsEmpty(const charQueue* queue)
{
	return queue->size == 0;
}

void charQueue_Traverse(const charQueue* queue, void(*fun)(charQueue_Item data))
{
	charQueueNode* node = queue->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}