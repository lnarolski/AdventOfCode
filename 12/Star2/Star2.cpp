#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main()
{
	std::string buffer;
	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <long>> coordinatesMoons;
	std::vector <std::vector <long>> speedMoons;

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
	}

	int steps = 0;
	while (steps < 4686774924)
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
	}

	std::vector <std::vector <long>> energy;

	for (int i = 0; i < coordinatesMoons.size(); ++i)
	{
		std::vector <long> energyTemp;

		energyTemp.push_back(abs(coordinatesMoons[i][0]) + abs(coordinatesMoons[i][1]) + abs(coordinatesMoons[i][2]));

		energyTemp.push_back(abs(speedMoons[i][0]) + abs(speedMoons[i][1]) + abs(speedMoons[i][2]));

		energyTemp.push_back(energyTemp[0] * energyTemp[1]);

		energy.push_back(energyTemp);
	}

	long energyTotal = 0;
	for (int i = 0; i < coordinatesMoons.size(); ++i)
	{
		energyTotal += energy[i][2];
	}

	std::cout << "Total energy after 1000 steps: " << energyTotal << std::endl;
}
