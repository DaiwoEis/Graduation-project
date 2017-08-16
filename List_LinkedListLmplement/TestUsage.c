#include "List.h"
#include <stdlib.h>

void printNumber(int data)
{
	printf("%d ", data);
}

int main()
{
	List* list = List_Create();

	srand(50);
	for (int i = 0; i < 30; ++i)
	{
		List_Add(list, rand());
	}

	for (int i = 0; i < List_Length(list); ++i)
	{
		if (i % 10 == 0) putchar('\n');
		printf("%d ", List_Get(list, i));		
	}

	List_Clear(list);

	for (int i = 0; i < 10; ++i)
	{
		List_Add(list, i);
	}

	putchar('\n');
	List_Traverse(list, printNumber);

	List_Insert(list, 1, 55);
	List_Insert(list, 1, 20);
	List_Insert(list, 5, 100);

	putchar('\n');
	List_Traverse(list, printNumber);

	List_Destroy(list);

	return 0;
}