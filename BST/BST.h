#pragma once

#include "BaseBST.h"
#include "Queue.h"

typedef struct BST BST;

BST* BST_Create();

BST* BST_Create_Cmp(int(*pCmp)(Key left, Key right));

void BST_Destroy(BST* bst);

void BST_Add(BST* bst, Key key, Value value);

Value BST_Get(const BST* bst, Key key);

void BST_Delete(BST* bst, Key key);

void BST_DeleteMax(BST* bst);

void BST_DeleteMin(BST* bst);

bool BST_Contains(const BST* bst, Key key);

bool BST_IsEmpty(const BST* bst);

int BST_Size(const BST* bst);

int BST_PartSize(const BST* bst, Key lo, Key hi);

Key BST_Min(const BST* bst);

Key BST_Max(const BST* bst);

Key BST_Floor(const BST* bst, Key key);

Key BST_Ceiling(const BST* bst, Key key);

int BST_Rank(const BST* bst, Key key);

Key BST_Select(const BST* bst, int k);

Queue* BST_Keys(BST* bst);

Queue* BST_PartKeys(BST* bst, Key lo, Key hi);

void BST_Traverse(BST* bst, void(*pFun)(Key key));