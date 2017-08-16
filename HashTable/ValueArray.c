#include "ValueArray.h"

struct ValueArray
{
	Value* values;
	int size;
};

bool ValueArray_ValidateIndex(const ValueArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

ValueArray* ValueArray_Create(int size)
{
	ValueArray* arr = (ValueArray*)malloc(sizeof(ValueArray));
	arr->size = size;
	arr->values = (Value*)calloc(size, sizeof(Value));
	return arr;
}

void ValueArray_Destroy(ValueArray* arr)
{
	if (arr == NULL) return;

	if (arr->values != NULL)
	{
		free(arr->values);
		arr->values = NULL;
	}
	free(arr);
}

void ValueArray_Set(ValueArray* arr, int index, Value value)
{
	if (!ValueArray_ValidateIndex(arr, index)) return;

	arr->values[index] = value;
}

Value ValueArray_Get(const ValueArray* arr, int index)
{
	if (!ValueArray_ValidateIndex(arr, index)) return 0;

	return arr->values[index];
}

int ValueArray_Size(const ValueArray* arr)
{
	return arr->size;
}
