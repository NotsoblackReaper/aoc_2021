#include <array>
#include <numeric>
#include <sstream>

#include "AOC_Solver.h"

int64_t aoc::day4::part_1(const std::vector<std::string>& input)
{
	std::vector<std::array<int,25>>boards{};
	for (size_t i = 2; i < input.size(); i += 6){
		std::array<int, 25>board{};
		for (int j = 0; j < 5; ++j){
			std::stringstream stream(input[i + j]);
			for (int k,x=0; stream >> k;){
				board[j*5+(x++)]=k;
			}
		}
		boards.push_back(board);
	}

	std::stringstream stream(input[0]);
	for (int i; stream >> i;)
	{
		if (stream.peek() == ',')
			stream.ignore();
		for (auto& j : boards){
			if (auto it = std::ranges::find(j, i); it != j.end())
				*it = 0;

			for (int k = 0; k < 5; ++k){
				if (j[k * 5 + k])continue;
				int sum_hor{ 0 };
				int sum_ver{ 0 };
				for (int x = 0; x < 5; ++x){
					sum_hor += j[k * 5 + x];
					sum_ver += j[5 * x + k];
				}
				if (!sum_hor || !sum_ver)
					return std::accumulate(j.begin(), j.end(), 0ll) * i;
			}
		}
	}
	return 0;
}

int64_t aoc::day4::part_2(const std::vector<std::string>& input)
{
	std::vector<std::array<int, 25>>boards{};
	for (size_t i = 2; i < input.size(); i += 6){
		std::array<int, 25>board{};
		for (int j = 0; j < 5; ++j){
			std::stringstream stream(input[i + j]);
			for (int k,x=0; stream >> k;){
				board[j*5+(x++)]=k;
			}
		}
		boards.push_back(board);
	}

	std::stringstream stream(input[0]);
	for (int i; stream >> i;){
		if (stream.peek() == ',')
			stream.ignore();
		for (auto it = boards.begin(); it != boards.end();){
			if (auto it_1 = std::ranges::find((*it), i); it_1 != (*it).end())
				*it_1 = 0;
			
			bool winner = false;
			for (int k = 0; k < 5; ++k){
				if ((*it)[k * 5 + k])continue;
				int sum_hor = 0;
				int sum_ver = 0;
				for (int x = 0; x < 5; ++x){
					sum_hor += (*it)[k * 5 + x];
					sum_ver += (*it)[5 * x + k];
				}
				if (!sum_hor || !sum_ver){
					winner = true;
					break;
				}
			}
			if (winner && boards.size() > 1)
				it = boards.erase(it);
			else if (winner)
				return std::accumulate((*it).begin(), (*it).end(), 0ll) * i;
			else
				++it;
		}
	}
	return 0;
}