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

bool rangeCompare(std::pair<long long, long long>& a, std::pair<long long, long long>& b)
{
	if (a.first == b.first)
	{
		return a.second > b.second;
	}
	else
	{
		return a.first > b.first;
	}
}

std::vector<long long> checkNumber(std::vector<long long> inputArray,std::vector<long long> outputArray, long long srcIndex, long long offset, long long destIndex)
{
	for (long long i = 0; i < inputArray.size(); i++)
	{
		std::cout << "tested " << inputArray[i] << std::endl;
		if (inputArray[i] < srcIndex + offset && inputArray[i] >= srcIndex)
		{
			std::cout << "replaced " << inputArray[i] << " with " << inputArray[i] - srcIndex + destIndex << std::endl;
			outputArray[i] = inputArray[i] - srcIndex + destIndex;
		}
	}
	return outputArray;
}

std::vector<std::pair<long long, long long>> checkRange(std::vector<std::pair<long long, long long>> inputRanges, std::vector<std::pair<long long, long long>> outputRanges, long long srcIndex, long long offset, long long destIndex)
{
	for (std::pair<long long, long long> range : inputRanges)
	// check if the beginning of the range is within the range, if it is within then check end to determine if second split is needed
	{// [======] -> [=] [====] [=]
		if (inRange(range.first, srcIndex + offset, srcIndex))
		{
			std::cout << "FOUND MATCH WITHIN RANGE " << range.first << " and " << range.second << '\n';
			// range is completely within filter range
			if (inRange(range.second, srcIndex + offset, srcIndex))
			{
				outputRanges.push_back(std::pair<long long, long long>(destIndex + (range.first - srcIndex), destIndex + (srcIndex + offset - range.second)));
			}
			// range is within on left, not within on right [====] [==]
			else
			{
				outputRanges.push_back(std::pair<long long, long long>(destIndex + (range.first - srcIndex), destIndex + offset));
				outputRanges.push_back(std::pair<long long, long long>(srcIndex + offset,range.second));
			}
		}
		else
		{
			// range is within on right, not within on left [==] [====]
			if (inRange(range.second, srcIndex + offset, srcIndex))
			{
				outputRanges.push_back(std::pair<long long, long long>(range.first,srcIndex));
				outputRanges.push_back(std::pair<long long, long long>(destIndex,destIndex + (srcIndex + offset - range.second)));
			}
			// range is not within on any values
			else
			{
				outputRanges.push_back(range);
			}
		}
	}
	return outputRanges;
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
	std::vector<std::pair<long long,long long>> seedPairs{};
	std::vector<std::pair<long long, long long>> soilPairs{};
	std::vector<std::pair<long long, long long>> fertPairs{};
	std::vector<std::pair<long long, long long>> waterPairs{};
	std::vector<std::pair<long long, long long>> lightPairs{};
	std::vector<std::pair<long long, long long>> tempPairs{};
	std::vector<std::pair<long long, long long>> humidPairs{};
	std::vector<std::pair<long long, long long>> locationPairs{};
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
				if (part == 1)
				{
					for (long long i = 1; i < rawSeeds.size(); i++)
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
							seedPairs.push_back(std::pair<long long, long long>(std::atoll(rawSeeds[i].c_str()), std::atoll(rawSeeds[i + 1].c_str())));
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
					if (part == 1)
					{
						if (soil)
						{
							soilMap = checkNumber(seedMap, soilMap, srcIndex, offset, destIndex);
						}
						else if (fert)
						{
							fertMap = checkNumber(soilMap, fertMap, srcIndex, offset, destIndex);
						}
						else if (water)
						{
							waterMap = checkNumber(fertMap, waterMap, srcIndex, offset, destIndex);
						}
						else if (light)
						{
							lightMap = checkNumber(waterMap, lightMap, srcIndex, offset, destIndex);
						}
						else if (temp)
						{
							tempMap = checkNumber(lightMap, tempMap, srcIndex, offset, destIndex);
						}
						else if (humid)
						{
							humidMap = checkNumber(tempMap, humidMap, srcIndex, offset, destIndex);
						}
						else if (location)
						{
							locationMap = checkNumber(humidMap, locationMap, srcIndex, offset, destIndex);
						}
					}
					else
					{
						if (soil)
						{
							soilPairs = checkRange(seedPairs, soilPairs, srcIndex, offset, destIndex);
						}
						else if (fert)
						{
							fertPairs = checkRange(soilPairs, fertPairs, srcIndex, offset, destIndex);
						}
						else if (water)
						{
							waterPairs = checkRange(fertPairs, waterPairs, srcIndex, offset, destIndex);
						}
						else if (light)
						{
							lightPairs = checkRange(waterPairs, lightPairs, srcIndex, offset, destIndex);
						}
						else if (temp)
						{
							tempPairs = checkRange(lightPairs, tempPairs, srcIndex, offset, destIndex);
						}
						else if (humid)
						{
							humidPairs = checkRange(tempPairs, humidPairs, srcIndex, offset, destIndex);
						}
						else if (location)
						{
							locationPairs = checkRange(humidPairs, locationPairs, srcIndex, offset, destIndex);
						}
					}
				
				}
			}
		}
		if (part == 1)
		{
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
			std::sort(locationPairs.begin(), locationPairs.end(), rangeCompare);
			for (std::pair<long long,long long> pair: locationPairs)
			{
				std::cout << "location starts at " << pair.first << " ends at " << pair.second << std::endl;
			}
			std::sort(soilPairs.begin(), soilPairs.end(), rangeCompare);
			for (std::pair<long long, long long> pair : soilPairs)
			{
				std::cout << "soil starts at " << pair.first << " ends at " << pair.second << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}