#pragma once

#include "StackBase.h"

typedef char Stack_Item;
typedef struct Stack Stack;
const static int Stack_INIT_SIZE = 2;

Stack* Stack_Create();

void Stack_Destroy(Stack* stack);

void Stack_Push(Stack* stack, Stack_Item data);

Stack_Item Stack_Pop(Stack* stack);

Stack_Item Stack_Peek(Stack* stack);

bool Stack_IsEmpty(const Stack* stack);

int Stack_Size(const Stack* stack);

void Stack_Traverse(const Stack* stack, void(*pfun)(Stack_Item data));