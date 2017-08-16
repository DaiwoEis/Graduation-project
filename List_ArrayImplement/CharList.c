#include "charList.h"

struct charList
{
	charList_Item* datas;
	int length;
	int capacity;
};

bool charList_IsFull(charList* list);
void charList_Resize(charList* list, int size);
bool charList_ValidateIndex(const charList* list, int index);

bool charList_IsFull(charList* list)
{
	return list->length == list->capacity;
}

void charList_Resize(charList* list, int size)
{
	charList_Item* newDatas = (charList_Item*)calloc(size, sizeof(charList_Item));
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

bool charList_ValidateIndex(const charList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

charList* charList_Create()
{
	charList* list = (charList*)malloc(sizeof(charList));
	list->length = 0;
	list->capacity = charList_INIT_CAPACITY;
	list->datas = (charList_Item*)calloc(charList_INIT_CAPACITY, sizeof(charList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = charList_DEAFULT_VALUE;
	return list;
}

charList* charList_Create_S(int size)
{
	charList* list = (charList*)malloc(sizeof(charList));
	list->length = 0;
	list->capacity = size;
	list->datas = (charList_Item*)calloc(size, sizeof(charList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = charList_DEAFULT_VALUE;
	return list;
}

void charList_Destroy(charList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void charList_Set(charList* list, int index, charList_Item data)
{
	if (!charList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

charList_Item charList_Get(const charList* list, int index)
{
	if (!charList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void charList_Add(charList* list, charList_Item data)
{
	if (charList_IsFull(list))
	{
		charList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void charList_Insert(charList* list, int index, charList_Item data)
{
	if (!charList_ValidateIndex(list, index)) exit(0);

	if (charList_IsFull(list))
	{
		charList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void charList_RemoveAt(charList* list, int index)
{
	if (!charList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = charList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		charList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int charList_Length(const charList* list)
{
	return list->length;
}

void charList_Clear(charList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = charList_DEAFULT_VALUE;
	}
}

void charList_Traverse(charList* list, void(*fun)(charList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void charListItem_Exch(charList* list, int index1, int index2)
{
	charList_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool charListItem_Less(charList_Item item1, charList_Item item2)
{
	return item1 < item2;
}

int charList_Partition(charList* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	charList_Item v = list->datas[lo];
	while (true)
	{
		while (charListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (charListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		charListItem_Exch(list, i, j);
	}
	charListItem_Exch(list, lo, j);
	return j;
}

void charList_PartSort(charList* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = charList_Partition(list, lo, hi);
	charList_PartSort(list, lo, j - 1);
	charList_PartSort(list, j + 1, hi);
}

void charList_Sort(charList* list)
{
	charList_PartSort(list, 0, list->length - 1);
}