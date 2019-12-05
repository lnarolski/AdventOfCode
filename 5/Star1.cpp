#define ADD_COMM 1
#define MUL_COMM 2
#define INPUT_COMM 3
#define OUTPUT_COMM 4
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
    int inputValue = 1;
    int outputValue = 0;

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
            j = j + 4;
            break;
        case MUL_COMM:
            commands[commands[j + 3]] = (firstParameterMode ? commands[j + 1] : commands[commands[j + 1]]) * (secondParameterMode ? commands[j + 2] : commands[commands[j + 2]]);
            j = j + 4;
            break;
        case INPUT_COMM:
            commands[commands[j + 1]] = inputValue;
            j = j + 2;
            break;
        case OUTPUT_COMM:
            outputValue = commands[commands[j + 1]];
            cout << "Output: " << outputValue << endl;
            j = j + 2;
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
