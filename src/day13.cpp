#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

int day13(int part)
{
	std::fstream input("./input/day13input.txt");
	std::string line{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{

		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}