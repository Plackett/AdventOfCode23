#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>
#include <map>

enum direction
{
	north, south, east, west
};

std::vector<direction> getNewDirection(char tile, direction d)
{
	std::vector<direction> directions{};
	switch (d)
	{
	case north:
		switch (tile)
		{
		case '/':
			directions.push_back(west);
			break;
		case '\\':
			directions.push_back(east);
			break;
		case '-':
			directions.push_back(west);
			directions.push_back(east);
			break;
		default:
			directions.push_back(d);
			break;
		}
		break;
	case south:
		switch (tile)
		{
		case '/':
			directions.push_back(east);
			break;
		case '\\':
			directions.push_back(west);
			break;
		case '-':
			directions.push_back(west);
			directions.push_back(east);
			break;
		default:
			directions.push_back(d);
			break;
		}
		break;
	case east:
		switch (tile)
		{
		case '|':
			directions.push_back(north);
			directions.push_back(south);
			break;
		case '/':
			directions.push_back(south);
			break;
		case '\\':
			directions.push_back(north);
			break;
		default:
			directions.push_back(d);
			break;
		}
		break;
	case west:
		switch (tile)
		{
		case '|':
			directions.push_back(north);
			directions.push_back(south);
			break;
		case '/':
			directions.push_back(north);
			break;
		case '\\':
			directions.push_back(south);
			break;
		default:
			directions.push_back(d);
			break;
		}
		break;
	}
	return directions;
}

std::vector<vec2> runSimulation(vec2 start, direction d, std::map<vec2, char> map)
{
	std::vector<vec2> energized{};
	vec2 currentPos = start;
}

int day16(int part)
{
	std::fstream input("./input/day16input.txt");
	std::string line{};
	std::vector<std::string> map{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			map.emplace_back(line);
		}

	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}