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

const unsigned long long numOfCards = 10007;

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

std::vector <unsigned long long> DealIntoNewStack(std::vector <unsigned long long>* cards)
{
	std::vector <unsigned long long> newStack;

	for (long long i = cards->size() - 1; i >= 0; --i)
	{
		newStack.push_back(cards->at(i));
	}

	return newStack;
}

std::vector <unsigned long long> CutNCards(std::vector <unsigned long long>* cards, long* _parameterValue)
{
	std::vector <unsigned long long> newStack;

	if (*_parameterValue >= 0)
	{
		for (size_t i = *_parameterValue; i < cards->size(); ++i)
		{
			newStack.push_back(cards->at(i));
		}

		for (size_t i = 0; i < *_parameterValue; ++i)
		{
			newStack.push_back(cards->at(i));
		}
	}
	else
	{
		for (size_t i = cards->size() + *_parameterValue; i < cards->size(); ++i)
		{
			newStack.push_back(cards->at(i));
		}

		for (size_t i = 0; i < cards->size() + *_parameterValue; ++i)
		{
			newStack.push_back(cards->at(i));
		}
	}

	return newStack;
}

std::vector <unsigned long long> DealWithIncrementN(std::vector <unsigned long long>* cards, long* _parameterValue)
{
	std::vector <unsigned long long> newStack;

	for (long long i = 0; i < cards->size(); ++i)
	{
		newStack.push_back(0);
	}

	size_t j = 0;
	size_t k = 0;
	bool stop = false;
	bool started = false;
	while (!stop)
	{
		if ((j % cards->size()) == 0)
		{
			if (started)
				stop = true;
			else
				started = true;
		}
		if (!stop)
		{
			newStack[j % cards->size()] = cards->at(k);
		}

		++k;
		j += *_parameterValue;
	}

	return newStack;
}

int main(int argc, char* argv[])
{
	std::vector <command> shuffleTechniques;
	std::vector <unsigned long long> cards;

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

	size_t position;
	for (size_t i = 0; i < cards.size(); ++i)
	{
		if (cards[i] == 2019)
		{
			position = i;
			break;
		}
	}

	std::cout << "Position of card 2019: " << position << std::endl;

	//for (size_t i = 0; i < cards.size(); i++)
	//{
	//	std::cout << cards[i] << " ";
	//}

	//std::cout << std::endl;
}