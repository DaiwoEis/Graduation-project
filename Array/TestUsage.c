#include "ArrayGeneric.h"
#include "CAString.h"
#include "CAStringArray.h"

int main()
{
	FILE* text;

	fopen_s(&text, "GameName.txt", "r");

	Array(CAString)* strings = Array_Create(CAString)(10);

	char str[30];

	int count = 0;
	while (fgets(str, 30, text) && str[0] != '\n')
	{
		CAString* castring = CAString_Create(str);
		Array_Set(CAString)(strings, count++, castring);
	}

	fclose(text);

	for (int i = 0; i < Array_Size(CAString)(strings); ++i)
	{
		printf("%s", CAString_ToString(Array_Get(CAString)(strings, i)));
	}
	putchar('\n');


	for (int i = 0; i < Array_Size(CAString)(strings); ++i)
		CAString_Destroy(Array_Get(CAString)(strings, i));
	Array_Destroy(CAString)(strings);

	return 0;
}
