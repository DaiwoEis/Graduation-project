#include "MinHeap.h"

struct MinHeap
{
	Key* keys;
	int size;
	int(*cmp)(Key left, Key right);
	int keyCapacity;
};

int MinHeap_DefaultCmp(Key left, Key right);

void MinHeap_Resize(MinHeap* heap, int size);

bool MinHeap_IsFull(const MinHeap* heap);

void MinHeap_Swim(MinHeap* heap, int k);

void MinHeap_Sink(MinHeap* heap, int k);

bool MinHeap_Greater(const MinHeap* heap, int i, int j)
{
	return heap->cmp(heap->keys[i], heap->keys[j]) > 0;
}

void MinHeap_Exch(MinHeap* heap, int i, int j)
{
	Key swap = heap->keys[i];
	heap->keys[i] = heap->keys[j];
	heap->keys[j] = swap;
}

MinHeap* MinHeap_Create(int(*cmpFun)(Key left, Key right))
{
	return MinHeap_Create_S(cmpFun, INIT_CAPACITY);
}

MinHeap* MinHeap_Create_S(int(*cmpFun)(Key left, Key right), int size)
{
	MinHeap* heap = (MinHeap*)calloc(1, sizeof(MinHeap));
	heap->size = 0;
	heap->keyCapacity = size + 1;
	heap->keys = (Key*)calloc(size + 1, sizeof(Key));
	if (cmpFun == NULL)
		heap->cmp = MinHeap_DefaultCmp;
	else
		heap->cmp = cmpFun;
	return heap;
}

void MinHeap_Destroy(MinHeap* heap)
{
	if (heap == NULL) return;

	if (heap->keys != NULL)
	{
		free(heap->keys);
		heap->keys = NULL;
	}

	free(heap);
}

bool MinHeap_IsEmpty(const MinHeap* heap)
{
	return heap->size == 0;
}

bool MinHeap_IsFull(const MinHeap* heap)
{
	return heap->size == heap->keyCapacity - 1;
}

int MinHeap_Size(const MinHeap* heap)
{
	return heap->size;
}

void MinHeap_Insert(MinHeap* heap, Key key)
{
	if (MinHeap_IsFull(heap))
		MinHeap_Resize(heap, heap->keyCapacity * 2);

	heap->keys[++heap->size] = key;
	MinHeap_Swim(heap, heap->size);
}

void MinHeap_Resize(MinHeap* heap, int size)
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

Key MinHeap_Min(MinHeap* heap)
{
	if (MinHeap_IsEmpty(heap))
		return 0;

	return heap->keys[1];
}

Key MinHeap_DeleteMin(MinHeap* heap)
{
	if (MinHeap_IsEmpty(heap))
		return 0;

	Key max = heap->keys[1];
	MinHeap_Exch(heap, 1, heap->size);
	heap->size--;
	MinHeap_Sink(heap, 1);
	heap->keys[heap->size + 1] = 0;

	if (heap->size > 0 && (heap->size == (heap->keyCapacity - 1) / 4))
		MinHeap_Resize(heap, heap->keyCapacity / 2);

	return max;
}

bool MinHeap_Contains(MinHeap* heap, Key key)
{
	if (MinHeap_IsEmpty(heap)) return false;

	for (int i = 1; i <= heap->size; ++i)
	{
		if (heap->cmp(key, heap->keys[i]) == 0)
		{
			return true;
		}
	}

	return false;
}

int MinHeap_DefaultCmp(Key left, Key right)
{
	if (left < right) return -1;
	if (left > right)return 1;
	return 0;
}

void MinHeap_Swim(MinHeap* heap, int k)
{
	while (k > 1 && MinHeap_Greater(heap, k / 2, k))
	{
		MinHeap_Exch(heap, k / 2, k);
		k = k / 2;
	}
}

void MinHeap_Sink(MinHeap* heap, int k)
{
	while (2 * k <= heap->size)
	{
		int maxChild = 2 * k;
		if (maxChild < heap->size&&MinHeap_Greater(heap, maxChild, maxChild + 1))
			maxChild++;
		if (!MinHeap_Greater(heap, k, maxChild))
			return;
		MinHeap_Exch(heap, k, maxChild);
		k = maxChild;
	}
}