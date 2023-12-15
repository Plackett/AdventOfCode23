#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

int HASH(std::string input)
{
	int currentValue = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		int ascii = input[i];
		currentValue += ascii;
		currentValue *= 17;
		currentValue = currentValue % 256;
	}
	return currentValue;
}

int day15(int part)
{
	std::fstream input("./input/day15input.txt");
	std::string line{};
	std::vector<std::string> initSequence{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			initSequence = split(line, ",");
		}
		if (part == 1)
		{
			int totalSum = 0;
			for (int i = 0; i < initSequence.size(); i++)
			{
				totalSum += HASH(initSequence[i]);
			}
			std::cout << "the total sum of hashes is " << totalSum << '\n';
		}
		else
		{
			std::vector<std::vector<std::pair<std::string, int>>> boxes(256);
			for (int i = 0; i < initSequence.size(); i++)
			{
				if (std::find(initSequence[i].begin(),initSequence[i].end(),'=' ) != initSequence[i].end())
				{
					int boxNum = HASH(split(initSequence[i], "=")[0]);
					bool replaced = false;
					for (size_t j = 0; j < boxes[boxNum].size(); j++)
					{
						if (boxes[boxNum][j].first == split(initSequence[i], "=")[0])
						{
							replaced = true;
							boxes[boxNum][j].second = std::stoi(split(initSequence[i], "=")[1]);
						}
					}
					if (replaced == false)
					{
						boxes[boxNum].push_back(std::pair<std::string, int>(split(initSequence[i], "=")[0], std::stoi(split(initSequence[i], "=")[1])));
					}
				}
				else if (std::find(initSequence[i].begin(), initSequence[i].end(), '-') != initSequence[i].end())
				{
					int boxNum = HASH(split(initSequence[i], "-")[0]);
					for (size_t j = 0; j < boxes[boxNum].size(); j++)
					{
						if (boxes[boxNum][j].first == split(initSequence[i], "-")[0])
						{
							boxes[boxNum].erase(boxes[boxNum].begin() + j);
						}
					}
				}
			}
			int totalPower = 0;
			for (size_t i = 0; i < boxes.size(); i++)
			{
				std::cout << '\n' << "Box: " << i;
				for (size_t j = 0; j < boxes[i].size(); j++)
				{
					std::cout << "[" << boxes[i][j].first << " " << boxes[i][j].second << "] ";
					totalPower += ((i + 1) * (j+1) * boxes[i][j].second);
				}
			}
			std::cout << "the total focusing power of every lens is " << totalPower << '\n';
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}