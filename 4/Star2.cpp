#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>
#include <climits>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

long getNumberOfPasswordCombinations(int minimum, int maximum)
{
    long numberOfPasswordCombinations = 0;

    string passwString;
    stringstream strstream;

    for (long i = 0; i < maximum - minimum + 1; ++i)
    {
        bool neverDecrease = true;
        bool doubleNumber = false;

        passwString = to_string(minimum + i);

        for (int j = 0; j < 6 - 1; ++j)
        {
            if (passwString[j + 1] < passwString[j])
            {
                neverDecrease = false;
                break;
            }
        }
        if (!neverDecrease)
            continue;

        int matchingDigits[10] = {0};
        for (int j = 0; j < 6; ++j)
        {
            char digit = passwString.at(j);
            ++matchingDigits[atoi(&digit)];
        }
        for (int j = 0; j < 10; ++j)
        {
            if (matchingDigits[j] == 2)
            {
                doubleNumber = true;
                break;
            }
        }
        if (!doubleNumber)
            continue;

        ++numberOfPasswordCombinations;
    }

    return numberOfPasswordCombinations;
}

int main(int argc, char *argv[])
{
    int minimum, maximum, lineNumber = 0;

    string buffer = "";

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    // Get input
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
                if (lineNumber == 0)
                    minimum = stoi(buffer);
                else
                    maximum = stoi(buffer);
            }
        }
        ++lineNumber;
        buffer = "";
    }

    input.close();

    cout << "Number of combinations: " << getNumberOfPasswordCombinations(minimum, maximum) << endl;
}
