#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>

int day13(int part)
{
	std::fstream input("./input/day13input.txt");
	std::vector<std::string> columns{};
	std::vector<std::string> rows{};
	std::string line{};
	std::vector <std::vector<std::string>> chunks{};
	std::vector<std::string> rawChunks{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (line.length() == 0)
			{
				chunks.push_back(rawChunks);
				rawChunks = {};
			}
			else
			{
				rawChunks.push_back(line);
			}
		}
		chunks.push_back(rawChunks);
		int totalCount = 0;
		for (size_t chunk = 0; chunk < chunks.size(); chunk++)
		{
			rows = {};
			columns = {};
			for (size_t line = 0; line < chunks[chunk].size(); line++)
			{
				rows.push_back(chunks[chunk][line]);
			}
			for (size_t x = 0; x < rows[0].length(); x++)
			{
				std::string column;
				for (size_t y = 0; y < chunks[chunk].size(); y++)
				{
					column.append(std::string(1, rows[y][x]));
				}
				columns.push_back(column);
			}
			for (size_t i = 0; i < rows.size(); i++)
			{
				if (i == rows.size() - 1)
				{
					if (rows[i] == rows[i - 1])
					{
						std::cout << " found mirror in chunk " << chunk << " at row " << rows[i] << '\n';
						totalCount += 100 * (rows[i].length() - i);
						break;
					}
				}
				else
				{
					if (rows[i] == rows[i + 1] || rows[i] == rows[i - 1])
					{
						std::cout << " found mirror in chunk " << chunk << " at row " << rows[i] << '\n';
						totalCount += 100 * (rows[i].length() - i);
						break;
					}
				}
			}
			for (size_t i = 0; i < columns.size(); i++)
			{
				if (i == 0)
				{
					if (columns[i] == columns[i + 1])
					{
						std::cout << " found mirror in chunk " << chunk << " at column " << columns[i] << '\n';
						totalCount += (columns[i].length() - i);
						break;
					}
				}
				else if (i == columns.size() - 1)
				{
					if (columns[i] == columns[i - 1])
					{
						std::cout << " found mirror in chunk " << chunk << " at column " << columns[i] << '\n';
						totalCount += (columns[i].length() - i);
						break;
					}
				}
				else
				{
					if (columns[i] == columns[i + 1] || columns[i] == columns[i - 1])
					{
						std::cout << " found mirror in chunk " << chunk << " at column " << columns[i] << '\n';
						totalCount += (columns[i].length() - i);
						break;
					}
				}
			}
			std::cout << "chunk count = " << totalCount << '\n';
		}
		std::cout << "total count: " << totalCount << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}