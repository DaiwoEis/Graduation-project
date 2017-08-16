#pragma once

#include "malloc.h"
#include "stdbool.h"

typedef struct Cell Cell;
typedef struct PathData PathData;

struct Coordinate
{
	int row;
	int col;
};

enum CellType
{
	Obstacle,
	Walkable
};

struct PathData
{
	int F;
	int G;
	int H;
};

Cell* Cell_Create(struct Coordinate coordinate, enum CellType type);

void Cell_Destroy(Cell* cell);

struct Coordinate Cell_Coordinate(Cell* cell);

enum CellType Cell_Type(Cell* cell);

bool Cell_Eql(Cell* left, Cell* right);

int Cell_Cmp(Cell* left, Cell* right);

PathData Cell_GetPathData(Cell* cell);

void Cell_SetPathData(Cell* cell, PathData pathData);