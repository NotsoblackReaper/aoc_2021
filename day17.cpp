#include <iostream>
#include <algorithm>
#include <numeric>

#include "AOC_Solver.h"

bool willHitX(int velX, int minX, int maxX) {
	int x = 0;
	while (velX > 0 && x < minX)
		x += velX--;
	if (x >= minX && x <= maxX)
		return true;
	return false;
}

int willHitY(int velY, int minY, int maxY) {
	int y = 0;
	int maxY_pos = INT_MIN;
	while (y+velY>=minY)
	{
		y += velY--;
		if (y > maxY_pos)maxY_pos = y;
	}
	if (y >= minY && y <= maxY)
		return maxY_pos;
	return 0;
}
bool willHitYBool(int velY, int minY, int maxY) {
	int y = 0;
	int maxY_pos = INT_MIN;
	while (y + velY >= minY) {
		y += velY--;
		if (y > maxY_pos)maxY_pos = y;
	}
	if (y >= minY && y <= maxY)
		return true;
	return false;
}

bool simulate(int velX, int velY, int minX, int minY, int maxX, int maxY, int maxSteps) {
	std::vector<std::pair<int, int>>positions{};
	int x_position = 0, y_position = 0;
	int maxX_pos = 0, maxY_pos = 0, minY_pos = INT_MAX;
	for (int i = 0; i < maxSteps; ++i) {
		if (x_position >= minX && x_position <= maxX && y_position >= minY && y_position <= maxY)
			return true;
		x_position += velX;
		y_position += velY;

		positions.emplace_back(x_position, y_position);
		if (x_position > maxX_pos)maxX_pos = x_position;
		if (y_position > maxY_pos)maxY_pos = y_position;
		if (y_position < minY_pos)minY_pos = y_position;
		if (velX < 0)
			++velX;
		else if (velX > 0)
			--velX;
		--velY;
	}
	return false;
}

bool print(int velX,int velY,int minX,int minY,int maxX,int maxY,int maxSteps)
{
	int initVelX=velX, initVelY = velY;
	bool hitX = willHitX(velX,minX,maxX);
	int hitY = willHitY(velY, minY, maxY);
	std::vector<std::pair<int, int>>positions{};
	int x_position = 0, y_position = 0;
	int maxX_pos = 0, maxY_pos = 0, minY_pos = INT_MAX;
	for(int i=0;i<maxSteps;++i)
	{
		if (x_position >= minX && x_position<=maxX && y_position>=minY && y_position <= maxY)
			break;
		x_position += velX;
		y_position += velY;

		positions.emplace_back(x_position, y_position);
		if (x_position > maxX_pos)maxX_pos = x_position;
		if (y_position > maxY_pos)maxY_pos = y_position;
		if (y_position < minY_pos)minY_pos = y_position;
		if (velX < 0)
			++velX;
		else if (velX > 0)
			--velX;
		--velY;
	}
	std::string print{};
	bool hit_shown = false;
	for(int y=(maxY_pos>1000?1000:maxY_pos);y>(minY_pos<minY?minY_pos:minY)-1;--y)
	{
		print += std::to_string(y) + '\t';
		for(int x=0;x<(maxX_pos>maxX?maxX_pos:maxX);++x)
		{
			if(x==0&&y==0)
				print += 'O';
			else if (std::ranges::any_of(positions, [&](auto& p) {return p.first == x && p.second == y; }))
			{
				print += '#';
				if (x >= minX && x <= maxX && y >= minY && y <= maxY)
					hit_shown = true;
			}
			else if (x >= minX && x<=maxX && y>=minY && y <= maxY)
				print += 'T';
			else
				print += '.';
		}
		print += "\n";
	}
	std::cout << print<< "Initial velocity x: " << initVelX << " y: " << initVelY << "\n"
	<< "Hit shown: " << (hit_shown ? "true" : "false") << " Max Y: " << maxY_pos << "\nShould hit X: " << (hitX ? "true" : "false") << "\nShould hit Y: " << (hitY ? "true" : "false") << " max Y calc " << hitY << "\n\n";
	return hit_shown;
}



uint64_t aoc::day17::part_1(std::vector<std::string>& input)
{
	int equals = input[0].find_last_of('=');
	int y_min = std::stoi(input[0].substr(equals + 1, input[0].find_last_of('.') - 1 - equals - 2));
	return (-y_min * (-y_min - 1)) / 2;
}

uint64_t aoc::day17::part_2(std::vector<std::string>& input)
{
	int x_char = input[0].find('x');
	int y_char = input[0].find('y');
	int x_dot = input[0].find_first_of('.');
	int y_dot = input[0].find_last_of('.') - 1;
	int x_min = std::stoi(input[0].substr(x_char + 2, x_dot - x_char - 2));
	int x_max = std::stoi(input[0].substr(x_dot + 2, y_char - x_dot - 2));
	int y_min = std::stoi(input[0].substr(y_char + 2, y_dot - y_char - 2));
	int y_max = std::stoi(input[0].substr(y_dot + 2));
	
	int count = 0;
	for (int i = -500; i < 5000; ++i) {
		bool y = willHitYBool(i, y_min, y_max);
		if (y) {
			for(int j=0;j<1000;++j)
			{
				if (willHitX(j, x_min, x_max))
				{
					if (simulate(j, i, x_min, y_min, x_max, y_max, 750))
					{
						++count;
					}
				}
			}
		}
	}
	return count;
}