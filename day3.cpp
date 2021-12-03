#include "AOC_Solver.h"

int64_t aoc_solutions::day3::part_1(const std::vector<std::string>input)
{
	const size_t digits = input.front().length();
	std::string  gamma_rate{}, epsilon_rate{};

	for (unsigned int i = 0; i < digits; ++i)
	{
		int ones{ 0 };
		for (std::string binary_val : input)
		{
			ones += (binary_val.at(i) == '1' ? 1 : 0);
		}

		gamma_rate += (ones > input.size() / 2 ? "1" : "0");
		epsilon_rate += (ones > input.size() / 2 ? "0" : "1");
	}
	return std::stoll(gamma_rate, nullptr, 2) * std::stol(epsilon_rate, nullptr, 2);
}

int64_t aoc_solutions::day3::part_2(const std::vector<std::string>input)
{
	const size_t digits = input.front().length();

	char common_bit;
	std::vector<std::string>oxygen{ input };
	for (unsigned int i = 0; i < digits && oxygen.size()>1; ++i)
	{
		if (oxygen.size() == 1)continue;
		std::vector<std::string>oxygen_tmp{};

		int ones{ 0 };
		for (auto& j : oxygen)
		{
			char digit = j.at(i);
			ones += (digit == '1' ? 1 : 0);
		}
		common_bit = (ones > (oxygen.size() / 2) ? '1' : '0');
		if (oxygen.size() % 2 == 0 && oxygen.size() / 2 == ones)common_bit = '1';

		for (auto& j : oxygen)
		{
			const char digit = j.at(i);
			if (digit == common_bit)
				oxygen_tmp.push_back(j);
		}

		oxygen = oxygen_tmp;
	}

	std::vector<std::string>co2{ input };
	for (unsigned int i = 0; i < digits && co2.size()>1; ++i)
	{
		if (co2.size() == 1)continue;
		std::vector<std::string>co2_tmp{};

		int ones{ 0 };
		for (auto& j : co2)
		{
			const char digit = j.at(i);
			ones += (digit == '1' ? 1 : 0);
		}
		common_bit = (ones > (co2.size() / 2) ? '1' : '0');
		if (co2.size() % 2 == 0 && co2.size() / 2 == ones)common_bit = '1';

		for (auto& j : co2)
		{
			const char digit = j.at(i);
			if (digit != common_bit)
				co2_tmp.push_back(j);
		}

		co2 = co2_tmp;
	}
	return std::stoll(oxygen.front(), nullptr, 2) * std::stoll(co2.front(), nullptr, 2);
}