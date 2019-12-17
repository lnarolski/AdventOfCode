#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	std::fstream input;
	std::string fileLine;
	input.open("input.txt", std::fstream::in);

	std::vector <long long> inputList;
	std::vector <long long> newList;
	std::vector <long long> tempList;

	std::vector <long long> patternSeed;
	std::vector <long long> pattern;

	int incBufferTemp = 0;
	std::string bufferTemp = "";
	while (getline(input, fileLine))
	{
		std::vector <long> coordinatesBuffer;

		for (int i = 0; i < fileLine.size() + 1; ++i)
		{
			if (isdigit(fileLine[i]))
			{
				std::string buffer = "";
				buffer.push_back(fileLine[i]);
				inputList.push_back(stoll(buffer));

				if (incBufferTemp < 7)
				{
					bufferTemp.push_back(fileLine[i]);
					++incBufferTemp;
				}
			}
		}
	}

	input.close();

	long long offset = stoll(bufferTemp);

	size_t inputListSize = inputList.size();
	for (long i = 0; i < 10000 - 1; ++i)
	{
		for (size_t j = 0; j < inputListSize; ++j)
		{
			inputList.push_back(inputList[j]);
		}
	}

	newList = inputList;

	patternSeed.push_back(0);
	patternSeed.push_back(1);
	patternSeed.push_back(0);
	patternSeed.push_back(-1);

	for (long l = 0; l < 4; ++l)
	{
		tempList.clear();
		for (size_t i = 0; i < inputList.size(); i++)
		{
			long long elementOfList = 0;

			size_t j = i - 1;
			for (size_t m = 0; m < 2 && j < inputList.size(); ++m)
			{
				for (size_t k = 0; k < i && j < inputList.size(); ++k)
				{
					elementOfList += patternSeed[2 * m + 1] * newList[j];

					++j;
				}
				j += (i + 1) * 2;
			}
			tempList.push_back(abs(elementOfList % 10));
		}

		newList = tempList;
	}

	for (long long k = offset; k < 8; ++k)
	{
		std::cout << newList[k];
	}
	std::cout << std::endl;
}
