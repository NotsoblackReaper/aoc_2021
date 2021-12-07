#include <algorithm>
#include <iostream>
#include <sstream>
#include <numeric>

#include "AOC_Solver.h"

int64_t aoc::day7::part_1(std::vector<int>& input) {
	std::vector<int>positions{input};
	std::ranges::sort(positions);

	int optimal_pos;
	if (positions.size() % 2 == 0)
		optimal_pos = (positions[positions.size() / 2 - 1] + positions[positions.size() / 2]) / 2;
	else
		optimal_pos = positions[positions.size() / 2];

	return std::accumulate(positions.begin(), positions.end(), 0ll, [&](auto a, auto b) {return a + std::abs(b - optimal_pos); });
}

int64_t aoc::day7::part_2(std::vector<int>& input) {
	std::vector<int>positions{input};
	int max = *std::ranges::max_element(positions);

	int min_score = INT_MAX;
	for (int i = 0; i < max; ++i)
	{
		if (int score = std::accumulate(positions.begin(), positions.end(), 0, [&](auto a, auto b) {
			int n = std::abs(b - i);
			return a + (n * (n + 1)) / 2;
			}); score < min_score)
			min_score = score;
	}

	return min_score;

}