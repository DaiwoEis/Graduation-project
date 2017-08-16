#include "List.h"

struct List
{
	List_Item* datas;
	int length;
	int capacity;
};

bool List_IsFull(List* list);
void List_Resize(List* list, int size);
bool List_ValidateIndex(const List* list, int index);

bool List_IsFull(List* list)
{
	return list->length == list->capacity;
}

void List_Resize(List* list, int size)
{
	List_Item* newDatas = (List_Item*)calloc(size, sizeof(List_Item));
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

bool List_ValidateIndex(const List* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

List* List_Create()
{
	List* list = (List*)malloc(sizeof(List));
	list->length = 0;
	list->capacity = List_INIT_CAPACITY;
	list->datas = (List_Item*)calloc(List_INIT_CAPACITY, sizeof(List_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = List_DEAFULT_VALUE;
	return list;
}

List* List_Create_S(int size)
{
	List* list = (List*)malloc(sizeof(List));
	list->length = 0;
	list->capacity = size;
	list->datas = (List_Item*)calloc(size, sizeof(List_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = List_DEAFULT_VALUE;
	return list;
}

void List_Destroy(List* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void List_Set(List* list, int index, List_Item data)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

List_Item List_Get(const List* list, int index)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void List_Add(List* list, List_Item data)
{
	if (List_IsFull(list))
	{
		List_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void List_Insert(List* list, int index, List_Item data)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	if (List_IsFull(list))
	{
		List_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void List_RemoveAt(List* list, int index)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = List_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		List_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int List_Length(const List* list)
{
	return list->length;
}

void List_Clear(List* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = List_DEAFULT_VALUE;
	}
}

void List_Traverse(List* list, void(*fun)(List_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}

void ListItem_Exch(List* list, int index1, int index2)
{
	List_Item temp = list->datas[index1];
	list->datas[index1] = list->datas[index2];
	list->datas[index2] = temp;
}

bool ListItem_Less(List_Item item1, List_Item item2)
{
	return item1 < item2;
}

int List_Partition(List* list, int lo, int hi)
{
	int i = lo, j = hi + 1;
	List_Item v = list->datas[lo];
	while (true)
	{
		while (ListItem_Less(list->datas[++i], v))
			if (i == hi) break;
		while (ListItem_Less(v, list->datas[++i]))
			if (j == lo) break;

		if (i >= j) break;
		ListItem_Exch(list, i, j);
	}
	ListItem_Exch(list, lo, j);
	return j;
}

void List_PartSort(List* list, int lo, int hi)
{
	if (hi <= lo) return;
	int j = List_Partition(list, lo, hi);
	List_PartSort(list, lo, j - 1);
	List_PartSort(list, j + 1, hi);
}

void List_Sort(List* list)
{
	List_PartSort(list, 0, list->length - 1);
}