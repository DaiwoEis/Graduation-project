#include "Array.h"

struct Array
{
	Array_Item* datas;
	int size;
};

bool Array_ValidateIndex(const Array* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

Array* Array_Create(int size)
{
	Array* arr = (Array*)malloc(sizeof(Array));
	arr->size = size;
	arr->datas = (Array_Item*)calloc(size, sizeof(Array_Item));
	return arr;
}

void Array_Destroy(Array* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void Array_Set(Array* arr, int index, Array_Item data)
{
	if (!Array_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

Array_Item Array_Get(const Array* arr, int index)
{
	if (!Array_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int Array_Size(const Array* arr)
{
	return arr->size;
}

