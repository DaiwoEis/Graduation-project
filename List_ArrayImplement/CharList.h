#pragma once

#include "ListBase.h"

typedef char charList_Item;
const static int charList_INIT_CAPACITY = 5;
const static charList_Item charList_DEAFULT_VALUE = '\0';

typedef struct charList charList;

charList* charList_Create();

charList* charList_Create_S(int size);

void charList_Destroy(charList* list);

void charList_Set(charList* list, int index, charList_Item data);

charList_Item charList_Get(const charList* list, int index);

void charList_Add(charList* list, charList_Item data);

void charList_Insert(charList* list, int index, charList_Item data);

void charList_RemoveAt(charList* list, int index);

int charList_Length(const charList* list);

void charList_Clear(charList* list);

void charList_Traverse(charList* list, void(*fun)(charList_Item data));

void charList_Sort(charList* list);