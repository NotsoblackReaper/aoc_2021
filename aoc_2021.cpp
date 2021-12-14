#include "AOC_Solver.h"
#define SOLVE_ALL

#include <iostream>
#include <chrono>
#include <tuple>


auto print = [](const std::string& name, const uint64_t part1, double elapsed1, const uint64_t part2, double elapsed2, double scale_from = 1000) {
	std::cout << "\t~~~ " << name << " ~~~"
		<< "\nPart 1: " << part1 << "\telapsed time " << (elapsed1 > scale_from ? elapsed1 / scale_from : elapsed1) << (elapsed1 > scale_from ? "ms" : "us")
		<< "\nPart 2: " << part2 << "\telapsed time " << (elapsed2 > scale_from ? elapsed2 / scale_from : elapsed2) << (elapsed2 > scale_from ? "ms" : "us") << "\n\n";
};

template<typename F, typename I>
std::tuple<uint64_t, double> Runner(F func, std::vector<I> input) {
	auto start = std::chrono::high_resolution_clock::now();
	uint64_t result = func(input);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	return std::make_tuple(result, elapsed);
}

double Day1(std::vector<int> data) {
	auto [result1, elapsed1] = Runner(aoc::day1::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day1::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day2(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day2::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day2::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day3(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day3::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day3::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day4(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day4::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day4::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day5(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day5::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day5::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day6(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day6::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day6::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day7(std::vector<int> data) {
	auto [result1, elapsed1] = Runner(aoc::day7::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day7::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day8(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day8::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day8::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day9(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day9::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day9::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day10(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day10::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day10::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day11(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day11::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day11::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day12(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day12::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day12::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day13(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day13::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day13::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day14(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day14::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day14::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

double Day15(std::vector<std::string> data) {
	auto [result1, elapsed1] = Runner(aoc::day15::part_1, data);
	auto [result2, elapsed2] = Runner(aoc::day15::part_2, data);
	print(__func__, result1, elapsed1, result2, elapsed2);
	return elapsed1 + elapsed2;
}

int main()
{
	double total_time{ 0 };
#ifdef SOLVE_ALL
	total_time += Day1(input::data_as_int("Input/day1.txt"));
	total_time += Day2(input::data_as_string("Input/day2.txt"));
	total_time += Day3(input::data_as_string("Input/day3.txt"));
	total_time += Day4(input::data_as_string("Input/day4.txt"));
	total_time += Day5(input::data_as_string("Input/day5.txt"));
	total_time += Day6(input::data_as_string("Input/day6.txt"));
	total_time += Day7(input::data_as_csv_int("Input/day7.txt"));
	total_time += Day8(input::data_as_string("Input/day8.txt"));
	total_time += Day9(input::data_as_string("Input/day9.txt"));
	total_time += Day10(input::data_as_string("Input/day10.txt"));
	total_time += Day11(input::data_as_string("Input/day11.txt"));
	//total_time += Day12(input::data_as_string("Input/day12.txt"));
	total_time += Day13(input::data_as_string("Input/day13.txt"));
	total_time += Day14(input::data_as_string("Input/day14.txt"));
#endif
	total_time += Day15(input::data_as_string("Input/day15.txt"));

	std::cout << "\t~~~ total ~~~\n" << (total_time > 1000 ? total_time / 1000 : total_time) << (total_time > 1000 ? "ms" : "us") << "\n\n";

	return 0;
}

