#include "MaxHeap.h"

struct MaxHeap
{
	Key* keys;
	int size;
	int(*cmp)(Key left, Key right);
	int keyCapacity;
};

int MaxHeap_DefaultCmp(Key left, Key right);

void MaxHeap_Resize(MaxHeap* heap, int size);

bool MaxHeap_IsFull(const MaxHeap* heap);

void MaxHeap_Swim(MaxHeap* heap, int k);

void MaxHeap_Sink(MaxHeap* heap, int k);

bool MaxHeap_Less(const MaxHeap* heap, int i, int j)
{
	return heap->cmp(heap->keys[i], heap->keys[j]) < 0;
}

void MaxHeap_Exch(MaxHeap* heap, int i, int j)
{
	Key swap = heap->keys[i];
	heap->keys[i] = heap->keys[j];
	heap->keys[j] = swap;
}

MaxHeap* MaxHeap_Create(int(*pCmp)(Key left, Key right))
{
	return MaxHeap_Create_S(pCmp, INIT_CAPACITY);
}

MaxHeap* MaxHeap_Create_S(int(*cmpFun)(Key left, Key right), int size)
{
	MaxHeap* heap = (MaxHeap*)calloc(1, sizeof(MaxHeap));
	heap->size = 0;
	heap->keyCapacity = size + 1;
	heap->keys = (Key*)calloc(size + 1, sizeof(Key));
	if (cmpFun == NULL)
		heap->cmp = MaxHeap_DefaultCmp;
	else
		heap->cmp = cmpFun;
	return heap;
}

void MaxHeap_Destroy(MaxHeap* heap)
{
	if (heap == NULL) return;

	if (heap->keys != NULL)
	{
		free(heap->keys);
		heap->keys = NULL;
	}

	free(heap);
}

bool MaxHeap_IsEmpty(const MaxHeap* heap)
{
	return heap->size == 0;
}

bool MaxHeap_IsFull(const MaxHeap* heap)
{
	return heap->size == heap->keyCapacity - 1;
}

int MaxHeap_Size(const MaxHeap* heap)
{
	return heap->size;
}

void MaxHeap_Insert(MaxHeap* heap, Key key)
{
	if (MaxHeap_IsFull(heap))
		MaxHeap_Resize(heap, heap->keyCapacity * 2);

	heap->keys[++heap->size] = key;
	MaxHeap_Swim(heap, heap->size);	
}

void MaxHeap_Resize(MaxHeap* heap, int size)
{
	Key* newKeys = (Key*)calloc(size, sizeof(Key));
	for (int i = 1; i <= heap->size; ++i)
	{
		newKeys[i] = heap->keys[i];
	}
	free(heap->keys);
	heap->keys = newKeys;
	heap->keyCapacity = size;
}

Key MaxHeap_Max(MaxHeap* heap)
{
	if (MaxHeap_IsEmpty(heap))
		return 0;

	return heap->keys[1];
}

Key MaxHeap_DeleteMax(MaxHeap* heap)
{
	if (MaxHeap_IsEmpty(heap))
		return 0;

	Key max = heap->keys[1];
	MaxHeap_Exch(heap, 1, heap->size);
	heap->size--;
	MaxHeap_Sink(heap, 1);
	heap->keys[heap->size + 1] = 0;
	
	if (heap->size > 0 && (heap->size == (heap->keyCapacity - 1) / 4))
		MaxHeap_Resize(heap, heap->keyCapacity / 2);

	return max;
}

int MaxHeap_DefaultCmp(Key left, Key right)
{
	if (left < right) return-1;
	if (left > right)return 1;
	return 0;
}

void MaxHeap_Swim(MaxHeap* heap, int k)
{
	while (k > 1 && MaxHeap_Less(heap, k / 2, k))
	{
		MaxHeap_Exch(heap, k / 2, k);
		k = k / 2;
	}
}

void MaxHeap_Sink(MaxHeap* heap, int k)
{
	while (2 * k <= heap->size)
	{
		int maxChild = 2 * k;
		if (maxChild < heap->size&&MaxHeap_Less(heap, maxChild, maxChild + 1))
			maxChild++;
		if (!MaxHeap_Less(heap, k, maxChild))
			return;
		MaxHeap_Exch(heap, k, maxChild);
		k = maxChild;
	}
}