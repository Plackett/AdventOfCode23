#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

enum direction
{
	north, south, east, west
};

int day17(int part)
{
	std::fstream input("./input/day17input.txt");
	std::string line{};
	std::vector<std::vector<int>> city{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			std::vector<int> currentBlocks{};
			for (size_t i = 0; i < line.length(); i++)
			{
				currentBlocks.emplace_back(std::stoi(std::string(1, line[i])));
			}
			city.emplace_back(currentBlocks);
		}
		int totalLoss = 0;
		int currentStreak = 0;
		vec2 currentBlock = vec2{ 0,0 };
		direction currentDirection = north;
		totalLoss += city[0][0];
		while (currentBlock.x != city[0].size() - 1 || currentBlock.y != city.size() - 1)
		{
			std::cout << "currentBlock: " << currentBlock.x << " " << currentBlock.y << '\n';
			std::pair<int, direction> bestHeat = std::pair<int, direction>(0, south);
			std::pair<int,direction> secondBestHeat = std::pair<int, direction>(0, south);
			if (currentBlock.x > 0)
			{
				bestHeat.first = city[currentBlock.y][currentBlock.x-1];
				bestHeat.second = west;
			}
			if (currentBlock.x < city[0].size())
			{
				std::cout << "moving east " << currentBlock.y << '\n';
				int heat = city[currentBlock.y][currentBlock.x + 1];
				if (heat < bestHeat.first)
				{
					bestHeat.first = heat;
					bestHeat.second = east;
				}
				else
				{
					secondBestHeat.first = heat;
					secondBestHeat.second = east;
				}
			}
			if (currentBlock.y > 0)
			{
				std::cout << "moving north " << currentBlock.y << '\n';
				int heat = city[currentBlock.y - 1][currentBlock.x];
				if (heat < bestHeat.first)
				{
					bestHeat.first = heat;
					bestHeat.second = north;
				}
				else if( heat < secondBestHeat.first)
				{
					secondBestHeat.first = heat;
					secondBestHeat.second = north;
				}
			}
			if (currentBlock.y < city.size())
			{
				int heat = city[currentBlock.y + 1][currentBlock.x];
				if (heat < bestHeat.first)
				{
					bestHeat.first = heat;
					bestHeat.second = south;
				}
				else if (heat < secondBestHeat.first)
				{
					secondBestHeat.first = heat;
					secondBestHeat.second = south;
				}
			}
			city[currentBlock.y][currentBlock.x] = 99;
			if (bestHeat.second == currentDirection && currentStreak >= 4)
			{
				currentDirection = secondBestHeat.second;
				switch (currentDirection)
				{
				case north:
					std::cout << "TP4" << '\n';
					currentBlock.y--;
					break;
				case south:
					currentBlock.y++;
					break;
				case east:
					currentBlock.x++;
					break;
				case west:
					currentBlock.x--;
					break;
				}
				totalLoss = totalLoss + secondBestHeat.first;
				currentStreak = 1;
			}
			// try going south and east to get to the finish
			else if (bestHeat.second == south || bestHeat.second == east)
			{
				if (currentDirection == bestHeat.second) { currentStreak++; }
				else { currentStreak = 1; }
				currentDirection = bestHeat.second;
				switch (currentDirection)
				{
					case north:
						std::cout << "TP3" << '\n';
						currentBlock.y--;
						break;
					case south:
						currentBlock.y++;
						break;
					case east:
						currentBlock.x++;
						break;
					case west:
						currentBlock.x--;
						break;
				}
				totalLoss = totalLoss + bestHeat.first;
			}
			else if (secondBestHeat.second == south || secondBestHeat.second == east)
			{
				if (currentDirection == secondBestHeat.second) { currentStreak++; }
				else { currentStreak = 1; }
				currentDirection = secondBestHeat.second;
				switch (currentDirection)
				{
				case north:
					std::cout << "TP2" << '\n';
					currentBlock.y--;
					break;
				case south:
					currentBlock.y++;
					break;
				case east:
					currentBlock.x++;
					break;
				case west:
					currentBlock.x--;
					break;
				}
				totalLoss = totalLoss + secondBestHeat.first;
			}
			else
			{
				if (currentDirection == bestHeat.second) { currentStreak++; }
				else { currentStreak = 1; }
				currentDirection = bestHeat.second;
				switch (currentDirection)
				{
				case north:
					std::cout << "TP1" << '\n';
					currentBlock.y--;
					break;
				case south:
					currentBlock.y++;
					break;
				case east:
					currentBlock.x++;
					break;
				case west:
					currentBlock.x--;
					break;
				}
				totalLoss = totalLoss + bestHeat.first;
			}
		}
		std::cout << " minimum loss: " << totalLoss << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}