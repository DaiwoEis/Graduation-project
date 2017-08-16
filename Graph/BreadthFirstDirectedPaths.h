#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "DirectedGraph.h"
#include "IntegerArray.h"
#include "ArrayGeneric.h"

typedef struct DirectedBFP DirectedBFP;

DirectedBFP* DirectedBFP_Create(DiGraph* graph, int s);

void DirectedBFP_Delete(DirectedBFP* bfp);

bool DirectedBFP_HasPathTo(DirectedBFP* bfp, int v);

Array(int)* DirectedBFP_PathTo(DirectedBFP* bfp, int v);

int DirectedBFP_DistTo(DirectedBFP* bfp, int v);