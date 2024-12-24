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

        bool good = false;

        for (int i = 0; i < report.size(); i++)
        {
            vector<int> reportl = vector<int>(report.begin(), report.begin() + i);
            vector<int> reportr = vector<int>(report.begin() + i + 1, report.end());
            reportl.insert(reportl.end(), reportr.begin(), reportr.end());

            bool increasing;
            if (reportl[0] < reportl[1]){
                increasing = true;
            }
            else if (reportl[0] > reportl[1]){
                increasing = false;
            }
            else{
                continue;
            }

            bool safe = true;

            for (int i = 1; i < reportl.size(); i++)
            {
                int diff = reportl[i] - reportl[i-1];

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
                good = true;
            }
        }
        if (good){
            totalSafe++;
        }
    }

    cout << totalSafe << endl;
}
