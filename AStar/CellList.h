#pragma once

#include "ListBase.h"
#include "Cell.h"

typedef Cell* CellList_Item;
const static int CellList_INIT_CAPACITY = 5;
const static CellList_Item CellList_DEAFULT_VALUE = NULL;

typedef struct CellList CellList;

CellList* CellList_Create();

CellList* CellList_Create_S(int size);

void CellList_Destroy(CellList* list);

void CellList_Set(CellList* list, int index, CellList_Item data);

CellList_Item CellList_Get(const CellList* list, int index);

void CellList_Add(CellList* list, CellList_Item data);

void CellList_Insert(CellList* list, int index, CellList_Item data);

void CellList_RemoveAt(CellList* list, int index);

int CellList_Length(const CellList* list);

void CellList_Clear(CellList* list);

void CellList_Traverse(CellList* list, void(*fun)(CellList_Item data));