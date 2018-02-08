#pragma once

#include "Vector2.h"

class Axis
{
public:
	Vector2* vector;
	Vector2* c1corners[4];
	Vector2* c2corners[4];
	Vector2* c1min, c1max, c2min, c2max;
	Axis();
};