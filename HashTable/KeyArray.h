#pragma once

#include "HashBase.h"

typedef struct KeyArray KeyArray;

KeyArray* KeyArray_Create(int size);

void KeyArray_Destroy(KeyArray* arr);

void KeyArray_Set(KeyArray* arr, int index, Key key);

Key KeyArray_Get(const KeyArray* arr, int index);

int KeyArray_Size(const KeyArray* arr);