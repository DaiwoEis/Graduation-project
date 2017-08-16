#include "BoolArray.h"

struct boolArray
{
	boolArray_Item* datas;
	int size;
};

bool boolArray_ValidateIndex(const boolArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

boolArray* boolArray_Create(int size)
{
	boolArray* arr = (boolArray*)malloc(sizeof(boolArray));
	arr->size = size;
	arr->datas = (boolArray_Item*)calloc(size, sizeof(boolArray_Item));
	return arr;
}

void boolArray_Destroy(boolArray* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void boolArray_Set(boolArray* arr, int index, boolArray_Item data)
{
	if (!boolArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

boolArray_Item boolArray_Get(const boolArray* arr, int index)
{
	if (!boolArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int boolArray_Size(const boolArray* arr)
{
	return arr->size;
}

