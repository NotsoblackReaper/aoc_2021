#include "AOC_Solver.h"

unsigned int simulate_step(std::vector<char>& map, unsigned int width)
{
	unsigned int cur_flash, flash_count{};
	for (unsigned int i = 0; i < map.size(); ++i) {
		unsigned int y = i / width, x = i % width;
		++map[y * width + x];
	}
	do
	{
		cur_flash = 0;
		for (unsigned int i = 0; i < map.size(); ++i) {
			unsigned int y = i / width, x = i % width;
			if (map[y * width + x] > '9')
			{
				++cur_flash;
				bool top = y > 0, bottom = y + 1 < map.size() / width, left = x > 0, right = x + 1 < width;

				if (top && left && map[(y - 1) * width + (x - 1)] > '0')//TOP LEFT
					++map[(y - 1) * width + (x - 1)];
				if (top && map[(y - 1) * width + x] > '0')//TOP
					++map[(y - 1) * width + x];
				if (top && right && map[(y - 1) * width + (x + 1)] > '0')//TOP RIGHT
					++map[(y - 1) * width + (x + 1)];
				if (right && map[y * width + (x + 1)] > '0')//RIGHT
					++map[y * width + (x + 1)];
				if (bottom && right && map[(y + 1) * width + (x + 1)] > '0')//BOTTOM RIGHT
					++map[(y + 1) * width + (x + 1)];
				if (bottom && map[(y + 1) * width + x] > '0')//BOTTOM
					++map[(y + 1) * width + x];
				if (bottom && left && map[(y + 1) * width + (x - 1)] > '0')//BOTTOM LEFT
					++map[(y + 1) * width + (x - 1)];
				if (left && map[y * width + (x - 1)] > '0')//LEFT
					++map[y * width + (x - 1)];

				map[y * width + x] = '0';
			}
		}
		flash_count += cur_flash;
	} while (cur_flash > 0);
	return flash_count;
}

uint64_t aoc::day11::part_1(std::vector<std::string>& input) {
	std::vector<char>map{};
	unsigned int width = input[0].length(), height = input.size();
	map.resize(width * height);
	for (unsigned int i = 0; i < height * width; ++i) {
		unsigned int y = i / width, x = i % width;
		map[y * width + x] = input[y][x];
	}
	unsigned int flashes{};
	for (int i = 0; i < 100; i++)
		flashes += simulate_step(map, width);
	return flashes;
}

uint64_t aoc::day11::part_2(std::vector<std::string>& input) {
	std::vector<char>map{};
	unsigned int width = input[0].length(), height = input.size();
	map.resize(width * height);
	for (unsigned int i = 0; i < height * width; ++i) {
		unsigned int y = i / width, x = i % width;
		map[y * width + x] = input[y][x];
	}
	for (uint64_t i = 0; i < 5000; i++)
		if (simulate_step(map, width) == map.size())return i + 1;
	return 0;
}