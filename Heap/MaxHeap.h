#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct MaxHeap MaxHeap;

typedef int Key;

#define INIT_CAPACITY 4

MaxHeap* MaxHeap_Create(int(*cmpFun)(Key left, Key right));

MaxHeap* MaxHeap_Create_S(int(*cmpFun)(Key left, Key right), int size);

void MaxHeap_Destroy(MaxHeap* heap);

bool MaxHeap_IsEmpty(const MaxHeap* heap);

int MaxHeap_Size(const MaxHeap* heap);

void MaxHeap_Insert(MaxHeap* heap, Key key);

Key MaxHeap_Max(MaxHeap* heap);

Key MaxHeap_DeleteMax(MaxHeap* heap);