#pragma once

#include "StackBase.h"

typedef bool boolStack_Item;
typedef struct boolStack boolStack;
typedef struct boolStackNode boolStackNode;

boolStack* boolStack_Create();

void boolStack_Destroy(boolStack* stack);

void boolStack_Push(boolStack* stack, boolStack_Item data);

boolStack_Item boolStack_Pop(boolStack* stack);

boolStack_Item boolStack_Peek(boolStack* stack);

bool boolStack_IsEmpty(const boolStack* stack);

int boolStack_Size(const boolStack* stack);

void boolStack_Traverse(const boolStack* stack, void(*fun)(boolStack_Item data));