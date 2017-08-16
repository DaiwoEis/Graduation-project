#pragma once

#include "ArrayBase.h"

typedef int intArray_Item;
typedef struct intArray intArray;

intArray* intArray_Create(int size);

void intArray_Destroy(intArray* arr);

void intArray_Set(intArray* arr, int index, intArray_Item data);

intArray_Item intArray_Get(const intArray* arr, int index);

int intArray_Size(const intArray* arr);