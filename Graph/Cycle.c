#include "Cycle.h"
#include "IntStack.h"
#include "ArrayGeneric.h"

struct Cycle
{
	Array(bool)* marked;
	Array(int)* edgeTo;
	IntStack* cycle;
};

void Cycle_dfs(Cycle* dc, Graph* graph, int v, int u)
{
	Array_Set(bool)(dc->marked, v, true);
	Array(int)* adj = Graph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);

		if (dc->cycle != NULL)
		{
			return;
		}
		else if (!Array_Get(bool)(dc->marked, w))
		{
			Array_Set(int)(dc->edgeTo, w, v);
			Cycle_dfs(dc, graph, w, v);
		}
		else if (w != u)
		{
			dc->cycle = IntStack_Create();
			for (int x = v; x != w; x = Array_Get(int)(dc->edgeTo, x))
			{
				IntStack_Push(dc->cycle, x);
			}
			IntStack_Push(dc->cycle, w);
			IntStack_Push(dc->cycle, v);
		}
	}
	Array_Destroy(int)(adj);
}

Cycle* Cycle_Create(Graph* graph)
{
	Cycle* dc = (Cycle*)malloc(sizeof(Cycle));
	dc->marked = Array_Create(bool)(Graph_V(graph));
	dc->edgeTo = Array_Create(int)(Graph_V(graph));
	dc->cycle = NULL;
	for (int v = 0; v < Graph_V(graph); ++v)
	{
		if (!Array_Get(bool)(dc->marked, v) && dc->cycle == NULL)
		{
			Cycle_dfs(dc, graph, v, -1);
		}
	}
	return dc;
}

void Cycle_Delete(Cycle* dc)
{
	if (dc != NULL) return;

	Array_Destroy(bool)(dc->marked);
	Array_Destroy(int)(dc->edgeTo);
	if (dc->cycle != NULL)
	{
		IntStack_Delete(dc->cycle);
		dc->cycle = NULL;
	}
	free(dc);
}

bool Cycle_HasCycle(Cycle* dc)
{
	return dc->cycle != NULL;
}

Array(int)* Cycle_Cycle(Cycle* dc)
{
	return IntStack_ToArray(dc->cycle);
}

int main()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");
	Graph* graph = Graph_Create_File(file);
	fclose(file);

	Cycle* dc = Cycle_Create(graph);
	if (Cycle_HasCycle(dc))
	{
		puts("Has cycle");
		Array(int)* cycle = Cycle_Cycle(dc);
		for (int i = 0; i < Array_Size(int)(cycle); ++i)
		{
			int v = Array_Get(int)(cycle, i);
			if (i == 0)
			{
				printf("%d", v);
			}
			else
			{
				printf("-%d", v);
			}
		}
		Array_Destroy(int)(cycle);
	}
	else
	{
		puts("No cycle");
	}

	putchar('\n');

	Graph_Delete(graph);
	Cycle_Delete(dc);
	return 0;
}