#include <iostream>
#include <fstream>
#include "dayLinker.hh"
#include <vector>
#include <string>
#include <algorithm>

typedef struct
{
	std::string hand; int type, bid;
} Card;

/**
* high card -- 0
* one pair -- 1
* two pair -- 2
* three of a kind -- 3
* full house -- 4
* four of a kind -- 5
* five of a kind -- 6
*/
int getType(std::string oldHand, int part)
{
	std::string hand{};
	std::vector<int> frequencies{};
	int freq;
	for (size_t i = 0; i < oldHand.length(); i++)
	{
		if (std::find(hand.begin(),hand.end(),oldHand[i]) == hand.end())
		{
			freq = 0;
			for (size_t j = 0; j < oldHand.length(); j++)
			{
				if (part == 2)
				{
					if (oldHand[j] == oldHand[i] && oldHand[i] != 'J')
					{
						freq++;
					}
				}
				else
				{
					if (oldHand[j] == oldHand[i])
					{
						freq++;
					}
				}
			}
			hand += oldHand[i];
			frequencies.push_back(freq);
		}
	}
	std::sort(frequencies.begin(), frequencies.end());
	if (part == 2)
	{
		for (size_t i = 0; i < oldHand.length(); i++)
		{
			if (oldHand[i] == 'J')
			{
				frequencies[frequencies.size() - 1] = frequencies[frequencies.size() - 1] + 1;
			}
		}
	}
	auto maxMatches = frequencies[frequencies.size() - 1];
	switch (maxMatches)
	{
	case 1:
		return 0;
		break;
	case 2:
		if (frequencies[frequencies.size() - 2] > 1)
		{
			return 2;
		}
		else
		{
			return 1;
		}
		break;
	case 3:
		if (frequencies[frequencies.size()-2] > 1)
		{
			return 4;
		} 
		else
		{
			return 3;
		}
		break;
	case 4:
		return 5;
		break;
	case 5:
		return 6;
			break;
	}
}

int getStrength(char input)
{
	switch (input)
	{
	case '2':
		return 0;
		break;
	case '3':
		return 1;
		break;
	case '4':
		return 2;
		break;
	case '5':
		return 3;
		break;
	case '6':
		return 4;
		break;
	case '7':
		return 5;
		break;
	case '8':
		return 6;
		break;
	case '9':
		return 7;
		break;
	case 'T':
		return 8;
		break;
	case 'J':
		return 9;
		break;
	case 'Q':
		return 10;
		break;
	case 'K':
		return 11;
		break;
	case 'A':
		return 12;
		break;
	}
}

int getStrengthPart2(char input)
{
	switch (input)
	{
	case '2':
		return 0;
		break;
	case '3':
		return 1;
		break;
	case '4':
		return 2;
		break;
	case '5':
		return 3;
		break;
	case '6':
		return 4;
		break;
	case '7':
		return 5;
		break;
	case '8':
		return 6;
		break;
	case '9':
		return 7;
		break;
	case 'T':
		return 8;
		break;
	case 'J':
		return -1;
		break;
	case 'Q':
		return 10;
		break;
	case 'K':
		return 11;
		break;
	case 'A':
		return 12;
		break;
	}
}

bool sortByCond(const Card& a, const Card& b)
{
	if (a.type == b.type)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			if (getStrength(a.hand[i]) != getStrength(b.hand[i]))
				return getStrength(a.hand[i]) > getStrength(b.hand[i]);
		}
	}
	return a.type > b.type;
}

bool sortByCond2(const Card& a, const Card& b)
{
	if (a.type == b.type)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			if (getStrengthPart2(a.hand[i]) != getStrengthPart2(b.hand[i]))
				return getStrengthPart2(a.hand[i]) > getStrengthPart2(b.hand[i]);
		}
	}
	return a.type > b.type;
}

int day7(int part)
{
	std::fstream input("./input/day7input.txt");
	std::string line{};
	std::vector<Card> cards{};

	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			Card temp{};
			temp.bid = std::stoi(split(line, " ")[1]);
			temp.hand = split(line, " ")[0];
			temp.type = getType(temp.hand, part);
			cards.push_back(temp);
		}
		if (part == 1)
		{
			std::sort(cards.begin(), cards.end(), sortByCond);
		}
		else
		{
			std::sort(cards.begin(), cards.end(), sortByCond2);
		}
		int total = 0;
		for (int i = 0; i < cards.size(); i++)
		{
			std::cout << "{ hand: \'" << cards[i].hand << "\', bid: \'" << cards[i].bid << "\', power: " << cards[i].type << " }" << '\n';
			total += cards[i].bid * (cards.size() - i);
		}
		std::cout << "total winings= " << total << '\n';
	}
	else
	{
		std::cerr << "missing input file.. exiting!" << std::endl;
	}
	return 0;
}