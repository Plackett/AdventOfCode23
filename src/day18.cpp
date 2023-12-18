#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

int day18(int part)
{
	std::fstream input("./input/day18input.txt");
	std::string line{};
	std::vector<std::string> trench{};
	std::vector<vec2> coords{};
	std::vector<std::pair<char, int>> directions{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			directions.push_back(std::pair<char, int>(split(line, " ")[0][0], std::stoi(split(line, " ")[1])));
		}
		int maxY = 0;
		int maxX = 0;
		// convert directions into coordinates
		vec2 currentPosition = vec2{ 0,0 };
		for (auto& d : directions)
		{
			switch (d.first)
			{
			case 'R':
				currentPosition.x += d.second;
				if (maxX < currentPosition.x) { maxX = currentPosition.x; }
				break;
			case 'L':
				currentPosition.x -= d.second;
				break;
			case 'U':
				currentPosition.y -= d.second;
				break;
			case 'D':
				currentPosition.y += d.second;
				if (maxY < currentPosition.y) { maxY = currentPosition.y; }
				break;
			}
			coords.push_back(currentPosition);
		}
		for (int i = 0; i < maxY; i++)
		{
			std::string curLine = "";
			for (int j = 0; j < maxX; j++)
			{
				if (std::find(coords.begin(), coords.end(), vec2{ i,j }) != coords.end())
				{
					curLine.append("#");
				}
				else
				{
					curLine.append(".");
				}
			}
			trench.push_back(curLine);
		}
		int count = coords.size();
		bool inside = false;
		for (int y = 0; y < maxY; y++)
		{
			inside = false;
			for (int x = 0; x < maxX; x++)
			{
				if (inside == true && trench[y][x] == '.')
				{
					count++;
				}
				if (trench[y][x] == '#')
				{
					inside = !inside;
				}
			}
		}
		std::cout << count << " # of . in map inside of the loop " << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}