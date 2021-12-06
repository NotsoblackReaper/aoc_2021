#include <array>
#include <sstream>

#include "AOC_Solver.h"

int64_t aoc::day6::part_1(std::vector<std::string>& input){
	std::array<int64_t, 9>days{};
	int pos = 0;
	for (auto& c : input[0]) {
		if (pos++ % 2 == 0)
			days[c - 48]++;
	}

	int n = 80;
	for (int i = 0; i < n; i++)
		days[(7 + i) % 9] += days[i % 9];

	uint64_t sum{};
	for (auto& i : days)
		sum += i;
	return sum;
}
int64_t aoc::day6::part_2(std::vector<std::string>& input){
	std::array<int64_t, 9>days{};
	int pos = 0;
	for (auto& c: input[0]) {
		if(pos++%2==0)
		days[c-48]++;
	}

	int n = 256;
	for (int i = 0; i < n; i++)
		days[(7 + i) % 9] += days[i % 9];

	int64_t sum{};
	for (auto& i : days)
		sum += i;
	return sum;
}