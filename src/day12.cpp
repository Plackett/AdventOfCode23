#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

bool verifyInput(std::string line, std::vector<int> pattern)
{
	int currentStreak = 0;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == '#')
			currentStreak++;
		if (line[i] == '.')
		{
			if (pattern.size() > 0)
			{
				if (currentStreak == pattern[0])
					pattern.erase(pattern.begin());
			}
			else
			{
				return false;
			}
			currentStreak = 0;
		}
	}
	return pattern.size() == 0 ? true : false;
}

int day12(int part)
{
	std::fstream input("./input/day12input.txt");
	std::string line{};
	std::vector<std::vector<int>> patterns{};
	std::vector<std::string> map{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			map.push_back(split(line, " ")[0]);
			std::vector<int> pattern{};
			for (std::string s : split(split(line, " ")[1], ","))
			{
				pattern.push_back(std::stoi(s));
			}
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}