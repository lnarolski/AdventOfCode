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
#define EMPTY -1

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

enum direction
{
	north = 1,
	east = 4,
	south = 2,
	west = 3
};

struct Point
{
	long x;
	long y;
};

direction TurnRight(direction robotDirection)
{
	switch (robotDirection)
	{
	case north:
		robotDirection = east;
		break;
	case east:
		robotDirection = south;
		break;
	case south:
		robotDirection = west;
		break;
	case west:
		robotDirection = north;
		break;
	}

	return robotDirection;
}

direction TurnLeft(direction robotDirection)
{
	switch (robotDirection)
	{
	case north:
		robotDirection = west;
		break;
	case east:
		robotDirection = north;
		break;
	case south:
		robotDirection = east;
		break;
	case west:
		robotDirection = south;
		break;
	}

	return robotDirection;
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

void PrintArea(std::vector <std::vector <char>> *area)
{
	system("cls");
	for (long y = 0; y < area->size(); ++y)
	{
		for (long x = 0; x < area->at(0).size(); ++x)
		{
			switch (area->at(y)[x])
			{
			case VISITED:
				printf("%c", '*');
				break;
			case WALL:
				printf("%c", 178);
				break;
			case OXYGEN_SYSTEM:
				printf("%c", 'X');
				break;
			case EMPTY:
				printf("%c", 0);
				break;
			default:
				break;
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
			if (outputValues.size() == 2)
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

	direction robotDirection = north;
	std::vector <std::vector <char>> area;
	Point robotPosition{};
	Point oxygenSystemPosition{};

	const int widthArea = 50;
	const int heightArea = 50;

	for (long i = 0; i < heightArea; ++i)
	{
		std::vector <char> charBuffer;
		for (long j = 0; j < widthArea; ++j)
		{
			charBuffer.push_back(EMPTY);
		}
		area.push_back(charBuffer);
	}

	robotPosition.x = widthArea / 2 + 1;
	robotPosition.y = heightArea / 2 + 1;

	area[robotPosition.y][robotPosition.x] = VISITED;

	while (!computerStop)
	{
		inputValue = robotDirection;

		IntCodeComputer();

		//if (outputValues.size() > 0)
		//{
		if (outputValues[0] == WALL)
		{
			Point newPosition = MoveRobot(robotPosition, robotDirection);
			area[newPosition.y][newPosition.x] = WALL;
			robotDirection = TurnLeft(robotDirection);
		}
		else if (outputValues[0] == MOVED)
		{
			Point newPosition = MoveRobot(robotPosition, robotDirection);
			if (area[newPosition.y][newPosition.x] == VISITED)
			{
				direction newDirectionLeft = TurnLeft(robotDirection);
				direction newDirectionRight = TurnRight(robotDirection);
				Point testPointLeft = MoveRobot(newPosition, newDirectionLeft);
				Point testPointRight = MoveRobot(newPosition, newDirectionRight);
				if (area[testPointRight.y][testPointRight.x] != VISITED && area[testPointRight.y][testPointRight.x] != WALL)
				{
					robotDirection = newDirectionRight;
					robotPosition = newPosition;

					area[robotPosition.y][robotPosition.x] = VISITED;
				}
				else if (area[testPointLeft.y][testPointLeft.x] != VISITED && area[testPointLeft.y][testPointLeft.x] != WALL)
				{
					robotDirection = newDirectionLeft;
					robotPosition = newPosition;

					area[robotPosition.y][robotPosition.x] = VISITED;
				}
				else
				{
					robotPosition = newPosition;

					area[robotPosition.y][robotPosition.x] = VISITED;
				}
			}
			else
			{
				robotPosition = newPosition;

				area[robotPosition.y][robotPosition.x] = VISITED;
			}
		}
		else
		{
			Point newPosition = MoveRobot(robotPosition, robotDirection);
			area[newPosition.y][newPosition.x] = OXYGEN_SYSTEM;
			oxygenSystemPosition = newPosition;
		}
		//}

		if (computerStop)
			break;

		outputValues.clear();

		PrintArea(&area);
	}

	std::cout << "Oxygen system position: " << oxygenSystemPosition.x << ":" << oxygenSystemPosition.y << std::endl;
}