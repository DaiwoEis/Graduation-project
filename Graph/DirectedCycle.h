#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "DirectedGraph.h"
#include "IntegerArray.h"

typedef struct DirectedCycle DirectedCycle;

DirectedCycle* DirectedCycle_Create(DiGraph* graph);

void DirectedCycle_Delete(DirectedCycle* dc);

bool DirectedCycle_HasCycle(DirectedCycle* dc);

Array(int)* DirectedCycle_Cycle(DirectedCycle* dc);