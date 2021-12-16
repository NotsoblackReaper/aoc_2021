#include <algorithm>
#include <array>

#include "AOC_Solver.h"
#include <map>
#include <unordered_map>
uint64_t aoc::day14::part_1(std::vector<std::string>& input) {
	std::string& polymer = input[0];
	std::unordered_map<std::string, uint64_t>parts{};
	std::map<std::string, char>rules{};

	for (int i = 0; i < polymer.length() - 1; ++i)
	{
		++parts[polymer.substr(i, 2)];
	}

	for (int i = 2; i < input.size(); ++i)
	{
		rules[input[i].substr(0, 2)] = input[i][6];
	}

	for (int i = 0; i < 10; ++i)
	{
		std::unordered_map<std::string, uint64_t>temp_parts{};
		for (auto [combination, count] : parts)
		{
			std::string combination_a{ combination[0], rules[combination] };
			std::string combination_b{ rules[combination] , combination[1] };

			temp_parts[combination_a] += count;
			temp_parts[combination_b] += count;
		}
		std::swap(parts, temp_parts);
	}

	std::unordered_map<char, uint64_t>letters{};
	for (auto [combination, count] : parts)
	{
		letters[combination[0]] += count;
	}
	letters[polymer.back()]++;
	auto max = std::max_element(letters.begin(), letters.end(), [](auto& a, auto& b)
		{
			return a.second < b.second;
		});
	auto min = std::min_element(letters.begin(), letters.end(), [](auto& a, auto& b)
		{
			if (a.second == 0)return false;
			if (b.second == 0)return true;
			return a.second < b.second;
		});
	return (*max).second - (*min).second;
}

uint64_t aoc::day14::part_2(std::vector<std::string>& input) {
	std::string& polymer = input[0];
	std::unordered_map<std::string, uint64_t>parts{};
	std::map<std::string, char>rules{};

	for (int i = 0; i < polymer.length() - 1;++i)
	{
		++parts[polymer.substr(i, 2)];
	}

	for (int i = 2; i < input.size(); ++i)
	{
		rules[input[i].substr(0, 2)] = input[i][6];
	}

	for(int i=0;i<40;++i)
	{
		std::unordered_map<std::string, uint64_t>temp_parts{};
		for(auto[combination,count]:parts)
		{
			std::string combination_a{ combination[0], rules[combination] };
			std::string combination_b{ rules[combination] , combination[1] };

			temp_parts[combination_a] += count;
			temp_parts[combination_b] += count;
		}
		std::swap(parts, temp_parts);
	}

	std::unordered_map<char, uint64_t>letters{};
	for (auto [combination, count] : parts)
	{
		letters[combination[0]]+=count;
	}
	letters[polymer.back()]++;
	auto max = std::max_element(letters.begin(), letters.end(),[](auto& a, auto& b)
		{
			return a.second < b.second;
		});
	auto min = std::min_element(letters.begin(), letters.end(), [](auto& a, auto& b)
		{
			if (a.second == 0)return false;
			if (b.second == 0)return true;
			return a.second < b.second;
		});
	return (*max).second -(*min).second;
}