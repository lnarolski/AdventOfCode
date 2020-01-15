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

const size_t numOfMinutes = 200;
std::vector <std::vector <char>> emptyArea;
std::vector <long long> levelsToAdd;

class level
{
public:
	long long depth;
	std::vector <std::vector <char>>* GetArea()
	{
		return area;
	}
	void SetArea(std::vector <std::vector <char>>* newArea)
	{
		delete area;

		area = newArea;
	}

	level(long long depth)
	{
		this->depth = depth;

		area = new std::vector <std::vector <char>>(emptyArea);
	}
	~level()
	{
		if (area != nullptr)
			delete area;
	}

private:
	std::vector <std::vector <char>>* area = nullptr;
};

bool LevelExist(long long depth, std::map <long long, level*>* areas)
{
	bool exist = false;
	for (auto i = areas->begin(); i != areas->end(); ++i)
	{
		if (i->first == depth)
		{
			exist = true;
			break;
		}
	}

	return exist;
}

char Run(size_t *x, size_t *y, std::map <long long, level*>* areas, long long* depth)
{
	unsigned int numOfBugs = 0;
	char returnValue;

	if (*x == 0)
	{
		if (LevelExist(*depth + 1, areas))
		{
			if (areas->at(*depth + 1)->GetArea()->at(emptyArea.size() / 2).at(emptyArea.at(0).size() / 2 - 1) == BUG)
			{
				++numOfBugs;
			}
		}
		else
		{
			levelsToAdd.push_back(*depth + 1);
		}
	}
	else
	{
		if (areas->at(*depth)->GetArea()->at(*y).at(*x - 1) == '?')
		{
			if (LevelExist(*depth - 1, areas))
			{
				for (size_t i = 0; i < emptyArea.size(); ++i)
				{
					if (areas->at(*depth - 1)->GetArea()->at(i).at(emptyArea.at(0).size() - 1) == BUG)
					{
						++numOfBugs;
					}
				}
			}
			else
			{
				levelsToAdd.push_back(*depth - 1);
			}
		}
		else
		{
			if (areas->at(*depth)->GetArea()->at(*y).at(*x - 1) == BUG)
			{
				++numOfBugs;
			}
		}
	}

	if (*y == 0)
	{
		if (LevelExist(*depth + 1, areas))
		{
			if (areas->at(*depth + 1)->GetArea()->at(emptyArea.size() / 2 - 1).at(emptyArea.at(0).size() / 2) == BUG)
			{
				++numOfBugs;
			}
		}
		else
		{
			levelsToAdd.push_back(*depth + 1);
		}
	}
	else
	{
		if (areas->at(*depth)->GetArea()->at(*y - 1).at(*x) == '?')
		{
			if (LevelExist(*depth - 1, areas))
			{
				for (size_t i = 0; i < emptyArea.at(0).size(); ++i)
				{
					if (areas->at(*depth - 1)->GetArea()->at(emptyArea.at(0).size() - 1).at(i) == BUG)
					{
						++numOfBugs;
					}
				}
			}
			else
			{
				levelsToAdd.push_back(*depth - 1);
			}
		}
		else
		{
			if (areas->at(*depth)->GetArea()->at(*y - 1).at(*x) == BUG)
			{
				++numOfBugs;
			}
		}
	}

	if (*x == emptyArea.at(0).size() - 1)
	{
		if (LevelExist(*depth + 1, areas))
		{
			if (areas->at(*depth + 1)->GetArea()->at(emptyArea.size() / 2).at(emptyArea.at(0).size() / 2 + 1) == BUG)
			{
				++numOfBugs;
			}
		}
		else
		{
			levelsToAdd.push_back(*depth + 1);
		}
	}
	else
	{
		if (areas->at(*depth)->GetArea()->at(*y).at(*x + 1) == '?')
		{
			if (LevelExist(*depth - 1, areas))
			{
				for (size_t i = 0; i < emptyArea.size(); ++i)
				{
					if (areas->at(*depth - 1)->GetArea()->at(i).at(0) == BUG)
					{
						++numOfBugs;
					}
				}
			}
			else
			{
				levelsToAdd.push_back(*depth - 1);
			}
		}
		else
		{
			if (areas->at(*depth)->GetArea()->at(*y).at(*x + 1) == BUG)
			{
				++numOfBugs;
			}
		}
	}

	if (*y == emptyArea.size() - 1)
	{
		if (LevelExist(*depth + 1, areas))
		{
			if (areas->at(*depth + 1)->GetArea()->at(emptyArea.size() / 2 + 1).at(emptyArea.at(0).size() / 2) == BUG)
			{
				++numOfBugs;
			}
		}
		else
		{
			levelsToAdd.push_back(*depth + 1);
		}
	}
	else
	{
		if (areas->at(*depth)->GetArea()->at(*y + 1).at(*x) == '?')
		{
			if (LevelExist(*depth - 1, areas))
			{
				for (size_t i = 0; i < emptyArea.at(0).size(); ++i)
				{
					if (areas->at(*depth - 1)->GetArea()->at(0).at(i) == BUG)
					{
						++numOfBugs;
					}
				}
			}
			else
			{
				levelsToAdd.push_back(*depth - 1);
			}
		}
		else
		{
			if (areas->at(*depth)->GetArea()->at(*y + 1).at(*x) == BUG)
			{
				++numOfBugs;
			}
		}
	}

	if ((numOfBugs == 1 || numOfBugs == 2) && areas->at(*depth)->GetArea()->at(*y).at(*x) == EMPTY)
		returnValue = BUG;
	else if (numOfBugs != 1 && areas->at(*depth)->GetArea()->at(*y).at(*x) == BUG)
		returnValue = EMPTY;
	else
		returnValue = areas->at(*depth)->GetArea()->at(*y).at(*x);

	return returnValue;
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

void PrintAreas(std::map <long long, level*> *areas)
{
	for (size_t y = 0; y < emptyArea.size(); ++y)
	{
		for (auto it = areas->begin(); it != areas->end(); ++it)
		{
			for (size_t x = 0; x < emptyArea.size(); ++x)
			{
				printf("%c", it->second->GetArea()->at(y).at(x));
			}
			printf("\t");
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(int argc, char* argv[])
{
	std::string buffer = "";
	long long numberOfCommands = 0;

	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <char>> initialState;
	std::vector <std::vector <char>> newArea;
	std::map <long long, level*> areas;
	std::map <long long, level*> newAreas;

	while (std::getline(input, fileLine))
	{
		std::vector <char> vectorBuffer;
		std::vector <char> emptyVector;
		for (int i = 0; i < fileLine.size(); ++i)
		{
			vectorBuffer.push_back(fileLine[i]);
			emptyVector.push_back(EMPTY);
		}
		initialState.push_back(vectorBuffer);
		newArea.push_back(vectorBuffer);
		emptyArea.push_back(emptyVector);
	}

	input.close();

	initialState[initialState.size() / 2][initialState.size() / 2] = '?';
	newArea[newArea.size() / 2][newArea.size() / 2] = '?';
	emptyArea[emptyArea.size() / 2][emptyArea.size() / 2] = '?';

	areas[0] = new level(0);
	areas[0]->SetArea(new std::vector <std::vector <char>>(initialState));
	unsigned long long numOfBugs = 0;

	for (size_t i = 0; i < numOfMinutes; ++i)
	{
		for (auto it = areas.begin(); it != areas.end(); ++it)
		{
			long long depth = it->first;

			for (size_t y = 0; y < it->second->GetArea()->size(); ++y)
			{
				for (size_t x = 0; x < it->second->GetArea()->at(0).size(); ++x)
				{
					if (it->second->GetArea()->at(y).at(x) == '?')
						continue;
					newArea[y][x] = Run(&x, &y, &areas, &depth);
				}
			}

			newAreas[depth] = new level(depth);
			newAreas[depth]->SetArea(new std::vector <std::vector <char>>(newArea));
		}

		size_t temp = levelsToAdd.size();
		for (size_t j = 0; j < temp; ++j)
		{
			if (!LevelExist(levelsToAdd[j], &areas))
			{
				long long depth = levelsToAdd[j];

				areas[depth] = new level(levelsToAdd[j]);
				areas[depth]->SetArea(new std::vector <std::vector <char>>(emptyArea));

				for (size_t y = 0; y < emptyArea.size(); ++y)
				{
					for (size_t x = 0; x < emptyArea[0].size(); ++x)
					{
						if (areas[depth]->GetArea()->at(y).at(x) == '?')
							continue;
						newArea[y][x] = Run(&x, &y, &areas, &depth);
					}
				}

				newAreas[depth] = new level(depth);
				newAreas[depth]->SetArea(new std::vector <std::vector <char>>(newArea));
			}
		}

		areas.clear();
		areas = newAreas;
		newAreas.clear();
		levelsToAdd.clear();

		//PrintAreas(&areas);
	}

	for (auto it = areas.begin(); it != areas.end(); ++it)
	{
		for (size_t y = 0; y < it->second->GetArea()->size(); ++y)
		{
			for (size_t x = 0; x < it->second->GetArea()->at(0).size(); ++x)
			{
				if (it->second->GetArea()->at(y).at(x) == BUG)
					++numOfBugs;
			}
		}
	}

	std::cout << "numOfBugs: " << numOfBugs << std::endl;
}