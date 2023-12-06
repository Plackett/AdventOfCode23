#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "dayLinker.hh";

typedef struct
{
	long long time, distance;
} Race;

int day6(int part)
{
	std::ifstream input("./input/day6input.txt");
	std::string line{};
	std::vector<Race> races{};
	std::vector<long long> times{};
	std::vector<long long> distances{};
	std::vector<long long> winningNumbers{};
	long long currentWins = 0;
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			switch (line[0])
			{
			case 'T':
				if (part == 1)
				{
					for (std::string num : split(line.substr(11, line.length()), " "))
					{
						line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
						if (num.length() > 0)
						{
							std::cout << num << '\n';
							times.push_back(std::atoll(num.c_str()));
						}
					}
				}
				else
				{
					line.erase(remove_if(line.begin(), line.end(), isspace),line.end());
					std::cout << line.substr(5,line.length()-5) << '\n';
					times.push_back(std::atoll(line.substr(5, line.length() - 5).c_str()));
				}
				break;
			case 'D':
				if (part == 1)
				{
					for (std::string num : split(line.substr(11, line.length()), " "))
					{
						line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
						if (num.length() > 0)
						{
							std::cout << num << '\n';
							distances.push_back(std::atoll(num.c_str()));
						}
					}
				}
				else
				{
					line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
					std::cout << line.substr(9, line.length() - 9) << '\n';
					distances.push_back(std::atoll(line.substr(9, line.length() - 9).c_str()));
				}
				break;
			}
		}
		for (long long i = 0; i < times.size(); i++)
		{
			races.push_back(Race{ times[i], distances[i] });
		}
		for (Race r : races)
		{
			currentWins = 0;
			for (long long i = 0; i < r.time; i++)
			{
				currentWins = 0;
				// distance = velocity * time
				if (i * (r.time - i) > r.distance)
				{
					std::cout << i << "is a winning number for " << r.time << '\n';
					currentWins++;
				}
			}
			winningNumbers.push_back(currentWins);
		}
		if (part == 1)
		{
			std::cout << "multiplying together winning combos gets " << winningNumbers[0] * winningNumbers[1] * winningNumbers[2] * winningNumbers[3] << '\n';
		}
		else
		{
			std::cout << "there are " << winningNumbers[0] << " ways to win the race" << '\n';
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}