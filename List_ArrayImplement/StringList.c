#include "StringList.h"

struct CAStringList
{
	CAStringList_Item* datas;
	int length;
	int capacity;
};

bool CAStringList_IsFull(CAStringList* list);
void CAStringList_Resize(CAStringList* list, int size);
bool CAStringList_ValidateIndex(const CAStringList* list, int index);

bool CAStringList_IsFull(CAStringList* list)
{
	return list->length == list->capacity;
}

void CAStringList_Resize(CAStringList* list, int size)
{
	CAStringList_Item* newDatas = (CAStringList_Item*)calloc(size, sizeof(CAStringList_Item));
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

bool CAStringList_ValidateIndex(const CAStringList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

CAStringList* CAStringList_Create()
{
	CAStringList* list = (CAStringList*)malloc(sizeof(CAStringList));
	list->length = 0;
	list->capacity = CAStringList_INIT_CAPACITY;
	list->datas = (CAStringList_Item*)calloc(CAStringList_INIT_CAPACITY, sizeof(CAStringList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = CAStringList_DEAFULT_VALUE;
	return list;
}

CAStringList* CAStringList_Create_S(int size)
{
	CAStringList* list = (CAStringList*)malloc(sizeof(CAStringList));
	list->length = 0;
	list->capacity = size;
	list->datas = (CAStringList_Item*)calloc(size, sizeof(CAStringList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = CAStringList_DEAFULT_VALUE;
	return list;
}

void CAStringList_Destroy(CAStringList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void CAStringList_Set(CAStringList* list, int index, CAStringList_Item data)
{
	if (!CAStringList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

CAStringList_Item CAStringList_Get(const CAStringList* list, int index)
{
	if (!CAStringList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void CAStringList_Add(CAStringList* list, CAStringList_Item data)
{
	if (CAStringList_IsFull(list))
	{
		CAStringList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void CAStringList_Insert(CAStringList* list, int index, CAStringList_Item data)
{
	if (!CAStringList_ValidateIndex(list, index)) exit(0);

	if (CAStringList_IsFull(list))
	{
		CAStringList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void CAStringList_RemoveAt(CAStringList* list, int index)
{
	if (!CAStringList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = CAStringList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		CAStringList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int CAStringList_Length(const CAStringList* list)
{
	return list->length;
}

void CAStringList_Clear(CAStringList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = CAStringList_DEAFULT_VALUE;
	}
}

void CAStringList_Traverse(CAStringList* list, void(*fun)(CAStringList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void CAStringListItem_Exch(CAStringList* list, int index1, int index2)
{
	CAStringList_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool CAStringListItem_Less(CAStringList_Item item1, CAStringList_Item item2)
{
	return CAString_Cmp(item1, item2) < 0;
}

int CAStringList_Partition(CAStringList* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	CAStringList_Item v = list->datas[lo];
	while (true)
	{
		while (CAStringListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (CAStringListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		CAStringListItem_Exch(list, i, j);
	}
	CAStringListItem_Exch(list, lo, j);
	return j;
}

void CAStringList_PartSort(CAStringList* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = CAStringList_Partition(list, lo, hi);
	CAStringList_PartSort(list, lo, j - 1);
	CAStringList_PartSort(list, j + 1, hi);
}

void CAStringList_Sort(CAStringList* list)
{
	CAStringList_PartSort(list, 0, list->length - 1);
}