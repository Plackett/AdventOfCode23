#include <conio.h>
#include <iostream>
#include <regex>
#include "dayLinker.hh"

int main(int argc, char** argv)
{
begin:
	std::cout << "please type the number of the day you would like to run, press enter to end your statement." << std::endl;
	std::string input{};
	std::cin >> input;
	for (char c : input)
	{
		if (!isdigit(c))
		{
			std::cout << "not a valid number, try again. (input must be a positive integer)" << '\n';
			input.clear();
			goto begin;
		}
	}
	while (std::stoi(input) > 25 || std::stoi(input) < 1)
	{
		std::cout << "number not in range, try again. (input must be between 1 and 25)" << std::endl;
		std::string input{};
		goto begin;
	}
	std::cout << "please type the number of the part you would like to run, 1 for part 1, and 2 for part 2." << std::endl;
	input.append(std::string(1,_getch()));
	while (!isdigit(input[input.length() - 1]))
	{
		std::cout << "not a valid number, try again. (input must be a positive integer)" << '\n';
		input[input.length() - 1] = _getch();
	}
	while (std::stoi(std::string(1,input[input.length() - 1])) > 2 || std::stoi(std::string(1,input[input.length() - 1])) < 1)
	{
		std::cout << "number not in range, please type either a 1 for part 1 or a 2 for part 2." << std::endl;
		input[input.length() - 1] = _getch();
	}
	int part = std::stoi(input.substr(1, input.length() - 1));
	std::cout << "Running day " << input.substr(0,input.length() - 1) << " part " << part << "..." << std::endl;
	switch (std::stoi(input.substr(0, input.length() - 1)))
	{
	case 1:
		day1(part);
		break;
	case 2:
		day2(part);
		break;
	case 3:
		day3(part);
		break;
	case 4:
		day4(part);
		break;
	case 5:
		day5(part);
		break;
	case 6:
		day6(part);
		break;
	case 7:
		day7(part);
		break;
	case 8:
		day8(part);
		break;
	case 9:
		day9(part);
		break;
	case 10:
		day10(part);
		break;
	case 11:
		day11(part);
		break;
	case 12:
		day12(part);
		break;
	case 13:
		day13(part);
		break;
	case 14:
		day14(part);
		break;
	case 15:
		day15(part);
		break;
	case 16:
		day16(part);
		break;
	case 17:
		day17(part);
		break;
	case 18:
		day18(part);
		break;
	case 19:
		day19(part);
		break;
	case 20:
		day20(part);
		break;
	case 21:
		day21(part);
		break;
	case 22:
		day22(part);
		break;
	case 23:
		day23(part);
		break;
	case 24:
		day24(part);
		break;
	case 25:
		day25(part);
		break;
	}
	std::cout << "Press r to rerun the program, Press any other key to exit." << std::endl;
	switch (_getch())
	{
	case 'r':
		goto begin;
	default:
		return 0;
	}
}