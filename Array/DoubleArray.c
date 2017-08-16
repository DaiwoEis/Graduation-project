#include "doubleArray.h"

struct doubleArray
{
	doubleArray_Item* datas;
	int size;
};

bool doubleArray_ValidateIndex(const doubleArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

doubleArray* doubleArray_Create(int size)
{
	doubleArray* arr = (doubleArray*)malloc(sizeof(doubleArray));
	arr->size = size;
	arr->datas = (doubleArray_Item*)calloc(size, sizeof(doubleArray_Item));
	return arr;
}

void doubleArray_Destroy(doubleArray* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void doubleArray_Set(doubleArray* arr, int index, doubleArray_Item data)
{
	if (!doubleArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

doubleArray_Item doubleArray_Get(const doubleArray* arr, int index)
{
	if (!doubleArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int doubleArray_Size(const doubleArray* arr)
{
	return arr->size;
}

