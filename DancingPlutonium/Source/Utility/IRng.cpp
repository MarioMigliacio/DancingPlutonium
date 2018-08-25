#include "IRng.h"

int DancingPlutonium::RandomIntRange(const int& A, const int& B)
{
	static std::random_device randDev;
	static std::mt19937 twister(randDev());
	static std::uniform_int_distribution<int> dist;
	dist.param(std::uniform_int_distribution<int>::param_type(A, B));

	return dist(twister);
}

float DancingPlutonium::RandomFloatRange()
{
	static std::random_device randDev;
	static std::mt19937 twister(randDev());
	static std::uniform_real_distribution<double> dist;
	dist.param(std::uniform_real_distribution<double>::param_type(0, 1));

	return static_cast<float>(dist(twister));
}
