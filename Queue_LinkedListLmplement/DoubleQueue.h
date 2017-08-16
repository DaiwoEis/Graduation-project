#pragma once

#include "QueueBase.h"

typedef double doubleQueue_Item;
typedef struct doubleQueue doubleQueue;
typedef struct doubleQueueNode doubleQueueNode;

doubleQueue* doubleQueue_Create();

void doubleQueue_Destroy(doubleQueue* queue);

void doubleQueue_EnQueue(doubleQueue* queue, doubleQueue_Item data);

doubleQueue_Item doubleQueue_DeQueue(doubleQueue* queue);

int doubleQueue_Size(const doubleQueue* queue);

bool doubleQueue_IsEmpty(const doubleQueue* queue);

void doubleQueue_Traverse(const doubleQueue* queue, void(*fun)(doubleQueue_Item data));