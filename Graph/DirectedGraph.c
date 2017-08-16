#include "DirectedGraph.h"
#include "ArrayGeneric.c"

struct DiGraph
{
	int V;
	int E;
	Array(IntVector)* adj;
};

DiGraph* DiGraph_Create(int vertexSize)
{
	DiGraph* graph = (DiGraph*)malloc(sizeof(DiGraph));
	graph->V = vertexSize;
	graph->E = 0;
	graph->adj = Array_Create(IntVector)(vertexSize);
	return graph;
}

DiGraph* DiGraph_Create_File(FILE* file)
{
	DiGraph* graph = (DiGraph*)malloc(sizeof(DiGraph));
	graph->V = graph->E = 0;
	char c;
	fscanf_s(file, "%d", &graph->V);
	fscanf_s(file, "%c", &c, 1);//read the '\n' char
	int e;
	fscanf_s(file, "%d", &e);
	fscanf_s(file, "%c", &c, 1);
	graph->adj = Array_Create(IntVector)(graph->V);
	int v, w;
	for (int i = 0; i < e; ++i)
	{
		fscanf_s(file, "%d", &v);
		fscanf_s(file, "%d", &w);
		fscanf_s(file, "%c", &c, 1);
		DiGraph_AddEdge(graph, v, w);
	}
	return graph;
}

void DiGraph_Delete(DiGraph* graph)
{
	if (graph == NULL) return;

	Array_Destroy(IntVector)(graph->adj);
	free(graph);
}

int DiGraph_V(const DiGraph* graph)
{
	return graph->V;
}

int DiGraph_E(const DiGraph* graph)
{
	return graph->E;
}

void DiGraph_AddEdge(DiGraph* graph, int v, int w)
{
	graph->E++;
	IntVector_Add(Array_Get(IntVector)(graph->adj, v), w);
}

Array(int)* DiGraph_Adj(const DiGraph* graph, int v)
{
	return IntVector_ToArray(Array_Get(IntVector)(graph->adj, v));
}

DiGraph* DiGraph_Reverse(const DiGraph* graph)
{
	DiGraph* reverseGraph = DiGraph_Create(graph->V);
	for (int v = 0; v < graph->V; ++v)
	{
		Array(int)* adj = IntVector_ToArray(Array_Get(IntVector)(graph->adj, v));
		for (int i = 0; i < Array_Size(int)(adj); ++i)
		{
			int w = Array_Get(int)(adj, i);
			DiGraph_AddEdge(reverseGraph, w, v);
		}
	}
	return reverseGraph;
}

int main100()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");
	DiGraph* graph = DiGraph_Create_File(file);
	fclose(file);
	printf("vertices:%d edges:%d\n", graph->V, graph->E);
	printf("vertex edge\n");
	for (int v = 0; v < graph->V; ++v)
	{
		printf("%-6d", v);
		Array(int)* adj = IntVector_ToArray(Array_Get(IntVector)(graph->adj, v));
		for (int i = 0; i < Array_Size(int)(adj); ++i)
		{
			int w = Array_Get(int)(adj, i);
			printf(" %d", w);
		}
		putchar('\n');
		Array_Destroy(int)(adj);
	}

	DiGraph_Delete(graph);
	return 0;
}