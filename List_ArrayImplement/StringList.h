#pragma once

#include "ListBase.h"
#include "CAString.h"

typedef CAString* CAStringList_Item;
const static int CAStringList_INIT_CAPACITY = 5;
const static CAStringList_Item CAStringList_DEAFULT_VALUE = false;

typedef struct CAStringList CAStringList;

CAStringList* CAStringList_Create();

CAStringList* CAStringList_Create_S(int size);

void CAStringList_Destroy(CAStringList* list);

void CAStringList_Set(CAStringList* list, int index, CAStringList_Item data);

CAStringList_Item CAStringList_Get(const CAStringList* list, int index);

void CAStringList_Add(CAStringList* list, CAStringList_Item data);

void CAStringList_Insert(CAStringList* list, int index, CAStringList_Item data);

void CAStringList_RemoveAt(CAStringList* list, int index);

int CAStringList_Length(const CAStringList* list);

void CAStringList_Clear(CAStringList* list);

void CAStringList_Traverse(CAStringList* list, void(*fun)(CAStringList_Item data));

void CAStringList_Sort(CAStringList* list);