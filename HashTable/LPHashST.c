#include "LPHashST.h"

struct LPHashST
{
	int size;
	int arraySize;
	Array(bool)* slots;
	Array(Key)* keys;
	Array(Value)* values;
	int(*hashFun)(Key key);
	bool(*eqlFun)(Key left, Key right);
};

int LPHashST_GetHash(const LPHashST* st, Key key)
{
	return (st->hashFun(key) & 0x7fffffff) % st->arraySize;
}

LPHashST* LPHashST_Create(int(*hashFun)(Key key))
{
	return LPHashST_Create_E(hashFun, NULL);
}

LPHashST* LPHashST_Create_E(int(*hashFun)(Key key), bool(*eqlFun)(Key left, Key right))
{
	return LPHashST_Create_ES(hashFun, eqlFun, 97);
}

LPHashST* LPHashST_Create_ES(int(*hashFun)(Key key), bool(*eqlFun)(Key left, Key right), int tableSize)
{
	LPHashST* st = (LPHashST*)malloc(sizeof(LPHashST));
	st->size = 0;
	st->arraySize = tableSize;
	st->hashFun = hashFun;
	if (eqlFun == NULL)
		st->eqlFun = DefaultEqlFun;
	else
		st->eqlFun = eqlFun;
	st->slots = Array_Create(bool)(tableSize);
	st->keys = Array_Create(Key)(tableSize);
	st->values = Array_Create(Value)(tableSize);
	return st;
}

void LPHashST_Destroy(LPHashST* st)
{
	Array_Destroy(bool)(st->slots);
	Array_Destroy(Key)(st->keys);
	Array_Destroy(Value)(st->values);
	free(st);
}

void LPHashST_Resize(LPHashST* st, int size)
{
	LPHashST* newST = LPHashST_Create_ES(st->hashFun, st->eqlFun, size);
	for (int i = 0; i < st->arraySize; ++i)
	{
		if (Array_Get(bool)(st->slots, i))
		{
			LPHashST_Add(newST, Array_Get(Key)(st->keys, i), Array_Get(Value)(st->values, i));
		}
	}

	Array_Destroy(bool)(st->slots);
	Array_Destroy(Key)(st->keys);
	Array_Destroy(Value)(st->values);

	st->slots = newST->slots;
	st->keys = newST->keys;
	st->values = newST->values;
	st->arraySize = newST->arraySize;
	free(newST);
}

void LPHashST_Add(LPHashST* st, Key key, Value value)
{
	if (st->size >= st->arraySize / 2)
		LPHashST_Resize(st, st->arraySize * 2);

	int i;
	for (i = LPHashST_GetHash(st, key); Array_Get(bool)(st->slots, i); i = (i + 1) % st->arraySize)
	{
		if (st->eqlFun(Array_Get(Key)(st->keys, i), key))
		{
			Array_Set(Value)(st->values, i, value);
			return;
		}
	}
	Array_Set(bool)(st->slots, i, true);
	Array_Set(Key)(st->keys, i, key);
	Array_Set(Value)(st->values, i, value);
	st->size++;
}

int LPHashST_GetIndex(const LPHashST* st, Key key)
{
	for (int i = LPHashST_GetHash(st, key); Array_Get(bool)(st->slots, i); i = (i + 1) % st->arraySize)
	{
		if (st->eqlFun(Array_Get(Key)(st->keys, i), key))
		{
			return i;
		}
	}

	return -1;
}

Value LPHashST_Get(const LPHashST* st, Key key)
{
	int index = LPHashST_GetIndex(st, key);
	if (index == -1)
	{
		puts("not contain the key");
		return 0;
	}
	else
	{
		return Array_Get(Value)(st->values, index);
	}	
}

void LPHashST_Delete(LPHashST* st, Key key)
{
	if (!LPHashST_Contains(st, key))
		return;

	int i = LPHashST_GetHash(st, key);
	while (!st->eqlFun(Array_Get(Key)(st->keys, i), key))
	{
		i = (i + 1) % st->arraySize;
	}

	Array_Set(bool)(st->slots, i, false);
	Array_Set(Key)(st->keys, i, 0);
	Array_Set(Value)(st->values, i, 0);

	i = (i + 1) % st->arraySize;
	while (Array_Get(bool)(st->slots, i))
	{
		Key keyToRehash = Array_Get(Key)(st->keys, i);
		Value valueToRehash = Array_Get(Value)(st->values, i);

		Array_Set(bool)(st->slots, i, false);
		Array_Set(Key)(st->keys, i, 0);
		Array_Set(Value)(st->values, i, 0);

		st->size--;
		LPHashST_Add(st, keyToRehash, valueToRehash);
		i = (i + 1) % st->arraySize;
	}

	st->size--;

	if (st->size > 0 && st->size <= st->arraySize / 8)
	{
		LPHashST_Resize(st, st->arraySize / 2);
	}
}

bool LPHashST_Contains(const LPHashST* st, Key key)
{
	return LPHashST_GetIndex(st, key) != -1;
}

bool LPHashST_IsEmpty(const LPHashST* st)
{
	return st->size == 0;
}

int LPHashST_Size(const LPHashST* st)
{
	return st->size;
}

Array(Key)* LPHashST_Keys(const LPHashST* st)
{
	Array(Key)* keys = Array_Create(Key)(st->size);
	int count = 0;
	for (int i = 0; i < st->arraySize; ++i)
	{
		if (Array_Get(bool)(st->slots, i))
		{
			Array_Set(Key)(keys, count++, Array_Get(Key)(st->keys, i));
		}
	}
	return keys;
}
