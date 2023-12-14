#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> spinCycle(std::vector<std::string> input, std::vector<std::pair<int,int>> roundRocks)
{
	// north
	for (int i = 0; i < roundRocks.size(); i++)
	{
		if (roundRocks[i].second > 0)
		{
			for (int j = roundRocks[i].second; j > 0; j--)
			{
				if (input[roundRocks[i].second - 1][roundRocks[i].first] == '.')
				{
					input[roundRocks[i].second - 1][roundRocks[i].first] = 'O';
					input[roundRocks[i].second][roundRocks[i].first] = '.';
					roundRocks[i].second--;
				}
				else
				{
					break;
				}
			}
		}
	}
	// west
	for (int i = 0; i < roundRocks.size(); i++)
	{
		if (roundRocks[i].first > 0)
		{
			for (int j = roundRocks[i].first; j > 0; j--)
			{
				if (input[roundRocks[i].second][roundRocks[i].first - 1] == '.')
				{
					input[roundRocks[i].second][roundRocks[i].first - 1] = 'O';
					input[roundRocks[i].second][roundRocks[i].first] = '.';
					roundRocks[i].first--;
				}
				else
				{
					break;
				}
			}
		}
	}
	// south
	for (int i = roundRocks.size(); i > -1; i--)
	{
		if (roundRocks[i].second < input.size() - 1)
		{
			while(true)
			{
				if (roundRocks[i].second == input.size() - 1)
					break;
				if (input[roundRocks[i].second + 1][roundRocks[i].first] == '.')
				{
					input[roundRocks[i].second + 1][roundRocks[i].first] = 'O';
					input[roundRocks[i].second][roundRocks[i].first] = '.';
					roundRocks[i].second++;
				}
				else
				{
					break;
				}
			}
		}
	}
	// east
	for (int i = roundRocks.size(); i > -1; i--)
	{
		if (roundRocks[i].first < input[0].length() - 1)
		{
			while(true)
			{
				if (roundRocks[i].first == input[0].length() - 1)
					break;
				if (input[roundRocks[i].second][roundRocks[i].first + 1] == '.')
				{
					input[roundRocks[i].second][roundRocks[i].first + 1] = 'O';
					input[roundRocks[i].second][roundRocks[i].first] = '.';
					roundRocks[i].first++;
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
			for (long long i = 0; i < 1000000000; i++)
			{
				platform = spinCycle(platform, roundedRocks);
			}
		}
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
		std::cout << "total load is " << totalCount << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}