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

    vector <vector <long>> finalImage;

    for (long y = 0; y < height; ++y)
    {
        vector <long> buffer;

        for (long x = 0; x < width; ++x)
        {
            for (long layer = 0; layer < image.size(); ++layer)
            {
                if (image[layer][y][x] == 0)
                {
                    buffer.push_back(0);
                    break;
                }
                if (image[layer][y][x] == 1)
                {
                    buffer.push_back(1);
                    break;
                }
            }
        }

        finalImage.push_back(buffer);
    }

    for (int y = 0; y < finalImage.size(); ++y)
    {
        for (int x = 0; x < finalImage[y].size(); ++x)
        {
            cout << finalImage[y][x];
        }
        cout << endl;
    }
    cout << endl;
}
