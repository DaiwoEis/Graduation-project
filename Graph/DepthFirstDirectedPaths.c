#include "DepthFirstDirectedPaths.h"

struct DirectedDFP
{
	Array(bool)* marked;
	Array(int)* edgeTo;
	int s;
};

void DirectedDFP_dfs(DirectedDFP* dfp, DiGraph* graph, int v)
{
	Array_Set(bool)(dfp->marked, v, true);
	Array(int)* adj = DiGraph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);
		if (!Array_Get(bool)(dfp->marked, w))
		{
			Array_Set(int)(dfp->edgeTo, w, v);
			DirectedDFP_dfs(dfp, graph, w);
		}
	}
}

DirectedDFP* DirectedDFP_Create(DiGraph* graph, int s)
{
	DirectedDFP* dfp = (DirectedDFP*)malloc(sizeof(DirectedDFP));
	dfp->s = s;
	dfp->marked = Array_Create(bool)(DiGraph_V(graph));
	dfp->edgeTo = Array_Create(int)(DiGraph_V(graph));
	DirectedDFP_dfs(dfp, graph, s);
	return dfp;
}

void DirectedDFP_Delete(DirectedDFP* dfp)
{
	Array_Destroy(bool)(dfp->marked);
	Array_Destroy(int)(dfp->edgeTo);
	free(dfp);
}

bool DirectedDFP_HasPathTo(DirectedDFP* dfp, int v)
{
	return Array_Get(bool)(dfp->marked, v);
}

Array(int)* DirectedDFP_PathTo(DirectedDFP* dfp, int v)
{
	if (!DirectedDFP_HasPathTo(dfp, v)) return NULL;

	IntVector* reversePath = IntVector_Create();
	for (int x = v; x != dfp->s; x = Array_Get(int)(dfp->edgeTo, x))
	{
		IntVector_Add(reversePath, x);
	}
	IntVector_Add(reversePath, dfp->s);

	Array(int)* path = IntVector_ToArray(reversePath);
	IntVector_Delete(reversePath);
	return path;
}

int main98()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");

	DiGraph* graph = DiGraph_Create_File(file);

	fclose(file);

	int s;
	puts("input the start point");
	scanf_s("%d", &s);

	DirectedDFP* dfp = DirectedDFP_Create(graph, s);

	for (int v = 0; v < DiGraph_V(graph); ++v)
	{
		if (DirectedDFP_HasPathTo(dfp, v))
		{
			printf("%d to %d: ", s, v);
			Array(int)* path = DirectedDFP_PathTo(dfp, v);
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

	DiGraph_Delete(graph);
	DirectedDFP_Delete(dfp);
	return 0;
}