#pragma once

#include "ArrayBase.h"

typedef int Array_Item;
typedef struct Array Array;

Array* Array_Create(int size);

void Array_Destroy(Array* arr);

void Array_Set(Array* arr, int index, Array_Item data);

Array_Item Array_Get(const Array* arr, int index);

int Array_Size(const Array* arr);