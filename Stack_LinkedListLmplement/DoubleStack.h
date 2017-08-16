#pragma once

#include "StackBase.h"

typedef double doubleStack_Item;
typedef struct doubleStack doubleStack;
typedef struct doubleStackNode doubleStackNode;

doubleStack* doubleStack_Create();

void doubleStack_Destroy(doubleStack* stack);

void doubleStack_Push(doubleStack* stack, doubleStack_Item data);

doubleStack_Item doubleStack_Pop(doubleStack* stack);

doubleStack_Item doubleStack_Peek(doubleStack* stack);

bool doubleStack_IsEmpty(const doubleStack* stack);

int doubleStack_Size(const doubleStack* stack);

void doubleStack_Traverse(const doubleStack* stack, void(*fun)(doubleStack_Item data));