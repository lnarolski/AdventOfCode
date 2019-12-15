#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

bool IsInMap(std::string chemical, std::map <std::string, int>* chemicalIndexes)
{
	for (auto i = chemicalIndexes->begin(); i != chemicalIndexes->end(); ++i)
	{
		if ((*i).first == chemical)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::map <std::string, int> chemicalIndexes;
	std::vector <std::vector <long>> equations;

	int fuelIndex = 0;
	int oreIndex = 0;

	std::string buffer;
	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <std::vector <long>> coordinatesMoons;
	std::vector <std::vector <long>> initialCoordinatesMoons;
	std::vector <std::vector <long>> speedMoons;
	std::vector <unsigned long long> numberOfSteps;

	int tempIndex = 0;
	while (getline(input, fileLine))
	{
		for (int i = 0; i < fileLine.size() + 1; ++i)
		{

			if (isalpha(fileLine[i]))
			{
				buffer.push_back(fileLine[i]);
			}
			else
			{
				if (buffer != "" && buffer != "FUEL" && buffer != "ORE")
				{
					if (!IsInMap(buffer, &chemicalIndexes)) 
					{
						chemicalIndexes[buffer] == tempIndex;
					}

					buffer = "";
					++tempIndex;
				}
			}
		}
	}


	input.close();

	input.open("input.txt", std::fstream::in);

	while (getline(input, fileLine))
	{
		std::vector <long> equation;
		for (int i = 0; i < chemicalIndexes.size() * 2; ++i)
		{
			equation.push_back(0);
		}

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
}