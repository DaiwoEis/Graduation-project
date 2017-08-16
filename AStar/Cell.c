#include "Cell.h"

struct Cell
{
	enum CellType type;
	struct Coordinate coordinate;
	PathData pathData;
};

Cell* Cell_Create(struct Coordinate coordinate, enum CellType type)
{
	Cell* cell = malloc(sizeof(Cell));
	cell->type = type;
	cell->coordinate = coordinate;

	return cell;
}

void Cell_Destroy(Cell* cell)
{
	if (cell == NULL) return;

	free(cell);
}

struct Coordinate Cell_Coordinate(Cell* cell)
{
	return cell->coordinate;
}

enum CellType Cell_Type(Cell* cell)
{
	return cell->type;
}

bool Cell_Eql(Cell* left, Cell* right)
{
	if (left == NULL || right == NULL) return false;

	if (left != right) return false;
	if (left->coordinate.col != right->coordinate.col) return false;
	if (left->coordinate.row != right->coordinate.row) return false;
	if (Cell_Type(left) != Cell_Type(right)) return false;

	return true;
}

int Cell_Cmp(Cell* left, Cell* right)
{
	if (left->pathData.F < right->pathData.F) return -1;
	if (left->pathData.F > right->pathData.F) return 1;

	return 0;
}

PathData Cell_GetPathData(Cell* cell)
{
	return cell->pathData;
}

void Cell_SetPathData(Cell* cell, PathData pathData)
{
	cell->pathData = pathData;
}
