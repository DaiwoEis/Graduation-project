#include "Graph.h"

struct Graph
{
	int V;
	int E;
	Array(IntVector)* adj;
};

Graph* Graph_Create(int vertexSize)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = vertexSize;
	graph->E = 0;
	graph->adj = Array_Create(IntVector)(vertexSize);
	return graph;
}

Graph* Graph_Create_File(FILE* file)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
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
		Graph_AddEdge(graph, v, w);
	}
	return graph;
}

void Graph_Delete(Graph* graph)
{
	if (graph == NULL) return;

	Array_Destroy(IntVector)(graph->adj);
	free(graph);
}

int Graph_V(const Graph* graph)
{
	return graph->V;
}

int Graph_E(const Graph* graph)
{
	return graph->E;
}

void Graph_AddEdge(Graph* graph, int v, int w)
{
	graph->E++;
	IntVector_Add(Array_Get(IntVector)(graph->adj, v), w);
	IntVector_Add(Array_Get(IntVector)(graph->adj, w), v);
}

Array(int)* Graph_Adj(const Graph* graph, int v)
{
	return IntVector_ToArray(Array_Get(IntVector)(graph->adj, v));
}

int main1()
{
	FILE* file;
	char fileName[50];
	puts("input the filename");
	scanf_s("%s", fileName, 50);
	fopen_s(&file, fileName, "r");
	Graph* graph = Graph_Create_File(file);
	fclose(file);
	printf("vertices:%d edges:%d\n", graph->V, graph->E);
	printf("vertex  edge\n");
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

	Graph_Delete(graph);
	return 0;
}