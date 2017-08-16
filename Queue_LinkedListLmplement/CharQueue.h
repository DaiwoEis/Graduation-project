#pragma once

#include "QueueBase.h"

typedef char charQueue_Item;
typedef struct charQueue charQueue;
typedef struct charQueueNode charQueueNode;

charQueue* charQueue_Create();

void charQueue_Destroy(charQueue* queue);

void charQueue_EnQueue(charQueue* queue, charQueue_Item data);

charQueue_Item charQueue_DeQueue(charQueue* queue);

int charQueue_Size(const charQueue* queue);

bool charQueue_IsEmpty(const charQueue* queue);

void charQueue_Traverse(const charQueue* queue, void(*fun)(charQueue_Item data));