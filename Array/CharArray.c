#include "charArray.h"

struct charArray
{
	charArray_Item* datas;
	int size;
};

bool charArray_ValidateIndex(const charArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

charArray* charArray_Create(int size)
{
	charArray* arr = (charArray*)malloc(sizeof(charArray));
	arr->size = size;
	arr->datas = (charArray_Item*)calloc(size, sizeof(charArray_Item));
	return arr;
}

void charArray_Destroy(charArray* arr)
{
	if (arr == NULL) return;

	if (arr->datas != NULL)
	{
		free(arr->datas);
		arr->datas = NULL;
	}
	free(arr);
}

void charArray_Set(charArray* arr, int index, charArray_Item data)
{
	if (!charArray_ValidateIndex(arr, index)) return;

	arr->datas[index] = data;
}

charArray_Item charArray_Get(const charArray* arr, int index)
{
	if (!charArray_ValidateIndex(arr, index)) return 0;

	return arr->datas[index];
}

int charArray_Size(const charArray* arr)
{
	return arr->size;
}

const char* charArray_ToString(const charArray* arr)
{
	return &arr->datas[0];
}