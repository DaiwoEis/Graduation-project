#pragma once

#include <stdbool.h>
#include <malloc.h>
#include "Graph.h"
#include "IntegerArray.h"
#include "ArrayGeneric.h"

typedef struct CC CC;

CC* CC_Create(Graph* graph);

void CC_Delete(CC* cc);

bool CC_Connect(const CC* cc, int v, int w);

int CC_Count(const CC* cc);

int CC_Size(const CC* cc, int v);

int CC_ID(const CC* cc, int v);