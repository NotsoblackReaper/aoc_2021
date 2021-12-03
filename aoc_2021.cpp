#include "AOC_Solver.h"
#include <iostream>
#include <chrono>
#include <tuple>

auto print = [](const std::string& name, const uint64_t part1, double elapsed1, const uint64_t part2, double elapsed2) {
    std::cout << "\t~~~ " << name << " ~~~"
        << "\nPart 1: " << part1 << " elapsed time " << elapsed1 << "us"
        << "\nPart 2: " << part2 << " elapsed time " << elapsed2 << "us\n\n";
};

template<typename F, typename I>
std::tuple<int64_t, double> Runner(F func, std::vector<I> input) {
    auto start = std::chrono::high_resolution_clock::now();
    int64_t result = func(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return std::make_tuple(result, elapsed);
}

void Day1(std::vector<int> data) {
    auto [result1, elapsed1] = Runner(aoc::day1::part_1, data);
    auto [result2, elapsed2] = Runner(aoc::day1::part_2, data);
    print(__func__, result1, elapsed1, result2, elapsed2);
}

void Day2(std::vector<std::string> data) {
    auto [result1, elapsed1] = Runner(aoc::day2::part_1, data);
    auto [result2, elapsed2] = Runner(aoc::day2::part_2, data);
    print(__func__, result1, elapsed1, result2, elapsed2);
}

void Day3(std::vector<std::string> data) {
    auto [result1, elapsed1] = Runner(aoc::day3::part_1, data);
    auto [result2, elapsed2] = Runner(aoc::day3::part_2, data);
    print(__func__, result1, elapsed1, result2, elapsed2);
}

void Day4(std::vector<std::string> data) {
    auto [result1, elapsed1] = Runner(aoc::day4::part_1, data);
    auto [result2, elapsed2] = Runner(aoc::day4::part_2, data);
    print(__func__, result1, elapsed1, result2, elapsed2);
}

int main()
{
    Day1(input::data_as_int("Input/day1.txt"));
    Day2(input::data_as_string("Input/day2.txt"));
    Day3(input::data_as_string("Input/day3.txt"));
    Day4(input::data_as_string("Input/day4.txt"));
}

