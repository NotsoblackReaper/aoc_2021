#include <algorithm>
#include <numeric>

#include "AOC_Solver.h"

int64_t aoc::day7::part_1(std::vector<int>& input) {
	int optimal_pos;
	std::ranges::nth_element(input, input.begin() + input.size() / 2);
	if (input.size() % 2 == 0) {
		std::ranges::nth_element(input, input.begin() + (input.size() - 1) / 2);
		optimal_pos = (input[(input.size() - 1) / 2]
			+ input[input.size() / 2]) / 2;
	}
	else
		optimal_pos = input[input.size() / 2];
	return std::accumulate(input.begin(), input.end(), 0ll, [&](auto a, auto b) {return a + std::abs(b - optimal_pos); });
}

int64_t aoc::day7::part_2(std::vector<int>& input) {
	int optimal_pos = std::accumulate(input.begin(), input.end(), 0) / input.size();
	return std::accumulate(input.begin(), input.end(), 0, [&](auto a, auto b) {
		int n = std::abs(b - optimal_pos);
		return a + (n * (n + 1)) / 2;
		});
}