#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <string_view>
#include <algorithm>
#include "dayLinker.hh"

struct Card
{
	int index;
	std::string data;
public:
	Card(int i, std::string d) : index(i), data(d) {};
};

int day4(bool part)
{
	std::ifstream input("./input/day4input.txt");
	std::string line{};
	std::vector<std::string> winNums{};
	std::vector<std::string> winsPerCard{};
	std::vector<Card> duplicateCards{};
	int totalWinnings = 0;
	int currentWinnings = 0;
	int currentCards = 0;
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
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
					if (!part)
					{
						currentWinnings = currentWinnings < 2 ? currentWinnings + 1 : currentWinnings * 2;
					}
					else
					{
						currentWinnings += 1;
					}
				}
			}
			if (!part)
			{
				totalWinnings += currentWinnings;
			}
			else
			{
				winsPerCard.push_back(std::to_string(currentWinnings));
				std::cout << currentWinnings << " wins at Card: " << winsPerCard.size() << '\n';
			}
		}
		if (part)
		{
			totalWinnings += winsPerCard.size();
			for (int i = 0; i < winsPerCard.size(); i++)
			{
				std::cout << "running Card:" << i+1 << '\n';
				currentCards = std::stoi(winsPerCard.at(i));
				while (currentCards > 0)
				{
					if (i + currentCards < winsPerCard.size())
					{
						duplicateCards.push_back(Card(i+currentCards,winsPerCard.at(i + currentCards)));
						totalWinnings++;
					}
					currentCards--;
				}
			}
			std::cout << "currentCards before duplicates: " << totalWinnings << '\n';
			int cardsToErase = 0;
			while (duplicateCards.size() > 0)
			{
				for (int i = 0; i < duplicateCards.size(); i++)
				{
					cardsToErase++;
					std::cout << "running Card:" << duplicateCards.at(i).index+1 << '\n';
					currentCards = std::stoi(duplicateCards.at(i).data);
					while (currentCards > 0)
					{
						if (duplicateCards.at(i).index + currentCards < winsPerCard.size())
						{
							duplicateCards.push_back(Card(duplicateCards.at(i).index+currentCards, winsPerCard.at(duplicateCards.at(i).index + currentCards)));
							totalWinnings++;
						}
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