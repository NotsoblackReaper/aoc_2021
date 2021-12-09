#include "AOC_Solver.h"

int64_t aoc::day9::part_1(std::vector<std::string>& input) {
	int width = input[0].length(), height = input.size(),sum{};
	for(int i=0;i<width*height;++i)
	{
		int x = i % width, y = i / width;
		if(y>0&&input[y][x]>=input[y-1][x])continue;//UP
		if (x > 0 && input[y][x] >= input[y][x-1])continue;//LEFT
		if (y < height-1 && input[y][x] >= input[y + 1][x])continue;//DOWN
		if (x < width - 1 && input[y][x] >= input[y][x+1])continue;//RIGHT
		sum += input[y][x] - 47;
	}
	return sum;
}

int get_basin(std::vector<int>& map, int low, int width)
{
	int count = 1;
	map[low] = INT_MAX;
	if (map[low - width] < 9)//UP
		count += get_basin(map, low - width, width);
	if (map[low + width] < 9)//DOWN
		count += get_basin(map, low + width, width);
	if (map[low + 1] < 9)//RIGHT
		count += get_basin(map, low + 1, width);
	if (map[low - 1] < 9)//LEFT
		count += get_basin(map, low - 1, width);
	return count;
}

int64_t aoc::day9::part_2(std::vector<std::string>& input) {
	std::vector<int>map{};
	int width = input[0].length() + 2, height = input.size() + 2;
	map.resize(width * height);
	for (int i = 0; i < height * width; ++i) {
		int y = i / width, x = i % width;
		int val = y - 1 > -1 && y - 1 < input.size() &&
			x - 1 > -1 && x - 1 < input[0].length() ?
			input[y - 1][x - 1] - 48 : INT_MAX;
		map[y * width + x] = val;
	}
	int _1st{}, _2nd{}, _3rd{};
	for (int x = width + 2; x < width * (height - 1) + 1; ++x) {
		if (x % width == 0 || width % x + 1 == 0)continue;
		if (map[x] < map[x - width] &&
			map[x] < map[x + width] &&
			map[x] < map[x - 1] &&
			map[x] < map[x + 1]) {
			int basin_size = get_basin(map, x, width);
			//Laziness from here onwards
			if (basin_size > _3rd) {
				if (basin_size > _2nd) {
					_3rd = _2nd;
					if (basin_size > _1st) {
						_2nd = _1st;
						_1st = basin_size;
					}
					else
						_2nd = basin_size;
				}
				else
					_3rd = basin_size;
			}
		}
	}

	return _1st * _2nd * _3rd;
}