#include "CAStringArray.h"

struct CAStringArray
{
	CAStringArray_Item* datas;
	int size;
};

bool CAStringArray_ValidateIndex(const CAStringArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

CAStringArray* CAStringArray_Create(int size)
{
	CAStringArray* arr = (CAStringArray*)malloc(sizeof(CAStringArray));
	arr->size = size;
	arr->datas = (CAStringArray_Item*)calloc(size, sizeof(CAStringArray_Item));
	return arr;
}

void CAStringArray_Destroy(CAStringArray* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void CAStringArray_Set(CAStringArray* arr, int index, CAStringArray_Item data)
{
	if (!CAStringArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

CAStringArray_Item CAStringArray_Get(const CAStringArray* arr, int index)
{
	if (!CAStringArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int CAStringArray_Size(const CAStringArray* arr)
{
	return arr->size;
}

