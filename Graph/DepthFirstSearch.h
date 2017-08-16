#pragma once

#include "Graph.h"
#include "ArrayBase.h"
#include "ArrayGeneric.h"

typedef struct DFS DFS;

DFS* DFS_Create(Graph* graph, int s);

void DFS_Delete(DFS* dfs);

bool DFS_Marked(DFS* dfs, int v);

int DFS_Count(DFS* dfs);