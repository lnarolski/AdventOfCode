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

using namespace std;

struct Point
{
	int xPoint;
	int yPoint;
};

bool IsOnMap(int x, int y, vector <vector <char>> map)
{
	if (x < 0 || y < 0 || x > map[0].size() - 1 || y > map.size() - 1)
		return false;
	return true;
}

int CheckQuarter(int x1, int y1, int x, int y)
{
	if (x1 >= x&& y1 <= y)
		return 1;
	if (x1 < x && y1 < y)
		return 2;
	if (x1 <= x && y1 >= y)
		return 3;
	if (x1 > x && y1 > y)
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
	while (angle >= 360.0)
		angle -= 360.0;

	return angle;
}

int main(int argc, char* argv[])
{
	long width = -1;
	long height = -1;

	int numberOfAsteroidsInFile = 0;

	vector <vector <char>> map;

	fstream input;
	string fileLine;
	input.open("input.txt", fstream::in);

	int y = 0;
	while (getline(input, fileLine))
	{
		vector <char> buffer;
		int x = 0;

		while (x < fileLine.size() && isgraph(fileLine[x]))
		{
			buffer.push_back(fileLine[x]);
			if (buffer[x] == ASTEROID)
				++numberOfAsteroidsInFile;
			++x;
		}
		map.push_back(buffer);
		width = x;

		++y;
	}

	input.close();
	height = y;

	vector <Point> notSee;
	vector <Point> See;

	int xBest = 0;
	int yBest = 0;
	int numberOfAsteroidsInSight = INT_MIN;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			vector <double> angles;
			if (map[y][x] == ASTEROID)
			{
				notSee.clear();
				See.clear();
				// Searching for asteroids around map[y][x]
				int BIASx1 = 0, BIASy1 = 0;
				int x1 = 0, y1 = 0;
				bool checkedSomething;

				int goodAsteroids = 0;

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
						if (!IsOnMap(x1, y1, map))
							continue;

						checkedSomething = true;

						if (map[y1][x1] == ASTEROID)
						{
							int quarter = CheckQuarter(x1, y1, x, y);
							cosinus = ((double) x1 - (double) x) / (sqrt(pow(((double) x1 - (double) x), 2) + pow(((double) y1 - (double) y), 2)));
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

							if (!VectorContains(angle, angles))
							{
								angles.push_back(angle);
								++goodAsteroids;
								Point asteroid = {
									x1,y1
								};
								See.push_back(asteroid);
							}
							else 
							{
								Point asteroid = {
									x1,y1
								};
								notSee.push_back(asteroid);
							}
						}
					}
					for (int i = 1; i < (BIASx1 * -2) + 1; ++i)
					{
						double cosinus;
						double angle;

						x1 = x + BIASx1;
						y1 = y + BIASy1 + i;
						if (!IsOnMap(x1, y1, map))
							continue;

						checkedSomething = true;

						if (map[y1][x1] == ASTEROID)
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

							if (!VectorContains(angle, angles))
							{
								angles.push_back(angle);
								++goodAsteroids;
								Point asteroid = {
									x1,y1
								};
								See.push_back(asteroid);
							}
							else
							{
								Point asteroid = {
									x1,y1
								};
								notSee.push_back(asteroid);
							}
						}
					}
					for (int i = 1; i < (BIASx1 * -2) + 1; ++i)
					{
						double cosinus;
						double angle;

						x1 = x - BIASx1;
						y1 = y + BIASy1 + i;
						if (!IsOnMap(x1, y1, map))
							continue;

						checkedSomething = true;

						if (map[y1][x1] == ASTEROID)
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

							if (!VectorContains(angle, angles))
							{
								angles.push_back(angle);
								++goodAsteroids;
								Point asteroid = {
									x1,y1
								};
								See.push_back(asteroid);
							}
							else
							{
								Point asteroid = {
									x1,y1
								};
								notSee.push_back(asteroid);
							}
						}
					}
					for (int i = 1; i < (BIASx1 * -2); ++i)
					{
						double cosinus;
						double angle;

						x1 = x + BIASx1 + i;
						y1 = y - BIASy1;
						if (!IsOnMap(x1, y1, map))
							continue;

						checkedSomething = true;

						if (map[y1][x1] == ASTEROID)
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

							if (!VectorContains(angle, angles))
							{
								angles.push_back(angle);
								++goodAsteroids;
								Point asteroid = {
									x1,y1
								};
								See.push_back(asteroid);
							}
							else
							{
								Point asteroid = {
									x1,y1
								};
								notSee.push_back(asteroid);
							}
						}
					}
				} while (checkedSomething);

				
				/*if (x == 1 && y == 8)
				{
					cout << "goodAsteroids: " << goodAsteroids << endl << "xBest: " << x << " yBest: " << y << endl << endl;

					vector <vector <char>> mapTemp;

					for (int i = 0; i < map.size(); ++i)
					{
						vector <char> buffer;
						for (int j = 0; j < map[0].size(); ++j)
						{

							buffer.push_back('.');
						}
						mapTemp.push_back(buffer);
					}

					for (int i = 0; i < See.size(); ++i)
					{
						mapTemp[See[i].yPoint][See[i].xPoint] = '#';
					}
					for (int i = 0; i < notSee.size(); ++i)
					{
						mapTemp[notSee[i].yPoint][notSee[i].xPoint] = '*';
					}

					mapTemp[y][x] = '@';


					for (int i = 0; i < map.size(); ++i)
					{
						for (int j = 0; j < map[0].size(); ++j)
						{
							cout << mapTemp[i][j];
						}
						cout << endl;
					}
					cout << endl;
				}*/

				if (goodAsteroids > numberOfAsteroidsInSight)
				{
					numberOfAsteroidsInSight = goodAsteroids;
					xBest = x;
					yBest = y;
				}
			}
		}
	}

	cout << "numberOfAsteroidsInSight: " << numberOfAsteroidsInSight << endl << "xBest: " << xBest << " yBest: " << yBest;

}
