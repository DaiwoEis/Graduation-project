#include "intList.h"

struct intList
{
	intList_Item* datas;
	int length;
	int capacity;
};

bool intList_IsFull(intList* list);
void intList_Resize(intList* list, int size);
bool intList_ValidateIndex(const intList* list, int index);

bool intList_IsFull(intList* list)
{
	return list->length == list->capacity;
}

void intList_Resize(intList* list, int size)
{
	intList_Item* newDatas = (intList_Item*)calloc(size, sizeof(intList_Item));
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

bool intList_ValidateIndex(const intList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

intList* intList_Create()
{
	intList* list = (intList*)malloc(sizeof(intList));
	list->length = 0;
	list->capacity = intList_INIT_CAPACITY;
	list->datas = (intList_Item*)calloc(intList_INIT_CAPACITY, sizeof(intList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = intList_DEAFULT_VALUE;
	return list;
}

intList* intList_Create_S(int size)
{
	intList* list = (intList*)malloc(sizeof(intList));
	list->length = 0;
	list->capacity = size;
	list->datas = (intList_Item*)calloc(size, sizeof(intList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = intList_DEAFULT_VALUE;
	return list;
}

void intList_Destroy(intList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void intList_Set(intList* list, int index, intList_Item data)
{
	if (!intList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

intList_Item intList_Get(const intList* list, int index)
{
	if (!intList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void intList_Add(intList* list, intList_Item data)
{
	if (intList_IsFull(list))
	{
		intList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void intList_Insert(intList* list, int index, intList_Item data)
{
	if (!intList_ValidateIndex(list, index)) exit(0);

	if (intList_IsFull(list))
	{
		intList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void intList_RemoveAt(intList* list, int index)
{
	if (!intList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = intList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		intList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int intList_Length(const intList* list)
{
	return list->length;
}

void intList_Clear(intList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = intList_DEAFULT_VALUE;
	}
}

void intList_Traverse(intList* list, void(*fun)(intList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void intListItem_Exch(intList* list, int index1, int index2)
{
	intList_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool intListItem_Less(intList_Item item1, intList_Item item2)
{
	return item1 < item2;
}

int intList_Partition(intList* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	intList_Item v = list->datas[lo];
	while (true)
	{
		while (intListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (intListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		intListItem_Exch(list, i, j);
	}
	intListItem_Exch(list, lo, j);
	return j;
}

void intList_PartSort(intList* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = intList_Partition(list, lo, hi);
	intList_PartSort(list, lo, j - 1);
	intList_PartSort(list, j + 1, hi);
}

void intList_Sort(intList* list)
{
	intList_PartSort(list, 0, list->length - 1);
}
