#include "CAString.h"

struct CAString
{
	Array(char)* arr;
};

CAString* CAString_Create(const char* str)
{
	CAString* castr = (CAString*)malloc(sizeof(CAString));
	int length = strlen(str) + 1;
	castr->arr = Array_Create(char)(length);
	for (int i = 0; i < length; ++i)
	{
		Array_Set(char)(castr->arr, i, str[i]);
	}
	Array_Set(char)(castr->arr, length - 1, '\0');
	return castr;
}

void CAString_Destroy(CAString* str)
{
	if (str == NULL) return;

	Array_Destroy(char)(str->arr);

	free(str);
}

void CAString_Set(CAString* str, int index, char data)
{
	Array_Set(char)(str->arr, index, data);
}

char CAString_Get(const CAString* str, int index)
{
	return Array_Get(char)(str->arr, index);
}

const char* CAString_ToString(const CAString* str)
{
	return charArray_ToString(str->arr);
}

int CAString_Size(const CAString* str)
{
	return Array_Size(char)(str->arr);
}

int CAString_Cmp(const CAString* left, const CAString* right)
{
	return strcmp(CAString_ToString(left), CAString_ToString(right));
}
