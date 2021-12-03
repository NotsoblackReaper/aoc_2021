#include "AOC_Solver.h"

#include <fstream>

std::vector<std::string> input::data_as_string(const char* filepath)
{
	std::ifstream MyReadFile(filepath);
	std::string input;
	std::vector<std::string>data{};
	while (std::getline(MyReadFile, input)) {
		data.push_back(input);
	}
	return data;
}