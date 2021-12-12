#include "AOC_Solver.h"

uint64_t aoc::day2::part_1(const std::vector<std::string>& input) {
	int down{ 0 }, horizontal{ 0 };
	for (auto& line : input) {
		if (line[0] == 'f')			horizontal += line[8] - 48;
		else if (line[0] == 'd')	down += line[5] - 48;
		else						down -= line[3] - 48;
	}
	return down * horizontal;
}

uint64_t aoc::day2::part_2(const std::vector<std::string>& input) {
	int down{ 0 }, horizontal{ 0 }, aim{ 0 };
	for (auto& line : input) {
		if (line[0] == 'd')aim += line[5] - 48;
		else if(line[0]=='u')aim -= line[3] - 48;
		else{
			horizontal += line[8] - 48;
			down += (line[8] - 48) * aim;
		}
	}
	return down * horizontal;
}
