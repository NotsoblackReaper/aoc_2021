#include <array>
#include <sstream>
#include <numeric>

#include "AOC_Solver.h"

int64_t calculate_fishes(std::string& input,int n){
	std::array<int64_t, 9>days{};
	int pos{};
	for (auto& c : input)
		if (pos++ % 2 == 0)
			days[c - 48]++;

	for (int i = 0; i < n; i++)
		days[(7 + i) % 9] += days[i % 9];

	return std::accumulate(days.begin(), days.end(), 0ll);
}

int64_t aoc::day6::part_1(std::vector<std::string>& input){
	return calculate_fishes(input[0], 80);
}
int64_t aoc::day6::part_2(std::vector<std::string>& input){
	return calculate_fishes(input[0], 256);
}