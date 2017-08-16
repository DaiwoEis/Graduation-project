#pragma once

#include "HashBase.h"

typedef struct ValueArray ValueArray;

ValueArray* ValueArray_Create(int size);

void ValueArray_Destroy(ValueArray* arr);

void ValueArray_Set(ValueArray* arr, int index, Value key);

Value ValueArray_Get(const ValueArray* arr, int index);

int ValueArray_Size(const ValueArray* arr);