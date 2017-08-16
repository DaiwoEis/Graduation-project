#pragma once

#include "ArrayBase.h"

typedef bool boolArray_Item;
typedef struct boolArray boolArray;

boolArray* boolArray_Create(int size);

void boolArray_Destroy(boolArray* arr);

void boolArray_Set(boolArray* arr, int index, boolArray_Item data);

boolArray_Item boolArray_Get(const boolArray* arr, int index);

int boolArray_Size(const boolArray* arr);