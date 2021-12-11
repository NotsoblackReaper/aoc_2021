#include "AOC_Solver.h"

int simulate_step(std::vector<char>& map, int width)
{
	std::vector<int>flashed{};
	flashed.resize(map.size());
	int curr_flash{}, flash_count{};
	for (int i = 0; i < map.size(); ++i) {
		int y = i / width, x = i % width;
		++map[y * width + x];
	}
	do
	{
		curr_flash = 0;
		for (int i = 0; i < map.size(); ++i) {
			int y = i / width, x = i % width;
			if (!flashed[y * width + x] && map[y * width + x] > '9')
			{
				++curr_flash;
				++flash_count;

				if (y > 0 && x > 0)//TOP LEFT
					++map[(y - 1) * width + (x - 1)];
				if (y > 0)//TOP
					++map[(y - 1) * width + x];
				if (y > 0 && x + 1 < width)//TOP RIGHT
					++map[(y - 1) * width + (x + 1)];
				if (x + 1 < width)//RIGHT
					++map[y * width + (x + 1)];
				if (y + 1 < map.size() / width && x + 1 < width)//BOTTOM RIGHT
					++map[(y + 1) * width + (x + 1)];
				if (y + 1 < map.size() / width)//BOTTOM
					++map[(y + 1) * width + x];
				if (y + 1 < map.size() / width && x > 0)//BOTTOM LEFT
					++map[(y + 1) * width + (x - 1)];
				if (x > 0)//LEFT
					++map[y * width + (x - 1)];

				flashed[y * width + x] = 1;
			}
		}
		for (int i = 0; i < map.size(); ++i) {
			int y = i / width, x = i % width;
			if (flashed[y * width + x])
				map[y * width + x] = '0';
		}
	} while (curr_flash > 0);
	return flash_count;
}

int64_t aoc::day11::part_1(std::vector<std::string>& input) {
	std::vector<char>map{};
	int width = input[0].length(), height = input.size();
	map.resize(width * height);
	for (int i = 0; i < height * width; ++i) {
		int y = i / width, x = i % width;
		map[y * width + x] = input[y][x];
	}
	int flashes{};
	for (int i = 0; i < 100; i++)
	{
		flashes += simulate_step(map, width);

	}
	return flashes;
}

int64_t aoc::day11::part_2(std::vector<std::string>& input) {
	std::vector<char>map{};
	int width = input[0].length(), height = input.size();
	map.resize(width * height);
	for (int i = 0; i < height * width; ++i) {
		int y = i / width, x = i % width;
		map[y * width + x] = input[y][x];
	}
	for (int i = 0; i < 5000; i++)
	{
		int curr_flashes = simulate_step(map, width);
		if (curr_flashes == map.size())return i + 1;

	}
	return 0;
}