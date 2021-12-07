#include "AOC_Solver.h"

#include <fstream>
#include <sstream>

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

std::vector<int> input::data_as_int(const char* filepath)
{
	std::ifstream MyReadFile(filepath);
	std::string input;
	std::vector<int>data{};
	while (std::getline(MyReadFile, input)) {
		data.push_back(std::stoi(input));
	}
	return data;
}

std::vector<int> input::data_as_csv_int(const char* filepath)
{
	std::ifstream MyReadFile(filepath);
	std::string input;
	std::vector<int>data{};
	std::getline(MyReadFile, input);
	std::stringstream stream(input);
	for (int k, j = 0; stream >> k;) {
		data.push_back(k);
		if (stream.peek() == ',')
			stream.ignore();
	}
	return data;
}