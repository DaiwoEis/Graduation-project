#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "ArrayGeneric.h"
#include "IntegerArray.h"
#include "Graph.h"

typedef struct DFP DFP;

DFP* DFP_Create(Graph* graph, int s);

void DFP_Delete(DFP* dfp);

bool DFP_HasPathTo(DFP* dfp, int v);

Array(int)* DFP_PathTo(DFP* dfp, int v);