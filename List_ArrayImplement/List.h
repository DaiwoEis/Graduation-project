#pragma once

#include "ListBase.h"

struct List_Item
{
	int test;
};

typedef int List_Item;
const static int List_INIT_CAPACITY = 5;
const static List_Item List_DEAFULT_VALUE;

typedef struct List List;

List* List_Create();

List* List_Create_S(int size);

void List_Destroy(List* list);

void List_Set(List* list, int index, List_Item data);

List_Item List_Get(const List* list, int index);

void List_Add(List* list, List_Item data);

void List_Insert(List* list, int index, List_Item data);

void List_RemoveAt(List* list, int index);

int List_Length(const List* list);

void List_Clear(List* list);

void List_Traverse(List* list, void(*fun)(List_Item data));

void List_Sort(List* list);