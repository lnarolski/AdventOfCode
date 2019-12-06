#include <iostream>
#include <map>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

//int numberOfOrbits(string orbit, map <string, string> objects)
//{
//    int orbits = 1;
//    if (orbit == "COM")
//        return orbits;
//    orbits += numberOfOrbits(objects[orbit], objects);
//
//    return orbits;
//}

int main(int argc, char *argv[])
{
    string buffer = "";

    map <string, string> objects;

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    while (getline(input, fileLine))
    {
        string object = "", orbit = "";
        for (int i = 0; i < fileLine.size() + 1; ++i)
        {
            if (isalpha(fileLine[i]) || isdigit(fileLine[i]))
            {
                buffer.push_back(fileLine[i]);
            }
            else
            {
                if (orbit == "")
                {
                    orbit = buffer;
                    buffer = "";
                }
                else
                {
                    object = buffer;
                    objects[object] = orbit;
                }

                buffer = "";
            }
        }
    }

    input.close();

    long orbits = 0;
    long objectNumber = 1;

    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        cout << "Object " << it->first << " " << objectNumber << "/" << objects.size() << endl;
        string orbit = it->second;
        ++orbits;
        while (orbit != "COM")
        {
            orbit = objects[orbit];
            ++orbits;
        }
        ++objectNumber;
    }

    cout << endl << "Number of orbits: " << orbits << endl;
}
