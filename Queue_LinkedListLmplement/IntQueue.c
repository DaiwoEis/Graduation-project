#include "intQueue.h"

struct intQueue
{
	intQueueNode* head;
	intQueueNode* tail;
	int size;
};

struct intQueueNode
{
	intQueue_Item data;
	intQueueNode* next;
};

intQueueNode* intQueueNode_Create(intQueue_Item data, intQueueNode* next)
{
	intQueueNode* node = (intQueueNode*)malloc(sizeof(intQueueNode));
	node->data = data;
	node->next = next;
	return node;
}

intQueue* intQueue_Create()
{
	intQueue* queue = (intQueue*)malloc(sizeof(intQueue));
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void intQueue_Destroy(intQueue* queue)
{
	if (queue == NULL) return;

	intQueueNode* head = queue->head;
	while (head != NULL)
	{
		queue->head = queue->head->next;
		free(head);
		head = queue->head;
	}
	free(queue);
}

void intQueue_EnQueue(intQueue* queue, intQueue_Item data)
{
	intQueueNode* oldTail = queue->tail;
	queue->tail = intQueueNode_Create(data, NULL);
	if (intQueue_IsEmpty(queue))
		queue->head = queue->tail;
	else
		oldTail->next = queue->tail;
	queue->size++;
}

intQueue_Item intQueue_DeQueue(intQueue* queue)
{
	if (intQueue_IsEmpty(queue))
		return 0;

	intQueue_Item data = queue->head->data;
	queue->head = queue->head->next;
	queue->size--;
	if (intQueue_IsEmpty(queue))
		queue->tail = NULL;
	return data;
}

int intQueue_Size(const intQueue* queue)
{
	return queue->size;
}

bool intQueue_IsEmpty(const intQueue* queue)
{
	return queue->size == 0;
}

void intQueue_Traverse(const intQueue* queue, void(*fun)(intQueue_Item data))
{
	intQueueNode* node = queue->head;
	while (node != NULL)
	{
		fun(node->data);
		node = node->next;
	}
}