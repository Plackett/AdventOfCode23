#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <string_view>
#include <algorithm>
#include <iterator>
#include <thread>
#include "dayLinker.hh"

void addIncreasingNumbers(std::vector<long long> in, long long startIndex, long long length)
{
	std::iota(in.begin() + startIndex, in.begin() + length, startIndex);
}

int day5(int part)
{
	std::ifstream input("./input/day5input.txt");
	std::string line{};
	std::istringstream test();
	std::vector<long long> seedMap{};
	std::vector<long long> soilMap{};
	std::vector<long long> fertMap{};
	std::vector<long long> waterMap{};
	std::vector<long long> lightMap{};
	std::vector<long long> tempMap{};
	std::vector<long long> humidMap{};
	std::vector<long long> locationMap{};
	bool seed = false;
	bool soil = false;
	bool fert = false;
	bool water = false;
	bool light = false;
	bool temp = false;
	bool humid = false;
	bool location = false;
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (line.substr(0, 5) == "seeds")
			{
				std::vector<std::string> rawSeeds = split(line.substr(6, line.length()), " ");
				std::vector<long long> numericSeeds{};
				std::vector<std::pair<long long, long long>> rawPairs{};
				if (part == 1)
				{
					for (long long i = 0; i < rawSeeds.size(); i++)
					{
						seedMap.push_back(std::atoll(rawSeeds[i].c_str()));
					}
				}
				else if (part == 2)
				{
					for (long long i = 1; i < rawSeeds.size(); i = i + 2)
					{
						if (std::atoll(rawSeeds[i].c_str()) != 0)
						{
							rawPairs.push_back(std::pair<long long, long long>(std::atoll(rawSeeds[i].c_str()), std::atoll(rawSeeds[i + 1].c_str())));
						}
					}
					/*
					std::thread _x[10]{
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[0].first,rawPairs[0].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[1].first,rawPairs[1].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[2].first,rawPairs[2].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[3].first,rawPairs[3].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[4].first,rawPairs[4].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[5].first,rawPairs[5].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[6].first,rawPairs[6].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[7].first,rawPairs[7].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[8].first,rawPairs[8].second),
						std::thread(addIncreasingNumbers, rawSeeds,rawPairs[9].first,rawPairs[9].second),
					};
					for (size_t i = 0; i < 10; ++i)
					{
						_x[i].join();
					}*/
				}
			}
			else if (line.substr(0, 4) == "seed")
			{
				std::cout << "MOVED TO SOIL TRANSLATION" << std::endl;
				soilMap = std::vector<long long>(seedMap);
				soil = true;
			}
			else if (line.substr(0, 4) == "soil")
			{
				std::cout << "MOVED TO FERTILIZER TRANSLATION" << std::endl;
				soil = false;
				fertMap = std::vector<long long>(soilMap);
				fert = true;
			}
			else if (line.substr(0, 4) == "fert")
			{
				std::cout << "MOVED TO WATER TRANSLATION" << std::endl;
				fert = false;
				waterMap = std::vector<long long>(fertMap);
				water = true;
			}
			else if (line.substr(0, 4) == "wate")
			{
				std::cout << "MOVED TO LIGHT TRANSLATION" << std::endl;
				water = false;
				lightMap = std::vector<long long>(waterMap);
				light = true;
			}
			else if (line.substr(0, 4) == "ligh")
			{
				std::cout << "MOVED TO TEMPERATURE TRANSLATION" << std::endl;
				light = false;
				tempMap = std::vector<long long>(lightMap);
				temp = true;
			}
			else if (line.substr(0, 4) == "temp")
			{
				std::cout << "MOVED TO HUMIDITY TRANSLATION" << std::endl;
				temp = false;
				humidMap = std::vector<long long>(tempMap);
				humid = true;
			}
			else if (line.substr(0, 4) == "humi")
			{
				std::cout << "MOVED TO LOCATION TRANSLATION" << std::endl;
				humid = false;
				locationMap = std::vector<long long>(humidMap);
				location = true;
			}
			else
			{
				if (line.length() > 1 && (soil || fert || water || light || temp || humid || location))
				{
					long long srcIndex = std::atoll(split(line, " ")[1].c_str());
					long long destIndex = std::atoll(split(line, " ")[0].c_str());
					long long offset = std::atoll(split(line, " ")[2].c_str());
					if (soil)
					{
						for (long long i = 0; i < seedMap.size(); i++)
						{
							std::cout << "tested " << seedMap[i] << std::endl;
							if (seedMap[i] < srcIndex + offset && seedMap[i] >= srcIndex)
							{
								std::cout << "replaced " << seedMap[i] << " with " << seedMap[i] - srcIndex + destIndex << std::endl;
								soilMap[i] = seedMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (fert)
					{
						for (long long i = 0; i < soilMap.size(); i++)
						{
							std::cout << "tested " << soilMap[i] << std::endl;
							if (soilMap[i] < srcIndex + offset && soilMap[i] >= srcIndex)
							{
								std::cout << "replaced " << soilMap[i] << " with " << soilMap[i] - srcIndex + destIndex << std::endl;
								fertMap[i] = soilMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (water)
					{
						for (long long i = 0; i < fertMap.size(); i++)
						{
							std::cout << "tested " << fertMap[i] << std::endl;
							if (fertMap[i] < srcIndex + offset && fertMap[i] >= srcIndex)
							{
								std::cout << fertMap[i] << " was between " << srcIndex << " and " << srcIndex + offset << std::endl;
								std::cout << "replaced " << fertMap[i] << " with " << fertMap[i] - srcIndex + destIndex << std::endl;
								waterMap[i] = fertMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (light)
					{
						for (long long i = 0; i < waterMap.size(); i++)
						{
							std::cout << "tested " << waterMap[i] << std::endl;
							if (waterMap[i] < srcIndex + offset && waterMap[i] >= srcIndex)
							{
								std::cout << "replaced " << waterMap[i] << " with " << waterMap[i] - srcIndex + destIndex << std::endl;
								lightMap[i] = waterMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (temp)
					{
						for (long long i = 0; i < lightMap.size(); i++)
						{
							std::cout << "tested " << lightMap[i] << std::endl;
							if (lightMap[i] < srcIndex + offset && lightMap[i] >= srcIndex)
							{
								std::cout << "replaced " << lightMap[i] << " with " << lightMap[i] - srcIndex + destIndex << std::endl;
								tempMap[i] = lightMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (humid)
					{
						for (long long i = 0; i < tempMap.size(); i++)
						{
							std::cout << "tested " << tempMap[i] << std::endl;
							if (tempMap[i] < srcIndex + offset && tempMap[i] >= srcIndex)
							{
								std::cout << "replaced " << tempMap[i] << " with " << tempMap[i] - srcIndex + destIndex << std::endl;
								humidMap[i] = tempMap[i] - srcIndex + destIndex;
							}
						}
					}
					else if (location)
					{
						for (long long i = 0; i < humidMap.size(); i++)
						{
							std::cout << "tested " << humidMap[i] << std::endl;
							if (humidMap[i] < srcIndex + offset && humidMap[i] >= srcIndex)
							{
								std::cout << "replaced " << humidMap[i] << " with " << humidMap[i] - srcIndex + destIndex << std::endl;
								locationMap[i] = humidMap[i] - srcIndex + destIndex;
							}
						}
					}
				}
			}
		}
		std::cout << "seeds soil fert water light temp humid" << std::endl;
		for (long long i = 0; i < seedMap.size(); i++)
		{
			std::cout << seedMap.at(i);
			std::cout << " " << soilMap.at(i);
			std::cout << " " << fertMap.at(i);
			std::cout << " " << waterMap.at(i);
			std::cout << " " << lightMap.at(i);
			std::cout << " " << tempMap.at(i);
			std::cout << " " << humidMap.at(i);
			std::cout << " " << locationMap.at(i) << std::endl;
		}
		auto smallestLocation = std::min_element(locationMap.begin(), locationMap.end());
		std::cout << "location " << *smallestLocation << "has the smallest location size and started off as seed " << seedMap.at(std::distance(locationMap.begin(), smallestLocation)) << std::endl;
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}