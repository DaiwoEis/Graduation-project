#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "IntegerArray.h"
#include "IntVectorArray.h"

typedef struct Graph Graph;

Graph* Graph_Create(int vertexSize);

Graph* Graph_Create_File(FILE* file);

void Graph_Delete(Graph* graph);

int Graph_V(const Graph* graph);

int Graph_E(const Graph* graph);

void Graph_AddEdge(Graph* graph, int v, int w);

Array(int)* Graph_Adj(const Graph* graph, int v);