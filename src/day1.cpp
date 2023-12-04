#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include "dayLinker.hh"

std::string replaceAllOccurences(std::string in, std::string pattern, std::string replacement)
{
	while (in.find(pattern) != std::string::npos)
	{
		in.replace(in.find(pattern) + 1, 1, replacement);
	}
	return in;
}

int day1(bool part)
{
	std::string line;
	std::string calibrationNumber = "";
	int sum = 0;
	// importing file
	std::ifstream input("./input/day1input.txt");
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			// part two only
			if (part == true)
			{
				line = replaceAllOccurences(line, "one", "1");
				line = replaceAllOccurences(line, "two", "2");
				line = replaceAllOccurences(line, "three", "3");
				line = replaceAllOccurences(line, "four", "4");
				line = replaceAllOccurences(line, "five", "5");
				line = replaceAllOccurences(line, "six", "6");
				line = replaceAllOccurences(line, "seven", "7");
				line = replaceAllOccurences(line, "eight", "8");
				line = replaceAllOccurences(line, "nine", "9");
				line = replaceAllOccurences(line, "ten", "10");
			}
			// part one and two
			calibrationNumber = "";
			for (int i = 0; i < line.length(); i++)
			{
				if (isdigit(line[i]))
				{
					calibrationNumber.append(std::string(1, line[i]));
					break;
				}
			}
			for (int i = line.length(); i > -1; i--)
			{
				if (isdigit(line[i]))
				{
					calibrationNumber.append(std::string(1, line[i]));
					break;
				}
			}
			std::cout << calibrationNumber << " + ";
			sum += std::stoi(calibrationNumber);
		}
		std::cout << "0 = ";
		std::cout << "final sum: " << sum << std::endl;
	}
	else {
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}