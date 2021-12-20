#include <array>
#include <iostream>

#include "AOC_Solver.h"

char getEnhanced(std::string& input, std::array<char, 9>bits) {
	std::string binary{};
	for (int i = 0; i < 9; ++i)
		binary += bits[i] == '#' ? '1' : '0';
	return input[std::stoi(binary, nullptr, 2)];
}

char getPixel(int x, int y, unsigned int size, std::vector<char>& image, int n = 0, char algo_first = '.', char algo_last = '#') {
	if (x + 1 > 0 && y + 1 > 0 && x < size && y < size)
		return image[y * size + x];
	if (!n || algo_first == '.')return '.';
	if (n % 2)return algo_first;
	return algo_last;
}

std::array<char, 9> getBits(std::vector<char>& image, unsigned int size, int x, int y, int n = 0, char algo_first = '.', char algo_last = '#') {
	std::array<char, 9>bits{};
	for (int i = 0; i < 9; ++i)
		bits[i] = getPixel((x - 1 + i % 3), (y + i / 3) - 1, size, image, n, algo_first, algo_last);
	return bits;
}

uint64_t solve(std::vector <std::string>& input, int iterations) {
	const unsigned int padding = iterations * 2, img_size = input.size() - 2 + padding;
	std::vector image(img_size * img_size, '.');
	for (int i = 0; i < img_size - padding; ++i) {
		for (int j = 0; j < img_size - padding; ++j) {
			if (input[i + 2][j] == '#')
				image[(i + padding / 2) * img_size + (j + padding / 2)] = '#';
		}
	}
	uint64_t count = 0;
	for (int n = 0; n < iterations; ++n) {
		count = 0;
		std::vector<char>new_image(img_size * img_size, '.');
		for (unsigned int i = 0; i < img_size; ++i) {
			for (unsigned int j = 0; j < img_size; ++j) {
				std::array<char, 9>bits = getBits(image, img_size, j, i, n, input[0][0], input[0].back());
				char c = getEnhanced(input[0], bits);
				new_image[i * img_size + j] = c;
				count += c == '#';
			}
		}
		std::swap(image, new_image);
	}

	return count;
}

uint64_t aoc::day20::part_1(std::vector<std::string>& input) {
	return solve(input, 2);
}

uint64_t aoc::day20::part_2(std::vector<std::string>& input) {
	return solve(input, 50);
}