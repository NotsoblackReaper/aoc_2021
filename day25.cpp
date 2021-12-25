#include <iostream>
#include <map>

#include "AOC_Solver.h"

void print(std::map<uint64_t, char>& map,size_t width, size_t height)
{
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			if (map.contains(y * width + x))
				std::cout << map[y * width + x];
			else
				std::cout << '.';
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

uint64_t aoc::day25::part_1(std::vector<std::string>& input) {
	std::map<uint64_t, char>map{};
	size_t width = input[0].length();
	size_t height = input.size();
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			if (input[y][x] != '.')
				map[y * width + x] = input[y][x];
		}
	}

	uint64_t changes = 0;
	uint64_t move_nr = 0;
	do {
		changes = 0;
		/*
		if (move_nr)
			std::cout << "Step: " << move_nr<<"\n";
		else
			std::cout << "Initial State:\n";
		print(map, width, height);
		*/
		std::map<uint64_t, uint64_t>move_list{};
		for (auto& c : map) {
			if (c.second == 'v')continue;
			size_t y = c.first / width;
			size_t x = c.first % width;
			size_t next_x = x + 1;
			if (next_x >= width)next_x = 0;
			if (!map.contains(y * width + next_x)) {
				move_list[c.first] = y * width + next_x;

			}
		}
		for (auto move : move_list) {
			auto nh = map.extract(move.first);
			nh.key() = move.second;
			map.insert(std::move(nh));
			++changes;
		}
		move_list.clear();
		for (auto& c : map) {
			if (c.second == '>')continue;
			size_t y = c.first / width;
			size_t x = c.first % width;
			size_t next_y = y + 1;
			if (next_y >= height)next_y = 0;
			if (!map.contains(next_y * width + x)) {
				move_list[c.first] = next_y * width + x;

			}
		}
		for (auto move : move_list) {
			auto nh = map.extract(move.first);
			nh.key() = move.second;
			map.insert(std::move(nh));
			++changes;
		}
		++move_nr;
	} while (changes);

	//print(map, width, height);

	return move_nr;
}

uint64_t aoc::day25::part_2(std::vector<std::string>& input) {
	return 0;
}