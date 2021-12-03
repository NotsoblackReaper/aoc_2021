#ifndef AOC_SOLVER
#define AOC_SOLVER

#include <string>
#include <vector>

namespace input {
	std::vector<std::string> data_as_string(const char*);
}

namespace aoc_solutions
{
	namespace day1
	{
		int64_t part_1(std::vector<std::string>);
		int64_t part_2(std::vector<std::string>);
	}

	namespace day2
	{
		int64_t part_1(std::vector<std::string>);
		int64_t part_2(std::vector<std::string>);
	}

	namespace day3
	{
		int64_t part_1(std::vector<std::string>);
		int64_t part_2(std::vector<std::string>);
	}
}
#endif