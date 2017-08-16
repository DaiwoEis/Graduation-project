#pragma once

#include "ListBase.h"

typedef double doubleList_Item;
const static int doubleList_INIT_CAPACITY = 5;
const static doubleList_Item doubleList_DEAFULT_VALUE = 0.0;

typedef struct doubleList doubleList;

doubleList* doubleList_Create();

doubleList* doubleList_Create_S(int size);

void doubleList_Destroy(doubleList* list);

void doubleList_Set(doubleList* list, int index, doubleList_Item data);

doubleList_Item doubleList_Get(const doubleList* list, int index);

void doubleList_Add(doubleList* list, doubleList_Item data);

void doubleList_Insert(doubleList* list, int index, doubleList_Item data);

void doubleList_RemoveAt(doubleList* list, int index);

int doubleList_Length(const doubleList* list);

void doubleList_Clear(doubleList* list);

void doubleList_Traverse(doubleList* list, void(*fun)(doubleList_Item data));

void doubleList_Sort(doubleList* list);