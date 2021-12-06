#include <array>
#include <iostream>
#include <sstream>

#include "AOC_Solver.h"

int64_t aoc::day6::part_1(std::vector<std::string>& input)
{
	std::vector<int> numbers{};

	std::stringstream stream(input[0]);

	for (int i; stream >> i;) {
		numbers.push_back(i);
		if (stream.peek() == ',')
			stream.ignore();
	}
	std::array<int64_t, 9>days{};
	for (auto j : numbers)
	{
		days[j]++;
	}

	int n = 80;
	for (int i = 0; i < n; i++)
	{
		int64_t last_day = 0;
		for (int j = 8; j > -1; j--)
		{
			uint64_t temp = days[j];
			days[j] = last_day;
			last_day = temp;
		}
		days[6] += last_day;
		days[8] += last_day;
	}

	uint64_t sum{};
	for (auto i : days)
		sum += i;

	return sum;
}
uint64_t aoc::day6::part_2(std::vector<std::string>& input)
{
	std::vector<int> numbers{};

	std::stringstream stream(input[0]);

	for (int i; stream >> i;) {
		numbers.push_back(i);
		if (stream.peek() == ',')
			stream.ignore();
	}
	std::array<uint64_t, 9>days{};
	for(auto j:numbers)
	{
		days[j]++;
	}

	int n = 256;
	for(int i=0;i<n;i++)
	{
		uint64_t last_day = 0;
		for(int j=8;j>-1;j--)
		{
			uint64_t temp = days[j];
			days[j]=last_day;
			last_day = temp;
		}
		days[6] += last_day;
		days[8] += last_day;
	}

	uint64_t sum{};
	for (auto i : days)
		sum += i;

	return sum;
}