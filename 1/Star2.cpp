#define WRONG_MASS_VALUE "Set in argument correct mass value."

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

long CalculateFuel(long mass)
{
    long calculatedFuel = ((int) ( (double) mass / 3.0)) - 2;
    if (calculatedFuel <= 0)
        return 0;
    else
        return calculatedFuel + CalculateFuel(calculatedFuel);
}

int main(int argc, char *argv[])
{
    int mass = 0;
    long fuel = 0;

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
                fuel += CalculateFuel(mass);
            }

            input.close();
            cout << fuel;
        }
        else
        {
            mass = stoi(argv[1]);
            fuel += CalculateFuel(mass);
            cout << fuel;
        }
    }
    catch(const std::exception& e)
    {
        cout << WRONG_MASS_VALUE << endl;
    }
}
