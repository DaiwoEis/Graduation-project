#include "Map.h"
#include "MinHeap.h"

void Fun(Cell* cell)
{
	printf("row:%4d col:%4d F:%4d", Cell_Coordinate(cell).row, Cell_Coordinate(cell).col, Cell_GetPathData(cell).F);
	if (Cell_Type(cell) == Obstacle)
		printf(" Obstacle\n");
	else
		printf(" Walkable\n");
}

bool List_Contains(List(Cell)* list, Cell* cell)
{
	for (int i = 0; i < List_Length(Cell)(list); ++i)
	{
		return Cell_Cmp(List_Get(Cell)(list, i), cell);
	}

	return false;
}

int main()
{
	Map* map = Map_Create("Map.xls");

	struct Coordinate coordinate = { 6,5 };
	List(Cell)* adjs = Map_GetAdjs(map, coordinate);
	//List_Traverse(Cell)(adjs, Fun);

	MinHeap* closeList = MinHeap_Create(Cell_Cmp);
	for (int i = List_Length(Cell)(adjs) - 1; i >= 0; --i)
	{
		PathData pathData = { List_Length(Cell)(adjs) - i,0,0 };
		Cell_SetPathData(List_Get(Cell)(adjs, i), pathData);
		MinHeap_Insert(closeList, List_Get(Cell)(adjs, i));
	}

	for (int i = List_Length(Cell)(adjs) - 1; i >= 0; --i)
	{
		if (MinHeap_Contains(closeList, (List_Get(Cell)(adjs, i))))
		{
			Fun(List_Get(Cell)(adjs, i));
		}
	}

	/*while (!MinHeap_IsEmpty(closeList))
	{
		Cell* cell = MinHeap_DeleteMin(closeList);
		Fun(cell);
	}*/

	MinHeap_Destroy(closeList);

	List_Destroy(Cell)(adjs);
	Map_Destroy(map);

	return 0;
}