#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

int calculateLoad(std::vector<std::string> platform)
{
	int totalCount = 0;
	for (size_t i = 0; i < platform.size(); i++)
	{
		for (int j = 0; j < platform[i].length(); j++)
		{
			if (platform[i][j] == 'O')
			{
				totalCount += platform.size() - i;
			}
		}
	}
	return totalCount;
}

std::vector<std::string> spinCycle(std::vector<std::string> input)
{
	// north
	for (size_t j = 0; j < input[0].length(); j++)
	{
		for (size_t i = input.size() - 1; i >= 1; i--)
		{
			while (true)
			{
				if (input[i - 1][j] == '.' && input[i][j] == 'O')
				{
					input[i - 1][j] = 'O';
					input[i][j] = '.';
					if (i < input.size()-1) i++;
				}
				else
				{
					break;
				}
			}
		}
	}
	// west
	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = 1; j < input[i].length(); j++)
		{
			while (true)
			{
				if (input[i][j - 1] == '.' && input[i][j] == 'O')
				{
					input[i][j - 1] = 'O';
					input[i][j] = '.';
					if (j > 1) j--;
				}
				else
				{
					break;
				}
			}
		}
	}
	// south
	for (size_t j = 0; j < input[0].length(); j++)
	{
		for (size_t i = 0; i < input.size() - 1; i++)
		{
			while (true)
			{
				if (input[i+1][j] == '.' && input[i][j] == 'O')
				{
					input[i+1][j] = 'O';
					input[i][j] = '.';
					if (i > 0) i--;
				}
				else
				{
					break;
				}
			}
		}
	}
	// east
	for (size_t i = 0; i < input.size(); i++)
	{
		for (int j = input[i].length() - 1; j > -1; j--)
		{
			while (true)
			{
				if (input[i][j + 1] == '.' && input[i][j] == 'O')
				{
					input[i][j + 1] = 'O';
					input[i][j] = '.';
					if (j < input[i].length() - 2) j++;
				}
				else
				{
					break;
				}
			}
		}
	}
	return input;
}

int getStartIndex(std::vector<std::vector<std::string>> patterns, std::vector < std::string> platform)
{
	for (size_t l = 0; l < patterns.size(); l++)
	{
		bool equal = true;
		for (size_t i = 0; i < platform.size(); i++)
		{
			for (size_t j = 0; j < platform[i].length(); j++)
			{
				if (platform[i][j] != patterns[l][i][j])
				{
					equal = false;
					goto next;
				}
			}
		}
	next:
		if (equal == true)
			return l;
	}
	return -1;
}

int day14(int part)
{
	std::fstream input("./input/day14input.txt");
	std::string line{};
	std::vector<std::string> platform{};
	std::vector<std::pair<int, int>> roundedRocks{};
	if (input.is_open())
	{
		int currentLine = 0;
		while (std::getline(input, line))
		{
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line[i] == 'O')
				{
					roundedRocks.push_back(std::pair<int, int>(i, currentLine));
				}
			}
			platform.push_back(line);
			currentLine++;
		}
		if (part == 1)
		{
			// test gravity for every rounded rock in order
			for (int i = 0; i < roundedRocks.size(); i++)
			{
				if (roundedRocks[i].second > 0)
				{
					for (int j = roundedRocks[i].second; j > 0; j--)
					{
						if (platform[roundedRocks[i].second - 1][roundedRocks[i].first] == '.')
						{
							platform[roundedRocks[i].second - 1][roundedRocks[i].first] = 'O';
							platform[roundedRocks[i].second][roundedRocks[i].first] = '.';
							roundedRocks[i].second--;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		else
		{
			long long needed_iteration = 1000000000;
			std::vector<std::vector<std::string>> patterns{};
			for (long long i = 0; i < needed_iteration; i++) {
				if (getStartIndex(patterns, platform) != -1)
				{
					// time skip by the length of the cycle...
					i = needed_iteration - ((needed_iteration - i) % (i - getStartIndex(patterns, platform)));
				}
				else
				{
					patterns.emplace_back(platform);
				}

				platform = spinCycle(platform);
			}
		}
		int totalCount = calculateLoad(platform);
		std::cout << "total load is " << totalCount << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}