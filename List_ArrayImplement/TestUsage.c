#include "ListGeneric.h"
#include "StringList.h"
#include "CharList.h"

void Print(CAString* str)
{
	printf("%s", CAString_ToString(str));
}

int main()
{
	List(char)* list = List_Create(char)();
	List_Add(char)(list, 'f');
	List_Add(char)(list, 'a');
	List_Add(char)(list, 'g');
	List_Add(char)(list, 'v');
	List_Add(char)(list, 'x');
	List_Add(char)(list, 'y');
	List_Add(char)(list, 'c');
	List_Add(char)(list, 'e');
	List_Add(char)(list, 'w');
	List_Add(char)(list, 'i');
	List_Sort(char)(list);
	for (int i = 0; i < List_Length(char)(list); ++i)
	{
		printf("%c ", List_Get(char)(list, i));
	}
	List_Destroy(char)(list);

	/*List(bool)* boolList = List_Create(bool)();
	List(int)* intList = List_Create(int)();
	List(double)* doubleList = List_Create(double)();
	List(char)* charList = List_Create(char)();

	for (int i = 0; i < 10; ++i)
	{
		List_Add(bool)(boolList, i % 2 == 0);
		List_Add(int)(intList, i);
		List_Add(double)(doubleList, i * 2);
		List_Add(char)(charList, (char)('a' + i));
	}

	for (int i = 0; i < List_Length(bool)(boolList); ++i)
		printf("%d ", List_Get(bool)(boolList, i));
	putchar('\n');
	for (int i = 0; i < List_Length(int)(intList); ++i)
		printf("%d ", List_Get(int)(intList, i));
	putchar('\n');
	for (int i = 0; i < List_Length(double)(doubleList); ++i)
		printf("%.3f ", List_Get(double)(doubleList, i));
	putchar('\n');
	for (int i = 0; i < List_Length(char)(charList); ++i)
		printf("%c ", List_Get(char)(charList, i));

	List_Destroy(bool)(boolList);
	List_Destroy(int)(intList);
	List_Destroy(double)(doubleList);
	List_Destroy(char)(charList);*/

	/*FILE* text;

	fopen_s(&text, "GameName.txt", "r");

	List(CAString)* gameNames = List_Create(CAString)();

	char str[30];

	int count = 0;
	while (fgets(str, 30, text) && str[0] != '\n')
	{
		CAString* temp = CAString_Create(str);
		List_Add(CAString)(gameNames, temp);
	}

	fclose(text);

	List_Traverse(CAString)(gameNames, Print);

	for (int i = 0; i < List_Length(CAString)(gameNames); ++i)
	{
		CAString_Destroy(List_Get(CAString)(gameNames, i));
	}
	List_Destroy(CAString)(gameNames);*/
	
	return 0;
}