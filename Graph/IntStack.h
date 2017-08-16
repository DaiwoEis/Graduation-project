#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "IntegerArray.h"

typedef struct IntStack IntStack;

IntStack* IntStack_Create();

void IntStack_Delete(IntStack* stack);

void IntStack_Push(IntStack* stack, int data);

int IntStack_Pop(IntStack* stack);

int IntStack_Peek(IntStack* stack);

bool IntStack_IsEmpty(const IntStack* stack);

int IntStack_Size(const IntStack* stack);

void IntStack_Traverse(const IntStack* stack, void(*pfun)(int data));

Array(int)* IntStack_ToArray(const IntStack* stack);