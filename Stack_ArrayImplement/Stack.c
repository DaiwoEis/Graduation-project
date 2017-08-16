#include "Stack.h"

struct Stack
{
	Stack_Item* datas;
	int size;
	int top;
	int dataCapacity;
};

bool Stack_IsFull(Stack* stack);
void Stack_Resize(Stack* stack, int size);

Stack* Stack_Create()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = 0;
	stack->size = 0;
	stack->dataCapacity = Stack_INIT_SIZE;
	stack->datas = (Stack_Item*)calloc(stack->dataCapacity, sizeof(Stack_Item));

	return stack;
}

void Stack_Destroy(Stack* stack)
{
	if (stack == NULL) return;

	if (stack->datas != NULL)
	{
		free(stack->datas);
		stack->datas = NULL;
	}

	free(stack);
}

void Stack_Push(Stack* stack, Stack_Item data)
{
	if (Stack_IsFull(stack))
	{
		Stack_Resize(stack, stack->dataCapacity * 2);
		stack->dataCapacity = stack->dataCapacity * 2;
	}

	stack->datas[stack->top++] = data;
	stack->size++;
}

Stack_Item Stack_Pop(Stack* stack)
{
	if (Stack_IsEmpty(stack)) return 0;

	Stack_Item data = stack->datas[--stack->top];
	stack->size--;

	if (stack->size > 0 && stack->size <= stack->dataCapacity / 4)
	{
		Stack_Resize(stack, stack->dataCapacity / 2);
		stack->dataCapacity = stack->dataCapacity / 2;
	}

	return data;
}


Stack_Item Stack_Peek(Stack* stack)
{
	return stack->datas[stack->top - 1];
}

bool Stack_IsEmpty(const Stack* stack)
{
	return stack->size == 0;
}

bool Stack_IsFull(Stack* stack)
{
	return stack->size == stack->dataCapacity;
}

void Stack_Resize(Stack* stack, int size)
{
	Stack_Item* newDatas = (Stack_Item*)calloc(size, sizeof(Stack_Item));
	for (int i = 0; i < stack->size; ++i)
	{
		newDatas[i] = stack->datas[i];
	}

	if (stack->datas != NULL)
	{
		free(stack->datas);
		stack->datas = NULL;
	}

	stack->datas = newDatas;
}

int Stack_Size(const Stack* stack)
{
	return stack->size;
}

void Stack_Traverse(const Stack* stack, void(*fun)(Stack_Item data))
{
	for (int top = stack->top - 1; top >= 0; --top)
	{
		fun(stack->datas[top]);
	}
}
