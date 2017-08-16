#pragma once

#include "ArrayBase.h"

typedef double doubleArray_Item;
typedef struct doubleArray doubleArray;

doubleArray* doubleArray_Create(int size);

void doubleArray_Destroy(doubleArray* arr);

void doubleArray_Set(doubleArray* arr, int index, doubleArray_Item data);

doubleArray_Item doubleArray_Get(const doubleArray* arr, int index);

int doubleArray_Size(const doubleArray* arr);