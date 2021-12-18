#include <iostream>

#include "AOC_Solver.h"

bool willHitX(int velX, int minX, int maxX) {
	int x = 0;
	while (velX > 0 && x < minX)
		x += velX--;
	if (x >= minX && x <= maxX)
		return true;
	return false;
}

bool willHitYBool(int velY, int minY, int maxY) {
	int y = 0;
	while (y + velY >= minY) {
		y += velY--;
	}
	if (y >= minY && y <= maxY)
		return true;
	return false;
}

bool simulate(int vel_x, int vel_y, int min_x, int min_y, int max_x, int max_y, int max_steps) {
	std::vector<std::pair<int, int>>positions{};
	int x_position = 0, y_position = 0;
	for (int i = 0; i < max_steps; ++i) {
		if (x_position >= min_x && x_position <= max_x && y_position >= min_y && y_position <= max_y)
			return true;
		x_position += vel_x;
		y_position += vel_y;

		if (x_position > max_x || y_position < min_y)return false;

		positions.emplace_back(x_position, y_position);

		if (vel_x < 0)
			++vel_x;
		else if (vel_x > 0)
			--vel_x;
		--vel_y;
	}
	return false;
}

uint64_t aoc::day17::part_1(std::vector<std::string>& input) {
	int equals = input[0].find_last_of('=');
	int y_min = std::stoi(input[0].substr(equals + 1, input[0].find_last_of('.') - equals - 2));
	return (-y_min * (-y_min - 1)) / 2;
}

uint64_t aoc::day17::part_2(std::vector<std::string>& input) {
	int x_char = input[0].find('x');
	int y_char = input[0].find('y');
	int x_dot = input[0].find_first_of('.');
	int y_dot = input[0].find_last_of('.') - 1;
	int x_min = std::stoi(input[0].substr(x_char + 2, x_dot - x_char - 2));
	int x_max = std::stoi(input[0].substr(x_dot + 2, y_char - x_dot - 2));
	int y_min = std::stoi(input[0].substr(y_char + 2, y_dot - y_char - 2));
	int y_max = std::stoi(input[0].substr(y_dot + 2));
	
	const int n = sqrt(-y_min * (-y_min - 1)) + 1;
	int count = 0;
	for (int i = y_min; i < n; ++i) {
		if (willHitYBool(i, y_min, y_max)) {
			for (int j = 0; j < x_max + 1; ++j) {
				if (willHitX(j, x_min, x_max) && simulate(j, i, x_min, y_min, x_max, y_max, 750)) {
					++count;
				}
			}
		}
	}
	return count;
}