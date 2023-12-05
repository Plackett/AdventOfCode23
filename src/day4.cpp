#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <string_view>
#include <algorithm>
#include <iterator>
#include "dayLinker.hh"

typedef struct
{
	int index, data;
} Card;

int day4(int part)
{
	std::ifstream input("./input/day4input.txt");
	std::string line{};
	std::vector<std::string> winNums{};
	std::vector<Card> winsPerCard{};
	std::vector<Card> duplicateCards{};
	int totalWinnings = 0;
	int currentWinnings = 0;
	int currentCards = 0;
	int cardIndex = 0;
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			cardIndex++;
			currentWinnings = 0;
			winNums = split(split(split(line,":")[1], "|")[0], " ");
			/*for (std::string win : winNums)
			{
				std::cout << win << std::endl;
			}*/
			for (std::string i : split(split(line, "|")[1], " "))
			{
				i.erase(remove_if(i.begin(), i.end(), isspace));
				if (std::find(winNums.begin(), winNums.end(), i) != winNums.end() && i != std::string(1, ' ') && i != "")
				{
					//std::cout << "DOUBLED WINNINGS " << currentWinnings << std::endl << i << std::endl;
					if (part == 1)
					{
						currentWinnings = currentWinnings < 2 ? currentWinnings + 1 : currentWinnings * 2;
					}
					else
					{
						currentWinnings += 1;
					}
				}
			}
			if (part == 1)
			{
				totalWinnings += currentWinnings;
			}
			else
			{
				std::cout << "current card: " << cardIndex << '\n';
				winsPerCard.push_back(Card{ cardIndex, currentWinnings });
				std::cout << currentWinnings << " wins at Card: " << winsPerCard.size() << '\n';
			}
		}
		if (part == 2)
		{
			totalWinnings += winsPerCard.size();
			duplicateCards = std::vector<Card>(winsPerCard);
			int cardsToErase = 0;
			while (duplicateCards.size() > 0)
			{
				for (int i = 0; i < duplicateCards.size(); i++)
				{
					cardsToErase++;
					std::cout << "running Card:" << duplicateCards.at(i).index << '\n';
					currentCards = duplicateCards.at(i).data;
					while (currentCards > 0)
					{
						duplicateCards.push_back(winsPerCard.at(duplicateCards.at(i).index + currentCards-1));
						totalWinnings++;
						currentCards--;
					}
				}
				duplicateCards.erase(duplicateCards.begin(),duplicateCards.begin() + cardsToErase);
			}
		}
		std::cout << "total: " << totalWinnings << '\n';
	}
	return 0;
}