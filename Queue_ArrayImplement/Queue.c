#include "Queue.h"

struct Queue
{
	Queue_Item* datas;
	int head;
	int tail;
	int size;
	int dataCapacity;
};

bool ArrayQueue_IsFull(const Queue* queue);

void ArrayQueue_Resize(Queue* queue, int size);

Queue* Queue_Create()
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = queue->tail = queue->size = 0;
	queue->dataCapacity = INIT_CAPACITY;
	queue->datas = (Queue_Item*)calloc(INIT_CAPACITY, sizeof(Queue_Item));
	return queue;
}

void Queue_Destroy(Queue* queue)
{
	if (queue != NULL)
	{
		if (queue->datas != NULL)
		{
			free(queue->datas);
			queue->datas = NULL;
		}

		free(queue);
	}
}

void Queue_EnQueue(Queue* queue, Queue_Item data)
{
	if (ArrayQueue_IsFull(queue))
		ArrayQueue_Resize(queue, queue->dataCapacity * 2);

	queue->datas[queue->tail++] = data;
	if (queue->tail == queue->dataCapacity)
		queue->tail = 0;
	queue->size++;
}

Queue_Item Queue_DeQueue(Queue* queue)
{
	if (Queue_IsEmpty(queue))
		return 0;

	Queue_Item data = queue->datas[queue->head];
	queue->datas[queue->head] = 0;
	queue->head++;
	if (queue->head == queue->dataCapacity)
		queue->head = 0;
	queue->size--;
	if (queue->size > 0 && queue->size <= queue->dataCapacity / 4)
		ArrayQueue_Resize(queue, queue->dataCapacity / 2);
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

void Queue_Traverse(const Queue* queue, void(*pfun)(Queue_Item data))
{
	for (int i = 0; i < queue->size; ++i)
	{
		pfun(queue->datas[(queue->head + i) % queue->dataCapacity]);
	}
}

bool ArrayQueue_IsFull(const Queue* queue)
{
	return queue->size == queue->dataCapacity;
}

void ArrayQueue_Resize(Queue* queue, int size)
{
	Queue_Item* newDatas = (Queue_Item*)calloc(size, sizeof(Queue_Item));
	for (int i = 0; i < queue->size; ++i)
	{
		newDatas[i] = queue->datas[(queue->head + i) % queue->dataCapacity];
	}

	if (queue->datas != NULL)
		free(queue->datas);

	queue->datas = newDatas;
	queue->head = 0;
	queue->tail = queue->size;
	queue->dataCapacity = size;
}