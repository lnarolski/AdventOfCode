#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

int main()
{
	std::string buffer;
	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <long>> coordinatesMoons;
	std::vector <std::vector <long>> initialCoordinatesMoons;
	std::vector <std::vector <long>> speedMoons;
	std::vector <unsigned long long> numberOfSteps;

	while (getline(input, fileLine))
	{
		std::vector <long> coordinatesBuffer;

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
				if (buffer != "")
				{
					coordinatesBuffer.push_back(stoll(buffer));
					buffer = "";
				}
			}
		}

		coordinatesMoons.push_back(coordinatesBuffer);
	}

	input.close();

	for (int i = 0; i < coordinatesMoons.size(); ++i)
	{
		std::vector <long> speeds;

		speeds.push_back(0);
		speeds.push_back(0);
		speeds.push_back(0);

		speedMoons.push_back(speeds);

		std::vector <long> initialCoordinates;

		initialCoordinates.push_back(coordinatesMoons[i][0]);
		initialCoordinates.push_back(coordinatesMoons[i][1]);
		initialCoordinates.push_back(coordinatesMoons[i][2]);

		initialCoordinatesMoons.push_back(initialCoordinates);
	}

	for (int i = 0; i < 3; ++i)
	{
		numberOfSteps.push_back(0);
	}

	unsigned long long steps = 0;
	bool stop = false;

	while (!stop)
	{
		for (int i = 0; i < coordinatesMoons.size(); ++i)
		{
			for (int j = 1 + i; j < coordinatesMoons.size(); ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (coordinatesMoons[i][k] > coordinatesMoons[j][k])
					{
						--speedMoons[i][k];
						++speedMoons[j][k];
					}
					else if (coordinatesMoons[i][k] < coordinatesMoons[j][k])
					{
						++speedMoons[i][k];
						--speedMoons[j][k];
					}
				}
			}
		}

		for (int i = 0; i < coordinatesMoons.size(); ++i)
		{
			coordinatesMoons[i][0] += speedMoons[i][0];
			coordinatesMoons[i][1] += speedMoons[i][1];
			coordinatesMoons[i][2] += speedMoons[i][2];
		}

		++steps;

		for (size_t i = 0; i < 3; ++i)
		{
			if (initialCoordinatesMoons[0][i] == coordinatesMoons[0][i] && initialCoordinatesMoons[1][i] == coordinatesMoons[1][i] && initialCoordinatesMoons[2][i] == coordinatesMoons[2][i] && initialCoordinatesMoons[3][i] == coordinatesMoons[3][i] && numberOfSteps[i] == 0)
			{
				numberOfSteps[i] = steps + 1;
			}
		}

		stop = true;
		for (size_t i = 0; i < numberOfSteps.size(); ++i)
		{
			if (numberOfSteps[i] == 0)
			{
				stop = false;
				break;
			}
		}
	}

	unsigned long long stepsPreviousState = std::lcm(numberOfSteps[0], std::lcm(numberOfSteps[1], numberOfSteps[2]));

	std::cout << "Number of steps: " << stepsPreviousState << std::endl;
}
