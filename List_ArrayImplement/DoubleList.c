#include "doubleList.h"

struct doubleList
{
	doubleList_Item* datas;
	int length;
	int capacity;
};

bool doubleList_IsFull(doubleList* list);
void doubleList_Resize(doubleList* list, int size);
bool doubleList_ValidateIndex(const doubleList* list, int index);

bool doubleList_IsFull(doubleList* list)
{
	return list->length == list->capacity;
}

void doubleList_Resize(doubleList* list, int size)
{
	doubleList_Item* newDatas = (doubleList_Item*)calloc(size, sizeof(doubleList_Item));
	for (int i = 0; i < list->length; ++i)
	{
		newDatas[i] = list->datas[i];
	}

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}

	list->datas = newDatas;
}

bool doubleList_ValidateIndex(const doubleList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

doubleList* doubleList_Create()
{
	doubleList* list = (doubleList*)malloc(sizeof(doubleList));
	list->length = 0;
	list->capacity = doubleList_INIT_CAPACITY;
	list->datas = (doubleList_Item*)calloc(doubleList_INIT_CAPACITY, sizeof(doubleList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = doubleList_DEAFULT_VALUE;
	return list;
}

doubleList* doubleList_Create_S(int size)
{
	doubleList* list = (doubleList*)malloc(sizeof(doubleList));
	list->length = 0;
	list->capacity = size;
	list->datas = (doubleList_Item*)calloc(size, sizeof(doubleList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = doubleList_DEAFULT_VALUE;
	return list;
}

void doubleList_Destroy(doubleList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void doubleList_Set(doubleList* list, int index, doubleList_Item data)
{
	if (!doubleList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

doubleList_Item doubleList_Get(const doubleList* list, int index)
{
	if (!doubleList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void doubleList_Add(doubleList* list, doubleList_Item data)
{
	if (doubleList_IsFull(list))
	{
		doubleList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void doubleList_Insert(doubleList* list, int index, doubleList_Item data)
{
	if (!doubleList_ValidateIndex(list, index)) exit(0);

	if (doubleList_IsFull(list))
	{
		doubleList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void doubleList_RemoveAt(doubleList* list, int index)
{
	if (!doubleList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = doubleList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		doubleList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int doubleList_Length(const doubleList* list)
{
	return list->length;
}

void doubleList_Clear(doubleList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = doubleList_DEAFULT_VALUE;
	}
}

void doubleList_Traverse(doubleList* list, void(*fun)(doubleList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void doubleListItem_Exch(doubleList* list, int index1, int index2)
{
	doubleList_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool doubleListItem_Less(doubleList_Item item1, doubleList_Item item2)
{
	return item1 < item2;
}

int doubleList_Partition(doubleList* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	doubleList_Item v = list->datas[lo];
	while (true)
	{
		while (doubleListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (doubleListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		doubleListItem_Exch(list, i, j);
	}
	doubleListItem_Exch(list, lo, j);
	return j;
}

void doubleList_PartSort(doubleList* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = doubleList_Partition(list, lo, hi);
	doubleList_PartSort(list, lo, j - 1);
	doubleList_PartSort(list, j + 1, hi);
}

void doubleList_Sort(doubleList* list)
{
	doubleList_PartSort(list, 0, list->length - 1);
}
