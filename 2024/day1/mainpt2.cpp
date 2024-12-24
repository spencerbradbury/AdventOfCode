#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

regex input("(\\d+)\\s*(\\d+)");

int main()
{
    ifstream file("input.txt");
    string line;
    vector<int> list1;
    // map<int,int> list1;
    map<int,int> list2;

    int similarity = 0;

    while (getline(file, line))
    {
        smatch match;

        regex_search(line, match, input);

        int num1 = stoi(match[1]);
        int num2 = stoi(match[2]);

        list1.push_back(num1);

        // list1.at(num1)++;;
        list2[num2]++;
    }

    for (int i = 0; i < list1.size(); i++)
    {
        similarity += list1.at(i) * list2[list1.at(i)];
    }

    cout << similarity << endl;
}
