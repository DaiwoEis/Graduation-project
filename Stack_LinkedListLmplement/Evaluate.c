#include "StackGeneric.h"
#include "CharStack.h"
#include "DoubleStack.h"
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXSTRNUM 40

int toNum(char c)
{
	return c - 48;
}

double strToNum(const char* str)
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		result = result * 10 + toNum(str[i]);
	}
	return (double)result;
}

int main()
{
	char str[MAXSTRNUM];

	Stack(char)* ops = Stack_Create(char)();
	Stack(double)* valus = Stack_Create(double)();

	while (gets(str) != NULL&& str[0] != '\0')
	{
		for (char* p = strtok(str, " "); p != NULL; p = strtok(NULL, " "))
		{
			if (isdigit(p[0]))
			{
				Stack_Push(double)(valus, strToNum(p));
			}
			else
			{
				char c = p[0];
				if (c == '(') continue;
				else if (c == '+') Stack_Push(char)(ops, c);
				else if (c == '-') Stack_Push(char)(ops, c);
				else if (c == '*') Stack_Push(char)(ops, c);
				else if (c == '/') Stack_Push(char)(ops, c);
				else if (c == 's') Stack_Push(char)(ops, c);
				else if (c == ')')
				{
					char op = Stack_Pop(char)(ops);
					double v = Stack_Pop(double)(valus);
					if (op == '+') v = Stack_Pop(double)(valus) + v;
					else if (op == '-') v = Stack_Pop(double)(valus) - v;
					else if (op == '*') v = Stack_Pop(double)(valus) * v;
					else if (op == '/') v = Stack_Pop(double)(valus) / v;
					else if (op == 's') v = sqrt(v);
					Stack_Push(double)(valus, v);
				}
			}
		}
		puts("result");
		printf("%.4f\n", Stack_Pop(double)(valus));
	}

	Stack_Destroy(char)(ops);
	Stack_Destroy(double)(valus);
	return 0;
}