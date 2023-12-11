#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

// function for line generation 
int bresenham(int x1, int y1, int x2, int y2)
{
	int count = 0;
	int m_new = 2 * (y2 - y1);
	int slope_error_new = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++) {
		count++;
		// Add slope to increment angle formed 
		slope_error_new += m_new;

		// Slope error reached limit, time to 
		// increment y and update slope error. 
		if (slope_error_new >= 0) {
			y++;
			slope_error_new -= 2 * (x2 - x1);
		}
	}
	return count;
}

int day11(int part)
{
	std::fstream input("./input/day11input.txt");
	std::string line{};
	std::vector<vec2> galaxies{};
	std::vector<std::string> map{};
	std::vector<std::pair<vec2,vec2>> galaxiesToConnect{};
	int currentLine = 0;
	int maxX = 0;
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == '#')
					galaxies.push_back(vec2{ i, currentLine });
			}
			map.push_back(line);
			maxX = line.length();
			currentLine++;
		}
		for (int y = map.size() - 1; y > -1; y--)
		{
			bool expand = true;
			for (int x = map[0].length() - 1; x > -1; x--)
			{
				if (map[y][x] == '#')
					expand = false;
			}
			if (expand == true)
			{
				for (size_t i = 0; i < galaxies.size(); i++)
				{
					if (galaxies[i].y > y)
					{
						if (part == 1)
						{
							galaxies[i].y = galaxies[i].y + 1;
						}
						else
						{
							galaxies[i].y = galaxies[i].y + 999999;
						}
					}
				}
			}
		}
		for (int x = map[0].length()-1; x > -1; x--)
		{
			bool expand = true;
			for (int y = map.size()-1; y > -1; y--)
			{
				if (map[y][x] == '#')
					expand = false;
			}
			if (expand == true)
			{
				for (size_t i = 0; i < galaxies.size(); i++)
				{
					if (galaxies[i].x > x)
					{
						if (part == 1)
						{
							galaxies[i].x = galaxies[i].x + 1;
						}
						else
						{
							galaxies[i].x = galaxies[i].x + 999999;
						}
					}
				}
			}
		}
		long long total = 0;
		for (size_t a = 0; a < galaxies.size(); a++)
		{
			for (size_t b = 0; b < galaxies.size(); b++)
			{
				if (a != b && a < b)
					galaxiesToConnect.push_back(std::pair<vec2, vec2>(galaxies[a], galaxies[b]));
			}
		}
		for (auto& pair : galaxiesToConnect)
		{
			total += std::abs(pair.second.x - pair.first.x) + std::abs(pair.second.y - pair.first.y);
		}
		std::cout << "total length between galaxies " << total << '\n';

	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}