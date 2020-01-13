#define BUG '#'
#define EMPTY '.'

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <random>
#include <conio.h>
#include <map>
#include <Windows.h>

char Run(size_t *x, size_t *y, std::vector <std::vector <char>>* area)
{
	unsigned int numOfBugs = 0;
	char returnValue;

	if (*x > 0 && area->at(*y).at(*x - 1) == BUG)
	{
		++numOfBugs;
	}
	if (*y > 0 && area->at(*y - 1).at(*x) == BUG)
	{
		++numOfBugs;
	}
	if (*x < area->at(*y).size() - 1 && area->at(*y).at(*x + 1) == BUG)
	{
		++numOfBugs;
	}
	if (*y < area->size() - 1 && area->at(*y + 1).at(*x) == BUG)
	{
		++numOfBugs;
	}

	if ((numOfBugs == 1 || numOfBugs == 2) && area->at(*y).at(*x) == EMPTY)
		returnValue = BUG;
	else if (numOfBugs != 1 && area->at(*y).at(*x) == BUG)
		returnValue = EMPTY;
	else
		returnValue = area->at(*y).at(*x);

	return returnValue;
}

void CorrectLayout(std::vector <std::vector <char>>* area)
{
	for (size_t y = 0; y < area->size(); ++y)
	{
		for (size_t x = 0; x < area->size(); ++x)
		{
			if (x > 0 && area->at(y).at(x - 1) == BUG && area->at(y).at(x) == BUG)
			{
				area->at(y).at(x - 1) = EMPTY;
				area->at(y).at(x) = EMPTY;
			}
			if (y > 0 && area->at(y - 1).at(x) == BUG && area->at(y).at(x) == BUG)
			{
				area->at(y - 1).at(x) = EMPTY;
				area->at(y).at(x) = EMPTY;
			}
			if (x < area->at(y).size() - 1 && area->at(y).at(x + 1) == BUG && area->at(y).at(x) == BUG)
			{
				area->at(y).at(x + 1) = EMPTY;
				area->at(y).at(x) = EMPTY;
			}
			if (y < area->size() - 1 && area->at(y + 1).at(x) == BUG && area->at(y).at(x) == BUG)
			{
				area->at(y + 1).at(x) = EMPTY;
				area->at(y).at(x) = EMPTY;
			}
		}
	}
}

long double CalculateBiodiversityRating(std::vector <std::vector <char>>* area)
{
	long double biodiversityRating = 0.0;

	for (size_t y = 0; y < area->size(); ++y)
	{
		for (size_t x = 0; x < area->size(); ++x)
		{
			if (area->at(y).at(x) == BUG)
			{
				long double toAdd = powl(2.0, area->at(y).size() * y + x);
				biodiversityRating += toAdd;
			}
		}
	}

	return biodiversityRating;
}

void PrintArea(std::vector <std::vector <char>>* area)
{
	//system("cls");
	for (size_t y = 0; y < area->size(); ++y)
	{
		for (size_t x = 0; x < area->at(y).size(); ++x)
		{
			printf("%c", area->at(y).at(x));
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	std::string buffer = "";
	long long numberOfCommands = 0;

	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <char>> area;
	std::vector <std::vector <char>> newArea;
	std::vector <std::vector <std::vector <char>>> areas;

	while (std::getline(input, fileLine))
	{
		std::vector <char> vectorBuffer;
		for (int i = 0; i < fileLine.size(); ++i)
		{
			vectorBuffer.push_back(fileLine[i]);
		}
		area.push_back(vectorBuffer);
		newArea.push_back(vectorBuffer);
	}

	input.close();

	areas.push_back(area);

	long double biodiversityRating = 0.0;
	bool stop = false;
	while (!stop)
	{
		//PrintArea(&areas[i]);

		for (size_t y = 0; y < area.size(); ++y)
		{
			for (size_t x = 0; x < area[0].size(); ++x)
			{
				newArea[y][x] = Run(&x, &y, &areas[areas.size() - 1]);
			}
		}

		areas.push_back(newArea);

		for (long long i = areas.size() - 2; i >= 0; --i)
		{
			bool theSameLayout = true;
			for (size_t y = 0; y < area.size() && theSameLayout; ++y)
			{
				for (size_t x = 0; x < area[0].size() && theSameLayout; ++x)
				{
					if (areas[i][y][x] != areas[areas.size() - 1][y][x])
					{
						theSameLayout = false;
					}
				}
			}

			if (theSameLayout)
			{
				stop = true;
			}
		}

		if (stop)
			biodiversityRating = CalculateBiodiversityRating(&areas[areas.size() - 1]);
	}

	PrintArea(&areas[areas.size() - 1]);

	std::cout << std::fixed;
	std::cout << "biodiversityRating: " << biodiversityRating << std::endl;
}