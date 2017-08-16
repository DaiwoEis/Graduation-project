#pragma once

// a string implement with char array.

#include "ArrayGeneric.h"
#include "CharArray.h"
#include <string.h>

typedef struct CAString CAString;

CAString* CAString_Create(const char* str);

void CAString_Destroy(CAString* str);

void CAString_Set(CAString* str, int index, char data);

char CAString_Get(const CAString* str, int index);

const char* CAString_ToString(const CAString* str);

int CAString_Size(const CAString* str);

int CAString_Cmp(const CAString* left, const CAString* right);