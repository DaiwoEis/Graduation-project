#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "LPHashST.h"
#include "ListGeneric.h"
#include "StringList.h"

#define MAX_STR_LENGTH 100

void Print_v2(CAString* str)
{
	printf("%s", CAString_ToString(str));
}

bool EalFun_v2(CAString* left, CAString* right)
{
	return strcmp(CAString_ToString(left), CAString_ToString(right)) == 0;
}

int HashFun_v2(CAString* str)
{
	int hash = 0;
	int length = CAString_Size(str);
	int R = 3;
	for (int i = 0; i < length; ++i)
	{
		hash = R*hash + CAString_Get(str, i);
	}
	return hash;
}

int main2()
{
	char str[MAX_STR_LENGTH];

	List(CAString)* strings = List_Create(CAString)();
	LPHashST* st = LPHashST_Create_E(HashFun_v2, EalFun_v2);

	FILE* file;
	puts("input the file name");
	gets_s(str, MAX_STR_LENGTH);
	fopen_s(&file, str, "r");

	puts("input key and value position");
	int keyField, valueField;
	scanf_s("%d%d", &keyField, &valueField);
	getchar();

	char del[] = ",\n";
	while (fgets(str, MAX_STR_LENGTH, file) != NULL&&str[0] != '\n')
	{
		CAString* key;
		CAString* value;
		int count = 0;
		char* next = NULL;
		for (char* p = strtok_s(str, del, &next); p != NULL; p = strtok_s(NULL, del, &next))
		{
			CAString* temp = CAString_Create(p);

			if (count == keyField)
			{
				List_Add(CAString)(strings, temp);
				key = temp;
			}
			else if (count == valueField)
			{
				List_Add(CAString)(strings, temp);
				value = temp;
			}
			count++;
		}
		LPHashST_Add(st, key, value);
	}

	puts("\ninput address");
	CAString* temp;
	while (gets_s(str, MAX_STR_LENGTH) != NULL&&str[0] != '\0')
	{
		temp = CAString_Create(str);
		if (LPHashST_Contains(st, temp))
		{
			puts(CAString_ToString(LPHashST_Get(st, temp)));
		}
		else
		{
			puts("not found");
		}
		CAString_Destroy(temp);

		puts("\ninput address");
	}

	// free memory 
	LPHashST_Destroy(st);
	for (int i = 0; i < List_Length(CAString)(strings); ++i)
	{
		CAString_Destroy(List_Get(CAString)(strings, i));
	}
	List_Destroy(CAString)(strings);

	return 0;
}