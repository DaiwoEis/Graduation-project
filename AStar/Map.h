#pragma once

#include "malloc.h"
#include "Cell.h"
#include "CellList.h"
#include "ListGeneric.h"

typedef struct Map Map;

Map* Map_Create(const char* fileName);

void Map_Destroy(Map* map);

void Map_Traverse(Map* map, void(*fun)(Cell* cell));

Cell* Map_GetCell(Map* map, struct Coordinate coordinate);

List(Cell)* Map_GetAdjs(Map* map, struct Coordinate coordinate);