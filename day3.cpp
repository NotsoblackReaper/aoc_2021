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
	for (unsigned int i = 0; i < digits && oxygen.size()>1; ++i)
	{
		size_t oxygen_size = oxygen.size();
		if (oxygen_size == 1)continue;
		std::vector<std::string>oxygen_tmp{};

		int ones{ 0 };
		for (auto& j : oxygen)
		{
			ones += (j[i] == '1' ? 1 : 0);
			if(ones > (oxygen_size / 2))break;
		}
		common_bit = (ones > (oxygen_size / 2) ? '1' : '0');
		if (oxygen_size % 2 == 0 && oxygen_size / 2 == ones)common_bit = '1';

		for (auto& j : oxygen)
		{
			const char digit = j[i];
			if (digit == common_bit)
				oxygen_tmp.push_back(j);
		}

		oxygen = oxygen_tmp;
	}

	std::vector<std::string>co2{ input };
	for (unsigned int i = 0; i < digits && co2.size()>1; ++i)
	{
		size_t co2_size = co2.size();
		if (co2_size == 1)continue;
		std::vector<std::string>co2_tmp{};

		int ones{ 0 };
		for (auto& j : co2)
		{
			ones += (j[i] == '1' ? 1 : 0);
			if (ones > (co2_size / 2))break;
		}
		common_bit = (ones > (co2_size / 2) ? '1' : '0');
		if (co2_size % 2 == 0 && co2_size / 2 == ones)common_bit = '1';

		for (auto& j : co2)
		{
			if (j[i] != common_bit)co2_tmp.push_back(j);
		}

		co2 = co2_tmp;
	}
	return std::stoll(oxygen.front(), nullptr, 2) * std::stoll(co2.front(), nullptr, 2);
}