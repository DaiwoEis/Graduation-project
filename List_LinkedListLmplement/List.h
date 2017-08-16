#pragma once

#include "ListBase.h"

//struct List_Item
//{
//	int test;
//};

typedef int List_Item;
typedef struct List List;
typedef struct ListNode ListNode;

List* List_Create();

void List_Destroy(List* list);

void List_Set(List* list, int index, List_Item data);

List_Item List_Get(const List* list, int index);

void List_Add(List* list, List_Item data);

void List_Insert(List* list, int index, List_Item data);

void List_RemoveAt(List* list, int index);

int List_Length(const List* list);

void List_Clear(List* list);

void List_Traverse(List* list, void(*fun)(List_Item data));
