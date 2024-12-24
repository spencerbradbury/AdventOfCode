#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>

using namespace std;

regex input("(\\d+)\\s*(\\d+)");

int main()
{
    ifstream file("input.txt");
    string line;
    vector<int> vector1;
    vector<int> vector2;

    int distance = 0;

    while (getline(file, line))
    {
        smatch match;

        regex_search(line, match, input);
        // cout << match[0] << endl;
        // cout << match[1] << endl;
        // cout << match[2] << endl;

        int num1 = stoi(match[1]);
        int num2 = stoi(match[2]);

        vector1.push_back(num1);
        vector2.push_back(num2);
    }

    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    for (int i = 0; i < vector1.size(); i++)
    {
        distance += abs(vector1[i] - vector2[i]);
    }
    cout << distance << endl;
}
