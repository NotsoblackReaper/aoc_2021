#include "AOC_Solver.h"

int64_t calc(std::vector<int>& input, int offset, int result = 0) {
	for (size_t i = 0; i < input.size() - offset; ++i)
		if (input[i] < input[i + offset])
			++result;
	return result;
}

int64_t aoc::day1::part_1(std::vector<int>& input) { return calc(input, 1); }
int64_t aoc::day1::part_2(std::vector<int>& input) { return calc(input, 3); }