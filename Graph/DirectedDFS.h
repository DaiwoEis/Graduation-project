#pragma once

#include "DirectedGraph.h"
#include "ArrayBase.h"
#include "ArrayGeneric.h"

typedef struct DirectedDFS DirectedDFS;

DirectedDFS* DirectedDFS_Create(DiGraph* graph, int s);

void DirectedDFS_Delete(DirectedDFS* dfs);

bool DirectedDFS_Marked(DirectedDFS* dfs, int v);

int DirectedDFS_Count(DirectedDFS* dfs);