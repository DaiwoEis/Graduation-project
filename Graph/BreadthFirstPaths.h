#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "Graph.h"
#include "IntegerArray.h"
#include "ArrayGeneric.h"

typedef struct BFP BFP;

BFP* BFP_Create(Graph* graph, int s);

void BFP_Delete(BFP* bfp);

bool BFP_HasPathTo(BFP* bfp, int v);

Array(int)* BFP_PathTo(BFP* bfp, int v);

int BFP_DistTo(BFP* bfp, int v);