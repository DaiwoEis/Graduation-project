#include "integerArray.h"

struct intArray
{
	intArray_Item* datas;
	int size;
};

bool intArray_ValidateIndex(const intArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

intArray* intArray_Create(int size)
{
	intArray* arr = (intArray*)malloc(sizeof(intArray));
	arr->size = size;
	arr->datas = (intArray_Item*)calloc(size, sizeof(intArray_Item));
	return arr;
}

void intArray_Destroy(intArray* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void intArray_Set(intArray* arr, int index, intArray_Item data)
{
	if (!intArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

intArray_Item intArray_Get(const intArray* arr, int index)
{
	if (!intArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int intArray_Size(const intArray* arr)
{
	return arr->size;
}

