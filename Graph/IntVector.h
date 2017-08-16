#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "ArrayBase.h"
#include "IntegerArray.h"

typedef struct IntVector IntVector, *pIntVector;

IntVector* IntVector_Create();

void IntVector_Delete(IntVector* vector);

void IntVector_Add(IntVector* vector, int data);

bool IntVector_IsEmpty(const IntVector* vector);

int IntVector_Size(const IntVector* vector);

void IntVector_Traverse(const IntVector* vector, void(*pfun)(int data));

Array(int)* IntVector_ToArray(const IntVector* vector);