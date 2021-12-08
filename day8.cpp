#include <iostream>
#include <array>

#include "AOC_Solver.h"

int64_t aoc::day8::part_1(const std::vector<std::string>& input){
	int count = 0;
	for (auto line : input)	{
		size_t end = line.length();
		for (int i = 0; i < 4; i++)	{
			size_t space = line.find_last_of(' ',end-2);
			if (end - (space + 1) < 5 || end - (space + 1) == 7)
				count++;
			line[space]='-';
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
	for (char& c_a : small)
	{
		bool exists = false;
		for (char& c_b : large)
		{
			if (c_a == c_b)exists = true;
		}
		if (!exists)diff.push_back(c_a);
	}
	return diff;
}

int decode(std::array<char, 7>positions, std::string s)
{
	if (s.length() == 2)return 1;
	if (s.length() == 4)return 4;
	if (s.length() == 3)return 7;
	if (s.length() == 7)return 8;
	std::string custom{};
	// 0
	custom += positions[0];
	custom += positions[1];
	custom += positions[2];
	custom += positions[4];
	custom += positions[5];
	custom += positions[6];
	if (difference(s, custom).empty())return 0;
	//2
	custom = "";
	custom += positions[0];
	custom += positions[2];
	custom += positions[3];
	custom += positions[4];
	custom += positions[6];
	if (difference(s, custom).empty())return 2;

	//3
	custom = "";
	custom += positions[0];
	custom += positions[2];
	custom += positions[3];
	custom += positions[5];
	custom += positions[6];
	if (difference(s, custom).empty())return 3;

	//5
	custom = "";
	custom += positions[0];
	custom += positions[1];
	custom += positions[3];
	custom += positions[5];
	custom += positions[6];
	if (difference(s, custom).empty())return 5;

	//6
	custom = "";
	custom += positions[0];
	custom += positions[1];
	custom += positions[3];
	custom += positions[4];
	custom += positions[5];
	custom += positions[6];
	if (difference(s, custom).empty())return 6;
	return 9;
}

int64_t aoc::day8::part_2(std::vector<std::string>& input)
{
	int out_sum{ 0 };
	for (auto line : input)
	{
		std::array<std::vector<std::string>, 8>parts{};
		std::vector<std::string>output{};
		for (int i = 0; i < 14; i++)
		{
			size_t space = line.find(' ');
			std::string digit = line.substr(0, space);
			line = line.substr(space + 1 + (i == 9 ? 2 : 0));

			size_t ln = digit.length();

			parts[ln].push_back(digit);
			if (i > 9)output.push_back(digit);
		}

		std::array<char, 7>positions{};
		if (!parts[2].empty() && !parts[3].empty())
		{
			char c = difference(parts[2].front(), parts[3].front()).front();
			positions[0] = c;
		}
		if (!parts[4].empty())
			for (auto& s : parts[6])
			{
				std::vector<char> diff = difference(s, parts[4].front() + positions[0]);
				if (diff.size() == 1)
					positions[6] = diff.front();
			}
		for (auto& s : parts[5])
		{
			std::vector<char> diff = difference(s, parts[3].front() + positions[6]);
			if (diff.size() == 1)
				positions[3] = diff.front();
		}
		if (!parts[4].empty() && !parts[3].empty())
		{
			char c = difference(parts[4][0], parts[3][0] + positions[3])[0];
			positions[1] = c;
		}
		if (!parts[4].empty() && !parts[7].empty())
		{
			char c = difference(parts[4][0] + positions[0] + positions[6], parts[7][0])[0];
			positions[4] = c;
		}
		for (auto& s : parts[6])
		{
			std::vector<char> diff = difference(s, "" + positions[0] + positions[1] + positions[3] + positions[4] + positions[6]);
			if (diff.size() == 1)
				positions[5] = diff[0];
		}
		for (auto& s : parts[5])
		{
			std::string custom{};
			custom += positions[0];
			custom += positions[3];
			custom += positions[4];
			custom += positions[6];
			std::vector<char> diff = difference(s, custom);
			if (diff.size() == 1)
				positions[2] = diff[0];
		}
		if (!parts[2].empty())
		{
			std::string custom{};
			custom += positions[2];
			std::vector<char> diff = difference(parts[2][0], custom);
			if (diff.size() == 1)
				positions[5] = diff[0];
		}

		for (int i = 3; i > -1; --i)
		{
			int decoded = decode(positions, output[i]);
			out_sum += decoded * std::pow(10, 3 - i);
		}
	}


	return out_sum;
}