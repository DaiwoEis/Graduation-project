#include "BreadthFirstDirectedPaths.h"
#include "IntQueue.h"

struct DirectedBFP
{
	int s;
	Array(bool)* marked;
	Array(int)* edgeTo;
	Array(int)* distTo;
};

void DirectedBFP_bfs(DirectedBFP* bfp, DiGraph* graph, int s)
{
	IntQueue* queue = IntQueue_Create();
	Array_Set(int)(bfp->distTo, s, 0);
	Array_Set(bool)(bfp->marked, s, true);
	IntQueue_EnQueue(queue, s);
	while (!IntQueue_IsEmpty(queue))
	{
		int v = IntQueue_DeQueue(queue);
		Array(int)* adj = DiGraph_Adj(graph, v);
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

DirectedBFP* DirectedBFP_Create(DiGraph* graph, int s)
{
	DirectedBFP* bfp = (DirectedBFP*)malloc(sizeof(DirectedBFP));
	bfp->s = s;
	bfp->marked = Array_Create(bool)(DiGraph_V(graph));
	bfp->edgeTo = Array_Create(int)(DiGraph_V(graph));
	bfp->distTo = Array_Create(int)(DiGraph_V(graph));
	DirectedBFP_bfs(bfp, graph, s);
	return bfp;
}

void DirectedBFP_Delete(DirectedBFP* bfp)
{
	if (bfp == NULL) return;

	Array_Destroy(bool)(bfp->marked);
	Array_Destroy(int)(bfp->edgeTo);
	Array_Destroy(int)(bfp->distTo);
	free(bfp);
}

bool DirectedBFP_HasPathTo(DirectedBFP* bfp, int v)
{
	return Array_Get(bool)(bfp->marked, v);
}

Array(int)* DirectedBFP_PathTo(DirectedBFP* bfp, int v)
{
	if (!DirectedBFP_HasPathTo(bfp, v)) return NULL;

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

int DirectedBFP_DistTo(DirectedBFP* bfp, int v)
{
	return Array_Get(int)(bfp->distTo, v);
}

int main97()
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

	DirectedBFP* bfp = DirectedBFP_Create(graph, s);

	for (int v = 0; v < DiGraph_V(graph); ++v)
	{
		if (DirectedBFP_HasPathTo(bfp, v))
		{
			printf("%d to %d(%d): ", s, v, DirectedBFP_DistTo(bfp, v));
			Array(int)* path = DirectedBFP_PathTo(bfp, v);
			for (int i = 0; i < Array_Size(int)(path); ++i)
			{
				int x = Array_Get(int)(path, i);
				if (x == s)
					printf("%d", x);
				else
					printf("->%d", x);
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
	DirectedBFP_Delete(bfp);
	return 0;
}