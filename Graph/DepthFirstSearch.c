#include "DepthFirstSearch.h"

struct DFS
{
	Array(bool)* marked;
	int count;
};

void DFS_dfs(DFS* dfs, Graph* graph, int v)
{
	dfs->count++;
	Array_Set(bool)(dfs->marked, v, true);
	Array(int)* adj = Graph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);
		if (!Array_Get(bool)(dfs->marked, w))
		{
			DFS_dfs(dfs, graph, w);
		}
	}
}

DFS* DFS_Create(Graph* graph, int s)
{
	DFS* dfs = (DFS*)malloc(sizeof(DFS));
	dfs->count = 0;
	dfs->marked = Array_Create(bool)(Graph_V(graph));
	DFS_dfs(dfs, graph, s);
	return dfs;
}

void DFS_Delete(DFS* dfs)
{
	if (dfs == NULL) return;

	Array_Destroy(bool)(dfs->marked);
	free(dfs);
}

bool DFS_Marked(DFS* dfs, int v)
{
	return Array_Get(bool)(dfs->marked, v);
}

int DFS_Count(DFS* dfs)
{
	return dfs->count;
}

int main2()
{
	FILE* file;
	fopen_s(&file, "tinyG.txt", "r");

	Graph* graph = Graph_Create_File(file);

	fclose(file);

	int s;
	scanf_s("%d", &s);

	DFS* dfs = DFS_Create(graph, s);

	for (int v = 0; v < Graph_V(graph); ++v)
	{
		if (DFS_Marked(dfs, v))
		{
			printf("%d ", v);
		}
	}

	putchar('\n');

	if (DFS_Count(dfs) != Graph_V(graph))
		puts("not connected");
	else
		puts("connected");

	getchar();

	DFS_Delete(dfs);
	Graph_Delete(graph);
	
	return 0;
}