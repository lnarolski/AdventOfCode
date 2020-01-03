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

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <random>
#include <conio.h>

void expandMemory(std::vector <long long>* commands, long j)
{
	long long size = commands->size();
	for (long long i = 0; i < j - size + 1; ++i)
	{
		commands->push_back(0);
	}
}

std::vector <long long> commands;
std::vector <unsigned int> inputValue;
size_t inputIndex;
std::vector <long long> outputValues;
bool computerStop = false;

void IntCodeComputer(std::vector <long long> commands)
{
	long j = 0;
	long relativeBase = 0;

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
			(firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) = inputValue[inputIndex];
			++inputIndex;
			if (!(j == commands[j + 3]))
				j = j + 2;
			break;
		case OUTPUT_COMM:
			outputValues.push_back((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]));
			j = j + 2;
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

	unsigned long pointsAffected = 0;
	for (unsigned int y = 0; y < 50; ++y)
	{
		for (unsigned int x = 0; x < 50; ++x)
		{
			inputValue.clear();
			inputIndex = 0;

			inputValue.push_back(x);
			inputValue.push_back(y);

			while (!computerStop)
			{
				IntCodeComputer(commands);
			}
			computerStop = false;

			if (outputValues[0] == 1)
			{
				printf("#");
				++pointsAffected;
			}
			else
			{
				printf(".");
			}

			outputValues.clear();
		}
		printf("\n");
	}

	std::cout << "Points affected: " << pointsAffected << std::endl;
}