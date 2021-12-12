#include <iostream>

#include "AOC_Solver.h"
#include <stack>
#include <algorithm>
uint64_t aoc::day10::part_1(std::vector<std::string>& input)
{
	int sum{};
	for (auto& line : input){
		std::stack<char>brackets{};
		for (auto& c : line){
			if (c == '(')
				brackets.push(')');
			else if (c == '{' || c == '[' || c == '<')
				brackets.push(c + 2);
			else
			{
				if(c!= brackets.top()){
					sum += c == ')' ? 3 : c == ']' ? 57 : c == '}' ? 1197 : 25137;
					break;
				}
				brackets.pop();
			}
		}
	}
	return sum;
}
uint64_t aoc::day10::part_2(std::vector<std::string>& input) {
	std::vector<uint64_t>scores{};
	for (auto& line : input){
		std::stack<char>brackets{};
		bool corrupt = false;
		for (auto& c : line){
			if (c == '(')
				brackets.push(')');
			else if (c == '{'||c=='['||c=='<')
				brackets.push(c+2);
			else{
				if (c != brackets.top())
				{
					corrupt = true;
					break;
				}
				brackets.pop();
			}
		}
		if (!corrupt){
			uint64_t score{};
			while (!brackets.empty())
			{
				score *= 5;
				char c = brackets.top();
				score += c == ')' ? 1 : c == ']' ? 2 : c == '}' ? 3 : 4;
				brackets.pop();
			}
			scores.push_back(score);
		}
	}
	std::ranges::sort(scores);
	return scores.at((scores.size() / 2));
}