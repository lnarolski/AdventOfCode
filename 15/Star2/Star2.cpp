#define ADD_COMM 1
#define MUL_COMM 2
#define INPUT_COMM 3
#define OUTPUT_COMM 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUALS 8
#define ADJ_RELATIVE_BASE 9
#define END_COMM 99

#define WALL 0
#define MOVED 1
#define OXYGEN_SYSTEM 2

#define VISITED 3
#define INTERSECTION 4
#define TO_CHECK 5
#define OXYGEN 6
#define EMPTY -1

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <random>
#include <conio.h>

enum direction
{
	north = 1,
	east = 4,
	south = 2,
	west = 3,
	null = 5
};

struct Point
{
	long x;
	long y;
};

struct OxygenPath
{
	direction pathDirection;
	Point position;
};

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

const int widthArea = 100;
const int heightArea = 100;

void PrintArea(std::vector <std::vector <char>>* area, Point* robotPosition, direction* robotDirection)
{
	system("cls");
	for (long y = 0; y < area->size(); ++y)
	{
		for (long x = 0; x < area->at(0).size(); ++x)
		{
			if (robotPosition->x == x && robotPosition->y == y)
			{
				switch (*robotDirection)
				{
				case north:
					printf("%c", '^');
					break;
				case south:
					printf("%c", 'v');
					break;
				case east:
					printf("%c", '>');
					break;
				case west:
					printf("%c", '<');
					break;
				default:
					break;
				}
			}
			else if (x == widthArea / 2 + 1 && y == heightArea / 2 + 1)
			{
				printf("%c", 'O');
			}
			else
			{
				switch (area->at(y)[x])
				{
				case VISITED:
					printf("%c", '*');
					break;
				case TO_CHECK:
					printf("%c", '?');
					break;
				case WALL:
					printf("%c", 178);
					break;
				case OXYGEN_SYSTEM:
					printf("%c", 'X');
					break;
				case OXYGEN:
					printf("%c", 'X');
					break;
				case EMPTY:
					printf("%c", 0);
					break;
				default:
					break;
				}
			}
		}
		std::cout << std::endl;
	}
}

void expandMemory(std::vector <long long>* commands, long j)
{
	long long size = commands->size();
	for (long long i = 0; i < j - size + 1; ++i)
	{
		commands->push_back(0);
	}
}

long j = 0;
long relativeBase = 0;

std::vector <long long> commands;
long long inputValue = 0;
std::vector <long long> outputValues;
bool computerStop = false;

void IntCodeComputer()
{
	int command = commands[j] % 100;
	int firstParameterMode = (commands[j] % 1000) / 100;
	int secondParameterMode = (commands[j] % 10000) / 1000;
	int thirdParameterMode = (commands[j] % 100000) / 10000;

	if (firstParameterMode == 0 && commands[j + 1] > (commands.size() - 1))
	{
		expandMemory(&commands, commands[j + 1]);
	}
	else if (firstParameterMode == 2 && (relativeBase + commands[j + 1]) > commands.size() - 1)
	{
		expandMemory(&commands, relativeBase + commands[j + 1]);
	}
	else if (firstParameterMode == 1 && j + 1 > commands.size() - 1)
	{
		expandMemory(&commands, j + 1);
	}

	if (secondParameterMode == 0 && commands[j + 2] > (commands.size() - 1))
	{
		expandMemory(&commands, commands[j + 2]);
	}
	else if (secondParameterMode == 2 && (relativeBase + commands[j + 2]) > commands.size() - 1)
	{
		expandMemory(&commands, relativeBase + commands[j + 2]);
	}
	else if (secondParameterMode == 1 && j + 2 > commands.size() - 1)
	{
		expandMemory(&commands, j + 1);
	}

	if (thirdParameterMode == 0 && commands[j + 3] > (commands.size() - 1))
	{
		expandMemory(&commands, commands[j + 3]);
	}
	else if (thirdParameterMode == 2 && (relativeBase + commands[j + 3]) > commands.size() - 1)
	{
		expandMemory(&commands, relativeBase + commands[j + 3]);
	}
	else if (thirdParameterMode == 1 && j + 3 > commands.size() - 1)
	{
		expandMemory(&commands, j + 3);
	}

	while (command != END_COMM)
	{
		switch (command)
		{
		case ADD_COMM:
			if (thirdParameterMode == 0)
			{
				commands[commands[j + 3]] = (firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) + (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
				if (!(j == commands[j + 3]))
					j = j + 4;
			}
			else //thirdParameterMode == 2
			{
				commands[relativeBase + commands[j + 3]] = (firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) + (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
				if (!(j == relativeBase + commands[j + 3]))
					j = j + 4;
			}
			break;
		case MUL_COMM:
			if (thirdParameterMode == 0)
			{
				commands[commands[j + 3]] = (firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) * (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
				if (!(j == commands[j + 3]))
					j = j + 4;
			}
			else //thirdParameterMode == 2
			{
				commands[relativeBase + commands[j + 3]] = (firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) * (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
				if (!(j == relativeBase + commands[j + 3]))
					j = j + 4;
			}
			break;
		case INPUT_COMM:
			(firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) = inputValue;
			if (!(j == commands[j + 3]))
				j = j + 2;
			break;
		case OUTPUT_COMM:
			outputValues.push_back((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]));
			//cout << "Output: " << outputValue << endl;
			j = j + 2;
			if (outputValues.size() == 1)
				return;
			break;
		case JUMP_IF_TRUE:
			if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) != 0)
			{
				j = (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
			}
			else
				j = j + 3;
			break;
		case JUMP_IF_FALSE:
			if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) == 0)
			{
				j = (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]);
			}
			else
				j = j + 3;
			break;
		case LESS_THAN:
			if (thirdParameterMode == 0)
			{
				if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) < (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]))
				{
					commands[commands[j + 3]] = 1;
					if (!(j == commands[j + 3]))
						j = j + 4;
				}
				else
				{
					commands[commands[j + 3]] = 0;
					if (!(j == commands[j + 3]))
						j = j + 4;
				}
			}
			else //thirdParameterMode == 2
			{
				if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) < (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]))
				{
					commands[relativeBase + commands[j + 3]] = 1;
					if (!(j == relativeBase + commands[j + 3]))
						j = j + 4;
				}
				else
				{
					commands[relativeBase + commands[j + 3]] = 0;
					if (!(j == commands[j + 3]))
						j = j + 4;
				}
			}
			break;
		case EQUALS:
			if (thirdParameterMode == 0)
			{
				if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) == (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]))
				{
					commands[commands[j + 3]] = 1;
					if (!(j == relativeBase + commands[j + 3]))
						j = j + 4;
				}
				else
				{
					commands[commands[j + 3]] = 0;
					if (!(j == commands[j + 3]))
						j = j + 4;
				}
			}
			else //thirdParameterMode == 2
			{
				if ((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) == (secondParameterMode == 1 ? commands[j + 2] : secondParameterMode == 0 ? commands[commands[j + 2]] : commands[relativeBase + commands[j + 2]]))
				{
					commands[relativeBase + commands[j + 3]] = 1;
					if (!(j == relativeBase + commands[j + 3]))
						j = j + 4;
				}
				else
				{
					commands[relativeBase + commands[j + 3]] = 0;
					if (!(j == relativeBase + commands[j + 3]))
						j = j + 4;
				}
			}
			break;
		case ADJ_RELATIVE_BASE:
			relativeBase += (firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]);
			j = j + 2;
			break;
		default:
			std::cout << "UndefOpcode: " << command << std::endl;
			++j;
			break;
		}

		command = commands[j] % 100;
		firstParameterMode = (commands[j] % 1000) / 100;
		secondParameterMode = (commands[j] % 10000) / 1000;
		thirdParameterMode = (commands[j] % 100000) / 10000;

		if (firstParameterMode == 0 && commands[j + 1] > (commands.size() - 1))
		{
			expandMemory(&commands, commands[j + 1]);
		}
		else if (firstParameterMode == 2 && (relativeBase + commands[j + 1]) > commands.size() - 1)
		{
			expandMemory(&commands, relativeBase + commands[j + 1]);
		}
		else if (firstParameterMode == 1 && j + 1 > commands.size() - 1)
		{
			expandMemory(&commands, j + 1);
		}

		if (secondParameterMode == 0 && commands[j + 2] > (commands.size() - 1))
		{
			expandMemory(&commands, commands[j + 2]);
		}
		else if (secondParameterMode == 2 && (relativeBase + commands[j + 2]) > commands.size() - 1)
		{
			expandMemory(&commands, relativeBase + commands[j + 2]);
		}
		else if (secondParameterMode == 1 && j + 2 > commands.size() - 1)
		{
			expandMemory(&commands, j + 1);
		}

		if (thirdParameterMode == 0 && commands[j + 3] > (commands.size() - 1))
		{
			expandMemory(&commands, commands[j + 3]);
		}
		else if (thirdParameterMode == 2 && (relativeBase + commands[j + 3]) > commands.size() - 1)
		{
			expandMemory(&commands, relativeBase + commands[j + 3]);
		}
		else if (thirdParameterMode == 1 && j + 3 > commands.size() - 1)
		{
			expandMemory(&commands, j + 3);
		}
	}

	computerStop = true;
}

int main(int argc, char* argv[])
{
	std::string buffer = "";
	long long numberOfCommands = 0;

	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	while (std::getline(input, fileLine))
	{
		for (int i = 0; i < fileLine.size() + 1; ++i)
		{
			if (fileLine[i] == '-')
			{
				buffer.push_back(fileLine[i]);
			}
			else if (isdigit(fileLine[i]))
			{
				buffer.push_back(fileLine[i]);
			}
			else
			{
				commands.push_back(stoll(buffer));
				buffer = "";
				++numberOfCommands;
			}
		}
	}

	input.close();

	direction robotDirection = east;
	direction moveDirection = east;
	std::vector <std::vector <char>> area;
	std::vector <std::vector <direction>> intersections;
	Point robotPosition{};
	Point oxygenSystemPosition{};

	for (long i = 0; i < heightArea; ++i)
	{
		std::vector <char> charBuffer;
		for (long j = 0; j < widthArea; ++j)
		{
			charBuffer.push_back(EMPTY);
		}
		area.push_back(charBuffer);
	}
	for (long i = 0; i < heightArea; ++i)
	{
		std::vector <direction> directionBuffer;
		for (long j = 0; j < widthArea; ++j)
		{
			directionBuffer.push_back(null);
		}
		intersections.push_back(directionBuffer);
	}

	robotPosition.x = widthArea / 2 + 1;
	robotPosition.y = heightArea / 2 + 1;

	long toCheck = 0;

	do
	{
		if (area[robotPosition.y][robotPosition.x] == TO_CHECK)
			--toCheck;
		area[robotPosition.y][robotPosition.x] = VISITED;

		int ways = 0;

		for (int i = 0; i < 4; ++i)
		{
			robotDirection = GetDirection(i);
			Point tempPosition = MoveRobot(robotPosition, robotDirection);

			inputValue = robotDirection;

			IntCodeComputer();

			if (outputValues[0] == WALL)
			{
				Point newPosition = MoveRobot(robotPosition, robotDirection);
				area[newPosition.y][newPosition.x] = WALL;
				outputValues.clear();
			}
			else if (outputValues[0] == MOVED)
			{
				++ways;
				Point newPosition = MoveRobot(robotPosition, robotDirection);
				if (area[newPosition.y][newPosition.x] == EMPTY)
				{
					area[newPosition.y][newPosition.x] = TO_CHECK;
					++toCheck;
				}
				outputValues.clear();

				inputValue = OppositeDirection(robotDirection);
				IntCodeComputer();
				outputValues.clear();
			}
			else
			{
				Point newPosition = MoveRobot(robotPosition, robotDirection);
				area[newPosition.y][newPosition.x] = OXYGEN_SYSTEM;
				oxygenSystemPosition = newPosition;
				outputValues.clear();

				inputValue = OppositeDirection(robotDirection);
				IntCodeComputer();
				outputValues.clear();
			}
		}

		if (ways > 2)
		{
			if (intersections[robotPosition.y][robotPosition.x] == null)
				intersections[robotPosition.y][robotPosition.x] = moveDirection;
			if (area[robotPosition.y - 1][robotPosition.x] == TO_CHECK)
			{
				robotDirection = north;
			}
			else if (area[robotPosition.y + 1][robotPosition.x] == TO_CHECK)
			{
				robotDirection = south;
			}
			else if (area[robotPosition.y][robotPosition.x - 1] == TO_CHECK)
			{
				robotDirection = west;
			}
			else if (area[robotPosition.y][robotPosition.x + 1] == TO_CHECK)
			{
				robotDirection = east;
			}
			else
			{
				robotDirection = OppositeDirection(intersections[robotPosition.y][robotPosition.x]);
			}
			moveDirection = robotDirection;
		}
		else
		{
			robotDirection = moveDirection;
			Point tempPosition = MoveRobot(robotPosition, robotDirection);
			if (area[tempPosition.y][tempPosition.x] == WALL)
			{
				Point tempLeftPosition = MoveRobot(robotPosition, TurnLeft(robotDirection));
				Point tempRightPosition = MoveRobot(robotPosition, TurnRight(robotDirection));
				if (area[tempLeftPosition.y][tempLeftPosition.x] != WALL)
				{
					robotDirection = TurnLeft(robotDirection);
					moveDirection = robotDirection;
				}
				else if (area[tempRightPosition.y][tempRightPosition.x] != WALL)
				{
					robotDirection = TurnRight(robotDirection);
					moveDirection = robotDirection;
				}
				else
				{
					robotDirection = OppositeDirection(moveDirection);
					moveDirection = robotDirection;
				}
			}
			else
			{
				robotDirection = moveDirection;
			}
		}

		inputValue = robotDirection;
		IntCodeComputer();
		outputValues.clear();

		robotPosition = MoveRobot(robotPosition, robotDirection);

	} while (toCheck > 0);

	PrintArea(&area, &robotPosition, &robotDirection);

	std::vector <OxygenPath> oxygenPaths;
	std::vector <OxygenPath> oxygenPathsToAdd;

	OxygenPath system;
	system.pathDirection = north;
	system.position = oxygenSystemPosition;
	oxygenPaths.push_back(system);

	long numberOfMinutes = 0;
	direction pathDirection;

	do
	{
		for (auto j = oxygenPaths.begin(); j != oxygenPaths.end();)
		{
			j->position = MoveRobot(j->position, j->pathDirection);
			area[j->position.y][j->position.x] = OXYGEN;

			int ways = 0;

			if (area[j->position.y - 1][j->position.x] != WALL)
			{
				++ways;
			}
			if (area[j->position.y + 1][j->position.x] != WALL)
			{
				++ways;
			}
			if (area[j->position.y][j->position.x - 1] != WALL)
			{
				++ways;
			}
			if (area[j->position.y][j->position.x + 1] != WALL)
			{
				++ways;
			}

			if (ways > 2)
			{
				if (area[j->position.y - 1][j->position.x] != WALL && j->pathDirection != south)
				{
					OxygenPath temp;
					temp.position = j->position;
					temp.pathDirection = north;
					oxygenPathsToAdd.push_back(temp);
				}
				if (area[j->position.y + 1][j->position.x] != WALL && j->pathDirection != north)
				{
					OxygenPath temp;
					temp.position = j->position;
					temp.pathDirection = south;
					oxygenPathsToAdd.push_back(temp);
				}
				if (area[j->position.y][j->position.x - 1] != WALL && j->pathDirection != east)
				{
					OxygenPath temp;
					temp.position = j->position;
					temp.pathDirection = west;
					oxygenPathsToAdd.push_back(temp);
				}
				if (area[j->position.y][j->position.x + 1] != WALL && j->pathDirection != west)
				{
					OxygenPath temp;
					temp.position = j->position;
					temp.pathDirection = east;
					oxygenPathsToAdd.push_back(temp);
				}
				
				j = oxygenPaths.erase(j);
			}
			else
			{
				Point tempPosition = MoveRobot(j->position, j->pathDirection);
				if (area[tempPosition.y][tempPosition.x] == WALL)
				{
					Point tempLeftPosition = MoveRobot(j->position, TurnLeft(j->pathDirection));
					Point tempRightPosition = MoveRobot(j->position, TurnRight(j->pathDirection));
					if (area[tempLeftPosition.y][tempLeftPosition.x] != WALL)
					{
						j->pathDirection = TurnLeft(j->pathDirection);
						++j;
					}
					else if (area[tempRightPosition.y][tempRightPosition.x] != WALL)
					{
						j->pathDirection = TurnRight(j->pathDirection);
						++j;
					}
					else
					{
						j = oxygenPaths.erase(j);
					}
				}
				else 
				{
					++j;
				}
			}
		}

		for (size_t i = 0; i < oxygenPathsToAdd.size(); ++i)
		{
			oxygenPaths.push_back(oxygenPathsToAdd[i]);
		}
		oxygenPathsToAdd.clear();

		if (oxygenPaths.size() >= 0)
			++numberOfMinutes;

		PrintArea(&area, &robotPosition, &robotDirection);

	} while (oxygenPaths.size() > 0);

	//PrintArea(&area, &robotPosition, &robotDirection);

	std::cout << "Start position: " << widthArea / 2 + 1 << ":" << heightArea / 2 + 1 << std::endl;
	std::cout << "Oxygen system position: " << oxygenSystemPosition.x << ":" << oxygenSystemPosition.y << std::endl;
	std::cout << "Number of minutes: " << numberOfMinutes << std::endl;
}