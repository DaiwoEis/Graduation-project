#pragma once

#include "HashBase.h"
#include "BoolArray.h"
#include "KeyArray.h"
#include "ValueArray.h"
#include "ArrayGeneric.h"

typedef struct LPHashST LPHashST;

LPHashST* LPHashST_Create(int(*pHash)(Key key));

LPHashST* LPHashST_Create_E(int(*pHash)(Key key), bool(*pEql)(Key left, Key right));

LPHashST* LPHashST_Create_ES(int(*pHash)(Key key), bool(*pEql)(Key left, Key right), int tableSize);

void LPHashST_Destroy(LPHashST* st);

void LPHashST_Add(LPHashST* st, Key key, Value value);

Value LPHashST_Get(const LPHashST* st, Key key);

void LPHashST_Delete(LPHashST* st, Key key);

bool LPHashST_Contains(const LPHashST* st, Key key);

bool LPHashST_IsEmpty(const LPHashST* st);

int LPHashST_Size(const LPHashST* st);

Array(Key)* LPHashST_Keys(const LPHashST* st);