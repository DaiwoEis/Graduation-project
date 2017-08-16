#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "IntVector.h"

typedef struct IntVectorArray IntVectorArray;

IntVectorArray* IntVectorArray_Create(int size);

void IntVectorArray_Destroy(IntVectorArray* arr);

void IntVectorArray_Set(IntVectorArray* arr, int index, IntVector* data);

IntVector* IntVectorArray_Get(const IntVectorArray* arr, int index);

int IntVectorArray_Size(const IntVectorArray* arr);