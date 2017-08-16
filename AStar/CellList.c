#include "CellList.h"

struct CellList
{
	CellList_Item* datas;
	int length;
	int capacity;
};

bool CellList_IsFull(CellList* list);
void CellList_Resize(CellList* list, int size);
bool CellList_ValidateIndex(const CellList* list, int index);

bool CellList_IsFull(CellList* list)
{
	return list->length == list->capacity;
}

void CellList_Resize(CellList* list, int size)
{
	CellList_Item* newDatas = (CellList_Item*)calloc(size, sizeof(CellList_Item));
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

bool CellList_ValidateIndex(const CellList* list, int index)
{
	if (index < 0 || index >= list->capacity)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

CellList* CellList_Create()
{
	CellList* list = (CellList*)malloc(sizeof(CellList));
	list->length = 0;
	list->capacity = CellList_INIT_CAPACITY;
	list->datas = (CellList_Item*)calloc(CellList_INIT_CAPACITY, sizeof(CellList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = CellList_DEAFULT_VALUE;
	return list;
}

CellList* CellList_Create_S(int size)
{
	CellList* list = (CellList*)malloc(sizeof(CellList));
	list->length = 0;
	list->capacity = size;
	list->datas = (CellList_Item*)calloc(size, sizeof(CellList_Item));
	for (int i = 0; i < list->capacity; ++i)
		list->datas[i] = CellList_DEAFULT_VALUE;
	return list;
}

void CellList_Destroy(CellList* list)
{
	if (list == NULL) return;

	if (list->datas != NULL)
	{
		free(list->datas);
		list->datas = NULL;
	}
	free(list);
}

void CellList_Set(CellList* list, int index, CellList_Item data)
{
	if (!CellList_ValidateIndex(list, index)) exit(0);

	list->datas[index] = data;
}

CellList_Item CellList_Get(const CellList* list, int index)
{
	if (!CellList_ValidateIndex(list, index)) exit(0);

	return list->datas[index];
}

void CellList_Add(CellList* list, CellList_Item data)
{
	if (CellList_IsFull(list))
	{
		CellList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	list->datas[list->length] = data;

	list->length++;
}

void CellList_Insert(CellList* list, int index, CellList_Item data)
{
	if (!CellList_ValidateIndex(list, index)) exit(0);

	if (CellList_IsFull(list))
	{
		CellList_Resize(list, list->capacity * 2);
		list->capacity = list->capacity * 2;
	}

	for (int i = list->length - 1; i > index; --i)
	{
		list->datas[i + 1] = list->datas[i];
	}
	list->datas[index] = data;

	list->length++;
}

void CellList_RemoveAt(CellList* list, int index)
{
	if (!CellList_ValidateIndex(list, index)) exit(0);

	for (int i = index + 1; i < list->length; ++i)
	{
		list->datas[i - 1] = list->datas[i];
	}
	list->datas[list->length - 1] = CellList_DEAFULT_VALUE;

	list->length--;

	if (list->length > 0 && list->length <= list->capacity / 4)
	{
		CellList_Resize(list, list->capacity / 2);
		list->capacity = list->capacity / 2;
	}
}

int CellList_Length(const CellList* list)
{
	return list->length;
}

void CellList_Clear(CellList* list)
{
	for (int i = 0; i < list->length; ++i)
	{
		list->datas[i] = CellList_DEAFULT_VALUE;
	}
}

void CellList_Traverse(CellList* list, void(*fun)(CellList_Item data))
{
	for (int i = 0; i < list->length; ++i)
	{
		fun(list->datas[i]);
	}
}
