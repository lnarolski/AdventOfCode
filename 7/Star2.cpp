#define ADD_COMM 1
#define MUL_COMM 2
#define INPUT_COMM 3
#define OUTPUT_COMM 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUALS 8
#define END_COMM 99

#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

bool endComm = false;
vector <long> commands;
vector <vector <long>> amplifiersCommands;
int amplifiersPointers[5] = {0};
int amplifiersFirstInput[5] = {true};

long IntCodeComputer(vector <long> commands, int input, int phase, int amplifier)
{
    int outputValue = 0;
    int inputValue = 0;

    int j = amplifiersPointers[amplifier];

    int command = commands[j] % 100;
    int firstParameterMode = (commands[j] % 1000) >= 100;
    int secondParameterMode = (commands[j] % 10000) >= 1000;
    int thirdParameterMode = (commands[j] % 100000) >= 10000;

    while (command != END_COMM)
    {
        switch (command)
        {
        case ADD_COMM:
            commands[commands[j + 3]] = (firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) + (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]);
            if (!(j == commands[j + 3]))
                j = j + 4;
            break;
        case MUL_COMM:
            commands[commands[j + 3]] = (firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) * (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]);
            if (!(j == commands[j + 3]))
                j = j + 4;
            break;
        case INPUT_COMM:
            if (amplifiersFirstInput[amplifier])
                inputValue = phase;
            else
                inputValue = input;
            commands[commands[j + 1]] = inputValue;
            if (!(j == commands[j + 3]))
                j = j + 2;
            amplifiersFirstInput[amplifier] = false;
            break;
        case OUTPUT_COMM:
            outputValue = commands[commands[j + 1]];
//            cout << "Output: " << outputValue << endl;
            j = j + 2;
            amplifiersPointers[amplifier] = j;
            return outputValue;
            break;
        case JUMP_IF_TRUE:
            if ((firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) != 0)
            {
                j = (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]);
            }
            else
                j = j + 3;
            break;
        case JUMP_IF_FALSE:
            if ((firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) == 0)
            {
                j = (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]);
            }
            else
                j = j + 3;
            break;
        case LESS_THAN:
            if ((firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) < (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]))
            {
                if (!thirdParameterMode)
                {
                    commands[commands[j + 3]] = 1;
                    if (!(j == commands[j + 3]))
                        j = j + 4;
                }
                else
                {
                    commands[j + 3] = 1;
                    j = j + 4;
                }
            }
            else
            {
                if (!thirdParameterMode)
                {
                    commands[commands[j + 3]] = 0;
                    if (!(j == commands[j + 3]))
                        j = j + 4;
                }
                else
                {
                    commands[j + 3] = 0;
                    j = j + 4;
                }
            }
            break;
        case EQUALS:
            if ((firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) == (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]))
            {
                if (!thirdParameterMode)
                {
                    commands[commands[j + 3]] = 1;
                    if (!(j == commands[j + 3]))
                        j = j + 4;
                }
                else
                {
                    commands[j + 3] = 1;
                    j = j + 4;
                }
            }
            else
            {
                if (!thirdParameterMode)
                {
                    commands[commands[j + 3]] = 0;
                    if (!(j == commands[j + 3]))
                        j = j + 4;
                }
                else
                {
                    commands[j + 3] = 0;
                    j = j + 4;
                }
            }
            break;
        default:
            cout << "UndefOpcode: " << command << endl;
            ++j;
            break;
        }

        command = commands[j] % 100;
        firstParameterMode = (commands[j] % 1000) >= 100;
        secondParameterMode = (commands[j] % 10000) >= 1000;
        thirdParameterMode = (commands[j] % 100000) >= 10000;
    }

//    if (amplifier == 4)
//    {
    endComm = true;
//    }

    return outputValue;
}

int main(int argc, char *argv[])
{
    string buffer = "";
    int numberOfCommands = 0;

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    while (getline(input, fileLine))
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
                commands.push_back(stoi(buffer));
                buffer = "";
                ++numberOfCommands;
            }
        }
    }

    input.close();

    long maximumOutput = LONG_MIN;
    int phaseSettingSequence[] = {5,6,7,8,9};
    int amplifiers[] = {0,1,2,3,4};

    do
    {
        amplifiersCommands.clear();
        for (int i = 0; i < ((sizeof phaseSettingSequence) / (sizeof *phaseSettingSequence)); ++i)
        {
            amplifiersCommands.push_back(commands);

            amplifiersFirstInput[i] = true;
            amplifiersPointers[i] = 0;
        }

        long inputValue = 0;

        endComm = false;

        while (!endComm)
        {
            for (int i = 0; i < ((sizeof phaseSettingSequence) / (sizeof *phaseSettingSequence)); ++i)
            {
                inputValue = IntCodeComputer(amplifiersCommands[i], inputValue, phaseSettingSequence[i], amplifiers[i]);

                if (inputValue > maximumOutput)
                {
                    maximumOutput = inputValue;
                }
            }
        }
    }
    while(next_permutation(phaseSettingSequence, phaseSettingSequence + ((sizeof phaseSettingSequence) / (sizeof *phaseSettingSequence))));

    cout << "Maximum output: " << maximumOutput << endl;
}
