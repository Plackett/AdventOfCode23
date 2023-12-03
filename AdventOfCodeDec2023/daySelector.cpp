#include <conio.h>
#include <iostream>
#include "dayLinker.hh"

int main(int argc, char** argv)
{
	std::cout << "please type the number of the day you would like to run then the part (1/2) ex: day 1 part 1 would be 1 then 1" << std::endl;
	std::string input = std::string(1,_getch());
	std::cout << input;
	input.append(std::string(1, _getch()));
	std::cout << input << std::endl;
	switch (input[0])
	{
	case '1':
		switch (input[1])
		{
		case '1':
			std::cout << "Running day 1 part 1..." << std::endl;
			day1(false);
			break;
		case '2':
			std::cout << "Running day 1 part 2..." << std::endl;
			day1(true);
			break;
		}
		break;
	case '2':
		switch (input[1])
		{
		case '1':
			std::cout << "Running day 2 part 1..." << std::endl;
			day2(false);
			break;
		case '2':
			std::cout << "Running day 2 part 2..." << std::endl;
			day2(true);
			break;
		}
		break;
	case '3':
		switch (input[1])
		{
		case '1':
			std::cout << "Running day 3 part 1..." << std::endl;
			day3(false);
			break;
		case '2':
			std::cout << "Running day 3 part 2..." << std::endl;
			day3(true);
			break;
		}
		break;
	}
	std::cout << "Press any key to exit." << std::endl;
	_getch();
}