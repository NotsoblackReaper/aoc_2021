#include <iostream>
#include <array>

#include "AOC_Solver.h"

uint64_t aoc::day8::part_1(const std::vector<std::string>& input) {
	int count = 0;
	for (auto line : input) {
		size_t end = line.length();
		for (int i = 0; i < 4; i++) {
			size_t space = line.find_last_of(' ', end - 2);
			if (end - (space + 1) < 5 || end - (space + 1) == 7)
				count++;
			line[space] = '-';
			end = space;
		}
	}
	return count;
}

std::vector<char>difference(std::string a, std::string b)
{
	std::string small = a.length() < b.length() ? b : a;
	std::string large = a.length() < b.length() ? a : b;
	std::vector<char>diff{};
	for (char& c_a : small) {
		bool exists = false;
		for (char& c_b : large)
			if (c_a == c_b)exists = true;
		if (!exists)diff.push_back(c_a);
	}
	return diff;
}

int decode(std::array<char, 7>positions, std::string& s)
{
	if (s.length() == 2)return 1;
	if (s.length() == 4)return 4;
	if (s.length() == 3)return 7;
	if (s.length() == 7)return 8;
	std::string custom = { positions[0], positions[1], positions[2], positions[4], positions[5], positions[6] };
	if (difference(s, custom).empty())return 0;
	custom = { positions[0] ,positions[2],positions[3],positions[4],positions[6] };
	if (difference(s, custom).empty())return 2;
	custom = { positions[0] ,positions[2],positions[3],positions[5],positions[6] };
	if (difference(s, custom).empty())return 3;
	custom = { positions[0] ,positions[1],positions[3],positions[5],positions[6] };
	if (difference(s, custom).empty())return 5;
	custom = { positions[0] ,positions[1],positions[3],positions[4],positions[5],positions[6] };
	if (difference(s, custom).empty())return 6;
	return 9;
}

uint64_t aoc::day8::part_2(std::vector<std::string>& input)
{
	int out_sum{ 0 };
	for (auto& line : input)
	{
		std::array<std::vector<std::string>, 8>parts{};
		std::array<std::string, 4>output{};
		size_t end = line.length();
		for (int i = 0; i < 13; i++) {
			size_t space = line.find_last_of(' ', end - 1);
			std::string digit = line.substr(space + 1, end - space - 1);
			size_t ln = digit.length();
			parts[ln].push_back(digit);
			if (i < 4)output[3-i] = digit;
			end = space;
			if (i == 3)
				end -= 2;
		}
		std::string digit = line.substr(0, end);
		size_t ln = digit.length();
		parts[ln].push_back(digit);

		std::array<char, 7>positions{};
		positions[0] = difference(parts[2][0], parts[3][0])[0];//found top segment
		for (auto& s : parts[6]) {
			std::vector<char> diff = difference(s, parts[4][0] + positions[0]);
			if (diff.size() == 1) {
				positions[6] = diff[0];//found bottom segment
				break;
			}
		}
		for (auto& s : parts[5]) {
			std::vector<char> diff = difference(s, parts[3][0] + positions[6]);
			if (diff.size() == 1) {
				positions[3] = diff[0];//found middle segment
				break;
			}
		}
		positions[4] = difference(parts[4][0] + positions[0] + positions[6], parts[7][0])[0];//found bottom left segment
		positions[1] = difference(parts[4][0], parts[3][0] + positions[3])[0];//found top left segment
		for (auto& s : parts[5]) {
			std::vector<char> diff = difference(s, { positions[0],positions[3],positions[4],positions[6] });
			if (diff.size() == 1) {
				positions[2] = diff[0];//found top right segment
				break;
			}
		}
		positions[5] = difference(parts[2][0], { positions[2] })[0];//found bottom right segment

		int part_sum = 0;
		for (int i = 0; i < 4; ++i)
			part_sum = 10 * part_sum + decode(positions, output[i]);
		out_sum += part_sum;
	}
	return out_sum;
}