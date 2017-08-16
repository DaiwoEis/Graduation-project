#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "IntegerArray.h"

typedef struct IntQueue IntQueue;

IntQueue* IntQueue_Create();

void IntQueue_Delete(IntQueue* queue);

void IntQueue_EnQueue(IntQueue* queue, int data);

int IntQueue_DeQueue(IntQueue* queue);

int IntQueue_Size(const IntQueue* queue);

bool IntQueue_IsEmpty(const IntQueue* queue);

void IntQueue_Traverse(const IntQueue* queue, void(*pfun)(int data));

Array(int)* IntQueue_ToArray(const IntQueue* queue);