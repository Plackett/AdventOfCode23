#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int day9(int part)
{
	std::fstream input("./input/day9input.txt");
	std::string line{};
	std::vector<std::vector<int>> extrapolation{};
	std::vector<long long> predictions = {};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			std::vector<std::string> initValues = split(line, " ");
			std::vector<int> firstLine{};
			for (std::string s : initValues)
			{
				firstLine.push_back(std::stoi(s));
			}
			extrapolation = {};
			extrapolation.push_back(firstLine);
			// check if all values are 0 for latest extrapolation line
			while (extrapolation[extrapolation.size() - 1] != std::vector<int>(extrapolation[extrapolation.size() - 1].size(), 0))
			{
				std::vector<int> temp{};
				for (size_t j = 0; j < extrapolation[extrapolation.size() - 1].size() - 1; j++)
				{
					temp.push_back(extrapolation[extrapolation.size() - 1][j + 1] - extrapolation[extrapolation.size() - 1][j]);
				}
				extrapolation.push_back(temp);
			}
			long long predictedValue = 0;
			if (part == 1)
			{
				for (size_t i = 0; i < extrapolation.size(); i++)
				{
					predictedValue += extrapolation[i][extrapolation[i].size() - 1];
				}
				predictions.push_back(predictedValue);
			}
			else
			{
				for (size_t i = extrapolation.size(); i > 0; i--)
				{
					predictedValue = extrapolation[i-1][0] - predictedValue;
				}
				predictions.push_back(predictedValue);
			}
		}
		int sum = 0;
		for (int p: predictions)
		{
			sum += p;
		}
		std::cout << "final sum: " << sum << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}