#pragma once

#include "StackBase.h"

typedef char charStack_Item;
typedef struct charStack charStack;
typedef struct charStackNode charStackNode;

charStack* charStack_Create();

void charStack_Destroy(charStack* stack);

void charStack_Push(charStack* stack, charStack_Item data);

charStack_Item charStack_Pop(charStack* stack);

charStack_Item charStack_Peek(charStack* stack);

bool charStack_IsEmpty(const charStack* stack);

int charStack_Size(const charStack* stack);

void charStack_Traverse(const charStack* stack, void(*fun)(charStack_Item data));