#include "IRng.h"

int DancingPlutonium::RandomIntRange(const int& A, const int& B)
{
	static std::random_device randDev;
	static std::mt19937 twister(randDev());
	static std::uniform_int_distribution<int> dist;
	dist.param(std::uniform_int_distribution<int>::param_type(A, B));

	return dist(twister);
}