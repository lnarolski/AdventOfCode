#define EMPTY '.'
#define ASTEROID '#'

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>
#include <map>

using namespace std;

struct Point
{
	int xPoint;
	int yPoint;
};

bool IsOnasteroidsMap(int x, int y, vector <vector <char>> asteroidsMap)
{
	if (x < 0 || y < 0 || x > asteroidsMap[0].size() - 1 || y > asteroidsMap.size() - 1)
		return false;
	return true;
}

int CheckQuarter(int x1, int y1, int x, int y)
{
	if (x1 >= x && y1 <= y)
		return 1;
	if (x1 < x && y1 < y)
		return 2;
	if (x1 <= x && y1 >= y)
		return 3;
	if (x1 > x&& y1 > y)
		return 4;
}

bool VectorContains(double angle, vector <double> angles)
{
	for (size_t i = 0; i < angles.size(); ++i)
	{
		if (angle == angles[i])
			return true;
	}
	return false;
}

double CorrectAngle(double angle)
{
	angle = 360.0 - angle + 90.0;

	while (angle >= 360.0)
		angle -= 360.0;
	while (angle < 0.0)
		angle += 360.0;

	return angle;
}

int main(int argc, char* argv[])
{
	long width = -1;
	long height = -1;

	int numberOfAsteroidsInFile = 0;

	vector <vector <char>> asteroidsMap;

	fstream input;
	string fileLine;
	input.open("input.txt", fstream::in);

	int y = 0;
	int x = 0;
	while (getline(input, fileLine))
	{
		vector <char> buffer;
		x = 0;

		while (x < fileLine.size() && isgraph(fileLine[x]))
		{
			buffer.push_back(fileLine[x]);
			if (buffer[x] == ASTEROID)
				++numberOfAsteroidsInFile;
			++x;
		}
		asteroidsMap.push_back(buffer);
		width = x;

		++y;
	}

	input.close();
	height = y;

	vector <Point> notSee;
	vector <Point> See;
	map <double, vector <Point>> asteroids;

	////////////////
	x = 14; // xBest
	y = 17; // yBest
	////////////////

	vector <double> angles;

	notSee.clear();
	See.clear();
	// Searching for asteroids around asteroidsMap[y][x]
	int BIASx1 = 0, BIASy1 = 0;
	int x1 = 0, y1 = 0;
	bool checkedSomething;

	do
	{
		checkedSomething = false;
		--BIASx1;
		--BIASy1;

		for (int i = 0; i < (BIASx1 * -2) + 1; ++i)
		{
			double cosinus;
			double angle;

			x1 = x + BIASx1 + i;
			y1 = y + BIASy1;
			if (!IsOnasteroidsMap(x1, y1, asteroidsMap))
				continue;

			checkedSomething = true;

			if (asteroidsMap[y1][x1] == ASTEROID)
			{
				int quarter = CheckQuarter(x1, y1, x, y);
				cosinus = ((double)x1 - (double)x) / (sqrt(pow(((double)x1 - (double)x), 2) + pow(((double)y1 - (double)y), 2)));
				cosinus = (double)((int)(cosinus * 1000000)) / 1000000;
				angle = acos(cosinus) * 180 / M_PI;
				switch (quarter)
				{
				case 1:
				case 2:
					break;
				case 3:
				case 4:
					angle = 360.0 - angle;
					break;
				default:
					break;
				}

				angle = CorrectAngle(angle);

				Point asteroid = {
					x1,y1
				};

				if (!VectorContains(angle, angles))
				{
					angles.push_back(angle);
					See.push_back(asteroid);
				}
				else
				{
					notSee.push_back(asteroid);
				}

				asteroids[angle].push_back(asteroid);
			}
		}
		for (int i = 1; i < (BIASx1 * -2) + 1; ++i)
		{
			double cosinus;
			double angle;

			x1 = x + BIASx1;
			y1 = y + BIASy1 + i;
			if (!IsOnasteroidsMap(x1, y1, asteroidsMap))
				continue;

			checkedSomething = true;

			if (asteroidsMap[y1][x1] == ASTEROID)
			{
				int quarter = CheckQuarter(x1, y1, x, y);
				cosinus = ((double)x1 - (double)x) / (sqrt(pow(((double)x1 - (double)x), 2) + pow(((double)y1 - (double)y), 2)));
				cosinus = (double)((int)(cosinus * 1000000)) / 1000000;
				angle = acos(cosinus) * 180 / M_PI;
				switch (quarter)
				{
				case 1:
				case 2:
					break;
				case 3:
				case 4:
					angle = 360.0 - angle;
					break;
				default:
					break;
				}

				angle = CorrectAngle(angle);

				Point asteroid = {
					x1,y1
				};

				if (!VectorContains(angle, angles))
				{
					angles.push_back(angle);
					See.push_back(asteroid);
				}
				else
				{
					notSee.push_back(asteroid);
				}

				asteroids[angle].push_back(asteroid);
			}
		}
		for (int i = 1; i < (BIASx1 * -2) + 1; ++i)
		{
			double cosinus;
			double angle;

			x1 = x - BIASx1;
			y1 = y + BIASy1 + i;
			if (!IsOnasteroidsMap(x1, y1, asteroidsMap))
				continue;

			checkedSomething = true;

			if (asteroidsMap[y1][x1] == ASTEROID)
			{
				int quarter = CheckQuarter(x1, y1, x, y);
				cosinus = ((double)x1 - (double)x) / (sqrt(pow(((double)x1 - (double)x), 2) + pow(((double)y1 - (double)y), 2)));
				cosinus = (double)((int)(cosinus * 1000000)) / 1000000;
				angle = acos(cosinus) * 180 / M_PI;
				switch (quarter)
				{
				case 1:
				case 2:
					break;
				case 3:
				case 4:
					angle = 360.0 - angle;
					break;
				default:
					break;
				}

				angle = CorrectAngle(angle);

				Point asteroid = {
					x1,y1
				};

				if (!VectorContains(angle, angles))
				{
					angles.push_back(angle);
					See.push_back(asteroid);
				}
				else
				{
					notSee.push_back(asteroid);
				}

				asteroids[angle].push_back(asteroid);
			}
		}
		for (int i = 1; i < (BIASx1 * -2); ++i)
		{
			double cosinus;
			double angle;

			x1 = x + BIASx1 + i;
			y1 = y - BIASy1;
			if (!IsOnasteroidsMap(x1, y1, asteroidsMap))
				continue;

			checkedSomething = true;

			if (asteroidsMap[y1][x1] == ASTEROID)
			{
				int quarter = CheckQuarter(x1, y1, x, y);
				cosinus = ((double)x1 - (double)x) / (sqrt(pow(((double)x1 - (double)x), 2) + pow(((double)y1 - (double)y), 2)));
				cosinus = (double)((int)(cosinus * 1000000)) / 1000000;
				angle = acos(cosinus) * 180 / M_PI;
				switch (quarter)
				{
				case 1:
				case 2:
					break;
				case 3:
				case 4:
					angle = 360.0 - angle;
					break;
				default:
					break;
				}

				angle = CorrectAngle(angle);

				Point asteroid = {
					x1,y1
				};

				if (!VectorContains(angle, angles))
				{
					angles.push_back(angle);
					See.push_back(asteroid);
				}
				else
				{
					notSee.push_back(asteroid);
				}

				asteroids[angle].push_back(asteroid);
			}
		}
	} while (checkedSomething);


	/*if (x == 1 && y == 8)
	{
		cout << "goodAsteroids: " << goodAsteroids << endl << "xBest: " << x << " yBest: " << y << endl << endl;

		vector <vector <char>> asteroidsMapTemp;

		for (int i = 0; i < asteroidsMap.size(); ++i)
		{
			vector <char> buffer;
			for (int j = 0; j < asteroidsMap[0].size(); ++j)
			{

				buffer.push_back('.');
			}
			asteroidsMapTemp.push_back(buffer);
		}

		for (int i = 0; i < See.size(); ++i)
		{
			asteroidsMapTemp[See[i].yPoint][See[i].xPoint] = '#';
		}
		for (int i = 0; i < notSee.size(); ++i)
		{
			asteroidsMapTemp[notSee[i].yPoint][notSee[i].xPoint] = '*';
		}

		asteroidsMapTemp[y][x] = '@';


		for (int i = 0; i < asteroidsMap.size(); ++i)
		{
			for (int j = 0; j < asteroidsMap[0].size(); ++j)
			{
				cout << asteroidsMapTemp[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}*/

	// Vaporising asteroids
	int vaporisedAsteroids = 0;
	Point foundAsteroid;
	while (vaporisedAsteroids <= 200)
	{
		for (auto i = asteroids.begin(); i != asteroids.end(); i++)
		{
			if ((*i).second.size() > 0)
			{
				++vaporisedAsteroids;
				if (vaporisedAsteroids == 200)
				{
					foundAsteroid = (*i).second[0];
					break;
				}
				else
				{
					(*i).second.erase((*i).second.begin());
				}
			}
		}
	}

	cout << "Multiplication result: " << foundAsteroid.xPoint * 100 + foundAsteroid.yPoint << endl;
}
