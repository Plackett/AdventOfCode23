#include <iostream>
#include "dayLinker.hh"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

typedef struct
{
	std::string key, left, right;
} Node;

int day8(int part)
{
	std::fstream input("./input/day8input.txt");
	std::string line{};
	int steps = 0;
	std::map<std::string,Node> nodes{};
	std::vector<std::string> ghostStarts{};
	std::string moves{};
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (line.length() == 0)
				continue;
			if (moves.length() == 0)
			{
				moves = line;
			}
			else
			{
				if (line.substr(2, 1) == "A")
				{
					ghostStarts.push_back(line.substr(0, 3));
				}
				nodes.emplace(line.substr(0, 3),Node{ line.substr(0,3),line.substr(7,3),line.substr(12,3) });
				//std::cout << "node of " << line.substr(0, 3) << " with left of " << nodes[line.substr(0, 3)].left << '\n';
			}
		}
		std::string currentNode = "AAA";
		int currentMove = 0;
		if (part == 1)
		{
			while (currentNode != "ZZZ")
			{
				//std::cout << currentNode << " with a move of " << moves[currentMove] << '\n';
				steps++;
				switch (moves[currentMove])
				{
				case 'L':
					//std::cout << "moves to new node " << nodes[currentNode].left << " because of node " << currentNode << '\n';
					currentNode = nodes[currentNode].left;
					break;
				case 'R':
					currentNode = nodes[currentNode].right;
					break;
				}
				currentMove++;
				if (currentMove >= moves.length())
					currentMove = 0;
			}
			std::cout << "got to ZZZ in " << steps << " steps!" << '\n';
		}
		else
		{
			std::vector<size_t> totalSteps;
			totalSteps = {};
			for (size_t i = 0; i < ghostStarts.size(); i++)
			{
				steps = 0;
				currentNode = ghostStarts[i];
				currentMove = 0;
				while (currentNode[2] != 'Z')
				{
					//std::cout << currentNode << " with a move of " << moves[currentMove] << '\n';
					steps++;
					switch (moves[currentMove])
					{
					case 'L':
						currentNode = nodes[currentNode].left;
						break;
					case 'R':
						currentNode = nodes[currentNode].right;
						break;
					}
					currentMove++;
					if (currentMove >= moves.length())
						currentMove = 0;
				}
				//std::cout << "ghost got to Z in " << steps << " steps!" << '\n';
				totalSteps.push_back(steps);
			}
			size_t totalLCM = std::accumulate(totalSteps.begin(), totalSteps.end(), size_t{ 1 }, [](size_t a, size_t b) { return std::lcm(a, b); });
			std::cout << "all ghosts get to Z by " << totalLCM << " steps" << '\n';
		}
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}