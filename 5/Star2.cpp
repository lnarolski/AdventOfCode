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

using namespace std;

int main(int argc, char *argv[])
{
    string buffer = "";
    int inputValue = 5;
    int outputValue = 0;
    int numberOfCommands = 0;

    vector <long> commands;

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

    int j = 0;

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
            commands[commands[j + 1]] = inputValue;
            if (!(j == commands[j + 3]))
                j = j + 2;
            break;
        case OUTPUT_COMM:
            outputValue = commands[commands[j + 1]];
            cout << "Output: " << outputValue << endl;
            j = j + 2;
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
}
