#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "CAString.h"

typedef CAString* Key;

typedef CAString* Value;

inline bool DefaultEqlFun(Key left, Key right)
{
	return left == right;
}