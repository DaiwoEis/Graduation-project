#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>

typedef int Key;

bool Less(Key* keys, int i, int j)
{
	return keys[i - 1] < keys[j - 1];
}

void Exch(Key* keys, int i, int j)
{
	Key swap = keys[i - 1];
	keys[i - 1] = keys[j - 1];
	keys[j - 1] = swap;
}

void Sink(Key* keys, int k, int n)
{
	while (2 * k <= n)
	{
		int maxChild = 2 * k;
		if (maxChild < n&&Less(keys, maxChild, maxChild + 1))
			maxChild++;
		if (!Less(keys, k, maxChild))
			return;
		Exch(keys, k, maxChild);
		k = maxChild;
	}
}

void Sort(Key* keys, int size)
{
	for (int k = size / 2; k >= 1; k--)
		Sink(keys, k, size);
	while (size > 1)
	{
		Exch(keys, 1, size);
		size--;
		Sink(keys, 1, size);
	}
}

bool IsSort(Key* keys, int n)
{
	for (int i = 1; i < n; ++i)
	{
		if (Less(keys, i, i - 1))
			return false;
	}
	return true;
}

int main2()
{
	int nums[] = { 1,45,321,2,4,323,4,123,5789,2 };

	Sort(nums, 10);

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", nums[i]);
	}

	assert(IsSort(nums, 10));

	getchar();

	return 0;
}