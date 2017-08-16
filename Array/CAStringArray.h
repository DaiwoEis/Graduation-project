#pragma once

#include "CAString.h"

typedef CAString* CAStringArray_Item;
typedef struct CAStringArray CAStringArray;

CAStringArray* CAStringArray_Create(int size);

void CAStringArray_Destroy(CAStringArray* arr);

void CAStringArray_Set(CAStringArray* arr, int index, CAStringArray_Item data);

CAStringArray_Item CAStringArray_Get(const CAStringArray* arr, int index);

int CAStringArray_Size(const CAStringArray* arr);