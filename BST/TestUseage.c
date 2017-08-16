#include "BST.h"

void Print(Key key)
{
	printf("%c ", key);
}

int main()
{
	FILE* file;
	fopen_s(&file, "data.txt", "r");

	BST* bst = BST_Create();

	char c;
	int n;
	while (fscanf_s(file, "%c", &c, 1) != EOF)
	{
		fscanf_s(file, "%d", &n);
		BST_Add(bst, c, n);
		fscanf_s(file, "%c", &c, 1);
	}
	fclose(file);

	printf("%d\n", BST_Size(bst));

	printf("min:%4c\n", BST_Min(bst));
	printf("max:%4c\n", BST_Max(bst));

	Queue* queue = BST_PartKeys(bst, 'c', 'h');

	Queue_Traverse(queue, Print);

	//BST_Traverse(bst, Print);

	putchar('\n');
	while (!BST_IsEmpty(bst))
	{
		char min = BST_Min(bst);
		printf("min:%4c %4d\n", min, BST_Get(bst, min));
		BST_DeleteMin(bst);
	}

	printf("size:%4d\n", BST_Size(bst));

	BST_Destroy(bst);	
	Queue_Destroy(queue);

	return 0;
}
