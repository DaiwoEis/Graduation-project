#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "Graph.h"
#include "IntegerArray.h"

typedef struct Cycle Cycle;

Cycle* Cycle_Create(Graph* graph);

void Cycle_Delete(Cycle* dc);

bool Cycle_HasCycle(Cycle* dc);

Array(int)* Cycle_Cycle(Cycle* dc);