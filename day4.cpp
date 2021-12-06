#include <numeric>
#include <sstream>

#include "AOC_Solver.h"



int64_t aoc::day4::part_1(const std::vector<std::string>& input)
{
	std::string number_order = input[0];
	std::vector<int> numbers{};

	std::stringstream stream(number_order);

	for (int i; stream >> i;) {
		numbers.push_back(i);
		if (stream.peek() == ',')
			stream.ignore();
	}

	std::vector<std::vector<int>>boards{};
	for (int i = 2; i < input.size(); i += 6)
	{
		std::vector<int>board{};
		board.resize(25);
		for (int j = 0; j < 5; ++j)
		{
			std::stringstream stream(input[i + j]);
			int x = 0;
			for (int k; stream >> k;) {
				board[j*5+x]=k;
				if (stream.peek() == ' ')
					stream.ignore();
			}
		}
		boards.push_back(board);
	}

	for (auto& i : numbers)
	{
		//std::cout << "Number: " << i << "\n";
		for (auto& j : boards)
		{
			auto it = std::find(j.begin(), j.end(), i);
			if (it != j.end())
				*it = 0;

			for (int k = 0; k < 5; ++k)
			{
				int sum_hor{ 0 };
				int sum_ver{ 0 };
				for (int x = 0; x < 5; ++x)
				{
					sum_hor += j[k * 5 + x];
					sum_ver += j[5 * x + k];
				}
				if (!sum_hor || !sum_ver)
					return std::accumulate(j.begin(), j.end(), 0) * i;
			}
		}
	}

	return 0;
}

int64_t aoc::day4::part_2(const std::vector<std::string>& input)
{
	std::string number_order = input[0];
	std::vector<int> numbers{};

	std::stringstream stream(number_order);

	for (int i; stream >> i;) {
		numbers.push_back(i);
		if (stream.peek() == ',')
			stream.ignore();
	}

	std::vector<std::vector<int>>boards{};
	for (int i = 2; i < input.size(); i += 6)
	{
		std::vector<int>board{};
		board.resize(25);
		for (int j = 0; j < 5; ++j)
		{
			std::stringstream stream(input[i + j]);
			int x = 0;
			for (int k; stream >> k;) {
				board[j*5+x]=k;
				if (stream.peek() == ' ')
					stream.ignore();
			}
		}
		boards.push_back(board);
	}

	for (auto& i : numbers)
	{
		for (auto it = boards.begin(); it != boards.end();)
		{
			auto it_1 = std::find((*it).begin(), (*it).end(), i);
			if (it_1 != (*it).end())
				*it_1 = 0;

			int sum_hor{ 0 };
			int sum_ver{ 0 };
			bool winner = false;
			for (int k = 0; k < 5; ++k)
			{
				sum_hor = 0;
				sum_ver = 0;
				for (int x = 0; x < 5; ++x)
				{
					sum_hor += (*it)[k * 5 + x];
					sum_ver += (*it)[5 * x + k];
				}
				if (!sum_hor || !sum_ver)
				{
					winner = true;
					break;
				}
			}
			if (winner && boards.size() == 1)
				return std::accumulate((*it).begin(), (*it).end(), 0) * i;
			else if (winner)
				it = boards.erase(it);
			else
				it++;
		}
	}

	return 0;
}
