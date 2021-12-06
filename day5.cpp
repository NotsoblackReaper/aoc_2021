#include <array>
#include <numeric>
#include <sstream>
#include <vector>
#include <numeric>
#include "AOC_Solver.h"

int64_t aoc::day5::part_1(std::vector<std::string>& input)
{
	int max = 0;
	std::vector<std::array<int,4>>lines{};
	for (auto& line : input){
		std::stringstream stream(line);
		std::array<int, 4>x{};
		int j = 0;
		for (int k; stream >> k;) {
			x[j++] = k;
			if (k > max)max = k;
			if (stream.peek() == ',')
				stream.ignore();
			else if (stream.peek() == ' ')
				stream.ignore(4);
		}
		lines.push_back(x);
	}
	++max;
	std::vector<int>board{};
	board.resize(max * max);

	for (auto& l : lines) {
		int x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];
		if (x1 == x2) {
			int ly = y1 < y2 ? y1 : y2, uy = y1 < y2 ? y2 : y1;
			for (int y = ly; y <= uy; y++)
				board[x1 + y * max] += 1;
		}
		else if (y1 == y2) {
			int lx = x1 < x2 ? x1 : x2, ux = x1 < x2 ? x2 : x1;
			for (int x = lx; x <= ux; x++)
				board[x + y1 * max] += 1;
		}
	}

	return std::accumulate(board.begin(), board.end(), 0, [](int a, int b) {return a + (b > 1); });
}

int64_t aoc::day5::part_2(std::vector<std::string>& input)
{
	int max = 0;
	std::vector<std::array<int, 4>>lines{};
	for (auto& line:input){
		std::stringstream stream(line);
		std::array<int, 4>x{};
		int j = 0;
		for (int k; stream >> k;) {
			x[j++] = k;
			if (k > max)max = k;
			if (stream.peek() == ',')
				stream.ignore();
			else if (stream.peek() == ' ')
				stream.ignore(4);
		}
		lines.push_back(x);
	}
	++max;
	std::vector<int>board{};
	board.resize(max * max);

	for (auto& l : lines) {
		int x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];

		if (x1 == x2) {
			int ly = y1 < y2 ? y1 : y2, uy = y1 < y2 ? y2 : y1;
			for (int y = ly; y <= uy; y++)
				board[x1 + y * max] += 1;
		}
		else if (y1 == y2) {
			int lx = x1 < x2 ? x1 : x2, ux = x1 < x2 ? x2 : x1;
			for (int x = lx; x <= ux; x++)
				board[x + y1 * max] += 1;
		}
		else {
			int step_x = x1<x2?1:-1,
			step_y = y1<y2?1:-1;
			int lx = x1 < x2 ? x1 : x2,ux = x1 < x2 ? x2 : x1;

			for (int i = 0; lx+i <= ux; i++)
				board[(x1 + i*step_x) + (y1+i*step_y) * max] += 1;
		}
	}
	return std::accumulate(board.begin(), board.end(), 0, [](int a, int b) {return a + (b > 1); });
}
