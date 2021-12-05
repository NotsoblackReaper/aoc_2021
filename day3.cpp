#include <iostream>
#include <numeric>

#include "AOC_Solver.h"

int64_t aoc::day3::part_1(std::vector<std::string>&input)
{
	const size_t digits = input[0].length();
	std::string  gamma_rate{}, epsilon_rate{};

	for (unsigned int i = 0; i < digits; ++i)
	{
		int ones{ 0 };
		for (auto& binary_val : input)
		{
			ones += (binary_val[i] == '1' ? 1 : 0);
		}
		if(ones > input.size() / 2)
		{
			gamma_rate += "1";
			epsilon_rate += "0";
		}else{
			gamma_rate += "0";
			epsilon_rate += "1";
		}
	}
	return std::stol(gamma_rate, nullptr, 2) * std::stol(epsilon_rate, nullptr, 2);
}

int64_t aoc::day3::part_2(std::vector<std::string>&input)
{
	const size_t digits = input.front().length();

	char common_bit;
	std::vector<std::string>oxygen{ input };
	auto end_it = oxygen.end();
	for (unsigned int i = 0; i < digits && oxygen.size()>1; ++i)
	{
		size_t oxygen_size = end_it-oxygen.begin();
		if (oxygen_size == 1)continue;

		int ones = std::accumulate(oxygen.begin(), end_it, 0,
			[&](int a, std::string& b) {return a + (b[i] == '1' ? 1 : 0); });

		common_bit = (ones > (oxygen_size / 2) ? '1' : '0');
		if (oxygen_size % 2 == 0 && oxygen_size / 2 == ones)common_bit = '1';

		end_it=std::remove_if(oxygen.begin(), end_it,
			[&](std::string& a) {return a[i] != common_bit; });
	}
	
	end_it = input.end();
	for (unsigned int i = 0; i < digits && input.size()>1; ++i)
	{
		size_t co2_size = end_it - input.begin();
		if (co2_size == 1)continue;

		int ones = std::accumulate(input.begin(), end_it, 0, 
			[&](int a, std::string& b) {return a + (b[i] == '1' ? 1 : 0); });

		common_bit = (ones > (co2_size / 2) ? '1' : '0');
		if (co2_size % 2 == 0 && co2_size / 2 == ones)common_bit = '1';

		end_it = std::remove_if(input.begin(), end_it,
			[&](std::string& a) {return a[i] == common_bit; });
	}
	return std::stoll(oxygen[0], nullptr, 2) * std::stoll(input[0], nullptr, 2);
}