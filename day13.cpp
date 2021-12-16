#include "AOC_Solver.h"
#include <algorithm>
#include <iostream>

struct Point
{
	int x, y;
	bool operator==(const Point& rhs) const	{
		return rhs.x == x && rhs.y == y;
	}
};

uint64_t aoc::day13::part_1(std::vector<std::string>& input) {
	uint32_t space=std::find(input.begin(), input.end(), "")-input.begin();
	//std::cout << space<<"\n";
	std::vector<Point>points{};
	points.resize(space);
	for(int i=0;i<space;++i)
	{
		int delim = input[i].find_first_of(",");
		int x = std::stoi(input[i].substr(0, delim));
		int y = std::stoi(input[i].substr(delim+1));
		//std::cout << x<<" "<<y<<"\n";
		points[i] = { x,y };
	}

	char direction = input[space + 1][11];
	int position = std::stoi(input[space + 1].substr(13));
	//std::cout << direction << "=" << position << "\n";
	for(auto it=points.begin();it!=points.end();)
	{
		bool erase = false;

		if((direction=='y'&&it->y>position) || (direction == 'x' && it->x > position))
		{
			int point_pos = direction == 'y' ? it->y : it->x;
			int new_pos = position - (point_pos - position);
			Point new_point = { direction == 'y'?it->x:new_pos, direction == 'y'?new_pos:it->y};
			if (std::any_of(points.begin(), points.end(), [&](Point& p){return new_point.x==p.x&&new_point.y==p.y;}))
				erase = true;
			else if (direction == 'y')
				it->y = new_pos;
			else
				it->x = new_pos;
				
		}

		if (erase)
			it = points.erase(it);
		else
			++it;
	}

	return points.size();
}

uint64_t aoc::day13::part_2(std::vector<std::string>& input) {
	uint32_t space = std::find(input.begin(), input.end(), "") - input.begin();
	//std::cout << space<<"\n";
	std::vector<Point>points{};
	points.resize(space);
	for (int i = 0; i < space; ++i)
	{
		int delim = input[i].find_first_of(",");
		int x = std::stoi(input[i].substr(0, delim));
		int y = std::stoi(input[i].substr(delim + 1));
		//std::cout << x<<" "<<y<<"\n";
		points[i] = { x,y };
	}
	int fold_x{}, fold_y{};
	for(int i=space+1;i<input.size();++i)
	{
		char direction = input[i][11];
		int position = std::stoi(input[i].substr(13));
		if (direction == 'y')fold_y = position;
		else fold_x = position;

		for (auto it = points.begin(); it != points.end();)
		{
			bool erase = false;

			if ((direction == 'y' && it->y > position) || (direction == 'x' && it->x > position))
			{
				int point_pos = direction == 'y' ? it->y : it->x;
				int new_pos = position - (point_pos - position);
				Point new_point = { direction == 'y' ? it->x : new_pos, direction == 'y' ? new_pos : it->y };
				if (std::any_of(points.begin(), points.end(), [&](Point& p) {return new_point.x == p.x && new_point.y == p.y; }))
					erase = true;
				else if (direction == 'y')
					it->y = new_pos;
				else
					it->x = new_pos;

			}

			if (erase)
				it = points.erase(it);
			else
				++it;
		}
	}
	std::string result{};
	for(int y=0;y<fold_y;++y)
	{
		for(int x=0;x<fold_x;++x)
		{
			Point new_point = { x,y };
			if (std::any_of(points.begin(), points.end(), [&](Point& p) {return new_point.x == p.x && new_point.y == p.y; }))
				result+='#';
			else
				result += ' ';
		}
		result += "\n";
	}
#if !NDEBUG
	std::cout << result;
#endif

	return 0;
}