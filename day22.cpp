#include <array>
#include <map>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <numeric>

#include "AOC_Solver.h"


struct Cube {
	int lx, hx, ly, hy, lz, hz;
	Cube(std::string l) {
		std::stringstream ss(l.substr(l.find('=')));
		char tr;
		ss >> tr >> lx >> tr >> tr >> hx >> tr;
		ss >> tr >> tr >> ly >> tr >> tr >> hy >> tr;
		ss >> tr >> tr >> lz >> tr >> tr >> hz;
	}
	Cube(int lx, int hx, int ly, int hy, int lz, int hz) :
		lx(lx), hx(hx), ly(ly), hy(hy), lz(lz), hz(hz) {
	}
	inline bool isValid() {
		return lx <= hx && ly <= hy && lz <= hz;
	}
	uint64_t volumep1() {
		if (lx <= -50 || hx >= 50 || ly <= -50 || hy >= 50 || lz <= -50 || hz >= 50)
			return 0;
		uint64_t out = hx - lx + 1;
		out *= hy - ly + 1;
		out *= hz - lz + 1;
		return out;
	}
	uint64_t volumep2() {
		uint64_t out = hx - lx + 1;
		out *= hy - ly + 1;
		out *= hz - lz + 1;
		return out;
	}
};

bool intersects(Cube& a, Cube& b) { // Optimized by GDB the homie
	if (a.hx < b.lx || b.hx < a.lx) return false;
	if (a.hy < b.ly || b.hy < a.ly) return false;
	if (a.hz < b.lz || b.hz < a.lz) return false;
	return true;
}

void subtract(Cube& a, Cube& b, std::vector<Cube>& build) {
	Cube c(std::max(a.lx, b.lx), std::min(a.hx, b.hx), std::max(a.ly, b.ly),
		std::min(a.hy, b.hy), std::max(a.lz, b.lz), std::min(a.hz, b.hz));
	if (a.lz < c.lz)	build.emplace_back(a.lx, a.hx, a.ly, a.hy, a.lz, c.lz - 1); // bottom part
	if (c.hz < a.hz)	build.emplace_back(a.lx, a.hx, a.ly, a.hy, c.hz + 1, a.hz); // top part
	if (a.lx < c.lx)	build.emplace_back(a.lx, c.lx - 1, a.ly, a.hy, c.lz, c.hz); // middle portions
	if (c.hx < a.hx)	build.emplace_back(c.hx + 1, a.hx, a.ly, a.hy, c.lz, c.hz);
	if (a.ly < c.ly)	build.emplace_back(c.lx, c.hx, a.ly, c.ly - 1, c.lz, c.hz);
	if (c.hy < a.hy)	build.emplace_back(c.lx, c.hx, c.hy + 1, a.hy, c.lz, c.hz);
}


uint64_t aoc::day22::part_1(std::vector<std::string>& input) {
	uint64_t p1(0), p2(0);
	std::vector<Cube> cubes;
	for (auto& l : input) {
		Cube cur(l);
		std::vector<Cube> build;
		for (auto& c : cubes)
			if (intersects(c, cur))
				subtract(c, cur, build);
			else
				build.push_back(c);
		if (l[1] == 'n') // on
			build.push_back(cur);
		cubes = std::move(build);
	}
	for (auto& c : cubes) {
		p1 += c.volumep1();
		p2 += c.volumep2();
	}
	return p1;
}



uint64_t aoc::day22::part_2(std::vector<std::string>& input) {
	uint64_t p1(0), p2(0);
	std::vector<Cube> cubes;
	for (auto& l : input) {
		Cube cur(l);
		std::vector<Cube> build;
		for (auto& c : cubes)
			if (intersects(c, cur))
				subtract(c, cur, build);
			else
				build.push_back(c);
		if (l[1] == 'n') // on
			build.push_back(cur);
		cubes = std::move(build);
	}
	for (auto& c : cubes) {
		p1 += c.volumep1();
		p2 += c.volumep2();
	}
	return p2;
}