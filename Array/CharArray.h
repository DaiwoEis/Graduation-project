#pragma once

#include "ArrayBase.h"

typedef char charArray_Item;
typedef struct charArray charArray;

charArray* charArray_Create(int size);

void charArray_Destroy(charArray* arr);

void charArray_Set(charArray* arr, int index, charArray_Item data);

charArray_Item charArray_Get(const charArray* arr, int index);

int charArray_Size(const charArray* arr);

const char* charArray_ToString(const charArray* arr);