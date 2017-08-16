#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct MinHeap MinHeap;

typedef int Key;

#define INIT_CAPACITY 4

MinHeap* MinHeap_Create(int(*cmpFun)(Key left, Key right));

MinHeap* MinHeap_Create_S(int(*cmpFun)(Key left, Key right), int size);

void MinHeap_Destroy(MinHeap* heap);

bool MinHeap_IsEmpty(const MinHeap* heap);

int MinHeap_Size(const MinHeap* heap);

void MinHeap_Insert(MinHeap* heap, Key key);

Key MinHeap_Min(MinHeap* heap);

Key MinHeap_DeleteMin(MinHeap* heap);