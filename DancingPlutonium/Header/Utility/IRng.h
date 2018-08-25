#pragma once

#include <random>

namespace DancingPlutonium
{
	/* Returns a random integer within the range of (A, B) */
	int RandomIntRange(const int& A, const int& B);
	/* Returns a random integer within the range of (0, 1) */
	float RandomFloatRange();
}