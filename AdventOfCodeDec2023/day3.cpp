#include <fstream>;
#include <string>;
#include <vector>;
#include <ctype.h>;
#include <iostream>;

int day3(int argc, char** argv)
{
	// setting up data storage
	std::vector<std::string> lines{};
	std::string current{};
	std::string oldCurrent{};
	int sum = 0;
	int skip = 0;
	// importing file
	std::ifstream input("day3input.txt");
	if (input.is_open())
	{
		// loop through all lines and add to the lines map
		std::string line;
		while (std::getline(input, line)) {
			lines.push_back(line);
		}
		// check for a non number, non period character in a 3x3 radius around each number
		// part 1
		/*
		for (int i = 0; i < lines.size(); ++i)
		{
			for (int j = 0; j < lines.at(i).length(); ++j)
			{
				if (isdigit(lines.at(i)[j]))
				{
					for (int k = i-1; k < i+2; k++)
					{
						if (k > -1 && k < lines.size())
						{
							for (int l = j - 1; l < j + 2; l++)
							{
								if (l > -1 && l < lines.at(k).length())
								{
									if (lines.at(k)[l] != '.' && isdigit(lines.at(k)[l]) == false)
									{
										skip = 0;
										current = std::string(1, lines.at(i)[j]);
										for (int m = j-1; m > -1; m--)
										{
											if (isdigit(lines.at(i)[m]) == false || lines.at(i)[m] == '.')
											{
												m = -1;
												break;
											}
											oldCurrent = current;
											current = std::string(1,lines.at(i)[m]);
											current.append(oldCurrent);
										}
										for (int n = j+1; n < lines.at(i).length(); n++)
										{
											if (isdigit(lines.at(i)[n]) == false || lines.at(i)[n] == '.')
											{
												n = lines.at(i).length();
												break;
											}
											current.append(std::string(1,lines.at(i)[n]));
											skip++;
										}
										sum += std::stoi(current);
										j += skip;
										break;
									}
								}
							}
						}
					}
				}
			}
		}*/
		//part 2
		int firstnumber = 0;
		for (int i = 0; i < lines.size(); ++i)
		{
			for (int j = 0; j < lines.at(i).length(); ++j)
			{
				if (lines.at(i)[j] == '*')
				{
					for (int k = i - 1; k < i + 2; k++)
					{
						if (k > -1 && k < lines.size())
						{
							for (int l = j - 1; l < j + 2; l++)
							{
								if (l > -1 && l < lines.at(k).length())
								{
									if (isdigit(lines.at(k)[l]))
									{
										if (firstnumber == 0)
										{
											skip = 0;
											current = std::string(1, lines.at(k)[l]);
											for (int m = l - 1; m > -1; m--)
											{
												if (isdigit(lines.at(k)[m]) == false || lines.at(k)[m] == '.')
												{
													m = -1;
													break;
												}
												oldCurrent = current;
												current = std::string(1, lines.at(k)[m]);
												current.append(oldCurrent);
											}
											for (int n = l + 1; n < lines.at(l).length(); n++)
											{
												if (isdigit(lines.at(k)[n]) == false || lines.at(k)[n] == '.')
												{
													n = lines.at(k).length();
													break;
												}
												current.append(std::string(1, lines.at(k)[n]));
												skip++;
											}
											firstnumber = std::stoi(current);
											l += skip;
										}
										else {
											current = std::string(1, lines.at(k)[l]);
											for (int m = l - 1; m > -1; m--)
											{
												if (isdigit(lines.at(k)[m]) == false || lines.at(k)[m] == '.')
												{
													m = -1;
													break;
												}
												oldCurrent = current;
												current = std::string(1, lines.at(k)[m]);
												current.append(oldCurrent);
											}
											for (int n = l + 1; n < lines.at(l).length(); n++)
											{
												if (isdigit(lines.at(k)[n]) == false || lines.at(k)[n] == '.')
												{
													n = lines.at(k).length();
													break;
												}
												current.append(std::string(1, lines.at(k)[n]));
											}
											std::cout << firstnumber << "first" << std::endl;
											std::cout << current << "second" << std::endl;
											firstnumber *= std::stoi(current);
											sum += firstnumber;
											std::cout << sum << std::endl;
											firstnumber = 0;
											break;
										}
									}
								}
							}
						}
					}
					firstnumber = 0;
				}
			}
		}
		std::cout << sum << std::endl;
	}
	else
	{
		throw "bro you forgot the input file";
		std::exit(0);
	}
	return 0;
}