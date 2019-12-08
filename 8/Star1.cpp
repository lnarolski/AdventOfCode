#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    const long width = 25;
    const long height = 6;

    vector <vector <vector <long>>> image;

    fstream input;
    string fileLine;
    input.open("input.txt", fstream::in);

    while (getline(input, fileLine))
    {
        for (int i = 0; i < fileLine.size() / (width * height) ; ++i)
        {
            vector <vector <long>> layer;
            vector <long> buffer;

            layer.clear();
            for (long y = 0; y < height; ++y)
            {
                buffer.clear();
                for (int x = 0; x < width; ++x)
                {
                    string temp;
                    temp.push_back(fileLine[x + y * width + i * width * height]);
                    buffer.push_back(stoi(temp));
                }
                layer.push_back(buffer);
            }
            image.push_back(layer);
        }
    }

    input.close();

    long minimum0Digits = LONG_MAX;
    long minimumLayer = 0;

    for (long layer = 0; layer < image.size(); ++layer)
    {
        long numberOfZeros = 0;

        for (long y = 0; y < height; ++y)
        {
            for (long x = 0; x < width; ++x)
            {
                if (image[layer][y][x] == 0)
                {
                    ++numberOfZeros;
                }
            }
        }

        if (numberOfZeros < minimum0Digits)
        {
            minimum0Digits = numberOfZeros;
            minimumLayer = layer;
        }
    }

    long numberOfOnes = 0;
    long numberOfTwos = 0;

    for (int y = 0; y < image[minimumLayer].size(); ++y)
    {
        for (int x = 0; x < image[minimumLayer][y].size(); ++x)
        {
            cout << image[minimumLayer][y][x] << " ";
            if (image[minimumLayer][y][x] == 1)
                ++numberOfOnes;
            if (image[minimumLayer][y][x] == 2)
                ++numberOfTwos;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Multiplication result: " << numberOfOnes * numberOfTwos  << endl;
}
