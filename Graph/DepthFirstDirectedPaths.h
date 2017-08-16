#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "ArrayGeneric.h"
#include "IntegerArray.h"
#include "DirectedGraph.h"

typedef struct DirectedDFP DirectedDFP;

DirectedDFP* DirectedDFP_Create(DiGraph* graph, int s);

void DirectedDFP_Delete(DirectedDFP* dfp);

bool DirectedDFP_HasPathTo(DirectedDFP* dfp, int v);

Array(int)* DirectedDFP_PathTo(DirectedDFP* dfp, int v);