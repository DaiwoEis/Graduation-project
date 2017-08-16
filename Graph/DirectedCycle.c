#include "DirectedCycle.h"
#include "IntStack.h"
#include "ArrayGeneric.h"

struct DirectedCycle
{
	Array(bool)* marked;
	Array(bool)* onStack;
	Array(int)* edgeTo;
	IntStack* cycle;
};

void DirectedCycle_dfs(DirectedCycle* dc, DiGraph* graph, int v)
{
	Array_Set(bool)(dc->marked, v, true);
	Array_Set(bool)(dc->onStack, v, true);
	Array(int)* adj = DiGraph_Adj(graph, v);
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
			DirectedCycle_dfs(dc, graph, w);
		}
		else if (Array_Get(bool)(dc->onStack, w))
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
	Array_Set(bool)(dc->onStack, v, false);
}

DirectedCycle* DirectedCycle_Create(DiGraph* graph)
{
	DirectedCycle* dc = (DirectedCycle*)malloc(sizeof(DirectedCycle));
	dc->marked = Array_Create(bool)(DiGraph_V(graph));
	dc->onStack = Array_Create(bool)(DiGraph_V(graph));
	dc->edgeTo = Array_Create(int)(DiGraph_V(graph));
	dc->cycle = NULL;
	for (int v = 0; v < DiGraph_V(graph); ++v)
	{
		if (!Array_Get(bool)(dc->marked, v) && dc->cycle == NULL)
		{
			DirectedCycle_dfs(dc, graph, v);
		}
	}
	return dc;
}

void DirectedCycle_Delete(DirectedCycle* dc)
{
	if (dc != NULL) return;

	Array_Destroy(bool)(dc->marked);
	Array_Destroy(bool)(dc->onStack);
	Array_Destroy(int)(dc->edgeTo);
	if (dc->cycle != NULL)
	{
		IntStack_Delete(dc->cycle);
		dc->cycle = NULL;
	}
	free(dc);
}

bool DirectedCycle_HasCycle(DirectedCycle* dc)
{
	return dc->cycle != NULL;
}

Array(int)* DirectedCycle_Cycle(DirectedCycle* dc)
{
	return IntStack_ToArray(dc->cycle);
}

int main96()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");
	DiGraph* graph = DiGraph_Create_File(file);
	fclose(file);

	DirectedCycle* dc = DirectedCycle_Create(graph);
	if (DirectedCycle_HasCycle(dc))
	{
		puts("Has directed cycle");
		Array(int)* cycle = DirectedCycle_Cycle(dc);
		for (int i = 0; i < Array_Size(int)(cycle); ++i)
		{
			int v = Array_Get(int)(cycle, i);
			if (i == 0)
			{
				printf("%d", v);
			}
			else
			{
				printf("->%d", v);
			}
		}
		Array_Destroy(int)(cycle);
	}
	else
	{
		puts("No directed cycle");
	}

	putchar('\n');

	DiGraph_Delete(graph);
	DirectedCycle_Delete(dc);
	return 0;
}