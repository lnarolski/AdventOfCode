#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <random>
#include <conio.h>
#include <sstream>
#include <list>

const unsigned long long numOfCards = 119315717514047;
const unsigned long long numOfRepeats = 101741582076661;

enum technique
{
	deal_with_increment,
	cut,
	deal_into_new_stack
};

struct command
{
	technique _technique;
	long _parameterValue;
};

long ExtractLong(std::string str)
{
	std::stringstream ss;

	/* Storing the whole string into string stream */
	ss << str;

	/* Running loop till the end of the stream */
	std::string temp;
	long found;
	while (!ss.eof()) {

		/* extracting word by word from stream */
		ss >> temp;

		/* Checking the given word is integer or not */
		if (std::stringstream(temp) >> found)
			return found;

		/* To save from space at the end of string */
		temp = "";
	}
}

std::list <unsigned long long> DealIntoNewStack(std::list <unsigned long long>* cards)
{
	std::list <unsigned long long> newStack;

	for (auto i = cards->end(); i != cards->begin();)
	{
		--i;
		newStack.push_back(*i);
	}

	return newStack;
}

std::list <unsigned long long> CutNCards(std::list <unsigned long long>* cards, long* _parameterValue)
{
	std::list <unsigned long long> newStack;
	size_t j;

	if (*_parameterValue >= 0)
	{
		j = 0;
		for (auto i = cards->begin(); i != cards->end(); ++i)
		{
			if (j >= *_parameterValue)
			{
				newStack.push_back(*i);
			}

			++j;
		}

		j = 0;
		for (auto i = cards->begin(); j < *_parameterValue; ++i)
		{
			newStack.push_back(*i);

			++j;
		}
	}
	else
	{
		j = 0;
		for (auto i = cards->begin(); i != cards->end(); ++i)
		{
			if (j >= cards->size() + *_parameterValue)
			{
				newStack.push_back(*i);
			}

			++j;
		}

		j = 0;
		for (auto i = cards->begin(); j < cards->size() + *_parameterValue; ++i)
		{
			newStack.push_back(*i);

			++j;
		}
	}

	return newStack;
}

std::list <unsigned long long> DealWithIncrementN(std::list <unsigned long long>* cards, long* _parameterValue)
{
	std::list <unsigned long long> newStack;

	for (long long i = 0; i < cards->size(); ++i)
	{
		newStack.push_back(0);
	}

	size_t j = 0;
	size_t k = 0;
	size_t m = 0;
	bool stop = false;
	bool started = false;
	auto ii = newStack.begin();
	for (auto i = cards->begin(); i != cards->end(); ++i)
	{
		while (m != j)
		{
			++m;
			++ii;
		}
		*ii = *i;

		j += *_parameterValue;

		if (j >= numOfCards)
		{
			j -= numOfCards;
			ii = newStack.begin();
			m = 0;
			while (j >= numOfCards)
			{
				j -= numOfCards;
			}
		}
	}

	return newStack;
}

int main(int argc, char* argv[])
{
	std::vector <command> shuffleTechniques;
	std::list <unsigned long long> cards;

	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	while (std::getline(input, fileLine))
	{
		command buffer;
		if (fileLine.find("deal with increment") != std::string::npos)
		{
			buffer._technique = deal_with_increment;
			buffer._parameterValue = ExtractLong(fileLine);
			shuffleTechniques.push_back(buffer);
		}
		else if (fileLine.find("cut") != std::string::npos)
		{
			buffer._technique = cut;
			buffer._parameterValue = ExtractLong(fileLine);
			shuffleTechniques.push_back(buffer);
		}
		else if (fileLine.find("deal into new stack") != std::string::npos)
		{
			buffer._technique = deal_into_new_stack;
			shuffleTechniques.push_back(buffer);
		}
	}

	input.close();

	for (unsigned long long i = 0; i < numOfCards; ++i)
	{
		cards.push_back(i);
	}

	for (unsigned long long j = 0; j < numOfRepeats; ++j)
	{
		for (size_t i = 0; i < shuffleTechniques.size(); ++i)
		{
			switch (shuffleTechniques[i]._technique)
			{
			case deal_with_increment:
				cards = DealWithIncrementN(&cards, &shuffleTechniques[i]._parameterValue);
				break;
			case cut:
				cards = CutNCards(&cards, &shuffleTechniques[i]._parameterValue);
				break;
			case deal_into_new_stack:
				cards = DealIntoNewStack(&cards);
				break;
			default:
				break;
			}
		}
	}

	size_t position = 0;
	for (auto i = cards.begin(); i != cards.end(); ++i)
	{
		if (*i == 2019)
		{
			break;
		}

		++position;
	}

	std::cout << "Position of card 2020: " << position << std::endl;

	//for (size_t i = 0; i < cards.size(); i++)
	//{
	//	std::cout << cards[i] << " ";
	//}

	//std::cout << std::endl;
}