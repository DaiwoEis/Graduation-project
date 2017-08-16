#pragma once

#include "QueueBase.h"

typedef int intQueue_Item;
typedef struct intQueue intQueue;
typedef struct intQueueNode intQueueNode;

intQueue* intQueue_Create();

void intQueue_Destroy(intQueue* queue);

void intQueue_EnQueue(intQueue* queue, intQueue_Item data);

intQueue_Item intQueue_DeQueue(intQueue* queue);

int intQueue_Size(const intQueue* queue);

bool intQueue_IsEmpty(const intQueue* queue);

void intQueue_Traverse(const intQueue* queue, void(*fun)(intQueue_Item data));