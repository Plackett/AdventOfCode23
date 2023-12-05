#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <string_view>
#include <algorithm>
#include <iterator>
#include "dayLinker.hh"

int main(int argc, char** argv)
{
	std::ifstream input("./input/day5input.txt");
	std::string line{};
	std::vector<int> initialSeeds{};
	std::vector<int> seedMap(100);
	std::vector<int> soilMap{};
	std::vector<int> fertMap{};
	std::vector<int> waterMap{};
	std::vector<int> lightMap{};
	std::vector<int> tempMap{};
	std::vector<int> humidMap{};
	std::vector<int> locationMap{};
	bool seed = false;
	bool soil = false;
	bool fert = false;
	bool water = false;
	bool light = false;
	bool temp = false;
	bool humid = false;
	for (int i = 0; i < seedMap.size(); i++)
	{
		seedMap[i] = i;
	}
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (line.substr(0, 4) == "seeds")
			{
				for (std::string num : split(split(line, ":")[1], " "))
				{
					initialSeeds.push_back(std::stoi(num));
				}
			}
			else if (line.substr(0, 4) == "seed")
			{
				soilMap = std::vector<int>(seedMap);
				seed = true;
			}
			else if (line.substr(0, 4) == "soil")
			{
				fertMap = std::vector<int>(soilMap);
				seed = false;
				soil = true;
			}
			else if (line.substr(0, 4) == "fert")
			{
				waterMap = std::vector<int>(fertMap);
				soil = false;
				fert = true;
			}
			else if (line.substr(0, 4) == "water")
			{
				lightMap = std::vector<int>(waterMap);
				fert = false;
				water = true;
			}
			else if (line.substr(0, 4) == "light")
			{
				tempMap = std::vector<int>(lightMap);
				water = false;
				light = true;
			}
			else if (line.substr(0, 4) == "temp")
			{
				humidMap = std::vector<int>(tempMap);
				light = false;
				temp = true;
			}
			else if (line.substr(0, 4) == "humid")
			{
				locationMap = std::vector<int>(humidMap);
				temp = false;
				humid = true;
			}
			else
			{
				std::cout << "current Line " << line << std::endl;
				if (line.length() > 1 && isdigit(line[0]))
				{
					std::cout << "startIndex= " << std::stoi(split(line, " ")[0]) << std::endl;
					if (soil)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							soilMap[std::stoi(split(line, " ")[0])] = seedMap[std::stoi(split(line, " ")[1]) + i];
						}
					} else if (fert)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							fertMap[std::stoi(split(line, " ")[0])] = soilMap[std::stoi(split(line, " ")[1]) + i];
						}
					}
					else if (water)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							waterMap[std::stoi(split(line, " ")[0])] = fertMap[std::stoi(split(line, " ")[1]) + i];
						}
					}
					else if (light)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							lightMap[std::stoi(split(line, " ")[0])] = waterMap[std::stoi(split(line, " ")[1]) + i];
						}
					}
					else if (temp)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							tempMap[std::stoi(split(line, " ")[0])] = lightMap[std::stoi(split(line, " ")[1]) + i];
						}
					}
					else if (humid)
					{
						for (int i = 0; i < std::stoi(split(line, " ")[2]); i++)
						{
							humidMap[std::stoi(split(line, " ")[0])] = tempMap[std::stoi(split(line, " ")[1]) + i];
						}
					}
				}
			}
		}
		std::cout << "seeds soil" << std::endl;
		for (int i = 0; i < seedMap.size(); i++)
		{
			std::cout << seedMap.at(i) << " " << soilMap.at(i) << std::endl;
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}