#include "AOC_Solver.h"
#include <iostream>

int main()
{
	std::cout << "AoC 2021 Solutions:";
	std::cout << "\n---Day1:---\n" <<
		"Part 1: " << aoc_solutions::day1::part_1(input::data_as_string("day1.txt"))
		<< "\nPart 1: " << aoc_solutions::day1::part_2(input::data_as_string("day1.txt"));
	std::cout << "\n---Day2:---\n" <<
		"Part 1: " << aoc_solutions::day2::part_1(input::data_as_string("day2.txt"))
		<< "\nPart 1: " << aoc_solutions::day2::part_2(input::data_as_string("day2.txt"));
	std::cout<<"\n---Day3:---\n"<<
		"Part 1: "<<aoc_solutions::day3::part_1(input::data_as_string("day3.txt"))
		<<"\nPart 2: "<< aoc_solutions::day3::part_2(input::data_as_string("day3.txt"));
}

