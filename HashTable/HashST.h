#pragma once

#include "HashBase.h"
#include "KeyArray.h"
#include "ValueArray.h"
#include "ArrayGeneric.h"

typedef struct HashST HashST;

HashST* HashST_Create(int(*hasnFun)(Key key));

HashST* HashST_Create_E(int(*hasnFun)(Key key), bool(*eqlFun)(Key left, Key right));

HashST* HashST_Create_ES(int(*hasnFun)(Key key), bool(*eqlFun)(Key left, Key right), int chainSize);

void HashST_Destroy(HashST* hashST);

void HashST_Add(HashST* hashST, Key key, Value value);

Value HashST_Get(const HashST* hashST, Key key);

void HashST_Delete(HashST* hashST, Key key);

bool HashST_Contains(const HashST* hashST, Key key);

bool HashST_IsEmpty(const HashST* hashST);

int HashST_Size(const HashST* hashST);

Array(Key)* HashST_Keys(const HashST* hashST);