#pragma once

#include "QueueBase.h"

typedef int Queue_Item;
typedef struct Queue Queue;

const static int INIT_CAPACITY = 7;

Queue* Queue_Create();

void Queue_Destroy(Queue* queue);

void Queue_EnQueue(Queue* queue, Queue_Item data);

Queue_Item Queue_DeQueue(Queue* queue);

int Queue_Size(const Queue* queue);

bool Queue_IsEmpty(const Queue* queue);

void Queue_Traverse(const Queue* queue, void(*pfun)(Queue_Item data));