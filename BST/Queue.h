#pragma once

#include "BaseBST.h"

typedef struct Queue Queue;

Queue* Queue_Create();

void Queue_Destroy(Queue* queue);

void Queue_EnQueue(Queue* queue, Key data);

Key Queue_DeQueue(Queue* queue);

int Queue_Size(const Queue* queue);

bool Queue_IsEmpty(const Queue* queue);

void Queue_Traverse(const Queue* queue, void(*pfun)(Key data));