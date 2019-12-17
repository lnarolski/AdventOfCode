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

	std::vector <long long> inputList;
	std::vector <long long> newList;
	std::vector <long long> tempList;

	std::vector <long long> patternSeed;
	std::vector <long long> pattern;

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
			}
		}
	}

	input.close();

	newList = inputList;

	patternSeed.push_back(0);
	patternSeed.push_back(1);
	patternSeed.push_back(0);
	patternSeed.push_back(-1);

	//for (size_t i = 0; i < inputList.size(); i++)
	//{
	//	pattern.push_back(patternSeed[i % 4]);
	//}

	for (long l = 0; l < 100; ++l)
	{
		tempList.clear();
		for (size_t i = 0; i < inputList.size(); i++)
		{
			pattern.clear();
			for (size_t j = 0; j < inputList.size() + 1;)
			{
				for (size_t m = 0; m < patternSeed.size(); m++)
				{
					for (size_t k = 0; (k < (i + 1)) && (j < inputList.size() + 1); ++k)
					{
						pattern.push_back(patternSeed[m]);
						++j;
					}
				}
			}

			long long elementOfList = 0;
			for (size_t i = 0; i < inputList.size(); i++)
			{
				elementOfList += pattern[i + 1] * newList[i];
			}
			tempList.push_back(abs(elementOfList % 10));
		}

		newList = tempList;
	}

	for (size_t k = 0; k < inputList.size(); ++k)
	{
		std::cout << newList[k];
	}
	std::cout << std::endl;
}
