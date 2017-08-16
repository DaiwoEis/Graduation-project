#include "IntVectorArray.h"

struct IntVectorArray
{
	pIntVector* datas;
	int size;
};

bool IntVectorArray_ValidateIndex(const IntVectorArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

IntVectorArray* IntVectorArray_Create(int size)
{
	IntVectorArray* arr = (IntVectorArray*)malloc(sizeof(IntVectorArray));
	arr->size = size;
	arr->datas = (pIntVector*)calloc(size, sizeof(pIntVector));
	for (int i = 0; i < arr->size; ++i)
	{
		arr->datas[i] = IntVector_Create();
	}
	return arr;
}

void IntVectorArray_Destroy(IntVectorArray* arr)
{
	if (arr == NULL) return;

	for (int i = 0; i < arr->size; ++i)
	{
		IntVector_Delete(arr->datas[i]);
	}

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void IntVectorArray_Set(IntVectorArray* arr, int index, IntVector* data)
{
	if (!IntVectorArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

IntVector* IntVectorArray_Get(const IntVectorArray* arr, int index)
{
	if (!IntVectorArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int IntVectorArray_Size(const IntVectorArray* arr)
{
	return arr->size;
}

