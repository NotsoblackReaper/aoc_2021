#include "AOC_Solver.h"

int64_t aoc::day1::part_1(std::vector<int>& input)
{
	int result{ 0 };
	int last{ input.front() };
	for (int i = 1; i < input.size(); ++i)
	{
		int tmp{ last };
		if (tmp < (last=input.at(i)))
			++result;
	}
	return result;
}

int64_t aoc::day1::part_2(std::vector<int>& input)
{
	int result{ 0 };
	for(int i=0;i<input.size()-3;++i)
	{
		if (input.at(i) < input.at(i + 3))
			++result;
	}
	return result;
}