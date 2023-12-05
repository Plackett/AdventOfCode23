#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <string_view>
#include <algorithm>
#include <iterator>
#include "dayLinker.hh"

int main(long argc, char** argv)
{
	std::ifstream input("./input/day5input.txt");
	std::string line{};
	std::istringstream test();
	std::vector<long> seedMap{};
	std::vector<long> soilMap{};
	std::vector<long> fertMap{};
	std::vector<long> waterMap{};
	std::vector<long> lightMap{};
	std::vector<long> tempMap{};
	std::vector<long> humidMap{};
	std::vector<long> locationMap{};
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
				for (std::string num : split(split(line, ":")[1], " "))
				{
					for (char c : num)
					{
						if (!isdigit(c))
						{
							std::cout << "FAILED AT " << num << std::endl;
							return 0;
						}
					}
					remove_if(num.begin(), num.end(), isspace);
					if (num.length())
					{
						std::cout << "seed at " << num << std::endl;
						seedMap.push_back(atol(num.c_str()));
					}
				}
			}
			else if (line.substr(0, 4) == "seed")
			{
				soilMap = std::vector<long>(seedMap);
				soil = true;
			}
			else if (line.substr(0, 4) == "soil")
			{
				soil = false;
				fertMap = std::vector<long>(soilMap);
				fert = true;
			}
			else if (line.substr(0, 4) == "fert")
			{
				fert = false;
				waterMap = std::vector<long>(fertMap);
				water = true;
			}
			else if (line.substr(0, 4) == "wate")
			{
				water = false;
				lightMap = std::vector<long>(waterMap);
				light = true;
			}
			else if (line.substr(0, 4) == "ligh")
			{
				light = false;
				tempMap = std::vector<long>(lightMap);
				temp = true;
			}
			else if (line.substr(0, 4) == "temp")
			{
				temp = false;
				humidMap = std::vector<long>(tempMap);
				humid = true;
			}
			else if (line.substr(0, 4) == "humi")
			{
				humid = false;
				locationMap = std::vector<long>(humidMap);
				location = true;
			}
			else
			{
				if (line.length() > 1 && isdigit(line[0]))
				{
					if (soil)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(seedMap.begin(), seedMap.end(), i) != seedMap.end())
							{
								std::cout << "replaced " << *find(seedMap.begin(), seedMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								soilMap[std::distance(seedMap.begin(),find(seedMap.begin(), seedMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					} else if (fert)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(soilMap.begin(), soilMap.end(), i) != soilMap.end())
							{
								std::cout << "replaced " << *find(soilMap.begin(), soilMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								fertMap[std::distance(soilMap.begin(), find(soilMap.begin(), soilMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
					else if (water)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(fertMap.begin(), fertMap.end(), i) != fertMap.end())
							{
								std::cout << "replaced " << *find(fertMap.begin(), fertMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								waterMap[std::distance(fertMap.begin(), find(fertMap.begin(), fertMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
					else if (light)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(waterMap.begin(), waterMap.end(), i) != waterMap.end())
							{
								std::cout << "replaced " << *find(waterMap.begin(), waterMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								lightMap[std::distance(waterMap.begin(), find(waterMap.begin(), waterMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
					else if (temp)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(lightMap.begin(), lightMap.end(), i) != lightMap.end())
							{
								std::cout << "replaced " << *find(lightMap.begin(), lightMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								tempMap[std::distance(lightMap.begin(), find(lightMap.begin(), lightMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
					else if (humid)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(tempMap.begin(), tempMap.end(), i) != tempMap.end())
							{
								std::cout << "replaced " << *find(tempMap.begin(), tempMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								humidMap[std::distance(tempMap.begin(), find(tempMap.begin(), tempMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
					else if (location)
					{
						for (long i = std::atol(split(line, " ")[1].c_str()); i < std::atol(split(line, " ")[1].c_str()) + std::atol(split(line, " ")[2].c_str()); i++)
						{
							std::cout << "range entered at " << i << std::endl;
							if (find(humidMap.begin(), humidMap.end(), i) != humidMap.end())
							{
								std::cout << "replaced " << *find(humidMap.begin(), humidMap.end(), i) << " with " << std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str()) << std::endl;
								locationMap[std::distance(humidMap.begin(), find(humidMap.begin(), humidMap.end(), i))] = std::atol(split(line, " ")[0].c_str()) + i - std::atol(split(line, " ")[1].c_str());
							}
						}
					}
				}
			}
		}
		std::cout << "seeds soil fert water light temp humid" << std::endl;
		for (long i = 0; i < seedMap.size(); i++)
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
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}