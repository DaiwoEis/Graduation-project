#include "BreadthFirstPaths.h"
#include "IntQueue.h"

struct BFP
{
	int s;
	Array(bool)* marked;
	Array(int)* edgeTo;
	Array(int)* distTo;
};

void BFP_bfs(BFP* bfp, Graph* graph, int s)
{
	IntQueue* queue = IntQueue_Create();
	Array_Set(int)(bfp->distTo, s, 0);
	Array_Set(bool)(bfp->marked, s, true);
	IntQueue_EnQueue(queue, s);
	while (!IntQueue_IsEmpty(queue))
	{
		int v = IntQueue_DeQueue(queue);
		Array(int)* adj = Graph_Adj(graph, v);
		for (int i = 0; i < Array_Size(int)(adj); ++i)
		{
		
			int w = Array_Get(int)(adj, i);
			if (!Array_Get(bool)(bfp->marked, w))
			{
				Array_Set(bool)(bfp->marked, w, true);
				Array_Set(int)(bfp->edgeTo, w, v);
				Array_Set(int)(bfp->distTo, w, Array_Get(int)(bfp->distTo, v) + 1);
				IntQueue_EnQueue(queue, w);
			}
		}
		Array_Destroy(int)(adj);
	}
}

BFP* BFP_Create(Graph* graph, int s)
{
	BFP* bfp = (BFP*)malloc(sizeof(BFP));
	bfp->s = s;
	bfp->marked = Array_Create(bool)(Graph_V(graph));
	bfp->edgeTo = Array_Create(int)(Graph_V(graph));
	bfp->distTo = Array_Create(int)(Graph_V(graph));
	BFP_bfs(bfp, graph, s);
	return bfp;
}

void BFP_Delete(BFP* bfp)
{
	if (bfp == NULL) return;

	Array_Destroy(bool)(bfp->marked);
	Array_Destroy(int)(bfp->edgeTo);
	Array_Destroy(int)(bfp->distTo);
	free(bfp);
}

bool BFP_HasPathTo(BFP* bfp, int v)
{
	return Array_Get(bool)(bfp->marked, v);
}

Array(int)* BFP_PathTo(BFP* bfp, int v)
{
	if (!BFP_HasPathTo(bfp, v)) return NULL;

	IntVector* reversePath = IntVector_Create();
	for (int x = v; x != bfp->s; x = Array_Get(int)(bfp->edgeTo, x))
	{
		IntVector_Add(reversePath, x);
	}
	IntVector_Add(reversePath, bfp->s);

	Array(int)* path = IntVector_ToArray(reversePath);
	IntVector_Delete(reversePath);
	return path;
}

int BFP_DistTo(BFP* bfp, int v)
{
	return Array_Get(int)(bfp->distTo, v);
}

int main5()
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

	BFP* bfp = BFP_Create(graph, s);

	for (int v = 0; v < Graph_V(graph); ++v)
	{
		if (BFP_HasPathTo(bfp, v))
		{
			printf("%d to %d(%d): ", s, v, BFP_DistTo(bfp, v));
			Array(int)* path = BFP_PathTo(bfp, v);
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
	BFP_Delete(bfp);
	return 0;
}