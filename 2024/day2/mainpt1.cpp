#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ifstream file("input.txt");
    string line;
    vector<int> report;

    int totalSafe = 0;

    while (getline(file, line))
    {
        string level = "";
        report = {};
        for (char c : line)
        {
            if (isdigit(c))
            {
                level += c;
            }
            else{
                report.push_back(stoi(level));
                level = "";
            }
        }

        report.push_back(stoi(level));

        // cout << "Report: ";
        // for (int i : report){
        //     cout << i << " ";
        // }
        // cout << endl;

        bool increasing;
        if (report[0] < report[1]){
            increasing = true;
        }
        else if (report[0] > report[1]){
            increasing = false;
        }
        else{
            continue;
        }

        bool safe = true;

        for (int i = 1; i < report.size(); i++)
        {
            int diff = report[i] - report[i-1];

            if (abs(diff) > 3 || abs(diff) == 0){
                safe = false;
                break;
            }
            
            if (increasing && diff < 0){
                safe = false;
                break;
            }
            else if (!increasing && diff > 0){
                safe = false;
                break;
            }
        }

        if (safe){
            totalSafe++;
        }
    }

    cout << totalSafe << endl;
}
