#include <array>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>

#include "AOC_Solver.h"
struct cube {
	std::pair<int, int>x, y, z;

	bool operator==(const cube& o) const {
		return x == o.x && y == o.y && z == o.z;
	}

	cube intersection(const cube& other)const {
		if (*this == other)return *this;
		if ((x.second < other.x.first) || (other.x.second < x.first) ||
			(y.second < other.y.first) || (other.y.second < y.first) ||
			(z.second < other.z.first) || (other.z.second < z.first))
			throw std::runtime_error("no intersection");
		std::pair<int, int> new_x = { std::max(x.first, other.x.first),std::min(x.second, other.x.second) };
		std::pair<int, int> new_y = { std::max(y.first, other.y.first),std::min(y.second, other.y.second) };
		std::pair<int, int> new_z = { std::max(z.first, other.z.first),std::min(z.second, other.z.second) };
		return cube{ new_x,new_y,new_z };
	}

	std::vector<cube>reduce(const cube& other)const {
		std::vector<cube>result{};
		if (*this == other)return result;
		try {
			cube intersection = this->intersection(other);
			//TODO solve


		}
		catch (std::runtime_error&) {
			result.emplace_back(cube{ x,y,z });
			return result;
		}
	}
};

struct command {
	bool on;
	bool fully_outside = false;
	std::pair<int, int>x, y, z;
	std::pair<int, int>limit = { -50,50 };

	[[nodiscard]] std::vector<std::tuple<int, int, int>>get_cubes() const {
		std::vector<std::tuple<int, int, int>>result{};
		for (int _x = x.first; _x <= x.second; ++_x) {
			for (int _y = y.first; _y <= y.second; ++_y) {
				for (int _z = z.first; _z <= z.second; ++_z) {
					result.emplace_back(_x, _y, _z);
				}
			}
		}
		return result;
	}

	cube get_cube() {
		return cube{ x,y,z };
	}

	operator cube() const { return cube{ x,y,z }; }

	command(bool on, int x_min, int x_max, int y_min, int y_max, int z_min, int z_max, bool limit_field = true) :on{ on } {
		if (limit_field) {
			x = std::make_pair(x_min > limit.first ? x_min : limit.first, x_max < limit.second ? x_max : limit.second);
			y = std::make_pair(y_min > limit.first ? y_min : limit.first, y_max < limit.second ? y_max : limit.second);
			z = std::make_pair(z_min > limit.first ? z_min : limit.first, z_max < limit.second ? z_max : limit.second);
			if ((x_min <= limit.first && x_max <= limit.first) || (x_min >= limit.second && x_max >= limit.second) ||
				(y_min <= limit.first && y_max <= limit.first) || (y_min >= limit.second && y_max >= limit.second) ||
				(z_min <= limit.first && z_max <= limit.first) || (z_min >= limit.second && z_max >= limit.second))
				fully_outside = true;
		}
		else {
			x = std::make_pair(x_min, x_max);
			y = std::make_pair(y_min, y_max);
			z = std::make_pair(z_min, z_max);
		}
	}
};

uint64_t aoc::day22::part_1(std::vector<std::string>& input) {
	std::vector<command>commands{};
	for (auto& line : input) {
		bool on = line[1] == 'n';

		std::stringstream stream(line.substr(on ? 5 : 6));
		std::array<int, 6>coords{};
		for (int k, j = 0; stream >> k;) {
			coords[j++] = k;
			char c = stream.peek();
			if (c == '.')
				stream.ignore(2);
			else if (c == ',')
				stream.ignore(3);
		}
		commands.emplace_back(command{ on,coords[0],coords[1],coords[2],coords[3],coords[4],coords[5] });
	}
	std::map<std::tuple<int, int, int>, bool>map;
	for (command c : commands) {
		if (c.fully_outside)continue;
		auto cubes = c.get_cubes();
		for (auto& tuple : cubes) {
			map.insert_or_assign(tuple, c.on);
		}
	}
	uint64_t on_count{};
	for (auto& p : map) {
		on_count += p.second;
	}
	return on_count;
}



uint64_t aoc::day22::part_2(std::vector<std::string>& input) {
	std::vector<command>commands{};
	for (auto& line : input) {
		bool on = line[1] == 'n';
		std::stringstream stream(line.substr(on ? 5 : 6));
		std::array<int, 6>coords{};
		for (int k, j = 0; stream >> k;) {
			coords[j++] = k;
			char c = stream.peek();
			if (c == '.')
				stream.ignore(2);
			else if (c == ',')
				stream.ignore(3);
		}
		commands.emplace_back(command{ on,coords[0],coords[1],coords[2],coords[3],coords[4],coords[5],false });
	}

	cube a = commands[0];
	cube b = commands[1];
	cube c = a.intersection(b);
	cube d = commands[2];
	cube e = a.reduce(d)[0];
	bool equal = a == e;
	auto res = a.reduce(e);
	return 0;
}