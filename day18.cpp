#include <iostream>
#include <algorithm>

#include "AOC_Solver.h"

void explode(std::string& number, int open_bracket, int close_bracket) {
	int l = number[open_bracket + 1] - 48;
	if (number[open_bracket + 2] >= '0' && number[open_bracket + 2] <= '9') {
		l = l * 10 + (number[open_bracket + 2] - 48);
	}
	int r = number[close_bracket - 1]-48;
	if (number[close_bracket - 2] >= '0' && number[close_bracket - 2] <= '9') {
		r = (number[close_bracket - 2] - 48) * 10 + r;
	}
	for (int i = open_bracket; i > -1; --i) {
		if (number[i] >= '0' && number[i] <= '9') {
			int n = number[i] - 48;
			if (i > 0 && number[i - 1] >= '0' && number[i - 1] <= '9') {
				n = (number[i - 1] - 48) * 10 + n;
				number.replace(number.begin() + i - 1, number.begin() + i + 1, std::to_string(n + l));
			}else
				number.replace(number.begin() + i, number.begin() + i + 1, std::to_string(n + l));
			if (n + l > 9&&n<10) {
				++open_bracket; ++close_bracket;
			}
			break;
		}
	}
	for (int i = close_bracket + 1; i < number.length(); ++i) {
		if (number[i] >= '0' && number[i] <= '9') {
			int n = number[i] - 48;
			if (i + 1 < number.length() && number[i + 1] >= '0' && number[i + 1] <= '9')
				number.replace(number.begin() + i, number.begin() + i + 2, std::to_string(n * 10 + (number[i + 1] - 48) + r));
			else
				number.replace(number.begin() + i, number.begin() + i + 1, std::to_string(n + r));
			break;
		}
	}
	number.replace(number.begin() + open_bracket, number.begin() + close_bracket + 1, "0");
}

bool reduce(std::string& number) {
	int offset = 0;
	while (offset < number.length() - 1) {
		int close_bracket = number.find_first_of(']', 3 + offset);
		int open_bracket = number.find_last_of('[', close_bracket);
		if (close_bracket < 0 || open_bracket < 0)break;
		int element_depth = std::count(number.begin(), number.begin() + close_bracket, '[')		- std::count(number.begin(), number.begin() + close_bracket, ']');
		if (element_depth > 4) {
			explode(number, open_bracket, close_bracket);
			return true;
		}
		offset = close_bracket;
	}

	for (int i = 0; i < number.length(); ++i) {
		if ((number[i] >= '0' && number[i] <= '9') && (number[i + 1] >= '0' && number[i + 1] <= '9'))
			//TODO possible bug, if numbers get into 3 digits
		{
			int n = (number[i] - 48) * 10 + (number[i + 1] - 48);
			int l = n / 2;
			int r = n / 2;
			if (n % 2)++r;
			std::string new_bracket = "[" + std::to_string(l) + "," + std::to_string(r) + "]";
			number.replace(number.begin() + i, number.begin() + i + 2, new_bracket);
			return true;
		}
	}

	return false;
}

std::string add(const std::string left, const std::string right) {
	return "[" + left + "," + right + "]";
}

uint64_t magnitude(const std::string& number){
	if (number.length() == 1)return number[0] - 48;
	int d = 0;
	int m = 0;
	for(int i=1;i<number.length();++i){
		if (number[i] == '[')++d;
		else if (number[i] == ']')--d;
		else if(number[i]==','&&d==0){
			m = i;
			break;
		}
	}
	return 3 * magnitude(number.substr(1, m - 1)) + 2 * 
		magnitude(number.substr(m + 1, number.length() - 2 - m));
}

uint64_t aoc::day18::part_1(const std::vector<std::string>& input) {
	std::string number= input[0];
	for (int i = 1; i < input.size(); ++i) {
		number = add(number, input[i]);
		while (reduce(number));
	}
	return magnitude(number);
}

uint64_t aoc::day18::part_2(std::vector<std::string>& input) {
	uint64_t max = 0;
	for (size_t a = 0; a < input.size(); ++a) {
		for(size_t b=0;b<input.size();++b){
			if (a == b)continue;
			std::string number = add(input[a], input[b]);
			while (reduce(number));
			uint64_t tmp = magnitude(number);
			if (tmp > max)max = tmp;
		}
	}

	return max;
}