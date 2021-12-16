#include <iostream>
#include <numeric>
#include <algorithm>

#include "AOC_Solver.h"

const char* hex_char_to_bin(char c)
{
	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	default: return "ERROR";
	}
}

std::pair<std::pair<int, uint64_t>, unsigned int> handle_packet(std::string binary_data)
{
	if (binary_data.length() == 0)
		return std::make_pair(std::make_pair(0, 0), 0);
	int version = std::stoi(binary_data.substr(0, 3), nullptr, 2);
	int type = std::stoi(binary_data.substr(3, 3), nullptr, 2);
	
	if (type == 4)
	{
		bool last = false;
		int offset = 6;
		std::string data{};
		while (!last)
		{
			if (binary_data[offset] == '0')
				last = true;
			data += binary_data.substr(offset + 1, 4);
			offset += 5;
		}
		uint64_t data_as_ull = std::stoull(data, nullptr, 2);
		return std::make_pair(std::make_pair(version, data_as_ull), offset);
	}
	int version_sum = version;
	const char length_type_id = binary_data[6];
	int packet_length=INT_MAX, packet_number = INT_MAX;
	
	int offset;
	if (length_type_id == '0')
	{
		packet_length = std::stoi(binary_data.substr(7, 15), nullptr, 2);
		offset = 22;
	}
	else
	{
		packet_number = std::stoi(binary_data.substr(7, 11), nullptr, 2);
		offset = 18;
	}
	uint64_t end = 0;
	std::vector<uint64_t>results{};
	while ((length_type_id == '0' && end < packet_length) || (length_type_id == '1' && packet_number > 0))
	{
		auto [result, packet_end] =
			handle_packet(binary_data.substr(offset + end, packet_length));
		version_sum += result.first;
		end += packet_end;
		--packet_number;
		results.push_back(result.second);
	}
	int operator_end = offset + end;
	uint64_t packet_result{};

	if (type == 0)
		packet_result = std::accumulate(results.begin(), results.end(), 0ull, [](uint64_t a, uint64_t b) {return a + b; });
	else if (type == 1)
		packet_result = std::accumulate(results.begin(), results.end(), 1ull, [](uint64_t a, uint64_t b) {return a * b; });
	else if (type == 2)
		packet_result = *std::ranges::min_element(results);
	else if (type == 3)
		packet_result = *std::ranges::max_element(results);
	else if (type == 5)
		packet_result = results[0] > results[1];
	else if (type == 6)
		packet_result = results[0] < results[1];
	else if (type == 7)
		packet_result = results[0] == results[1];

	return std::make_pair(std::make_pair(version_sum, packet_result), operator_end);
}

uint64_t aoc::day16::part_1(const std::vector<std::string>& input){
	std::string binary{};
	for (const char& i : input[0])
		binary += hex_char_to_bin(i);

	auto [result, packet_end] = handle_packet(binary);
	return result.first;
}

uint64_t aoc::day16::part_2(const std::vector<std::string>& input){
	std::string binary{};
	for (const char& i : input[0])
		binary += hex_char_to_bin(i);

	auto [result, packet_end] = handle_packet(binary);
	return result.second;
}