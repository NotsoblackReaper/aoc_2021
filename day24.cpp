#include <array>
#include <cassert>
#include <charconv>
#include <iostream>
#include <stack>

#include "AOC_Solver.h"
using IType = int;

struct ProcessingBlock {
	bool doPush{};
	IType val{};

	friend std::istream& operator>>(std::istream& is, ProcessingBlock& pb) noexcept {
		std::string line{};
		for (size_t i{ 0 }; i < 18; ++i) {
			if (!std::getline(is, line)) {
				break;
			}
			if (i == 4 || i == 5 || i == 15) {
				IType num{};
				const auto first{ line.data() + 6 };
				const auto last{ line.data() + line.size() };
				[[maybe_unused]] const auto convRes{ std::from_chars(first, last, num) };
				assert(convRes.ptr == last);
				if (i == 4) {
					pb.doPush = (num == 1);
				}
				else if (i == 5) {
					if (!pb.doPush) {
						pb.val = num;
					}
				}
				else {
					assert(i == 15);
					if (pb.doPush) {
						pb.val = num;
					}
				}
			}
		}
		return is;
	}

	ProcessingBlock(std::vector<std::string>& input,int block)
	{
		std::string line{};
		for (size_t i{ 0 }; i < 18; ++i) {
			line = input[block * 18 + i];
			if (i == 4 || i == 5 || i == 15) {
				IType num{};
				const auto first{ line.data() + 6 };
				const auto last{ line.data() + line.size() };
				[[maybe_unused]] const auto convRes{ std::from_chars(first, last, num) };
				assert(convRes.ptr == last);
				if (i == 4) {
					doPush = (num == 1);
				}
				else if (i == 5) {
					if (!doPush) {
						val = num;
					}
				}
				else {
					assert(i == 15);
					if (doPush) {
						val = num;
					}
				}
			}
		}
	}
	ProcessingBlock() {}
};



uint64_t aoc::day24::part_1(std::vector<std::string>& input) {
	std::array<ProcessingBlock, 14>pbs{};
	for (int i = 0; i < 14; ++i)
		pbs[i] = ProcessingBlock{ input,i };

	const auto [part1, part2] {[&]() {
		std::array<std::array<IType, 14>, 2> result{};
		auto& [resMax, resMin] {result};

		struct StackMem {
			size_t loc;
			ProcessingBlock pb;
		};

		std::stack<StackMem> stack{};

		for (size_t loc{ 0 }; loc < 14; ++loc) {
			const auto& pb{ pbs.at(loc) };
			if (pb.doPush) {
				stack.push({ loc, pb });
			}
			else {
				const auto& [locOld, pbOld] {stack.top()};
				const auto diff{ pbs.at(locOld).val + pbs.at(loc).val };
				if (diff <= 0) {
					resMax.at(locOld) = 9;
					resMax.at(loc) = 9 + diff;
					resMin.at(locOld) = 1 - diff;
					resMin.at(loc) = 1;
				}
				else {
					resMax.at(locOld) = 9 - diff;
					resMax.at(loc) = 9;
					resMin.at(locOld) = 1;
					resMin.at(loc) = 1 + diff;
				}
				stack.pop();
			}
		}
		assert(stack.empty());

		return result;
	}()};
	uint64_t res{};
	for (int i = 0; i < 14; ++i)
		res += part1[i] * std::pow(10, 13 - i);
	return res;
}

uint64_t aoc::day24::part_2(std::vector<std::string>& input) {
	std::array<ProcessingBlock, 14>pbs{};
	for (int i = 0; i < 14; ++i)
		pbs[i] = ProcessingBlock{ input,i };

	const auto [part1, part2] {[&]() {
		std::array<std::array<IType, 14>, 2> result{};
		auto& [resMax, resMin] {result};

		struct StackMem {
			size_t loc;
			ProcessingBlock pb;
		};

		std::stack<StackMem> stack{};

		for (size_t loc{ 0 }; loc < 14; ++loc) {
			const auto& pb{ pbs.at(loc) };
			if (pb.doPush) {
				stack.push({ loc, pb });
			}
			else {
				const auto& [locOld, pbOld] {stack.top()};
				const auto diff{ pbs.at(locOld).val + pbs.at(loc).val };
				if (diff <= 0) {
					resMax.at(locOld) = 9;
					resMax.at(loc) = 9 + diff;
					resMin.at(locOld) = 1 - diff;
					resMin.at(loc) = 1;
				}
				else {
					resMax.at(locOld) = 9 - diff;
					resMax.at(loc) = 9;
					resMin.at(locOld) = 1;
					resMin.at(loc) = 1 + diff;
				}
				stack.pop();
			}
		}
		assert(stack.empty());

		return result;
	}()};
	uint64_t res{};
	for (int i = 0; i < 14; ++i)
		res += part2[i] * std::pow(10, 13 - i);
	return res;
}