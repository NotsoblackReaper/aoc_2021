#include <iostream>
#include <numeric>
#include <algorithm>
#include <map>

#include "AOC_Solver.h"

std::map<char, std::string>hex_bin_map = {
	{'0',std::string{"0000"}},
	{'1',std::string{"0001"}},
	{'2',std::string{"0010"}},
	{'3',std::string{"0011"}},
	{'4',std::string{"0100"}},
	{'5',std::string{"0101"}},
	{'6',std::string{"0110"}},
	{'7',std::string{"0111"}},
	{'8',std::string{"1000"}},
	{'9',std::string{"1001"}},
	{'A',std::string{"1010"}},
	{'B',std::string{"1011"}},
	{'C',std::string{"1100"}},
	{'D',std::string{"1101"}},
	{'E',std::string{"1110"}},
	{'F',std::string{"1111"}}};

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
	if (length_type_id == '0'){
		packet_length = std::stoi(binary_data.substr(7, 15), nullptr, 2);
		offset = 22;
	}else{
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
		binary += hex_bin_map[i];

	auto [result, packet_end] = handle_packet(binary);
	return result.first;
}

uint64_t aoc::day16::part_2(const std::vector<std::string>& input){
	std::string binary{};
	for (const char& i : input[0])
		binary += hex_bin_map[i];

	auto [result, packet_end] = handle_packet(binary);
	return result.second;
}