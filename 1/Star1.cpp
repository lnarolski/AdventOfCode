#define WRONG_MASS_VALUE "Set in argument correct mass value."

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    long fuel = 0;
    int mass = 0;

    try
    {
        if (argc == 1)
        {
            fstream input;
            string fileLine;
            input.open("input.txt", fstream::in);

            while (getline(input, fileLine))
            {
                mass = stoi(fileLine.c_str());
                fuel += ((int) ( (double) mass / 3.0)) - 2;
            }

            input.close();
            cout << fuel;
        }
        else
        {
            mass = stoi(argv[1]);
            fuel += ((int) ( (double) mass / 3.0)) - 2;
            cout << fuel;
        }
    }
    catch(const std::exception& e)
    {
        cout << WRONG_MASS_VALUE << endl;
    }
}
