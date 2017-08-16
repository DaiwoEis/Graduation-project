#include "DepthFirstPaths.h"

struct DFP
{
	Array(bool)* marked;
	Array(int)* edgeTo;
	int s;
};

void DFP_dfs(DFP* dfp, Graph* graph, int v)
{
	Array_Set(bool)(dfp->marked, v, true);
	Array(int)* adj = Graph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);
		if (!Array_Get(bool)(dfp->marked, w))
		{
			Array_Set(int)(dfp->edgeTo, w, v);
			DFP_dfs(dfp, graph, w);
		}
	}
}

DFP* DFP_Create(Graph* graph, int s)
{
	DFP* dfp = (DFP*)malloc(sizeof(DFP));
	dfp->s = s;
	dfp->marked = Array_Create(bool)(Graph_V(graph));
	dfp->edgeTo = Array_Create(int)(Graph_V(graph));
	DFP_dfs(dfp, graph, s);
	return dfp;
}

void DFP_Delete(DFP* dfp)
{
	Array_Destroy(bool)(dfp->marked);
	Array_Destroy(int)(dfp->edgeTo);
	free(dfp);
}

bool DFP_HasPathTo(DFP* dfp, int v)
{
	return Array_Get(bool)(dfp->marked, v);
}

Array(int)* DFP_PathTo(DFP* dfp, int v)
{
	if (!DFP_HasPathTo(dfp, v)) return NULL;
	
	IntVector* reversePath = IntVector_Create();
	for (int x = v; x != dfp->s; x = Array_Get(int)(dfp->edgeTo, x))
	{
		IntVector_Add(reversePath, x);
	}
	IntVector_Add(reversePath, dfp->s);

	Array(int)* path = IntVector_ToArray(reversePath);
	IntVector_Delete(reversePath);
	/*int size = Array_Size(int)(path);
	for (int i = 0; i < size / 2; ++i)
	{
		int temp = Array_Get(int)(path, i);
		Array_Set(int)(path, i, Array_Get(int)(path, size - i - 1));
		Array_Set(int)(path, size - i - 1, temp);
	}*/
	return path;
}

int main3()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");

	Graph* graph = Graph_Create_File(file);

	fclose(file);

	int s;
	puts("input the start point");
	scanf_s("%d", &s);

	DFP* dfp = DFP_Create(graph, s);

	for (int v = 0; v < Graph_V(graph); ++v)
	{
		if (DFP_HasPathTo(dfp, v))
		{
			printf("%d to %d: ", s, v);
			Array(int)* path = DFP_PathTo(dfp, v);
			for (int i = 0; i < Array_Size(int)(path); ++i)
			{
				int x = Array_Get(int)(path, i);
				if (x == s)
					printf("%d", x);
				else
					printf("-%d", x);
			}
			putchar('\n');
			Array_Destroy(int)(path);
		}
		else
		{
			printf("%d to %d: not connected\n", s, v);
		}
	}

	Graph_Delete(graph);
	DFP_Delete(dfp);
	return 0;
}