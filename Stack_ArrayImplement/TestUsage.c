#include "Stack.h"

void PrintData(char data)
{
	printf("%c ", data);
}

int main()
{
	Stack* stack = Stack_Create();

	const char* str = "ABCDEFG";
	for (int i = 0; i < (int)strlen(str); ++i)
	{
		Stack_Push(stack, str[i]);
	}

	Stack_Traverse(stack, PrintData);
	putchar('\n');

	char str1[20];
	int i = 0;
	while (!Stack_IsEmpty(stack))
	{
		str1[i] = Stack_Pop(stack);
		i++;
	}
	str1[i] = '\0';

	puts(str1);

	printf("size = %d\n", Stack_Size(stack));

	Stack_Destroy(stack);

	return 0;
}