#include "ConnectComponent.h"

struct CC
{
	Array(bool)* marked;
	Array(int)* size;
	Array(int)* id;
	int count;
};

void CC_dfs(CC* cc, Graph* graph, int v)
{
	Array_Set(bool)(cc->marked, v, true);
	int curCC = cc->count;
	Array_Set(int)(cc->id, v, curCC);
	Array_Set(int)(cc->size, curCC, Array_Get(int)(cc->size, curCC));
	Array(int)* adj = Graph_Adj(graph, v);
	for (int i = 0; i < Array_Size(int)(adj); ++i)
	{
		int w = Array_Get(int)(adj, i);
		if (!Array_Get(bool)(cc->marked, w))
		{
			CC_dfs(cc, graph, w);
		}
	}
}

CC* CC_Create(Graph* graph)
{
	CC* cc = (CC*)malloc(sizeof(CC));
	cc->count = 0;
	cc->marked = Array_Create(bool)(Graph_V(graph));
	cc->id = Array_Create(int)(Graph_V(graph));
	cc->size = Array_Create(int)(Graph_V(graph));
	for (int v = 0; v < Graph_V(graph); ++v)
	{
		if (!Array_Get(bool)(cc->marked, v))
		{
			CC_dfs(cc, graph, v);
			cc->count++;
		}
	}
	return cc;
}

void CC_Delete(CC* cc)
{
	if (cc == NULL) return;

	Array_Destroy(bool)(cc->marked);
	Array_Destroy(int)(cc->id);
	Array_Destroy(int)(cc->size);
	free(cc);
}

bool CC_Connect(const CC* cc, int v, int w)
{
	return Array_Get(int)(cc->id, v) == Array_Get(int)(cc->id, w);
}

int CC_Count(const CC* cc)
{
	return cc->count;
}

int CC_Size(const CC* cc, int v)
{
	return Array_Get(int)(cc->size, Array_Get(int)(cc->id, v));
}

int CC_ID(const CC* cc, int v)
{
	return Array_Get(int)(cc->id, v);
}

int main4()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");
	Graph* graph = Graph_Create_File(file);
	fclose(file);

	CC* cc = CC_Create(graph);
	int count = CC_Count(cc);
	printf("%d components\n", count);
	
	for (int i = 0; i < count; ++i)
	{
		for (int v = 0; v < Graph_V(graph); ++v)
		{
			if (CC_ID(cc, v) == i)
			{
				printf("%d ", v);
			}
		}
		putchar('\n');
	}

	putchar('\n');
	CC_Delete(cc);
	Graph_Delete(graph);
	return 0;
}