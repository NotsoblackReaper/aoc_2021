#include <array>
#include <iostream>

#include "AOC_Solver.h"

uint64_t aoc::day21::part_1(std::vector<std::string>& input) {
	int p1 = input[0][28] - 48;
	int p2 = input[1][28] - 48;
	int s1 = 0, s2 = 0;
	int die = 1, rolls = 0;
	bool turn_p1 = true;
	while (s1 < 1000 && s2 < 1000) {

		int die_value;
		if (die <= 98)
			die_value = 3 * die + 3;
		else
			die_value = die + ((die + 1) % 100) + ((die + 2) % 100);
		die += 3;
		rolls += 3;
		if (die > 100)die -= 100;
		if (turn_p1) {
			p1 = p1 + die_value;
			while (p1 > 10)p1 -= 10;
			s1 += p1;
		}
		else {
			p2 = p2 + die_value;
			while (p2 > 10)p2 -= 10;
			s2 += p2;
		}
		turn_p1 = !turn_p1;
	}
	int loosing = (s1 < 1000 ? s1 : s2);
	return loosing * rolls;
}

std::pair<uint64_t, uint64_t> play(int p1,int p2,int s1,int s2) {
	if(s2>=21) return std::make_pair(0,1);
	uint64_t w1 = 0, w2 = 0;
	int rolls[7][2] = { {3,1},{4,3},{5,6},{6,7},{7,6},{8,3},{9,1} };
	for(auto comb:rolls)
	{
		int p = (p1 + comb[0]) % 10 ? (p1 + comb[0]) % 10 : 10;
		auto [v2, v1] = play(p2, p, s2, s1 + p);
		w1 = w1 + v1 * comb[1];
		w2 = w2 + v2 * comb[1];

	}
	return std::make_pair(w1, w2);
}

uint64_t aoc::day21::part_2(std::vector<std::string>& input) {
	int p1 = input[0][28] - 48;
	int p2 = input[1][28] - 48;
	auto[wins_p1,wins_p2] = play(p1, p2, 0, 0);

	return wins_p1>wins_p2?wins_p1:wins_p2;
}