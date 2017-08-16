#include "boolList.h"

struct boolList
{
	boolList_Item* datas;
	int length;
	int capacity;
};

bool boolList_IsFull(boolList* list);
void boolList_Resize(boolList* list, int size);
bool boolList_ValidateIndex(const boolList* list, int index);

bool boolList_IsFull(boolList* list)
{
	return list->length == list->capacity;
}

void boolList_Resize(boolList* list, int size)
{
	boolList_Item* newDatas = (boolList_Item*)calloc(size, sizeof(boolList_Item));
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

bool boolList_ValidateIndex(const boolList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

boolList* boolList_Create()
{
	boolList* list = (boolList*)malloc(sizeof(boolList));
	list->length = 0;
	list->capacity = boolList_INIT_CAPACITY;
	list->datas = (boolList_Item*)calloc(boolList_INIT_CAPACITY, sizeof(boolList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = boolList_DEAFULT_VALUE;
	return list;
}

boolList* boolList_Create_S(int size)
{
	boolList* list = (boolList*)malloc(sizeof(boolList));
	list->length = 0;
	list->capacity = size;
	list->datas = (boolList_Item*)calloc(size, sizeof(boolList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = boolList_DEAFULT_VALUE;
	return list;
}

void boolList_Destroy(boolList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void boolList_Set(boolList* list, int index, boolList_Item data)
{
	if (!boolList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

boolList_Item boolList_Get(const boolList* list, int index)
{
	if (!boolList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void boolList_Add(boolList* list, boolList_Item data)
{
	if (boolList_IsFull(list))
	{
		boolList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void boolList_Insert(boolList* list, int index, boolList_Item data)
{
	if (!boolList_ValidateIndex(list, index)) exit(0);

	if (boolList_IsFull(list))
	{
		boolList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void boolList_RemoveAt(boolList* list, int index)
{
	if (!boolList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = boolList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		boolList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int boolList_Length(const boolList* list)
{
	return list->length;
}

void boolList_Clear(boolList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = boolList_DEAFULT_VALUE;
	}
}

void boolList_Traverse(boolList* list, void(*fun)(boolList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void boolListItem_Exch(boolList* list, int index1, int index2)
{
	boolList_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool boolListItem_Less(boolList_Item item1, boolList_Item item2)
{
	return item1 < item2;
}

int boolList_Partition(boolList* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	boolList_Item v = list->datas[lo];
	while (true)
	{
		while (boolListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (boolListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		boolListItem_Exch(list, i, j);
	}
	boolListItem_Exch(list, lo, j);
	return j;
}

void boolList_PartSort(boolList* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = boolList_Partition(list, lo, hi);
	boolList_PartSort(list, lo, j - 1);
	boolList_PartSort(list, j + 1, hi);
}

void boolList_Sort(boolList* list)
{
	boolList_PartSort(list, 0, list->length - 1);
}