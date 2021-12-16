#include <iostream>
#include <list>
#include <queue>

#include "AOC_Solver.h"

uint64_t aoc::day15::part_1(std::vector<std::string>& input)
{
	std::vector<int>map{};
	int width = input[0].length(), height = input.size();
	map.resize(width * height);
	for (int i = 0; i < height * width; ++i) {
		int y = i / width, x = i % width;
		int val =input[y][x]-'0';
		map[y * width + x] = val;
	}

	std::vector costs(width * height, INT_MAX);
	costs[0] = 0;
	std::priority_queue < std::pair<int, int>> pq;
	pq.push(std::make_pair(0, 0));
	while (costs[width * height - 1] == INT_MAX){
		int c = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		int x = u % width, y = u / width;

		int i;
		//South
		if(y<height-1)
		{
			i = (y + 1) * width + x;
			int cost = costs[u] + map[i];
			if(costs[i]>cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX -cost, i));
			}
		}
		//north
		if (y > 0)
		{
			i = (y - 1) * width + x;
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
		//east
		if (x<width-1)
		{
			i = y * width + (x+1);
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
		//west
		if (x >0)
		{
			i = y * width + (x - 1);
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
	}

	return costs[width * height - 1];
}

uint64_t aoc::day15::part_2(std::vector<std::string>& input)
{
	std::vector<int>map{};
	const size_t input_width = input[0].length(), input_height = input.size();
	const size_t width = input_width*5, height = input_height*5;
	map.resize(width * height);
	for (int i = 0; i < height * width; ++i) {
		int y = i / width, x = i % width;
		int val = input[y % input_height][x%input_width] - '0';
		int offset = y / input_height + x / input_width;
		map[y * width + x] = (val+offset-1)%9+1;
	}

	std::vector costs(width * height, INT_MAX);
	costs[0] = 0;
	std::priority_queue < std::pair<int, int>> pq;
	pq.push(std::make_pair(0, 0));
	while (costs[width * height - 1] == INT_MAX) {
		int u = pq.top().second;
		pq.pop();

		int x = u % width, y = u / width;

		int i;
		//South
		if (y+1 < height)
		{
			i = (y + 1) * width + x;
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
		//north
		if (y > 0)
		{
			i = (y - 1) * width + x;
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
		//east
		if (x+1 < width)
		{
			i = y * width + (x + 1);
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
		//west
		if (x > 0)
		{
			i = y * width + (x - 1);
			int cost = costs[u] + map[i];
			if (costs[i] > cost)
			{
				costs[i] = cost;
				pq.push(std::make_pair(INT_MAX - cost, i));
			}
		}
	}

	return costs[width * height - 1];
}