#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "AOC_Solver.h"
//#define DEBUG
struct cave
{
	bool big;
	std::string name;
	std::unordered_map<std::string, cave>connections{};
	void add_connection(std::string& cave_name, cave c)
	{
		connections.insert_or_assign(cave_name, c);
	}
	cave(std::string n)
	{
		name = n;
		if (n[0] < 'a')
			big = true;
		else
			big = false;
	}
	cave()
	{
		name = "undefined";
		big = false;
	}
};
std::vector<std::vector<std::string>> getPaths(std::unordered_map<std::string, cave>& caves, std::vector<std::string>& path)
{

	std::vector<std::vector<std::string>>allPaths{};
	if (path.back() == "end")
	{
		allPaths.push_back(path);
		return allPaths;
	}
	for (auto& cave : caves[path.back()].connections)
	{
		if (path.size() > 15)
			std::cout << path.size();
		if (std::ranges::any_of(path, [&](const std::string& str) {	return !cave.second.big && str == cave.first; }))
			continue;
		std::vector<std::string>path_copy{ path };
		path_copy.push_back(cave.first);
		for (auto new_path : getPaths(caves, path_copy))
			allPaths.push_back(new_path);
	}
	return allPaths;
}

uint64_t aoc::day12::part_1(std::vector<std::string>& input) {
	std::unordered_map<std::string, cave>caves{};
	for (auto& line : input)
	{
		int dash = line.find_last_of('-');
		std::string cave_a = line.substr(0, dash);
		std::string cave_b = line.substr(dash + 1);
		cave c_a{ cave_a };
		if (caves.contains(cave_a))
			c_a = caves[cave_a];
		else
			caves[cave_a] = c_a;
		cave c_b{ cave_b };
		if (caves.contains(cave_b))
			c_b = caves[cave_b];
		else
			caves[cave_b] = c_b;

		caves[cave_a].add_connection(cave_b, c_b);
		caves[cave_b].add_connection(cave_a, c_a);
	}

	std::vector<std::string>path{ "start" };
	return  getPaths(caves, path).size();
}

std::vector<std::vector<std::string>> getPaths_part2(std::unordered_map<std::string, cave>& caves, std::vector<std::string>& path, bool visited_twice = false)
{
	std::vector<std::vector<std::string>>allPaths{};
	if (path.back() == "end")
	{
		allPaths.push_back(path);
		return allPaths;
	}
	std::string back = path.back();
	for (auto& cave : caves[back].connections)
	{
		bool v_2 = visited_twice;
		if (!cave.second.big && std::ranges::any_of(path, [&](const std::string& str)
			{
				if (!v_2)
				{
					if (str == cave.first)
						v_2 = true;
					return cave.first == "start";
				}
				return cave.first == "start" || str == cave.first;
			}))
			continue;

			std::vector<std::string>path_copy{ path };
			path_copy.push_back(cave.first);
			for (auto new_path : getPaths_part2(caves, path_copy, v_2))
				allPaths.push_back(new_path);
	}
	return allPaths;
}
uint64_t aoc::day12::part_2(std::vector<std::string>& input) {
	std::unordered_map<std::string, cave>caves{};
	for (auto& line : input)
	{
		int dash = line.find_last_of('-');
		std::string cave_a = line.substr(0, dash);
		std::string cave_b = line.substr(dash + 1);
		cave c_a{ cave_a };
		if (caves.contains(cave_a))
			c_a = caves[cave_a];
		else
			caves[cave_a] = c_a;
		cave c_b{ cave_b };
		if (caves.contains(cave_b))
			c_b = caves[cave_b];
		else
			caves[cave_b]=c_b;

		caves[cave_a].add_connection(cave_b, c_b);
		caves[cave_b].add_connection(cave_a, c_a);
	}

	std::vector<std::string>path{"start"};
	return getPaths_part2(caves, path).size();
}