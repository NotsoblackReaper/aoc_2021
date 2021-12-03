#include "AOC_Solver.h"

int64_t aoc_solutions::day1::part_1(const std::vector<std::string>input)
{
	int result{ 0 };
	int last{ std::stoi(input.front()) };
	for (int i = 1; i < input.size(); ++i)
	{
		int tmp{ last };
		if (tmp < (last=std::stoi(input.at(i))))
			++result;
	}
	return result;
}

int64_t aoc_solutions::day1::part_2(const std::vector<std::string>input)
{
	int result{ 0 };
	for(int i=0;i<input.size()-3;++i)
	{
		if (std::stoi(input.at(i)) < std::stoi(input.at(i + 3)))
			++result;
	}
	return result;
}