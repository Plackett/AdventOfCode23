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
			bool mirrorCheck = true;
			for (size_t i = 1; i < rows.size(); i++)
			{
				if (part == 1)
				{
					if (rows[i] == rows[i - 1])
					{
						mirrorCheck = true;
						for (int front = i, back = i - 1; back < rows.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (rows[front] != rows[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between rows " << i << " and " << i - 1 << '\n';
							totalCount += i * 100;
							goto finish;
						}
					}
				}
				else
				{
					if (chunk == 20)
						std::cout << "Here" << '\n';
					if (hamming(rows[i], rows[i - 1]) == 1)
					{
						//rows[i - 1] = rows[i];
						mirrorCheck = true;
						for (int back = i, front = i - 1; back < rows.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (rows[front] != rows[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between rows " << i << " and " << i - 1 << '\n';
							totalCount += i * 100;
							goto finish;
						}
					}
					else if (rows[i] == rows[i - 1])
					{
						mirrorCheck = false;
						for (int back = i, front = i - 1; back < rows.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (hamming(rows[front], rows[back]) == 1)
							{
								mirrorCheck = true;
								//rows[front] = rows[back];
							}
							else if (rows[front] != rows[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between rows " << i << " and " << i - 1 << '\n';
							totalCount += i * 100;
							goto finish;
						}
					}
				}
			}
			for (size_t i = 1; i < columns.size(); i++)
			{
				if (part == 1)
				{
					if (columns[i] == columns[i - 1])
					{
						mirrorCheck = true;
						for (int back = i, front = i - 1; back < columns.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (columns[front] != columns[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between columns " << i << " and " << i - 1 << '\n';
							totalCount += i;
							goto finish;
						}
					}
				}
				else
				{
					if (hamming(columns[i], columns[i - 1]) == 1)
					{
						//columns[i - 1] = columns[i];
						mirrorCheck = true;
						for (int back = i, front = i - 1; back < columns.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (columns[front] != columns[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between columns " << i << " and " << i - 1 << '\n';
							totalCount += i;
							goto finish;
						}
					}
					else if (columns[i] == columns[i - 1])
					{
						mirrorCheck = false;
						for (int back = i, front = i - 1; back < columns.size(); front--, back++)
						{
							if (front <= -1)
								break;
							if (hamming(columns[front], columns[back]) == 1)
							{
								mirrorCheck = true;
								//columns[front] = columns[back];
							}
							else if (columns[front] != columns[back] && front != i && front != i - 1 && back != i && back != i - 1)
							{
								mirrorCheck = false;
								break;
							}
						}
						if (mirrorCheck)
						{
							std::cout << " found mirror in chunk" << chunk << "between columns " << i << " and " << i - 1 << '\n';
							totalCount += i;
							goto finish;
						}
					}
				}
			}
		finish:
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