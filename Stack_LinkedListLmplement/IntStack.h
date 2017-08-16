#pragma once

#include "StackBase.h"

typedef int intStack_Item;
typedef struct intStack intStack;
typedef struct intStackNode intStackNode;

intStack* intStack_Create();

void intStack_Destroy(intStack* stack);

void intStack_Push(intStack* stack, intStack_Item data);

intStack_Item intStack_Pop(intStack* stack);

intStack_Item intStack_Peek(intStack* stack);

bool intStack_IsEmpty(const intStack* stack);

int intStack_Size(const intStack* stack);

void intStack_Traverse(const intStack* stack, void(*fun)(intStack_Item data));