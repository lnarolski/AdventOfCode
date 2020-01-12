#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <random>
#include <conio.h>
#include <thread>         // std::thread
#include <Windows.h>

const size_t numOfComputers = 50;

class IntCodeComputer
{
public:
	IntCodeComputer(std::vector <long long> commands)
	{
		this->commands = commands;
	};
	~IntCodeComputer();

	std::vector <long long> inputValues;
	std::vector <long long> outputValues;

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

	bool ExternalModInput = false;
	bool ExternalModOutput = false;
	bool InternalModInput = false;
	bool InternalModOutput = false;

	bool idle = false;

	bool stop = false;
	bool stopped = true;
	std::thread* thread;

	void Run()
	{
		stopped = false;

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

		while (command != END_COMM && !stop)
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
				while (ExternalModInput || ExternalModOutput) {}
				InternalModInput = true;
				InternalModOutput = true;
				if (inputValues.size() == 0)
				{
					if (outputValues.size() == 0)
						idle = true;
					(firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) = -1;
				}
				else {
					idle = false;
					(firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]) = inputValues[0];
					inputValues.erase(inputValues.begin());
				}
				InternalModInput = false;
				InternalModOutput = false;
				if (!(j == commands[j + 3]))
					j = j + 2;
				break;
			case OUTPUT_COMM:
				InternalModOutput = true;
				outputValues.push_back((firstParameterMode == 1 ? commands[j + 1] : firstParameterMode == 0 ? commands[commands[j + 1]] : commands[relativeBase + commands[j + 1]]));
				++outputI;
				if (outputI >= 3) {
					InternalModOutput = false;
					outputI = 0;
				}
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

		stopped = true;
	}
	void RunAsThread()
	{
		thread = new std::thread(&IntCodeComputer::Run, this);
	}

private:

	long j = 0;
	long relativeBase = 0;
	size_t outputI = 0;

	std::vector <long long> commands;

	void expandMemory(std::vector <long long>* commands, long j)
	{
		long long size = commands->size();
		for (long long i = 0; i < j - size + 1; ++i)
		{
			commands->push_back(0);
		}
	}
};

std::vector <IntCodeComputer*> computers;

std::vector <long long> NATBufferX;
std::vector <long long> NATBufferY;

bool stop = false;

bool InternalNATBufferLock = false;
bool ExternalNATBufferLock = false;

bool NATNewPacket = false;
bool NATFirstPacket = false;

bool NATstopped = true;

void RunNAT()
{
	NATstopped = false;

	bool stopNAT = false;
	long long NATSended[2] = { 0, 0 };
	long long NATSendedPrev[2] = { 1, 1 };

	while (!stopNAT)
	{
		if (NATSendedPrev[0] == NATSended[0] && NATSendedPrev[1] == NATSended[1])
		{
			while (ExternalNATBufferLock) {}
			InternalNATBufferLock = true;

			std::cout << "outputY: " << NATSended[1] << std::endl;
			InternalNATBufferLock = false;

			stopNAT = true;
		}
		else if (NATFirstPacket)
		{
			bool allIdle = true;
			for (size_t i = 0; i < computers.size() && allIdle; ++i)
			{
				if (!computers[i]->idle)
					allIdle = false;
			}
			if (allIdle)
			{
				while (computers[0]->InternalModOutput) {}
				computers[0]->ExternalModInput = true;
				while (ExternalNATBufferLock) {}
				InternalNATBufferLock = true;

				if (NATNewPacket)
				{
					NATSendedPrev[0] = NATSended[0];
					NATSendedPrev[1] = NATSended[1];

					NATSended[0] = NATBufferX.at(NATBufferX.size() - 1);
					NATSended[1] = NATBufferY.at(NATBufferY.size() - 1);

					NATNewPacket = false;
				}

				computers[0]->inputValues.push_back(NATSended[0]);
				computers[0]->inputValues.push_back(NATSended[1]);

				InternalNATBufferLock = false;
				computers[0]->ExternalModInput = false;
			}
		}
	}

	stop = true;
	NATstopped = true;
}

int main(int argc, char* argv[])
{
	std::vector <long long> commands;

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

	for (size_t i = 0; i < numOfComputers; ++i)
	{
		computers.push_back(new IntCodeComputer(commands));
		computers[i]->inputValues.push_back(i);

		computers[i]->RunAsThread();
	}

	Sleep(1000);
	std::thread NATThread(RunNAT);

	while (!stop)
	{
		for (size_t i = 0; i < numOfComputers; ++i)
		{
			if (!computers[i]->InternalModOutput)
			{
				computers[i]->ExternalModOutput = true;
				if (computers[i]->outputValues.size() >= 3)
				{
					if (computers[i]->outputValues[0] == 255)
					{
						while (InternalNATBufferLock) {};
						ExternalNATBufferLock = true;

						NATBufferX.push_back(computers[i]->outputValues[1]);
						NATBufferY.push_back(computers[i]->outputValues[2]);

						computers[i]->outputValues.erase(computers[i]->outputValues.begin());
						computers[i]->outputValues.erase(computers[i]->outputValues.begin());
						computers[i]->outputValues.erase(computers[i]->outputValues.begin());

						NATNewPacket = true;
						NATFirstPacket = true;

						ExternalNATBufferLock = false;
					}
					else
					{
						if (computers[i]->outputValues.size() >= 3)
						{
							computers[i]->ExternalModOutput = false;

							while (computers[i]->InternalModOutput) {}
							computers[i]->ExternalModOutput = true;

							Sleep(10);
							while (computers[computers[i]->outputValues[0]]->InternalModInput) {}
							computers[computers[i]->outputValues[0]]->ExternalModInput = true;

							computers[computers[i]->outputValues[0]]->inputValues.push_back(computers[i]->outputValues[1]);
							computers[computers[i]->outputValues[0]]->inputValues.push_back(computers[i]->outputValues[2]);

							computers[computers[i]->outputValues[0]]->ExternalModInput = false;

							computers[i]->outputValues.erase(computers[i]->outputValues.begin());
							computers[i]->outputValues.erase(computers[i]->outputValues.begin());
							computers[i]->outputValues.erase(computers[i]->outputValues.begin());
							computers[i]->ExternalModOutput = false;
						}
					}
				}
				computers[i]->ExternalModOutput = false;
			}
		}
	}

	for (size_t i = 0; i < computers.size(); i++)
	{
		computers[i]->stop = true;
	}

	for (size_t i = 0; i < computers.size(); i++)
	{
		computers[i]->thread->join();
	}

	NATThread.join();
}