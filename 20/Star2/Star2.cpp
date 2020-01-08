#define TO_CHECK '?'
#define VISITED 'o'
#define WALL '#'
#define PATH '.'
#define INTERSECTION '%'
#define CHECKED '!'
#define PORTAL 'X'

#define BIAS 1000

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

struct Point
{
	size_t x = 0;
	size_t y = 0;

	bool operator== (const Point& c1) {
		return (x == c1.x && y == c1.y);
	}
};

struct Portal
{
	Point start;
	Point end;
};

enum direction
{
	north = 1,
	east = 4,
	south = 2,
	west = 3,
	null = 5
};

struct Path
{
	direction pathDirection;
	Point position;
	unsigned long long steps;
};

void PrintArea(std::vector <std::vector <char>> *area)
{
	system("cls");
	for (size_t y = 0; y < area->size(); ++y)
	{
		for (size_t x = 0; x < area->at(y).size(); ++x)
		{
			printf("%c", area->at(y).at(x));
		}
		printf("\n");
	}
}

Point Teleportation(Point position, std::map <std::string, Portal> *portals)
{
	for (auto i = portals->begin(); i != portals->end(); ++i)
	{
		if (*&i->second.start.x == position.x && *&i->second.start.y == position.y)
		{
			position.x = *&i->second.end.x;
			position.y = *&i->second.end.y;

			return position;
		}
		else if (*&i->second.end.x == position.x && *&i->second.end.y == position.y)
		{
			position.x = *&i->second.start.x;
			position.y = *&i->second.start.y;

			return position;
		}
	}

	Point temp;
	return temp;
}

Point MoveRobot(Point robotPosition, direction robotDirection)
{
	switch (robotDirection)
	{
	case north:
		--robotPosition.y;
		break;
	case east:
		++robotPosition.x;
		break;
	case south:
		++robotPosition.y;
		break;
	case west:
		--robotPosition.x;
		break;
	}

	return robotPosition;
}

direction GetDirection(int input)
{
	switch (input)
	{
	case 0:
		return north;
		break;
	case 1:
		return east;
		break;
	case 2:
		return south;
		break;
	case 3:
		return west;
		break;
	}
}

direction OppositeDirection(direction input)
{
	switch (input)
	{
	case north:
		return south;
		break;
	case south:
		return north;
		break;
	case east:
		return west;
		break;
	case west:
		return east;
		break;
	}
}

direction TurnRight(direction input)
{
	switch (input)
	{
	case north:
		return east;
		break;
	case east:
		return south;
		break;
	case south:
		return west;
		break;
	case west:
		return north;
		break;
	}
}

direction TurnLeft(direction input)
{
	switch (input)
	{
	case north:
		return west;
		break;
	case east:
		return north;
		break;
	case south:
		return east;
		break;
	case west:
		return south;
		break;
	}
}

int main(int argc, char* argv[])
{
	std::string buffer = "";
	long long numberOfCommands = 0;

	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <char>> area;
	std::vector <char> vectorBuffer;

	while (std::getline(input, fileLine))
	{
		for (int i = 0; i < fileLine.size() + 1; ++i)
		{
			vectorBuffer.push_back(fileLine[i]);
		}
		area.push_back(vectorBuffer);
		vectorBuffer.clear();
	}

	input.close();

	for (int i = 0; i < fileLine.size() + 1; ++i)
	{
		vectorBuffer.push_back('\0');
	}
	area.push_back(vectorBuffer);
	vectorBuffer.clear();

	std::map <std::string, Portal> portals;
	Point start, end;

	for (size_t y = 0; y < area.size(); ++y)
	{
		std::string stringBuffer = "";
		unsigned int numOfLetters = 0;

		for (size_t x = 0; x < area[y].size(); ++x)
		{
			if (isalpha(area[y][x]))
			{
				stringBuffer.push_back(area[y][x]);
				++numOfLetters;
			}
			else
			{
				if (numOfLetters == 2)
				{
					if (isblank(area[y][x]) || area[y][x] == '\0')
					{
						area[y][x - 3] = PORTAL;
						numOfLetters = 0;

						if (portals[stringBuffer].start.x == 0 && portals[stringBuffer].start.y == 0)
						{
							portals[stringBuffer].start.x = x - 3;
							portals[stringBuffer].start.y = y;
						}
						else
						{
							portals[stringBuffer].end.x = x - 3;
							portals[stringBuffer].end.y = y;
						}

						area[y][x - 2] = WALL;

						if (stringBuffer == "AA")
						{
							start.x = x - 3;
							start.y = y;
						}
						if (stringBuffer == "ZZ")
						{
							end.x = x - 3;
							end.y = y;
						}
					}
					else
					{
						area[y][x] = PORTAL;
						numOfLetters = 0;

						if (portals[stringBuffer].start.x == 0 && portals[stringBuffer].start.y == 0)
						{
							portals[stringBuffer].start.x = x;
							portals[stringBuffer].start.y = y;
						}
						else
						{
							portals[stringBuffer].end.x = x;
							portals[stringBuffer].end.y = y;
						}

						area[y][x - 1] = WALL;

						if (stringBuffer == "AA")
						{
							start.x = x;
							start.y = y;
						}
						if (stringBuffer == "ZZ")
						{
							end.x = x;
							end.y = y;
						}
					}

					numOfLetters = 0;
				}
				else
				{
					numOfLetters = 0;
					stringBuffer.clear();
				}
			}
		}
	}

	for (size_t x = 0; x < area[0].size(); ++x)
	{
		std::string stringBuffer = "";
		unsigned int numOfLetters = 0;

		for (size_t y = 0; y < area.size(); ++y)
		{
			if (isalpha(area[y][x]))
			{
				stringBuffer.push_back(area[y][x]);
				++numOfLetters;
			}
			else
			{
				if (numOfLetters == 2)
				{
					if (isblank(area[y][x]) || area[y][x] == '\0')
					{
						area[y - 3][x] = PORTAL;
						numOfLetters = 0;

						if (portals[stringBuffer].start.x == 0 && portals[stringBuffer].start.y == 0)
						{
							portals[stringBuffer].start.x = x;
							portals[stringBuffer].start.y = y - 3;
						}
						else
						{
							portals[stringBuffer].end.x = x;
							portals[stringBuffer].end.y = y - 3;
						}

						area[y - 2][x] = WALL;

						if (stringBuffer == "AA")
						{
							start.x = x;
							start.y = y - 3;
						}
						if (stringBuffer == "ZZ")
						{
							end.x = x;
							end.y = y - 3;
						}
					}
					else
					{
						area[y][x] = PORTAL;
						numOfLetters = 0;

						if (portals[stringBuffer].start.x == 0 && portals[stringBuffer].start.y == 0)
						{
							portals[stringBuffer].start.x = x;
							portals[stringBuffer].start.y = y;
						}
						else
						{
							portals[stringBuffer].end.x = x;
							portals[stringBuffer].end.y = y;
						}

						area[y - 1][x] = WALL;

						if (stringBuffer == "AA")
						{
							start.x = x;
							start.y = y;
						}
						if (stringBuffer == "ZZ")
						{
							end.x = x;
							end.y = y;
						}
					}

					numOfLetters = 0;
				}
				else
				{
					numOfLetters = 0;
					stringBuffer.clear();
				}
			}
		}
	}

	//PrintArea(&area);

	std::vector <Path> Paths;
	std::vector <Path> PathsToAdd;

	long minNumOfSteps = LONG_MAX;

	Path system;
	system.pathDirection = south;
	system.position = start;
	system.steps = 0;
	Paths.push_back(system);

	do
	{
		//PrintArea(&area);

		for (auto j = Paths.begin(); j != Paths.end();)
		{
			Point testPosition = MoveRobot(j->position, j->pathDirection);
			if (area[testPosition.y][testPosition.x] == WALL)
			{
				do
				{
					j->pathDirection = TurnLeft(j->pathDirection);
					testPosition = MoveRobot(j->position, j->pathDirection);
				} while (area[testPosition.y][testPosition.x] == WALL);
			}
			j->position = testPosition;
			++(j->steps);

			if (j->position == start)
				area[j->position.y][j->position.x] = VISITED;
			else if (j->position == end)
			{
				if (j->steps < minNumOfSteps)
					minNumOfSteps = j->steps;
				j = Paths.erase(j);
				continue;
			}
			if (area[j->position.y][j->position.x] == PORTAL)
			{
				j->position = Teleportation(j->position, &portals);
				++j->steps;
			}

			area[j->position.y][j->position.x] = VISITED;

			int ways = 0;

			if (area[j->position.y - 1][j->position.x] != WALL && area[j->position.y - 1][j->position.x] != VISITED)
			{
				++ways;
			}
			if (area[j->position.y + 1][j->position.x] != WALL && area[j->position.y + 1][j->position.x] != VISITED)
			{
				++ways;
			}
			if (area[j->position.y][j->position.x - 1] != WALL && area[j->position.y][j->position.x - 1] != VISITED)
			{
				++ways;
			}
			if (area[j->position.y][j->position.x + 1] != WALL && area[j->position.y][j->position.x + 1] != VISITED)
			{
				++ways;
			}

			if (ways > 1)
			{
				if (area[j->position.y - 1][j->position.x] != WALL && area[j->position.y - 1][j->position.x] != VISITED && j->pathDirection != south)
				{
					Path temp;
					temp.position = j->position;
					temp.pathDirection = north;
					temp.steps = j->steps;
					PathsToAdd.push_back(temp);
				}
				if (area[j->position.y + 1][j->position.x] != WALL && area[j->position.y + 1][j->position.x] != VISITED && j->pathDirection != north)
				{
					Path temp;
					temp.position = j->position;
					temp.pathDirection = south;
					temp.steps = j->steps;
					PathsToAdd.push_back(temp);
				}
				if (area[j->position.y][j->position.x - 1] != WALL && area[j->position.y][j->position.x - 1] != VISITED && j->pathDirection != east)
				{
					Path temp;
					temp.position = j->position;
					temp.pathDirection = west;
					temp.steps = j->steps;
					PathsToAdd.push_back(temp);
				}
				if (area[j->position.y][j->position.x + 1] != WALL && area[j->position.y][j->position.x + 1] != VISITED && j->pathDirection != west)
				{
					Path temp;
					temp.position = j->position;
					temp.pathDirection = east;
					temp.steps = j->steps;
					PathsToAdd.push_back(temp);
				}

				j = Paths.erase(j);
			}
			else
			{
				Point tempPosition = MoveRobot(j->position, j->pathDirection);
				if (area[tempPosition.y][tempPosition.x] == WALL && area[tempPosition.y][tempPosition.x] != VISITED)
				{
					Point tempLeftPosition = MoveRobot(j->position, TurnLeft(j->pathDirection));
					Point tempRightPosition = MoveRobot(j->position, TurnRight(j->pathDirection));
					Point tempOppositePosition = MoveRobot(j->position, OppositeDirection(j->pathDirection));
					if (area[tempLeftPosition.y][tempLeftPosition.x] != WALL && area[tempLeftPosition.y][tempLeftPosition.x] != VISITED)
					{
						j->pathDirection = TurnLeft(j->pathDirection);
						++j;
					}
					else if (area[tempRightPosition.y][tempRightPosition.x] != WALL && area[tempRightPosition.y][tempRightPosition.x] != VISITED)
					{
						j->pathDirection = TurnRight(j->pathDirection);
						++j;
					}
					else if (area[tempOppositePosition.y][tempOppositePosition.x] != WALL && area[tempOppositePosition.y][tempOppositePosition.x] != VISITED)
					{
						j->pathDirection = OppositeDirection(j->pathDirection);
						++j;
					}
					else
					{
						j = Paths.erase(j);
					}
				}
				else
				{
					++j;
				}
			}
		}

		for (size_t i = 0; i < PathsToAdd.size(); ++i)
		{
			Paths.push_back(PathsToAdd[i]);
		}
		PathsToAdd.clear();

		//PrintArea(&area, &robotPosition, &robotDirection);

	} while (Paths.size() > 0);

	PrintArea(&area);

	std::cout << "Steps: " << minNumOfSteps << std::endl;
}