#include "StackGeneric.h"
#include "CharStack.h"
#include <string.h>

void PrinteData(char data)
{
	printf("%c ", data);
}

int main1()
{
	char str1[] = "ABCDEFG";
	puts(str1);

	Stack(char)* stack = Stack_Create(char)();

	for (int i = 0; i < (int)strlen(str1); ++i)
	{
		Stack_Push(char)(stack, str1[i]);
	}
	printf("size: %d\n", Stack_Size(char)(stack));

	Stack_Traverse(char)(stack, PrinteData);
	putchar('\n');

	char str2[20];
	int i = 0;
	while (!Stack_IsEmpty(char)(stack))
	{
		str2[i] = Stack_Pop(char)(stack);
		i++;
	}
	str2[i] = '\0';

	puts(str2);

	printf("size = %d\n", Stack_Size(char)(stack));

	Stack_Destroy(char)(stack);

	return 0;
}