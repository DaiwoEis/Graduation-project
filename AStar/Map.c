#include "Map.h"

struct Map
{
	List(Cell)* cells;
	int rows;
	int cols;
};

Map* Map_Create(const char* fileName)
{
	Map* map = malloc(sizeof(Map));

	FILE* file;
	fopen_s(&file, fileName, "r");
	fscanf_s(file, "%d%d", &map->rows, &map->cols);

	map->cells = List_Create_S(Cell)(map->rows*map->cols);
	List_Clear(Cell)(map->cells);

	int temp;
	int count = 0;
	while (fscanf_s(file, "%d", &temp) != EOF)
	{		
		struct Coordinate coordinate;
		coordinate.row = count / map->cols + 1;
		coordinate.col = count%map->cols + 1;
		Cell* cell;
		if (temp == 0)
		{
			cell = Cell_Create(coordinate, Obstacle);			
		}
		else
		{
			cell = Cell_Create(coordinate, Walkable);
		}
		List_Add(Cell)(map->cells, cell);
		count++;
	}

	fclose(file);

	return map;
}

void Map_Destroy(Map* map)
{
	if (map == NULL) return;

	for (int i = 0; i < List_Length(Cell)(map->cells); ++i)
	{
		if (List_Get(Cell)(map->cells, i) != NULL)
		{
			Cell_Destroy(List_Get(Cell)(map->cells, i));
		}
	}
	List_Destroy(Cell)(map->cells);

	free(map);
}

void Map_Traverse(Map* map, void(*fun)(Cell* cell))
{
	for (int i = 0; i < List_Length(Cell)(map->cells); ++i)
	{
		if (List_Get(Cell)(map->cells, i) != NULL)
		{
			fun(List_Get(Cell)(map->cells, i));
		}
	}
}

Cell* Map_GetCell(Map* map, struct Coordinate coordinate)
{
	int index = (coordinate.row - 1)*map->cols + coordinate.col - 1;
	if (index<0 || index>=List_Length(Cell)(map->cells))
	{
		return NULL;
	}
	else
	{
		return List_Get(Cell)(map->cells, index);
	}
}

bool Map_ValidateCoordinate(const Map* map, struct Coordinate coordinate)
{
	return coordinate.col >= 1 && coordinate.col <= map->cols&&coordinate.row >= 1 && coordinate.row <= map->rows;
}

List(Cell)* Map_GetAdjs(Map* map, struct Coordinate coordinate)
{
	List(Cell)* cells = List_Create(Cell)();
	for (int i = -1; i <= 1; ++i)
	{
		struct Coordinate adjCoordinate;
		adjCoordinate.row = coordinate.row + i;
		for (int j = -1; j <= 1; ++j)
		{
			adjCoordinate.col = coordinate.col + j;
			if (coordinate.col == adjCoordinate.col&&coordinate.row == adjCoordinate.row) continue;
			if (Map_ValidateCoordinate(map, adjCoordinate))
			{
				List_Add(Cell)(cells, Map_GetCell(map, adjCoordinate));
			}
		}
	}

	return cells;
}

