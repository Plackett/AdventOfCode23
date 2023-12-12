#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct Opening
{
	bool north, south, east, west;
};

struct Pipe
{
	int x, y;
	Opening open;
	char shape;
};
/*
	 N
	W+E
	 S
*/
Opening getOpenings(char shape)
{
	Opening temp{};
	switch (shape)
	{
	case '|':
		temp.north = true;
		temp.south = true;
		break;
	case '-':
		temp.east = true;
		temp.west = true;
		break;
	case 'L':
		temp.north = true;
		temp.east = true;
		break;
	case 'J':
		temp.north = true;
		temp.west = true;
		break;
	case '7':
		temp.south = true;
		temp.west = true;
		break;
	case 'F':
		temp.south = true;
		temp.east = true;
		break;
	case '.':
		temp = Opening{ false,false,false,false };
		break;
	case 'S':
		temp = Opening{ true, true, true, true };
		break;
	}
	return temp;
}

int day10(int part)
{
	std::fstream input("./input/day10input.txt");
	std::string line{};
	int currentLine = 0;
	int currentChar = 0;
	std::map<std::pair<int,int>,Pipe> originalMap{};
	std::vector<Pipe> possibleLoops{};
	size_t maxX = 0;
	size_t maxY = 0;
	Pipe start{};
	if (input.is_open())
	{
		Pipe temp{};
		while (std::getline(input, line))
		{
			temp.y = currentLine;
			maxX = line.length();
			for (size_t i = 0; i < line.length(); i++)
			{
				temp.x = i;
				temp.open = getOpenings(line[i]);
				temp.shape = line[i];
				originalMap.emplace(std::pair<std::pair<int,int>, Pipe>(std::pair<int,int>(temp.x, temp.y), temp));
				if (line[i] == 'S')
					start = temp;
			}
			currentLine++;
		}
		maxY = currentLine;
		if (start.x < maxX)
		{
			if (originalMap.at(std::pair<int, int>(start.x + 1, start.y)).open.west)
			{
				possibleLoops.push_back(originalMap.at(std::pair<int, int>(start.x + 1, start.y)));
			}
		}
		if (start.x > 0)
		{
			if (originalMap.at(std::pair<int, int>(start.x - 1, start.y)).open.east)
			{
				possibleLoops.push_back(originalMap.at(std::pair<int, int>(start.x - 1, start.y)));
			}
		}
		if (start.y < maxY)
		{
			if (originalMap.at(std::pair<int, int>(start.x, start.y + 1)).open.south)
			{
				possibleLoops.push_back(originalMap.at(std::pair<int, int>(start.x, start.y + 1)));
			}
		}
		if (start.y > 0)
		{
			if (originalMap.at(std::pair<int, int>(start.x, start.y - 1)).open.north)
			{
				possibleLoops.push_back(originalMap.at(std::pair<int, int>(start.x, start.y - 1)));
			}
		}
			
		int steps = 0;
		std::map<std::pair<int, int>, Pipe> map = std::map < std::pair<int, int>,Pipe>(originalMap);
		std::vector<vec2> currentLoop{};
		for (Pipe s : possibleLoops)
		{
			steps = 0;
			std::map<std::pair<int, int>, Pipe> map = std::map < std::pair<int, int>,Pipe>(originalMap);
			currentLoop = {};
			currentLoop.push_back(vec2(s.x, s.y));
			currentLoop.push_back(vec2(start.x, start.y));
			temp = s;
			while (true)
			{
				steps++;
				if (steps == 2)
				{
					currentLoop.erase(std::find(currentLoop.begin(),currentLoop.end(),vec2(start.x, start.y)));
				}
				if (temp.x == start.x && temp.y == start.y)
				{
					goto finish;
				}
				if (temp.x < maxX && temp.open.east)
				{
					if (map.at(std::pair<int, int>(temp.x + 1, temp.y)).open.west && std::find(currentLoop.begin(), currentLoop.end(), vec2(temp.x + 1, temp.y)) == currentLoop.end())
					{
						currentLoop.push_back(vec2(temp.x, temp.y));
						temp = map.at(std::pair<int, int>(temp.x + 1, temp.y));
						continue;
					}
				}
				if (temp.x > 0 && temp.open.west)
				{
					if (map.at(std::pair<int, int>(temp.x - 1, temp.y)).open.east && std::find(currentLoop.begin(), currentLoop.end(), vec2(temp.x - 1, temp.y)) == currentLoop.end())
					{
						currentLoop.push_back(vec2(temp.x, temp.y));
						temp = map.at(std::pair<int, int>(temp.x - 1, temp.y));
						continue;
					}
				}
				if (temp.y < maxY && temp.open.south)
				{
					if (map.at(std::pair<int, int>(temp.x, temp.y + 1)).open.north && std::find(currentLoop.begin(), currentLoop.end(), vec2(temp.x, temp.y + 1)) == currentLoop.end())
					{
						currentLoop.push_back(vec2(temp.x, temp.y));
						temp = map.at(std::pair<int, int>(temp.x, temp.y + 1));
						continue;
					}
				}
				if (temp.y > 0 && temp.open.north)
				{
					if (map.at(std::pair<int, int>(temp.x, temp.y - 1)).open.south && std::find(currentLoop.begin(), currentLoop.end(), vec2(temp.x, temp.y - 1)) == currentLoop.end())
					{
						currentLoop.push_back(vec2(temp.x, temp.y));
						temp = map.at(std::pair<int, int>(temp.x, temp.y - 1));
						continue;
					}
				}
				if (!temp.open.east && !temp.open.west && !temp.open.south && !temp.open.north)
					break;
			}
		}
	finish:
		if (part == 1)
		{
			std::cout << "total steps: " << steps << '\n';
			std::cout << "midpoint: " << steps / 2 << '\n';
		}
		else
		{
			int count = 0;
			bool inside = false;
			for (int y = 0; y < maxY; y++)
			{
				inside = false;
				for (int x = 0; x < maxX; x++)
				{
					if (inside == true && std::find(currentLoop.begin(), currentLoop.end(), vec2(x, y)) == currentLoop.end())
					{
						count++;
					}
					if (std::find(currentLoop.begin(), currentLoop.end(), vec2(x, y)) != currentLoop.end())
					{
						switch (originalMap.at(std::pair<int, int>(x, y)).shape)
						{
						case 'L':
							inside = !inside;
							break;
						case 'S':
							inside = !inside;
							break;
						case 'J':
							inside = !inside;
							break;
						case '|':
							inside = !inside;
							break;
						}
					}
				}
			}
			std::cout << count << " # of . in map inside of the loop " << '\n';
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}