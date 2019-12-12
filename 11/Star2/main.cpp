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

#define TURN_LEFT 0
#define TURN_RIGHT 1

#define BLACK_PANEL 0
#define WHITE_PANEL 1

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

enum direction
{
	up,
	right,
	down,
	left
};

struct Point
{
	long x;
	long y;
};

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

	direction robotDirection = up;
	std::vector <std::vector <char>> area;
	std::vector <std::vector <bool>> paintedOnce;
	Point robotPosition{};

	const int widthArea = 100;
	const int heightArea = 100;

	for (long i = 0; i < heightArea; ++i)
	{
		std::vector <char> charBuffer;
		std::vector <bool> boolBuffer;
		for (long j = 0; j < widthArea; ++j)
		{
			charBuffer.push_back(BLACK_PANEL);
			boolBuffer.push_back(false);
		}
		area.push_back(charBuffer);
		paintedOnce.push_back(boolBuffer);
	}

	robotPosition.x = widthArea / 2 + 1;
	robotPosition.y = heightArea / 2 + 1;

	area[robotPosition.y][robotPosition.x] = WHITE_PANEL;

	while (!computerStop)
	{
		inputValue = area[robotPosition.y][robotPosition.x];

		IntCodeComputer();

		if (computerStop)
			break;

		if (outputValues[0] != area[robotPosition.y][robotPosition.x])
		{
			area[robotPosition.y][robotPosition.x] = outputValues[0];
			paintedOnce[robotPosition.y][robotPosition.x] = true;
		}

		if (outputValues[1] == TURN_LEFT)
		{
			switch (robotDirection)
			{
			case up:
				robotDirection = left;
				break;
			case right:
				robotDirection = up;
				break;
			case down:
				robotDirection = right;
				break;
			case left:
				robotDirection = down;
				break;
			}
		}
		else //TURN_RIGHT
		{
			switch (robotDirection)
			{
			case up:
				robotDirection = right;
				break;
			case right:
				robotDirection = down;
				break;
			case down:
				robotDirection = left;
				break;
			case left:
				robotDirection = up;
				break;
			}
		}
	
		switch (robotDirection)
		{
		case up:
			--robotPosition.y;
			break;
		case right:
			++robotPosition.x;
			break;
		case down:
			++robotPosition.y;
			break;
		case left:
			--robotPosition.x;
			break;
		}

		outputValues.clear();
	}

	long countOfPaintedOnce = 0;
	for (long y = 0; y < heightArea; ++y)
	{
		for (long x = 0; x < widthArea; ++x)
		{
			if (area[y][x] == WHITE_PANEL)
				printf("%c", 178);
			else
				printf("%c", 0);
		}
		std::cout << std::endl;
	}
}