#define ADD_COMM 1
#define MUL_COMM 2
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

//    cout << strlen(argv[1]) << endl << endl;
//    cout << argv[1] << endl;

    if (argc == 1)
    {
        vector <long> commands;

        fstream input;
        string fileLine;
        input.open("input.txt", fstream::in);

        while (getline(input, fileLine))
        {
            for (int i = 0; i < fileLine.size() + 1; ++i)
            {
                if (isdigit(fileLine[i]))
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

        commands[1] = 12;
        commands[2] = 2;

        int j = 0;
        while (commands[j] != END_COMM)
        {
            switch (commands[j])
            {
            case ADD_COMM:
                commands[commands[j + 3]] = commands[commands[j + 1]] + commands[commands[j + 2]];
                j = j + 4;
                break;
            case MUL_COMM:
                commands[commands[j + 3]] = commands[commands[j + 1]] * commands[commands[j + 2]];
                j = j + 4;
                break;
            default:
                ++j;
                break;
            }
        }

        cout << commands[0] << endl;
    }
    else
    {
        vector <long> commands;

        for (int i = 0; i < strlen(argv[1]) + 1; ++i)
        {
            if (isdigit(argv[1][i]))
            {
                buffer.push_back(argv[1][i]);
            }
            else
            {
                commands.push_back(stoi(buffer));
                buffer = "";
            }
        }

        int j = 0;
        while (commands[j] != END_COMM)
        {
            switch (commands[j])
            {
            case ADD_COMM:
                commands[commands[j + 3]] = commands[commands[j + 1]] + commands[commands[j + 2]];
                j = j + 4;
                break;
            case MUL_COMM:
                commands[commands[j + 3]] = commands[commands[j + 1]] * commands[commands[j + 2]];
                j = j + 4;
                break;
            default:
                ++j;
                break;
            }
        }

        for (int i = 0; i < commands.size(); ++i)
        {
            cout << commands[i] << ",";
        }
    }
}
