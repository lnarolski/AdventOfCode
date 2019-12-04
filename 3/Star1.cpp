#define FIRST_WIRE 1
#define SECOND_WIRE 2
#define NOT_WIRE 0

#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>
#include <climits>

using namespace std;

enum moveType
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

long calculateManhattanDistance(long x1, long y1, long x2, long y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

int main(int argc, char *argv[])
{
    string buffer = "";

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    char **grid;

    long minX[3] = {0, 0, 0}, minY[3] = {0, 0, 0}, maxX[3] = {0, 0, 0}, maxY[3] = {0, 0, 0}, posX, posY;
    moveType moveT;

    int lineNumber = 0;

    while (getline(input, fileLine))
    {
        posX = 0;
        posY = 0;

        for (int i = 0; i < fileLine.size() + 1; ++i)
        {
            if (isalpha(fileLine[i]))
            {
                switch (fileLine[i])
                {
                case 'U':
                    moveT = UP;
                    break;
                case 'D':
                    moveT = DOWN;
                    break;
                case 'R':
                    moveT = RIGHT;
                    break;
                case 'L':
                    moveT = LEFT;
                    break;
                default:
                    break;
                }
            }
            else if (isdigit(fileLine[i]))
            {
                buffer.push_back(fileLine[i]);
            }
            else
            {
                switch (moveT)
                {
                case UP:
                    posY += stoi(buffer);
                    break;
                case DOWN:
                    posY -= stoi(buffer);
                    break;
                case RIGHT:
                    posX += stoi(buffer);
                    break;
                case LEFT:
                    posX -= stoi(buffer);
                    break;
                default:
                    break;
                }

                buffer = "";

                if (posX < minX[lineNumber])
                {
                    minX[lineNumber] = posX;
                }
                else if (posX > maxX[lineNumber])
                {
                    maxX[lineNumber] = posX;
                }
                else if (posY < minY[lineNumber])
                {
                    minY[lineNumber] = posY;
                }
                else if (posY > maxY[lineNumber])
                {
                    maxY[lineNumber] = posY;
                }
            }
        }
        ++lineNumber;
    }

    input.close();

    minX[2] = minX[0] < minX[1] ? minX[0] : minX[1];
    minY[2] = minY[0] < minY[1] ? minY[0] : minY[1];
    maxX[2] = maxX[0] > maxX[1] ? maxX[0] : maxX[1];
    maxY[2] = maxY[0] > maxY[1] ? maxY[0] : maxY[1];

    long yBIAS = abs(minY[2]);
    long xBIAS = abs(minX[2]);

    long widthGrid = abs(minX[2]) + maxX[2];
    long heightGrid = abs(minY[2]) + maxY[2];

    long startX = xBIAS;
    long startY = yBIAS;

    long minimumDistance = LONG_MAX;

    grid = new char*[widthGrid + 1];
    for (int i = 0; i < widthGrid + 1; ++i)
    {
        grid[i] = new char[heightGrid + 1];
    }

    for (int i = 0; i < widthGrid + 1; ++i)
    {
        for (int j = 0; j < heightGrid + 1; ++j)
        {
            grid[i][j] = NOT_WIRE;
        }
    }

    lineNumber = 0;
    input.open("input.txt", fstream::in);
    while (getline(input, fileLine))
    {
        posX = startX;
        posY = startY;

        for (int i = 0; i < fileLine.size() + 1; ++i)
        {
            if (isalpha(fileLine[i]))
            {
                switch (fileLine[i])
                {
                case 'U':
                    moveT = UP;
                    break;
                case 'D':
                    moveT = DOWN;
                    break;
                case 'R':
                    moveT = RIGHT;
                    break;
                case 'L':
                    moveT = LEFT;
                    break;
                default:
                    break;
                }
            }
            else if (isdigit(fileLine[i]))
            {
                buffer.push_back(fileLine[i]);
            }
            else
            {
                int bufferINT = stoi(buffer);
                switch (moveT)
                {
                case UP:
                    for (int k = 0; k < stoi(buffer); ++k)
                    {
                        posY += 1;
                        if (grid[posX][posY] == FIRST_WIRE && lineNumber == 1)
                        {
                            long distance = calculateManhattanDistance(startX, startY, posX, posY);
                            if (distance < minimumDistance)
                                minimumDistance = distance;
                        }
                        else
                        {
                            if (lineNumber == 0)
                            {
                                grid[posX][posY] = FIRST_WIRE;
                            }
                            else
                            {
                                grid[posX][posY] = SECOND_WIRE;
                            }
                        }
                    }
                    break;
                case DOWN:
                    for (int k = 0; k < stoi(buffer); ++k)
                    {
                        posY -= 1;
                        if (grid[posX][posY] == FIRST_WIRE && lineNumber == 1)
                        {
                            long distance = calculateManhattanDistance(startX, startY, posX, posY);
                            if (distance < minimumDistance)
                                minimumDistance = distance;
                        }
                        else
                        {
                            if (lineNumber == 0)
                            {
                                grid[posX][posY] = FIRST_WIRE;
                            }
                            else
                            {
                                grid[posX][posY] = SECOND_WIRE;
                            }
                        }
                    }
                    break;
                case RIGHT:
                    for (int k = 0; k < bufferINT; ++k)
                    {
                        posX += 1;
                        if (grid[posX][posY] == FIRST_WIRE && lineNumber == 1)
                        {
                            long distance = calculateManhattanDistance(startX, startY, posX, posY);
                            if (distance < minimumDistance)
                                minimumDistance = distance;
                        }
                        else
                        {
                            if (lineNumber == 0)
                            {
                                grid[posX][posY] = FIRST_WIRE;
                            }
                            else
                            {
                                grid[posX][posY] = SECOND_WIRE;
                            }
                        }
                    }
                    break;
                case LEFT:
                    bufferINT = stoi(buffer);
                    for (int k = 0; k < bufferINT; ++k)
                    {
                        posX -= 1;
                        if (grid[posX][posY] == FIRST_WIRE && lineNumber == 1)
                        {
                            long distance = calculateManhattanDistance(startX, startY, posX, posY);
                            if (distance < minimumDistance)
                                minimumDistance = distance;
                        }
                        else
                        {
                            if (lineNumber == 0)
                            {
                                grid[posX][posY] = FIRST_WIRE;
                            }
                            else
                            {
                                grid[posX][posY] = SECOND_WIRE;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }

                buffer = "";
            }
        }
        ++lineNumber;
    }

    input.close();

    cout << "Minimum distance: " << minimumDistance << endl;

}
