#pragma once

#include "ListBase.h"

typedef bool boolList_Item;
const static int boolList_INIT_CAPACITY = 5;
const static boolList_Item boolList_DEAFULT_VALUE = false;

typedef struct boolList boolList;

boolList* boolList_Create();

boolList* boolList_Create_S(int size);

void boolList_Destroy(boolList* list);

void boolList_Set(boolList* list, int index, boolList_Item data);

boolList_Item boolList_Get(const boolList* list, int index);

void boolList_Add(boolList* list, boolList_Item data);

void boolList_Insert(boolList* list, int index, boolList_Item data);

void boolList_RemoveAt(boolList* list, int index);

int boolList_Length(const boolList* list);

void boolList_Clear(boolList* list);

void boolList_Traverse(boolList* list, void(*fun)(boolList_Item data));

void boolList_Sort(boolList* list);