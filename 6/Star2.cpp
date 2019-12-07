#include <iostream>
#include <map>
#include <list>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

long SANfound = LONG_MAX;
map <string, list <string>> objects;
list <string> visitedNodes;

void VisitNode(string node, long orbitalNodes)
{
    visitedNodes.push_back(node);
    ++orbitalNodes;
    for (auto it = objects[node].begin(); it != objects[node].end(); ++it)
    {
        if (*it == "SAN")
        {
            ++orbitalNodes;
            if (orbitalNodes < SANfound)
            {
                SANfound = orbitalNodes;
            }
        }
        else if (find(visitedNodes.begin(), visitedNodes.end(), *it) == visitedNodes.end())
        {
            VisitNode(*it, orbitalNodes);
        }
    }
    return;
}

void DepthFirstSearch()
{
    long orbitalTransfers = 0;

    visitedNodes.push_back("COM");
    visitedNodes.push_back("YOU");

    for (auto it = objects["YOU"].begin(); it != objects["YOU"].end(); ++it)
    {
        if (find(visitedNodes.begin(), visitedNodes.end(), *it) == visitedNodes.end())
        {
            VisitNode(*it, orbitalTransfers);
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    string buffer = "";

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    while (getline(input, fileLine))
    {
        string object = "";
        string connection = "";
        for (int i = 0; i < fileLine.size() + 1; ++i)
        {
            if (isalnum(fileLine[i]))
            {
                buffer.push_back(fileLine[i]);
            }
            else
            {
                if (connection == "")
                {
                    connection = buffer;
                    buffer = "";
                }
                else
                {
                    object = buffer;
                    std::map<string, list <string>>::iterator it;

                    if ((it = objects.find(connection)) != objects.end())
                        it->second.push_back(object);
                    else
                        objects[connection].push_back(object);

                    if ((it = objects.find(object)) != objects.end())
                        it->second.push_back(connection);
                    else
                        objects[object].push_back(connection);
                }

                buffer = "";
            }
        }
    }

    input.close();

    DepthFirstSearch();

//    for (auto it = objects.begin(); it != objects.end(); ++it)
//    {
//        cout << "Object: " << it->first << endl;
//        cout << "Connections: ";
//        for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
//        {
//            cout << *itt << " ";
//        }
//        cout << endl;
//    }

    cout << "Number of orbital transfers: " << SANfound - 2 << endl;
}
