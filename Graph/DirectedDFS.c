#include "DirectedDFS.h"

struct DirectedDFS
{
	Array(bool)* marked;
	int count;
};

void DirectedDFS_dfs(DirectedDFS* dfs, DiGraph* graph, int v)
{
	dfs->count++;
	Array_Set(bool)(dfs->marked, v, true);
	Array(int)* adj = DiGraph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);
		if (!Array_Get(bool)(dfs->marked, w))
		{
			DirectedDFS_dfs(dfs, graph, w);
		}
	}
}

DirectedDFS* DirectedDFS_Create(DiGraph* graph, int s)
{
	DirectedDFS* dfs = (DirectedDFS*)malloc(sizeof(DirectedDFS));
	dfs->count = 0;
	dfs->marked = Array_Create(bool)(DiGraph_V(graph));
	DirectedDFS_dfs(dfs, graph, s);
	return dfs;
}

void DirectedDFS_Delete(DirectedDFS* dfs)
{
	if (dfs == NULL) return;

	Array_Destroy(bool)(dfs->marked);
	free(dfs);
}

bool DirectedDFS_Marked(DirectedDFS* dfs, int v)
{
	return Array_Get(bool)(dfs->marked, v);
}

int DirectedDFS_Count(DirectedDFS* dfs)
{
	return dfs->count;
}

int main99()
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

	DirectedDFS* dfs = DirectedDFS_Create(graph, s);
	printf("vertices can reached with %d\n", s);
	for (int v = 0; v < DiGraph_V(graph); ++v)
	{
		if (DirectedDFS_Marked(dfs, v))
		{
			printf("%d ", v);
		}
	}

	putchar('\n');

	DirectedDFS_Delete(dfs);
	DiGraph_Delete(graph);

	return 0;
}