#include "AOC_Solver.h"

int64_t aoc_solutions::day2::part_1(const std::vector<std::string>input)
{
	int down{ 0 }, horizontal{ 0 };

	for (auto line : input) {
		if (line.front() == 'f') {
			horizontal += line.at(8) - 48;
		}
		if (line.front() == 'd')down += line.at(5) - 48;
		if (line.front() == 'u')down -= line.at(3) - 48;
	}
	return down * horizontal;
}

int64_t aoc_solutions::day2::part_2(const std::vector<std::string>input)
{
	int down{ 0 }, horizontal{ 0 }, aim{ 0 };

	for (auto line:input) {
		if (line.front()=='f') {
			int x = line.at(8) - 48;
			horizontal += x;
			down += x * aim;
		}
		if (line.front() == 'd')aim += line.at(5) - 48;
		if (line.front() == 'u')aim -= line.at(3) - 48;
	}
	return down * horizontal;
}
