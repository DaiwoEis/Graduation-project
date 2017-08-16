#include "KeyArray.h"

struct KeyArray
{
	Key* keys;
	int size;
};

bool KeyArray_ValidateIndex(const KeyArray* arr, int index)
{
	if (index < 0 || index >= arr->size)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

KeyArray* KeyArray_Create(int size)
{
	KeyArray* arr = (KeyArray*)malloc(sizeof(KeyArray));
	arr->size = size;
	arr->keys = (Key*)calloc(size, sizeof(Key));
	return arr;
}

void KeyArray_Destroy(KeyArray* arr)
{
	if (arr == NULL) return;

	if (arr->keys != NULL)
	{
		free(arr->keys);
		arr->keys = NULL;
	}
	free(arr);
}

void KeyArray_Set(KeyArray* arr, int index, Key key)
{
	if (!KeyArray_ValidateIndex(arr, index)) return;

	arr->keys[index] = key;
}

Key KeyArray_Get(const KeyArray* arr, int index)
{
	if (!KeyArray_ValidateIndex(arr, index)) return 0;

	return arr->keys[index];
}

int KeyArray_Size(const KeyArray* arr)
{
	return arr->size;
}
