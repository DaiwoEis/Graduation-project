#include "MaxHeap.h"

int main()
{
	MaxHeap* heap = MaxHeap_Create(NULL);

	MaxHeap_Insert(heap, 1);
	MaxHeap_Insert(heap, 5);
	MaxHeap_Insert(heap, 4);
	MaxHeap_Insert(heap, 10);

	printf("%d\n", MaxHeap_Size(heap));

	printf("%d\n", MaxHeap_DeleteMax(heap));
	printf("%d\n", MaxHeap_DeleteMax(heap));

	printf("%d\n", MaxHeap_Size(heap));

	MaxHeap_Destroy(heap);

	return 0;
}