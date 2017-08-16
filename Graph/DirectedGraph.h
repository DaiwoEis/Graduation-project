#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "IntegerArray.h"
#include "IntVectorArray.h"

typedef struct DiGraph DiGraph;

DiGraph* DiGraph_Create(int vertexSize);

DiGraph* DiGraph_Create_File(FILE* file);

void DiGraph_Delete(DiGraph* graph);

int DiGraph_V(const DiGraph* graph);

int DiGraph_E(const DiGraph* graph);

void DiGraph_AddEdge(DiGraph* graph, int v, int w);

Array(int)* DiGraph_Adj(const DiGraph* graph, int v);

DiGraph* DiGraph_Reverse(const DiGraph* graph);