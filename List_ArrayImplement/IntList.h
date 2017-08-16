#pragma once

#include "ListBase.h"

typedef int intList_Item;
const static int intList_INIT_CAPACITY = 5;
const static intList_Item intList_DEAFULT_VALUE = 0;

typedef struct intList intList;

intList* intList_Create();

intList* intList_Create_S(int size);

void intList_Destroy(intList* list);

void intList_Set(intList* list, int index, intList_Item data);

intList_Item intList_Get(const intList* list, int index);

void intList_Add(intList* list, intList_Item data);

void intList_Insert(intList* list, int index, intList_Item data);

void intList_RemoveAt(intList* list, int index);

int intList_Length(const intList* list);

void intList_Clear(intList* list);

void intList_Traverse(intList* list, void(*fun)(intList_Item data));

void intList_Sort(intList* list);