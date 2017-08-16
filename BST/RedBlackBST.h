#pragma once

#include "BaseBST.h"
#include "Queue.h"

typedef struct RedBlackBST RedBlackBST;

RedBlackBST* RedBlackBST_Create();

RedBlackBST* RedBlackBST_Create_Cmp(int(*pCmp)(Key left, Key right));

void RedBlackBST_Delete(RedBlackBST** bst);

void RedBlackBST_Add(RedBlackBST* bst, Key key, Value value);

Value RedBlackBST_Get(const RedBlackBST* bst, Key key);

bool RedBlackBST_Contains(const RedBlackBST* bst, Key key);

bool RedBlackBST_IsEmpty(const RedBlackBST* bst);

int RedBlackBST_Size(const RedBlackBST* bst);

Queue* RedBlackBST_Keys(RedBlackBST* bst);