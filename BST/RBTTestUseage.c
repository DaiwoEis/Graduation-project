#include "RedBlackBST.h"

void print(Key key)
{
	printf("%c ", key);
}

int main2()
{
	FILE* file;
	fopen_s(&file, "data.txt", "r");

	RedBlackBST* bst = RedBlackBST_Create();

	char c;
	int n;
	while (fscanf_s(file, "%c", &c, 1) != EOF)
	{
		fscanf_s(file, "%d", &n);
		RedBlackBST_Add(bst, c, n);
		fscanf_s(file, "%c", &c, 1);
	}
	fclose(file);

	printf("%d\n", RedBlackBST_Size(bst));

	Queue* queue = RedBlackBST_Keys(bst);

	Queue_Traverse(queue, print);

	RedBlackBST_Delete(&bst);
	Queue_Destroy(queue);

	getchar();
	return 0;
}