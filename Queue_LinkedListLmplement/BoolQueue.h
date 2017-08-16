#pragma once

#include "QueueBase.h"

typedef bool boolQueue_Item;
typedef struct boolQueue boolQueue;
typedef struct boolQueueNode boolQueueNode;

boolQueue* boolQueue_Create();

void boolQueue_Destroy(boolQueue* queue);

void boolQueue_EnQueue(boolQueue* queue, boolQueue_Item data);

boolQueue_Item boolQueue_DeQueue(boolQueue* queue);

int boolQueue_Size(const boolQueue* queue);

bool boolQueue_IsEmpty(const boolQueue* queue);

void boolQueue_Traverse(const boolQueue* queue, void(*fun)(boolQueue_Item data));