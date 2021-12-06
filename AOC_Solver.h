#ifndef AOC_SOLVER
#define AOC_SOLVER

#include <string>
#include <vector>

namespace input {
	std::vector<std::string> data_as_string(const char*);
	std::vector<int> data_as_int(const char*);
}

namespace aoc
{
	namespace day1
	{
		int64_t part_1(std::vector<int>&);
		int64_t part_2(std::vector<int>&);
	}

	namespace day2
	{
		int64_t part_1(const std::vector<std::string>&);
		int64_t part_2(const std::vector<std::string>&);
	}

	namespace day3
	{
		int64_t part_1(std::vector<std::string>&);
		int64_t part_2(std::vector<std::string>&);
	}

	namespace day4
	{
		int64_t part_1(const std::vector<std::string>&);
		int64_t part_2(const std::vector<std::string>&);
	}

	namespace day5
	{
		int64_t part_1(std::vector<std::string>&);
		int64_t part_2(std::vector<std::string>&);
	}

	namespace day6
	{
		int64_t part_1(std::vector<std::string>&);
		int64_t part_2(std::vector<std::string>&);
	}
}
#endif